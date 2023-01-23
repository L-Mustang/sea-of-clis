#ifndef SOC_SHIP_H
#define SOC_SHIP_H

namespace Soc {
	class Goods;
	class Cannons;
	enum class Cannons_type : int;
	enum class Ship_type : int;

	class Ship
	{
	public:
		/**
		 * @brief Constructor
		 * @param id Ship ID
		 * @param type Ship type
		 * @param price Price
		 * @param cargo Maximum cargo capacity
		 * @param cannons Maximum cannon slots
		 * @param hp HP
		 * @param weight_class Weight class (determines sailing behaviour)
		 */
		Ship(int id, std::string type, int price, int cargo,
			int cannons, int hp, Ship_type weight_class);
		virtual ~Ship();
		Ship(const Ship& other) = delete;
		Ship(Ship&& other) noexcept;
		Ship& operator=(const Ship& other) = delete;
		Ship& operator=(Ship&& other) noexcept;

		/**
		 * @brief Returns the type of ship
		 * @return Type of ship
		 */
		[[nodiscard]] virtual std::string type() const;
		/**
		 * @brief Returns the size of the ship
		 * @return Size of ship
		 */
		[[nodiscard]] virtual std::string size() const;
		/**
		 * @brief Returns the current amount of cargo
		 * @return Current amount of cargo
		 */
		[[nodiscard]] virtual int cargo_amount() const;
		/**
		 * @brief Returns the maximum amount of cargo
		 * @return Maximum amount of cargo
		 */
		[[nodiscard]] virtual int cargo_max() const;
		/**
		 * @brief Returns the current amount of free cargo space
		 * @return Amount of free cargo space
		 */
		[[nodiscard]] virtual int cargo_space() const;
		/**
		 * @brief Returns the current amount of cannons
		 * @return Current amount of cannons
		 */
		[[nodiscard]] virtual int cannons_amount() const;
		/**
		 * @brief Returns the maximum amount of cannons
		 * @return Maximum amount of cannons
		 */
		[[nodiscard]] virtual int cannons_max() const;
		/**
		 * @brief Returns the current amount of free cannon slots
		 * @return Amount of free cannon slots
		 */
		[[nodiscard]] virtual int cannons_space() const;
		/**
		 * @brief Returns a const map representing the on-board cannons
		 * @return Const map representing the on-board cannons
		 */
		[[nodiscard]] virtual std::map<Cannons_type, std::shared_ptr<Cannons>> cannons() const;
		/**
		 * @brief Returns a map representing the on-board cannons
		 * @return Map representing the on-board cannons
		 */
		[[nodiscard]] virtual std::map<Cannons_type, std::shared_ptr<Cannons>> cannons();
		/**
		 * @brief Returns a const map representing the on-board cargo
		 * @return Const map representing the on-board cargo
		 */
		[[nodiscard]] virtual const std::map<int, std::shared_ptr<Goods>>& cargo() const;
		/**
		 * @brief Returns a map representing the on-board cargo
		 * @return Map representing the on-board cargo
		 */
		[[nodiscard]] virtual std::map<int, std::shared_ptr<Goods>>& cargo();
		/**
		 * @brief Adds cargo to the ship
		 * @param key Key of cargo
		 * @param amount Amount
		 * @param good Shared pointer to the good
		 * @return True if successful, false otherwise
		 */
		virtual bool cargo_add(int key, int amount, std::shared_ptr<Goods> good);
		/**
		 * @brief Removes cargo from the ship
		 * @param key Key of cargo
		 * @param amount Amount
		 * @return True if successful, false otherwise
		 */
		virtual bool cargo_remove(int key, int amount);
		/**
		 * @brief Adds cannons to the ship
		 * @param key Key of cannons
		 * @param amount Amount
		 * @param cannon Shared pointer to the cannon
		 * @return True if successful, false otherwise
		 */
		virtual bool cannons_add(Cannons_type key, int amount, std::shared_ptr<Cannons> cannon);
		/**
		 * @brief Removes cannons from the ship
		 * @param key Key of cannon
		 * @param amount Amount
		 * @return True if successful, false otherwise
		 */
		virtual bool cannons_remove(Cannons_type key, int amount);
		/**
		 * @brief Returns the types of cannons compatible with this ship
		 * @return Types of cannons compatible with this ship
		 */
		[[nodiscard]] virtual std::set<Cannons_type> cannons_types() const;
		/**
		 * @brief Updates the prices of the on-board cargo
		 * @param from Map of goods with up-to-date prices
		 */
		virtual void cargo_update_prices(const std::map<int, std::shared_ptr<Goods>>& from);
		/**
		 * @brief Returns the price of the ship
		 * @return Price of the ship
		 */
		[[nodiscard]] virtual int price() const;
		/**
		 * @brief Sets the price of the ship
		 * @price Price of the ship
		 */
		virtual void price(int price);
		/**
		 * @brief Returns the current HP of the ship
		 * @return Current HP of the ship
		 */
		[[nodiscard]] virtual int hp() const;
		/**
		 * @brief Returns the max HP of the ship
		 * @return Max HP of the ship
		 */
		[[nodiscard]] virtual int hp_max() const;
		/**
		 * @brief Returns the current damage the ship has suffered
		 * @return Current damage the ship has suffered
		 */
		[[nodiscard]] virtual int hp_dmg() const;
		/**
		 * @brief Adds damage to the ship
		 * @param dmg Damage to be added
		 */
		virtual void  hp_dmg_add(int dmg);
		/**
		 * @brief Returns the weight class of the ship
		 * @return Weight class
		 */
		[[nodiscard]] virtual Ship_type weight_class() const;
		/**
		 * @brief Returns the damage of a full broadside
		 * @return Damage of a full broadside
		 */
		[[nodiscard]] virtual int broadside() const;

	protected:
		int m_id;
		std::string m_type;
		int m_price;
		int m_cargo_max;
		int m_cannons_max;
		int m_hp;
		int m_hp_max;
		Ship_type m_weight_class;
		std::map<Cannons_type, std::shared_ptr<Cannons>> m_cannons;
		std::map<int, std::shared_ptr<Goods>> m_cargo;
	private:
		friend std::ostream& operator<<(std::ostream& os, const Ship& obj);
	};
}

#endif // SOC_SHIP_H
