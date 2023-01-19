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
			m_money = Random::random(100000, 250000);
			m_harbors = m_filesystem->harbors();
			m_harbor_player = m_harbors[Random::random(0, static_cast<int>(m_harbors.size() - 1))];
			loop();
		}

		void loop()
		{
			while (m_money < 1000000)
			{
				at_harbor();
				at_sea();
			}
		}

		void seed_harbor()
		{
			const std::shared_ptr<Harbor> harbor = m_harbor_player.lock();
			m_harbor_goods = m_filesystem->goods(harbor->id());
			m_harbor_cannons = {
				{Cannons_type::light, std::make_shared<Cannons_light>(0, 5, 50)},
				{Cannons_type::medium, std::make_shared<Cannons_medium>(0, 3, 200)},
				{Cannons_type::heavy, std::make_shared<Cannons_heavy>(0, 2, 1000)}
			};
		}

		void at_harbor()
		{
			bool at_harbor = true;
			seed_harbor();
			const std::shared_ptr<Harbor> harbor = m_harbor_player.lock();

			while (at_harbor)
			{
				m_console->write("Welcome in", harbor->harbor());
				m_console->write(
					"What would you like to do?\n"
					"[1]  Buy/sell goods\n"
					"[2]  Buy/sell cannons\n"
					"[3]  Buy/sell ships\n"
					"[4]  Repair ship\n"
					"[5]  Set sail\n"
					"[6]  Quit game"
				);
				switch (m_console->read(6))
				{
				case 1:
					{
						m_console->write("Chose option 1");

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

		void at_sea()
		{

		}

		[[nodiscard]] int money() const;
	private:
		std::unique_ptr<Filesystem::Filesystem> m_filesystem;
		int m_money;
		std::shared_ptr<Ship> m_ship;
		std::map<int, std::shared_ptr<Harbor>> m_harbors;
		std::weak_ptr<Harbor> m_harbor_player;
		std::map<Cannons_type, std::shared_ptr<Cannons>> m_harbor_cannons;
		std::map<int, Goods> m_harbor_goods;
		std::unique_ptr<Logger> m_console;
	};
}

#endif //SOC_PLAYER_H
