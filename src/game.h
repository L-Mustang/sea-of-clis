#ifndef SOC_GAME_H
#define SOC_GAME_H

namespace Soc::Filesystem
{
	class Filesystem;
}

namespace Soc
{
	class Logger;
	class Goods;
	class Cannons;
	enum class Cannons_type : int;
	class Harbor;
	class Ship;

	class Game
	{
	public:
		explicit Game(std::unique_ptr<const Filesystem::Filesystem> filesystem);
		~Game();
		Game(const Game& other) = delete;
		Game(Game&& other) noexcept = delete;
		Game& operator=(const Game& other) = delete;
		Game& operator=(Game&& other) noexcept = delete;

		void victory();
		void game_over() const;
		void loop();
		void harbor_seed();
		void harbor();
		void harbor_buy_sell_goods();
		void harbor_buy_goods();
		void harbor_sell_goods();
		void harbor_buy_sell_cannons();
		void harbor_buy_cannons();
		void harbor_sell_cannons();
		void harbor_buy_ships();
		void harbor_repair();
		void harbor_set_sail();
		void sea();
		std::shared_ptr<Ship> sea_pirate_ship();
		void sea_battle();
		[[nodiscard]] int sea_escape(const std::shared_ptr<const Ship>& pirate_ship) const;
		void sea_move();
		[[nodiscard]] std::string state() const;

	private:
		std::unique_ptr<const Filesystem::Filesystem> m_filesystem;
		int m_money = 0;
		std::shared_ptr<Ship> m_player_ship;
		std::map<int, std::shared_ptr<Harbor>> m_harbors;
		std::shared_ptr<Harbor> m_player_harbor;
		std::map<Cannons_type, std::shared_ptr<Cannons>> m_harbor_cannons;
		std::map<int, std::shared_ptr<Goods>> m_harbor_goods;
		std::map<int, std::shared_ptr<Ship>> m_harbor_ships;
		std::unique_ptr<Logger> m_console;
		std::function<void()> m_status_bar;
		bool m_exit = false;
		bool m_at_harbor = false;
		bool m_at_sea = false;
		bool m_is_fighting = false;
		bool m_has_died = false;
		bool m_has_won = false;

		friend std::ostream& operator<<(std::ostream& os, const Game& obj);
	};
}

#endif //SOC_GAME_H
