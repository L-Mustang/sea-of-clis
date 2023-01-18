#include <ship.h>

namespace Soc
{
	Ship::Ship(const int id, std::string type, const int price, const int cargo, const int cannons, const int hp, const int peculiarity) : m_id(id),
		m_type(std::move(type)),
		m_price(price),
		m_cargo(cargo),
		m_cannons(cannons),
		m_hp(hp),
		m_peculiarity(peculiarity)
	{}

	Ship::~Ship() = default;

	Ship::Ship(const Ship& other) = default;

	Ship::Ship(Ship&& other) noexcept : m_id(other.m_id),
		m_type(std::move(other.m_type)),
		m_price(other.m_price),
		m_cargo(other.m_cargo),
		m_cannons(other.m_cannons),
		m_hp(other.m_hp),
		m_peculiarity(other.m_peculiarity)
	{}

	Ship& Ship::operator=(const Ship& other)
	{
		if (this == &other)
			return *this;
		m_id = other.m_id;
		m_type = other.m_type;
		m_price = other.m_price;
		m_cargo = other.m_cargo;
		m_cannons = other.m_cannons;
		m_hp = other.m_hp;
		m_peculiarity = other.m_peculiarity;
		return *this;
	}

	Ship& Ship::operator=(Ship&& other) noexcept
	{
		if (this == &other)
			return *this;
		m_id = other.m_id;
		m_type = std::move(other.m_type);
		m_price = other.m_price;
		m_cargo = other.m_cargo;
		m_cannons = other.m_cannons;
		m_hp = other.m_hp;
		m_peculiarity = other.m_peculiarity;
		return *this;
	}
}
