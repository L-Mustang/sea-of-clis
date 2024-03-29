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

	void Harbor::distance(const int distance)
	{
		m_distance = distance;
	}

	int Harbor::distance() const
	{
		return m_distance > 0 ? m_distance : 0;
	}

	void Harbor::distance_remove(const int distance)
	{
		m_distance -= distance;
	}

	std::ostream& operator<<(std::ostream& os, const Harbor& obj)
	{
		return os
			<< " "
			<< std::left << std::setw(16) << obj.m_harbor << " |"
			<< " "
			<< std::right << std::setw(2) << obj.m_distance << " days";
	}
}
