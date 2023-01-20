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
			m_console(std::make_unique<Logger>(std::filesystem::path{ "logs/" }))
		{
			m_bar = [&]()
			{
				m_console->write(*this);

			};
			m_money = Random::random(100000, 250000);
			m_harbors = m_filesystem->harbors();
			m_harbor_ships = m_filesystem->ships();
			m_player_harbor = Utils::Map::random(m_harbors);
			m_player_ship = Utils::Map::random(m_harbor_ships);
			loop();
		}

		void loop()
		{
			while (m_money < 1000000)
			{
				harbor();
				sea();
			}
		}

		void harbor_seed_shops()
		{
			const std::shared_ptr<Harbor> harbor = m_player_harbor.lock();
			m_harbor_goods = m_filesystem->goods(harbor->id());
			m_harbor_cannons = {
				{Cannons_type::light, std::make_shared<Cannons_light>(0, 5, 50)},
				{Cannons_type::medium, std::make_shared<Cannons_medium>(0, 3, 200)},
				{Cannons_type::heavy, std::make_shared<Cannons_heavy>(0, 2, 1000)}
			};
			m_harbor_ships = m_filesystem->ships();
			// TODO remove random ships
			// Remove elements where amount rolled 0;
			Utils::Map::remove_if_none(m_harbor_cannons);
			Utils::Map::remove_if_none(m_harbor_goods);
		}

		void harbor()
		{
			bool at_harbor = true;
			harbor_seed_shops();
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
				default:
				{
					m_console->write("Chose option smth");
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
			m_console->write("GOODS TRADER");
			m_console->write(m_harbor_goods);
			m_console->write("Please enter the number of the good you'd wish to buy, or [0] to return:");
			const int key = m_console->read(m_harbor_goods); // Get type
			if(key == 0) return;

			const std::shared_ptr<Goods> good = m_harbor_goods.at(key); 
			const int threshold = std::min({m_money/good->price(), good->amount(), m_player_ship->cannons_space()}); // Calculate threshold
			m_console->write(std::format("Please enter the amount of {} you'd wish to buy (max {}), or [0] to cancel:", good->goods(), threshold));
			const int amount = m_console->read(threshold); // Get amount
			if(amount == 0) return;

			m_player_ship->cargo_add(key, amount, good); // Transaction
			Utils::Map::decrement_remove_if_none(key, amount, m_harbor_goods);
			m_money -= good->price()*amount;
		}

		void harbor_sell_goods()
		{
			m_console->clear(m_bar);  // Setup
			m_console->write("GOODS TRADER");
			m_console->write(m_player_ship->cargo());
			m_console->write("Please enter the number of the good you'd wish to sell, or [0] to return:");
			const int key = m_console->read(m_player_ship->cargo());  // Get type
			if(key == 0) return;

			const std::shared_ptr<Goods> good = m_player_ship->cargo().at(key);
			m_console->write(std::format("Please enter the amount of {} you'd wish to sell (max {}), or [0] to cancel:", good->goods(), good->amount()));
			const int amount = m_console->read(good->amount());  // Get amount
			if(amount == 0) return;

			m_player_ship->cargo_remove(key, amount); // Transaction
			Utils::Map::increment_add_if_not_found(key, amount, *good, m_harbor_goods);
			m_money += good->price()/2*amount;
		}

		void sea()
		{

		}

		[[nodiscard]] int money() const;
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

		friend std::ostream& operator<<(std::ostream& os, const Player& obj)
		{
			return os << std::format(
				"${}   {}   {}   Cargo: {}/{}   Cannons: {}/{}",
				Logger::format(obj.m_money),
				obj.m_player_harbor.lock()->harbor(),
				obj.m_player_ship->type(),
				obj.m_player_ship->cargo_amount(),
				obj.m_player_ship->cargo_max(),
				obj.m_player_ship->cannons_amount(),
				obj.m_player_ship->cannons_max()
			);
		}
	};
}

#endif //SOC_PLAYER_H
