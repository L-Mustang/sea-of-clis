#include <cannons_heavy.h>
#include <random/random.h>
#include <tradable.h>



namespace Soc
{
	Cannons_heavy::Cannons_heavy(int min_amount, int max_amount, int price): Cannons("32-pounder long guns", min_amount, max_amount, price)
	{}

	int Cannons_heavy::damage()
	{
		return Random::random(0, 6);
	}

	std::shared_ptr<Tradable> Cannons_heavy::copy() const
	{
		return std::make_shared<Cannons_heavy>(*this);
	}
}
