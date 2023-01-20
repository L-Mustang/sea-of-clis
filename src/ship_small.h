#ifndef SOC_SHIP_SMALL_H
#define SOC_SHIP_SMALL_H

#include <cannons.h>
#include <cannons_small.h>
#include <cannons_type.h>
#include <ship.h>
#include <ship_type.h>

#include <utility>

namespace Soc {
	class Ship_small final : public Ship
	{
	public:
		Ship_small(const int id, std::string type, const int price, const int cargo_max, const int cannons_max, const int hp, Ship_type weight_class) :
		Ship(id, std::move(type), price, cargo_max, cannons_max, hp, weight_class)
		{}

		std::string size() const override
		{
			return "Small";
		}
	};
}

#endif // SOC_SHIP_SMALL_H
