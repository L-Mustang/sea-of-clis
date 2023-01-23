#ifndef SOC_SHIP_SMALL_H
#define SOC_SHIP_SMALL_H

#include <ship.h>

namespace Soc {
	class Ship_small final : public Ship
	{
	public:
		Ship_small(int id, std::string type, int price,
			int cargo_max, int cannons_max, int hp, Ship_type weight_class);

		[[nodiscard]] std::string size() const override;
		[[nodiscard]] std::set<Cannons_type> cannons_types() const override;
	};
}

#endif // SOC_SHIP_SMALL_H
