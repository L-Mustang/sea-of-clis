#ifndef SOC_CANNONS_HEAVY_H
#define SOC_CANNONS_HEAVY_H

#include <cannons.h>

namespace Soc
{
	class Cannons_heavy final : public Cannons
	{
	public:
		Cannons_heavy(int min_amount, int max_amount, int price);

		[[nodiscard]] int damage() const override;
		[[nodiscard]] std::shared_ptr<Tradable> copy() const override;
	};
}

#endif //SOC_CANNONS_HEAVY_H
