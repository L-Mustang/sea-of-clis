#include <cannons.h>
#include <random/random.h>


namespace Soc
{
	Cannons::Cannons(std::string cannons, int min_amount, int max_amount, int price):
		m_cannons(std::move(cannons)),
		m_amount(Random::random(min_amount, max_amount)),
		m_price(price)
	{}

	int Cannons::amount() const
	{
		return m_amount;
	}

	void Cannons::amount(int amount)
	{
		m_amount = amount;
	}

	int Cannons::price() const
	{
		return m_price;
	}
}
