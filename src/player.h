#ifndef SOC_PLAYER_H
#define SOC_PLAYER_H

#include <filesystem/filesystem.h>
#include <random/random.h>
#include <ship.h>
#include <goods.h>
#include <logger.h>
#include <harbor.h>
#include <cannons_heavy.h>
#include <cannons_medium.h>
#include <cannons_light.h>
#include <cannons.h>
#include <cannons_type.h>
#include <ostream>
#include <utils/map.h>


namespace Soc
{
	class Player
	{
	public:
		explicit Player(std::unique_ptr<Filesystem::Filesystem> filesystem)
			: m_filesystem(std::move(filesystem)),
			m_money(0),
			m_console(std::make_unique<Logger>(std::filesystem::path{ "logs/" })),
			m_exit(false)
		{
			m_bar = [&]() {	m_console->write(*this); };
			m_money = Random::random(100000, 250000);
			m_harbors = m_filesystem->harbors();
			m_harbor_ships = m_filesystem->ships();
			m_player_harbor = Utils::Map::random_view(m_harbors);
			m_player_ship = Utils::Map::random(m_harbor_ships);
			m_player_ship->price(m_player_ship->price() / 2); // Player's ship should be at 50% of the new price
			loop();
		}

		void loop()
		{
			while (true)
			{
				if (m_money > 1000000)
				{
					// TODO winning
					break;
				}
				if (m_exit) break;
				harbor();
				sea();
			}
		}

		void harbor_seed()
		{
			const std::shared_ptr<Harbor> harbor = m_player_harbor.lock();
			m_harbor_goods = m_filesystem->goods(harbor->id());
			m_harbor_cannons = {
				{Cannons_type::light, std::make_shared<Cannons_light>(0, 5, 50)},
				{Cannons_type::medium, std::make_shared<Cannons_medium>(0, 3, 200)},
				{Cannons_type::heavy, std::make_shared<Cannons_heavy>(0, 2, 1000)}
			};
			m_harbor_ships = m_filesystem->ships();
			m_player_ship->cargo_update_prices(m_harbor_goods); // Must update cargo prices before removing goods where amount = 0
			Utils::Map::random_remove(m_harbor_ships); // Remove, at random, ships
			Utils::Map::remove_if_none(m_harbor_cannons); // Remove elements where amount rolled 0;
			Utils::Map::remove_if_none(m_harbor_goods);
		}

		void harbor()
		{
			bool at_harbor = true;
			harbor_seed();
			const std::shared_ptr<Harbor> harbor = m_player_harbor.lock();

			while (at_harbor)
			{
				m_console->clear(m_bar);
				m_console->write(std::format("Welcome to the port of {}!", harbor->harbor()));
				m_console->write(
					"What would you like to do?\n"
					"[1]  Buy/sell goods\n"
					"[2]  Buy/sell cannons\n"
					"[3]  Buy/sell ships\n"
					"[4]  Repair ship\n"
					"[5]  Set sail\n"
					"[0]  Quit game"
				);
				switch (m_console->read(5))
				{
				case 1:
					{
						harbor_buy_sell_goods();
						break;
					}
				case 2:
					{
						harbor_buy_sell_cannons();
						break;
					}
				case 3:
					{
						harbor_buy_ships();
						break;
					}
				case 4:
					{
						harbor_repair();
						break;
					}
				default:
					{
						at_harbor = false;
						m_exit = true;
						break;
					}
				}
			}
		}

		void harbor_buy_sell_goods()
		{
			m_console->clear(m_bar);
			m_console->write(
				"Would you like to buy or sell goods?\n"
				"[1] Buy goods\n"
				"[2] Sell goods\n"
				"[0] Return to harbor"
			);
			switch (m_console->read(2))
			{
			case 1:
			{
				harbor_buy_goods();
				break;
			}
			case 2:
			{
				harbor_sell_goods();
				break;
			}
			default:
			{
				break;
			}
			}
		}

