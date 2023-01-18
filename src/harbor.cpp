#include <harbor.h>
#include <goods.h>

namespace Soc
{
	Harbor::Harbor(int id, std::string harbor) : m_id(id),
		m_harbor(std::move(harbor))
	{
	}

	Harbor::~Harbor() = default;

	Harbor::Harbor(const Harbor& other) = default;

	Harbor::Harbor(Harbor&& other) noexcept : m_id(other.m_id),
		m_harbor(std::move(other.m_harbor)),
		m_goods(std::move(other.m_goods))
	{
	}

	Harbor& Harbor::operator=(const Harbor& other)
	{
		if (this == &other)
			return *this;
		m_id = other.m_id;
		m_harbor = other.m_harbor;
		m_goods = other.m_goods;
		return *this;
	}

	Harbor& Harbor::operator=(Harbor&& other) noexcept
	{
		if (this == &other)
			return *this;
		m_id = other.m_id;
		m_harbor = std::move(other.m_harbor);
		m_goods = std::move(other.m_goods);
		return *this;
	}

	int Harbor::id() const
	{
		return m_id;
	}

	void Harbor::id(int id)
	{
		m_id = id;
	}

	std::string Harbor::harbor() const
	{
		return m_harbor;
	}

	void Harbor::harbor(std::string harbor)
	{
		m_harbor = std::move(harbor);
	}

	const std::vector<std::shared_ptr<const Goods>>& Harbor::goods() const
	{
		return m_goods;
	}

	void Harbor::goods_add(const std::shared_ptr<const Goods> goods) //NOLINT
	{
		m_goods.push_back(goods);
	}

	void Harbor::goods_take(const std::shared_ptr<const Goods>& goods)
	{
		std::erase(m_goods, goods);
	}
}
