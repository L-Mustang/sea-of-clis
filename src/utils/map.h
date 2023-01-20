#ifndef SOC_UTILS_MAP_H
#define SOC_UTILS_MAP_H

#include <tradable.h>
#include <random/random.h>

namespace Soc::Utils::Map
{
	template<typename K, typename T>
	void decrement_if_found(std::map<K, std::shared_ptr<T>> map)
	{
		static_assert(std::is_base_of_v<Tradable, T>, "Type T must derive from Tradable");
			//		std::find_if(m_cannons.begin(), m_cannons.end(),
			//[cannons](std::shared_ptr<Cannons>& i){ return *i == *cannons; });
	}

	template <typename K, typename T>
	void remove_if_none(std::map<K, std::shared_ptr<T>>& map)
	{
		static_assert(std::is_base_of_v<Tradable, T>, "Type T must derive from Tradable");
		for (auto it = map.begin(); it != map.end();)
		{
			if (it->second->amount() == 0)
			{
				it = map.erase(it);
			}
			else
			{
				++it;
			}
		}
	}

	template <typename K, typename T>
	std::shared_ptr<T> random(const std::map<K, std::shared_ptr<T>>& map)
	{
		int rand = Random::random(0, static_cast<int>(map.size()-1));
		auto it = map.begin();
		std::advance(it, rand);
		return it->second;
	}

}
#endif // SOC_UTILS_MAP_H
