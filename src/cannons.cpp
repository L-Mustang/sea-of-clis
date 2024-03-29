#include <cannons.h>

#include <logger.h>
#include <random/random.h>


namespace Soc
{
	Cannons::Cannons(std::string cannons, const int min_amount, const int max_amount, const int price):
		m_cannons(std::move(cannons)),
		m_amount(Random::random(min_amount, max_amount)),
		m_price(price)
	{
	}

	std::string Cannons::cannons() const
	{
		return m_cannons;
	}

	int Cannons::amount() const
	{
		return m_amount;
	}

	void Cannons::amount(const int amount)
	{
		m_amount = amount;
	}

	int Cannons::price() const
	{
		return m_price;
	}

	void Cannons::price(const int price)
	{
		m_price = price;
	}

	std::ostream& operator<<(std::ostream& os, const Cannons& obj)
	{
		return os
			<< " "
			<< std::left << std::setw(23) << obj.m_cannons << " |"
			<< " Amount: "
			<< std::right << std::setw(2) << obj.m_amount << " |"
			<< std::left << " $ "
			<< std::right << std::setw(5) << Logger::format(obj.m_price);
	}
}
