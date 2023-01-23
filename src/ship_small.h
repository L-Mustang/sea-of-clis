#ifndef SOC_SHIP_SMALL_H
#define SOC_SHIP_SMALL_H

#include <ship.h>

namespace Soc {
	class Ship_small final : public Ship
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
		Ship_small(int id, std::string type, int price,
			int cargo, int cannons, int hp, Ship_type weight_class);

		/**
		 * @brief Returns the size of the ship
		 * @return Size of ship
		 */
		[[nodiscard]] std::string size() const override;
		/**
		 * @brief Returns the types of cannons compatible with this ship
		 * @return Types of cannons compatible with this ship
		 */
		[[nodiscard]] std::set<Cannons_type> cannons_types() const override;
	};
}

#endif // SOC_SHIP_SMALL_H
