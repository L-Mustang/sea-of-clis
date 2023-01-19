#include <goods.h>
#include <random/random.h>

namespace Soc
{
	Goods::Goods(int id, std::string goods, int amount, int price) : m_id(id),
		m_goods(std::move(goods)),
		m_amount(amount),
		m_price(price)
	{}

	Goods::Goods(int id, std::string goods, int min_amount, int max_amount, int min_price, int max_price) : m_id(id),
		m_goods(std::move(goods)),
		m_amount(Random::random(min_amount, max_amount)),
		m_price(Random::random(min_price, max_price))
	{}

	Goods::~Goods() = default;

	Goods::Goods(const Goods& other) = default;

	Goods::Goods(Goods&& other) noexcept: m_id(other.m_id),
	                                      m_goods(std::move(other.m_goods)),
	                                      m_amount(other.m_amount),
	                                      m_price(other.m_price)
	{
	}

	Goods& Goods::operator=(const Goods& other)
	{
		if (this == &other)
			return *this;
		m_id = other.m_id;
		m_goods = other.m_goods;
		m_amount = other.m_amount;
		m_price = other.m_price;
		return *this;
	}

	Goods& Goods::operator=(Goods&& other) noexcept
	{
		if (this == &other)
			return *this;
		m_id = other.m_id;
		m_goods = std::move(other.m_goods);
		m_amount = other.m_amount;
		m_price = other.m_price;
		return *this;
	}

	std::ostream& operator<<(std::ostream& os, const Goods& obj)
	{
		return os
			<< " ID: "
			<< std::right << std::setw(5) << obj.m_id
			<< " Good: "
			<< std::right << std::setw(10) << obj.m_goods
			<< " Amount: "
			<< std::right << std::setw(5) << obj.m_amount
			<< " Price: "
			<< std::right << std::setw(5) << obj.m_price;
	}
}
