#include <ship_small.h>

#include <cannons_type.h>

namespace Soc
{
	Ship_small::Ship_small(const int id, std::string type, const int price, const int cargo,
		const int cannons, const int hp, const Ship_type weight_class):
		Ship(id, std::move(type), price, cargo, cannons, hp, weight_class)
	{
	}

	std::string Ship_small::size() const
	{
		return "Small";
	}

	std::set<Cannons_type> Ship_small::cannons_types() const
	{
		return {Cannons_type::light, Cannons_type::medium};
	}
}
