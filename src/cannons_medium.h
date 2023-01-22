#ifndef SOC_CANNONS_MEDIUM_H
#define SOC_CANNONS_MEDIUM_H

#include <cannons.h>

namespace Soc
{
	class Cannons_medium final : public Cannons
	{
	public:
		Cannons_medium(int min_amount, int max_amount, int price);
		int damage() override;
		[[nodiscard]] std::shared_ptr<Tradable> copy() const override;
	};
}

#endif //SOC_CANNONS_MEDIUM_H
