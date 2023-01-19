#include <cannons_medium.h>

#include <random/random.h>

namespace Soc
{
	Cannons_medium::Cannons_medium(int min_amount, int max_amount, int price): Cannons("18-pounder medium guns", min_amount, max_amount, price)
	{}

	int Cannons_medium::damage()
	{
		return Random::random(0, 4);
	}
}
