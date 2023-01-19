#include <cannons_small.h>
#include <random/random.h>


namespace Soc
{
	Cannons_small::Cannons_small(std::string cannons, int min_amount, int max_amount, int price):
		m_cannons(std::move(cannons)),
		m_amount(Random::random(min_amount, max_amount)),
		m_price(price)
	{}

	Cannons_small::~Cannons_small() = default;

	int Cannons_small::amount() const
	{
		return m_amount;
	}

	void Cannons_small::amount(int amount)
	{
		m_amount = amount;
	}

	int Cannons_small::price() const
	{
		return m_price;
	}

	void Cannons_small::price(int price)
	{
		m_price = price;
	}
	
}
