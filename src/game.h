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
		/**
		 * @brief Constructor
		 * @param filesystem Unique pointer to a Filesystem to be used for file I/O
		 */
		explicit Game(std::unique_ptr<const Filesystem::Filesystem> filesystem);
		~Game();
		Game(const Game& other) = delete;
		Game(Game&& other) noexcept = delete;
		Game& operator=(const Game& other) = delete;
		Game& operator=(Game&& other) noexcept = delete;

		/**
		 * @brief Victory screen
		 */
		void victory();
		/**
		 * @brief Game over screen
		 */
		void game_over() const;
		/**
		 * @brief Main game loop
		 */
		void loop();
		/**
		 * @brief Seeds the harbor with data from the Filesystem
		 */
		void harbor_seed();
		/**
		 * @brief Harbor logic
		 */
		void harbor();
		/**
		 * @brief Goods trader buy/sell prompt
		 */
		void harbor_buy_sell_goods();
		/**
		 * @brief Goods trader buy screen
		 */
		void harbor_buy_goods();
		/**
		 * @brief Goods trader sell screen
		 */
		void harbor_sell_goods();
		/**
		 * @brief Ironworks buy/sell prompt
		 */
		void harbor_buy_sell_cannons();
		/**
		 * @brief Ironworks buy screen
		 */
		void harbor_buy_cannons();
		/**
		 * @brief Ironworks sell screen
		 */
		void harbor_sell_cannons();
		/**
		 * @brief Shipyard buy/sell screen
		 */
		void harbor_buy_ships();
		/**
		 * @brief Shipyard repairs screen
		 */
		void harbor_repair();
		/**
		 * @brief Set sail screen
		 */
		void harbor_set_sail();
		/**
		 * @brief Sea logic
		 */
		void sea();
		/**
		 * @brief Get a random pirate ship with random cannons
		 * @return A shared pointer to a Ship
		 */
		std::shared_ptr<Ship> sea_pirate_ship();
		/**
		 * @brief Sea battle logic
		 */
		void sea_battle();
		/**
		 * @brief Calculates the chance that a player will escape from a Ship
		 * @param pirate_ship Ship to be escaped from
		 * @return Escape chance
		 */
		[[nodiscard]] int sea_escape(const std::shared_ptr<const Ship>& pirate_ship) const;
		/**
		 * @brief Sea sailing logic
		 */
		void sea_move();
		/**
		 * @brief Returns current the state of the player
		 * @return String representing the player's current state
		 */
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
