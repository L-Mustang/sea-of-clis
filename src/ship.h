#ifndef SOC_SHIP_H
#define SOC_SHIP_H

#include <cannons.h>
#include <cannons_small.h>
#include <cannons_type.h>
#include <ostream>
#include <ship_type.h>
#include <utils/map.h>

#include "goods.h"

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

		[[nodiscard]] virtual int cargo_amount() const
		{
			return Utils::Map::amount(m_cargo);
		}

		[[nodiscard]] virtual int cargo_max() const
		{
			return m_cargo_max;
		}

		[[nodiscard]] virtual int cargo_space() const
		{
			return cargo_max() - cargo_amount();
		}

		[[nodiscard]] virtual int cannons_amount() const
		{
			return Utils::Map::amount(m_cannons);
		}

		[[nodiscard]] virtual int cannons_max() const
		{
			return m_cannons_max;
		}

		[[nodiscard]] virtual int cannons_space() const
		{
			return cannons_max() - cannons_amount();
		}

		[[nodiscard]] virtual const std::map<int, std::shared_ptr<Goods>>& cargo() const
		{
			return m_cargo;
		}

		[[nodiscard]] virtual std::map<int, std::shared_ptr<Goods>>& cargo()
		{
			return m_cargo;
		}

		virtual bool cargo_add(int key, int amount, std::shared_ptr<Goods> good)
		{
			Utils::Map::increment_add_if_not_found(key, amount, *good, m_cargo);
			return true;
		}

		virtual bool cargo_remove(int key, int amount)
		{
			Utils::Map::decrement_remove_if_none(key, amount, m_cargo);
			return true;
		}

		virtual void cannons_add(Cannons_type key, std::shared_ptr<Cannons> cannon)
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
		std::map<int, std::shared_ptr<Goods>> m_cargo;
	private:
		friend std::ostream& operator<<(std::ostream& os, const Ship& obj);
	};
}

#endif // SOC_SHIP_H
