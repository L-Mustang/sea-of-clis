#ifndef SOC_CANNONS_LIGHT_H
#define SOC_CANNONS_LIGHT_H

#include <cannons.h>

namespace Soc
{
	class Cannons_light final : public Cannons
	{
	public:
		Cannons_light(int min_amount, int max_amount, int price);
		int damage() override;
	};
}

#endif //SOC_CANNONS_LIGHT_H
