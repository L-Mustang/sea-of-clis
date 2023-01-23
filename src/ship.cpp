#include <ship.h>

#include <cannons.h>
#include <cannons_type.h>
#include <goods.h>
#include <logger.h>
#include <ranges>
#include <ship_type.h>
#include <utils/map.h>

namespace Soc
{
	Ship::Ship(const int id, std::string type, const int price,
		const int cargo, const int cannons, const int hp,
		const Ship_type weight_class) :
		m_id(id),
		m_type(std::move(type)),
		m_price(price),
		m_cargo_max(cargo),
		m_cannons_max(cannons),
		m_hp(hp),
		m_hp_max(hp),
		m_weight_class(weight_class)
	{
	}

	Ship::~Ship() = default;

	Ship::Ship(Ship&& other) noexcept = default;

	Ship& Ship::operator=(Ship&& other) noexcept = default;

	std::string Ship::type() const
	{
		return m_type;
	}

	std::string Ship::size() const
	{
		return "Large";
	}

	int Ship::cargo_amount() const
	{
		return Utils::Map::amount(m_cargo);
	}

	int Ship::cargo_max() const
	{
		return m_cargo_max;
	}

	int Ship::cargo_space() const
	{
		return cargo_max() - cargo_amount();
	}

	int Ship::cannons_amount() const
	{
		return Utils::Map::amount(m_cannons);
	}

	int Ship::cannons_max() const
	{
		return m_cannons_max;
	}

	int Ship::cannons_space() const
	{
		return cannons_max() - cannons_amount();
	}

	std::map<Cannons_type, std::shared_ptr<Cannons>> Ship::cannons() const
	{
		return m_cannons;
	}

	std::map<Cannons_type, std::shared_ptr<Cannons>> Ship::cannons()
	{
		return m_cannons;
	}

	const std::map<int, std::shared_ptr<Goods>>& Ship::cargo() const
	{
		return m_cargo;
	}

	std::map<int, std::shared_ptr<Goods>>& Ship::cargo()
	{
		return m_cargo;
	}

	bool Ship::cargo_add(const int key, const int amount, std::shared_ptr<Goods> good)
	{
		Utils::Map::increment_add_if_not_found(key, amount, std::move(good), m_cargo);
		return true;
	}

	bool Ship::cargo_remove(const int key, const int amount)
	{
		Utils::Map::decrement_remove_if_none(key, amount, m_cargo);
		return true;
	}

	bool Ship::cannons_add(const Cannons_type key, const int amount, std::shared_ptr<Cannons> cannon)
	{
		Utils::Map::increment_add_if_not_found(key, amount, std::move(cannon), m_cannons);
		return true;
	}

	bool Ship::cannons_remove(const Cannons_type key, const int amount)
	{
		Utils::Map::decrement_remove_if_none(key, amount, m_cannons);
		return true;
	}

	std::set<Cannons_type> Ship::cannons_types() const
	{
		return { Cannons_type::light, Cannons_type::medium, Cannons_type::heavy };
	}

	void Ship::cargo_update_prices(const std::map<int, std::shared_ptr<Goods>>& from)
	{
		for (auto& [key, val] : m_cargo)
		{
			val->price(from.at(key)->price());
		}
	}

	int Ship::price() const
	{
		return m_price;
	}

	void Ship::price(const int price)
	{
		m_price = price;
	}

	int Ship::hp() const
	{
		return m_hp;
	}

	int Ship::hp_max() const
	{
		return m_hp_max;
	}

	int Ship::hp_dmg() const
	{
		return m_hp_max - m_hp;
	}

	void Ship::hp_dmg_add(const int dmg)
	{
		m_hp -= dmg;
	}

	Ship_type Ship::weight_class() const
	{
		return m_weight_class;
	}

	int Ship::broadside() const
	{
		int dmg{};
		// values_view can be useful for extracting values from associative containers
		// https://en.cppreference.com/w/cpp/ranges/values_view
		for (const auto& val : m_cannons | std::views::values) 
		{
			for (int i = 0; i < val->amount(); ++i) // 
			{
				dmg += val->damage();
			}
		}
		return dmg / 2; // divide damage by 2 because a broadside can only be fired from one side
	}

	std::ostream& operator<<(std::ostream& os, const Ship& obj)
	{
		return os
			<< " "
			<< std::left << std::setw(16) << obj.m_type << " |"
			<< " Cargo capacity: "
			<< std::right << std::setw(3) << obj.m_cargo_max << " tonnes" << " |"
			<< " Cannon slots: "
			<< std::right << std::setw(2) << obj.m_cannons_max << " |"
			<< " HP: "
			<< std::right << std::setw(3) << obj.m_hp << " |"
			<< std::right << std::setw(7) << obj.m_weight_class << " |"
			<< std::right << std::setw(6) << obj.size() << " |"
			<< std::left << " $ "
			<< std::right << std::setw(7) << Logger::format(obj.m_price);
	}
}
