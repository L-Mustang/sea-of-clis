#ifndef SOC_SHIP_H
#define SOC_SHIP_H

#include <cannons.h>
#include <cannons_small.h>
#include <cannons_type.h>
#include <ostream>
#include <ship_type.h>

namespace Soc {
	class Ship
	{
	public:
		Ship(const int id, std::string type, const int price, const int cargo, const int cannons, const int hp, Ship_type weight_class) : m_id(id),
			m_type(std::move(type)),
			m_price(price),
			m_cargo_max(cargo),
			m_cannons_max(cannons),
			m_hp(hp),
			m_weight_class(weight_class)
		{}
		virtual ~Ship() = default;

		[[nodiscard]] virtual std::string type() const
		{
			return m_type;
		}

		[[nodiscard]] virtual std::string size() const
		{
			return "Large";
		}

		virtual void cannons_add(std::shared_ptr<Cannons> cannons)
		{
		}
	protected:
		int m_id;
		std::string m_type;
		int m_price;
		int m_cargo_max;
		int m_cannons_max;
		int m_hp;
		Ship_type m_weight_class;
		std::map<Cannons_type, std::shared_ptr<Cannons>> m_cannons;
	private:
		friend std::ostream& operator<<(std::ostream& os, const Ship& obj);
	};
}

#endif // SOC_SHIP_H
