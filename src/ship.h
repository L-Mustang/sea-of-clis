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
		Ship(int id, std::string type, int price, int cargo,
			int cannons, int hp, Ship_type weight_class);
		virtual ~Ship();
		Ship(const Ship& other) = delete;
		Ship(Ship&& other) noexcept;
		Ship& operator=(const Ship& other) = delete;
		Ship& operator=(Ship&& other) noexcept;

		[[nodiscard]] virtual std::string type() const;
		[[nodiscard]] virtual std::string size() const;
		[[nodiscard]] virtual int cargo_amount() const;
		[[nodiscard]] virtual int cargo_max() const;
		[[nodiscard]] virtual int cargo_space() const;
		[[nodiscard]] virtual int cannons_amount() const;
		[[nodiscard]] virtual int cannons_max() const;
		[[nodiscard]] virtual int cannons_space() const;
		[[nodiscard]] virtual std::map<Cannons_type, std::shared_ptr<Cannons>> cannons() const;
		[[nodiscard]] virtual std::map<Cannons_type, std::shared_ptr<Cannons>> cannons();
		[[nodiscard]] virtual const std::map<int, std::shared_ptr<Goods>>& cargo() const;
		[[nodiscard]] virtual std::map<int, std::shared_ptr<Goods>>& cargo();
		virtual bool cargo_add(int key, int amount, std::shared_ptr<Goods> good);
		virtual bool cargo_remove(int key, int amount);
		virtual bool cannons_add(Cannons_type key, int amount, std::shared_ptr<Cannons> cannon);
		virtual bool cannons_remove(Cannons_type key, int amount);
		[[nodiscard]] virtual std::set<Cannons_type> cannons_types() const;
		virtual void cargo_update_prices(const std::map<int, std::shared_ptr<Goods>>& from);
		[[nodiscard]] virtual int price() const;
		virtual void price(int price);
		[[nodiscard]] virtual int hp() const;
		[[nodiscard]] virtual int hp_max() const;
		[[nodiscard]] virtual int hp_dmg() const;
		virtual void  hp_dmg_add(int dmg);
		[[nodiscard]] virtual Ship_type weight_class() const;
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
