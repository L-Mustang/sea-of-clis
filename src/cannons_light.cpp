#include <cannons_light.h>

#include <tradable.h>
#include <random/random.h>

namespace Soc
{
	Cannons_light::Cannons_light(const int min_amount, const int max_amount, const int price): Cannons(
		"12-pounder short guns", min_amount, max_amount, price)
	{
	}

	int Cannons_light::damage() const
	{
		return Random::random(0, 2);
	}

	std::shared_ptr<Tradable> Cannons_light::copy() const
	{
		return std::make_shared<Cannons_light>(*this);
	}
}
