#include <goods.h>

#include <random/random.h>

namespace Soc
{
	Goods::Goods(const int id, std::string goods, const int min_amount,
		const int max_amount, const int min_price, const int max_price):
		m_id(id),
		m_goods(std::move(goods)),
		m_amount(Random::random(min_amount, max_amount)),
		m_price(Random::random(min_price, max_price))
	{
	}

	std::string Goods::goods() const
	{
		return m_goods;
	}

	int Goods::amount() const
	{
		return m_amount;
	}

	void Goods::amount(const int amount)
	{
		m_amount = amount;
	}

	int Goods::price() const
	{
		return m_price;
	}

	void Goods::price(const int price)
	{
		m_price = price;
	}

	std::shared_ptr<Tradable> Goods::copy() const
	{
		return std::make_shared<Goods>(*this);
	}

	std::ostream& operator<<(std::ostream& os, const Goods& obj)
	{
		return os
			<< " Good: "
			<< std::right << std::setw(10) << obj.m_goods << " |"
			<< " Amount: "
			<< std::right << std::setw(5) << obj.m_amount << " |"
			<< " Price: "
			<< std::right << std::setw(5) << obj.m_price;
	}
}
