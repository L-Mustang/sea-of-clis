#include <cannons_heavy.h>

#include <random/random.h>



namespace Soc
{
	Cannons_heavy::Cannons_heavy(int min_amount, int max_amount, int price): Cannons("32-pounder long guns", min_amount, max_amount, price)
	{}

	int Cannons_heavy::damage()
	{
		return Random::random(0, 6);
	}
}
