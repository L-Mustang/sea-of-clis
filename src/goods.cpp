#include <goods.h>

namespace Soc
{
	Goods::Goods(int id, std::string goods, int amount, int price) : m_id(id),
		m_goods(std::move(goods)),
		m_amount(amount),
		m_price(price)
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
}
