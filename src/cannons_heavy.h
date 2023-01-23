#ifndef SOC_CANNONS_HEAVY_H
#define SOC_CANNONS_HEAVY_H

#include <cannons.h>

namespace Soc
{
	class Cannons_heavy final : public Cannons
	{
	public:
		/**
		 * @brief Constructor
		 * @param min_amount Minimum amount
		 * @param max_amount Maximum amount
		 * @param price Price
		 */
		Cannons_heavy(int min_amount, int max_amount, int price);

		/**
		 * @brief Returns the amount of damage this type of cannons will deal
		 * @return Amount of damage
		 */
		[[nodiscard]] int damage() const override;
		/**
		 * @brief Returns a deep copy of these cannons
		 * @return Deep copy of this instance, in Tradable pointer
		 */
		[[nodiscard]] std::shared_ptr<Tradable> copy() const override;
	};
}

#endif //SOC_CANNONS_HEAVY_H
