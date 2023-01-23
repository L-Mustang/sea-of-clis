#include <cannons_heavy.h>

#include <tradable.h>
#include <random/random.h>

namespace Soc
{
	Cannons_heavy::Cannons_heavy(const int min_amount, const int max_amount, const int price): Cannons("32-pounder long guns", min_amount, max_amount, price)
	{}

	int Cannons_heavy::damage() const
	{
		return Random::random(0, 6);
	}

	std::shared_ptr<Tradable> Cannons_heavy::copy() const
	{
		return std::make_shared<Cannons_heavy>(*this);
	}
}