		void harbor_buy_goods()
		{
			m_console->clear(m_bar); // Setup
			m_console->write("GOODS TRADER\n");
			m_console->write(m_harbor_goods);
			m_console->write("\nPlease enter the number of the good you'd wish to buy, or [0] to return:");
			const int key = m_console->read(m_harbor_goods); // Get type
			if (key == 0) return;

			const std::shared_ptr<Goods> good = m_harbor_goods.at(key);
			const int threshold = std::min({ m_money / good->price(), good->amount(), m_player_ship->cargo_space() }); // Calculate threshold
			m_console->write(std::format(
				"Please enter the amount of {} you'd wish to buy (max {}) for ${} p/tonne, or [0] to cancel:",
				good->goods(), threshold, Logger::format(good->price())
			));
			const int amount = m_console->read(threshold); // Get amount
			if (amount == 0) return;

			m_player_ship->cargo_add(key, amount, good); // Transaction
			Utils::Map::decrement_remove_if_none(key, amount, m_harbor_goods);
			m_money -= good->price() * amount;
		}

		void harbor_sell_goods()
		{
			m_console->clear(m_bar);  // Setup
			m_console->write("GOODS TRADER\n");
			m_console->write(m_player_ship->cargo());
			m_console->write("\nPlease enter the number of the good you'd wish to sell, or [0] to return:");
			const int key = m_console->read(m_player_ship->cargo());  // Get type
			if (key == 0) return;

			const std::shared_ptr<Goods> good = m_player_ship->cargo().at(key);
			m_console->write(std::format(
				"Please enter the amount of {} you'd wish to sell (max {}) for ${} p/tonne, or [0] to cancel:",
				good->goods(), good->amount(), Logger::format(good->price())
			));
			const int amount = m_console->read(good->amount()); // Get amount
			if (amount == 0) return;

			m_player_ship->cargo_remove(key, amount); // Transaction
			Utils::Map::increment_add_if_not_found(key, amount, *good, m_harbor_goods);
			m_money += good->price() * amount;
		}

		void harbor_buy_sell_cannons()
		{
			m_console->clear(m_bar);
			m_console->write(
				"Would you like to buy or sell cannons?\n"
				"[1] Buy cannons\n"
				"[2] Sell cannons\n"
				"[0] Return to harbor"
			);
			switch (m_console->read(2))
			{
			case 1:
			{
				harbor_buy_cannons();
				break;
			}
			case 2:
			{
				harbor_sell_cannons();
				break;
			}
			default:
			{
				break;
			}
			}
		}

		void harbor_buy_cannons()
		{
			const auto cannons_filtered = Utils::Map::filter_view(m_player_ship->cannons_types(), m_harbor_cannons); // Must get compatible cannons
			m_console->clear(m_bar); // Setup
			m_console->write("IRONWORKS\n");
			m_console->write(cannons_filtered);
			m_console->write("\nPlease enter the number of the cannons you'd wish to buy, or [0] to return:");
			const Cannons_type key = m_console->read(cannons_filtered); // Get type
			if (key == Cannons_type::invalid) return;

			const std::shared_ptr<Cannons> cannon = m_harbor_cannons.at(key);
			const int threshold = std::min({ m_money / cannon->price(), cannon->amount(), m_player_ship->cannons_space() }); // Calculate threshold
			m_console->write(std::format(
				"Please enter the amount of {} you'd wish to buy (max {}) for ${} p/piece, or [0] to cancel:",
				cannon->cannons(), threshold, Logger::format(cannon->price())
			));
			const int amount = m_console->read(threshold); // Get amount
			if (amount == 0) return;

			auto cannon_cpy = *cannon;
			cannon_cpy.price(cannon_cpy.price() / 2); // Price of cannon should become 50%
			m_player_ship->cannons_add(key, amount, cannon_cpy); // Transaction
			Utils::Map::decrement_remove_if_none(key, amount, m_harbor_cannons);
			m_money -= cannon->price() * amount;
		}

		void harbor_sell_cannons()
		{
			m_console->clear(m_bar);  // Setup
			m_console->write("IRONWORKS\n");
			m_console->write(m_player_ship->cannons());
			m_console->write("\nPlease enter the number of the cannons you'd wish to sell, or [0] to return:");
			const Cannons_type key = m_console->read(m_player_ship->cannons());  // Get type
			if (key == Cannons_type::invalid) return;

			const std::shared_ptr<Cannons> cannon = m_player_ship->cannons().at(key);
			m_console->write(std::format(
				"Please enter the amount of {} you'd wish to sell (max {}) for ${} p/piece, or [0] to cancel:",
				cannon->cannons(), cannon->amount(), Logger::format(cannon->price())));
			const int amount = m_console->read(cannon->amount()); // Get amount
			if (key == Cannons_type::invalid) return;

			m_player_ship->cannons_remove(key, amount); // Transaction
			auto cannon_cpy = *cannon;
			cannon_cpy.price(cannon_cpy.price() * 2); // Price of cannon should become 200%
			Utils::Map::increment_add_if_not_found(key, amount, cannon_cpy, m_harbor_cannons);
			m_money += cannon->price() * amount;
		}

