#include <cannons_medium.h>

#include <random/random.h>
#include <tradable.h>

namespace Soc
{
	Cannons_medium::Cannons_medium(const int min_amount, const int max_amount, const int price): Cannons(
		"18-pounder medium guns", min_amount, max_amount, price)
	{
	}

	int Cannons_medium::damage() const
	{
		return Random::random(0, 4);
	}

	std::shared_ptr<Tradable> Cannons_medium::copy() const
	{
		return std::make_shared<Cannons_medium>(*this);
	}
}
