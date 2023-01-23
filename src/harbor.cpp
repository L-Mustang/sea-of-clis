#include <harbor.h>

#include <goods.h>

namespace Soc
{
	Harbor::Harbor(const int id, std::string harbor) : m_id(id),
		m_distance(0),
		m_harbor(std::move(harbor))
	{
	}

	int Harbor::id() const
	{
		return m_id;
	}

	void Harbor::id(const int id)
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

	void Harbor::goods_add(const std::shared_ptr<const Goods>& goods)
	{
		m_goods.push_back(goods);
	}

	void Harbor::goods_take(const std::shared_ptr<const Goods>& goods)
	{
		std::erase(m_goods, goods);
	}

	void Harbor::distance(int distance)
	{
		m_distance = distance;
	}

	int Harbor::distance() const
	{
		return m_distance > 0 ? m_distance : 0;
	}

	void Harbor::distance_remove(int distance)
	{
		m_distance -= distance;
	}
}