		void harbor_buy_ships()
		{
			m_console->clear(m_bar);  // Setup
			m_console->write("SHIPYARD\n");
			m_console->write(m_harbor_ships);
			m_console->write("\nPlease enter the number of the ship you'd wish to buy, or [0] to return:");
			int key{};
			while (true) {
				key = m_console->read(m_harbor_ships);  // Get type
				if (key == 0) return;
				if(m_money + m_player_ship->price() >= m_harbor_ships.at(key)->price()) break;
				m_console->write(std::format("The {} is too expensive, please pick another ship:", m_harbor_ships.at(key)->type()));
			}
			const std::shared_ptr<Ship> ship_new = m_harbor_ships.at(key);
			const std::shared_ptr<Ship> ship_old = m_player_ship;
			if (ship_old->cargo_amount() != 0 || ship_old->cannons_amount() != 0) // TODO Errmsg could be improved
			{
				m_console->write(std::format(
					"Warning! There are still {} tonnes of cargo and {} cannons on board of your ship.\n"
					"These will also be transferred to the shipyard along with your ship.",
					ship_old->cargo_amount(), ship_old->cannons_amount()
				));
			}
			m_console->write(std::format(
				"Are you sure you want to sell your ship for ${}. and buy a {} for ${}?"
				"\n[0] No"
				"\n[1] Yes",
				ship_old->price(),
				ship_new->type(),
				ship_new->price()
			));
			switch (m_console->read(1))
			{
			case 1:
				{
					m_money -= ship_new->price();
					m_money += ship_old->price();
					m_player_ship = ship_new; // Assign to player and remove new ship for yard
					m_harbor_ships.erase(key);
					m_player_ship->price(m_player_ship->price() / 2);
					ship_old->price(ship_old->price() * 2); // Assign old ship to yard, fix price
					m_harbor_ships.insert({99, ship_old});
					break;
				}
			default:
				{
					break;
				}
			}
		}

		void harbor_repair()
		{
			m_player_ship->hp_dmg_add(10);
			m_console->clear(m_bar);  // Setup
			m_console->write("SHIPYARD\n");
			if(m_player_ship->hp_dmg() == 0) // Check if ship is repaired
			{
				m_console->write(
					"Your vessel is pristine condition. There is no need for repairs.\n"
					"Press enter to return:"
				);
				m_console->pause();
				return;
			}
			const int threshold = std::min({ m_money / 10, m_player_ship->hp_dmg()});
			m_console->write(std::format(
				"\nPlease enter the amount of HP you'd wish to repair (max {}) for $10 per HP, or [0] to cancel:",
				threshold
			));
			const int repairs = m_console->read(threshold);
			m_money -= 10 * repairs;
			m_player_ship->hp_dmg_add(-repairs);
		}

		void sea()
		{

		}

	private:
		std::unique_ptr<Filesystem::Filesystem> m_filesystem;
		int m_money;
		std::shared_ptr<Ship> m_player_ship;
		std::map<int, std::shared_ptr<Harbor>> m_harbors;
		std::weak_ptr<Harbor> m_player_harbor;
		std::map<Cannons_type, std::shared_ptr<Cannons>> m_harbor_cannons;
		std::map<int, std::shared_ptr<Goods>> m_harbor_goods;
		std::map<int, std::shared_ptr<Ship>> m_harbor_ships;
		std::unique_ptr<Logger> m_console;
		std::function<void()> m_bar;
		bool m_exit;

		friend std::ostream& operator<<(std::ostream& os, const Player& obj)
		{
			return os << std::format(
				"${}   {}   {}   Cargo: {}/{}   Cannons: {}/{}   HP:  {}/{}",
				Logger::format(obj.m_money),
				obj.m_player_harbor.lock()->harbor(),
				obj.m_player_ship->type(),
				obj.m_player_ship->cargo_amount(),
				obj.m_player_ship->cargo_max(),
				obj.m_player_ship->cannons_amount(),
				obj.m_player_ship->cannons_max(),
				obj.m_player_ship->hp(),
				obj.m_player_ship->hp_max()
			);
		}
	};
}

#endif //SOC_PLAYER_H
