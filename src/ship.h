#ifndef SOC_SHIP_H
#define SOC_SHIP_H

#include <cannons.h>
#include <cannons_small.h>
#include <cannons_type.h>

namespace Soc {
	template<class T>
	class Ship
	{
	public:
		static_assert(std::disjunction_v<std::is_base_of<Cannons, T>, std::is_base_of<Cannons_small, T>>, "Type must be Cannon, Small_cannon or derived from Cannon, Small_cannon");
		Ship(const int id, std::string type, const int price, const int cargo, const int cannons, const int hp, const int peculiarity) : m_id(id),
			m_type(std::move(type)),
			m_price(price),
			m_cargo(cargo),
			m_cannons_max(cannons),
			m_hp(hp),
			m_peculiarity(peculiarity)
		{}

	private:
		int m_id;
		std::string m_type;
		int m_price;
		int m_cargo;
		int m_cannons_max;
		int m_hp;
		int m_peculiarity;
		std::map<Cannons_type, std::shared_ptr<T>> m_cannons;
	};
}

#endif // SOC_SHIP_H
