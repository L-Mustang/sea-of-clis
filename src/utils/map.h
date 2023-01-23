#ifndef SOC_UTILS_MAP_H
#define SOC_UTILS_MAP_H

#include <random/random.h>

namespace Soc
{
	class Harbor;
}

namespace Soc::Utils::Map
{
	/**
	 * @brief Increments the tradable. Adds it if it isn't found
	 * @tparam K Key type
	 * @tparam T Value type
	 * @param key Key
	 * @param amount Amount
	 * @param val Value
	 * @param to Map to which the tradable will be added
	 */
	template<typename K, typename T>
	void increment_add_if_not_found(K key, int amount, std::shared_ptr<T> val, std::map<K, std::shared_ptr<T>>& to)
	{
		static_assert(std::is_base_of_v<Tradable, T>, "Type T must derive from Tradable");
		if (to.contains(key)) // check if key already exists in to.
		{
			to.at(key)->amount(to.at(key)->amount() + amount); // if so, increment
		}
		else // if not, insert copy and adjust amount
		{
			const auto val_cpy = val->copy();
			val_cpy->amount(amount);
			to.emplace(key, std::static_pointer_cast<T>(val_cpy));
		}
	}
	/**
	 * @brief Decrements the tradable. Removes it if the amount becomes 0
	 * @tparam K Key type
	 * @tparam T Value type
	 * @param key Key
	 * @param amount Amount
	 * @param from Map from which the tradable will be removed
	 */
	template<typename K, typename T>
	void decrement_remove_if_none(K key, int amount, std::map<K, std::shared_ptr<T>>& from)
	{
		static_assert(std::is_base_of_v<Tradable, T>, "Type T must derive from Tradable");
		if (from.at(key)->amount() <= amount)
		{
			from.erase(key); // if amount will be 0 or less in from, erase
		}
		else
		{
			from.at(key)->amount(from.at(key)->amount() - amount); // else decrement key in from
		}
	}
	/**
	 * @brief Removes all tradables from the where amount = 0
	 * @tparam K Key type
	 * @tparam T Value type
	 * @param map Map
	 */
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
	/**
	 * @brief Removes tradables where amount = 0
	 * @tparam K Key type
	 * @param map Map
	 */
	template <typename K>
	void remove_if_none(std::map<K, std::shared_ptr<Harbor>>& map)
	{
		for (auto it = map.begin(); it != map.end();)
		{
			if (it->second->distance() == 0)
			{
				it = map.erase(it);
			}
			else
			{
				++it;
			}
		}
	}
	/**
	 * @brief Returns a filtered copy of a map
	 * @tparam K Key type
	 * @tparam T Value type
	 * @param keys Keys used for the filter
	 * @param map Map to be filtered
	 * @return Filtered map
	 */
	template <typename K, typename T>
	std::map<K, T> filter_view(const std::set<K>& keys, std::map<K, T> map)
	{
		for (auto it = map.begin(); it != map.end();)
		{
			if (!keys.contains(it->first))
			{
				it = map.erase(it);
			}
			else
			{
				++it;
			}
		}
		return map;
	}
	/**
	 * @brief Randomly removes a random amount of elements from a map
	 * @tparam K Key type
	 * @tparam T Value type
	 * @param map Map
	 */
	template <typename K, typename T>
	void random_remove(std::map<K, T>& map)
	{
		std::vector<K> keys; // collect all the keys of the map in a vector
		keys.reserve(map.size());
		for (const auto& [key, value] : map) {
			keys.push_back(key);
		}

		for (int i = 0; i < static_cast<int>(map.size() - 1); ++i) { // get a random key and delete its value, a random amount of times
			auto random_key = keys[Random::random(0, static_cast<int>(keys.size() - 1))];
			map.erase(random_key);
		}
	}
	/**
	 * @brief Returns a random element from map
	 * @tparam K Key type
	 * @tparam T Value type
	 * @param map Map
	 * @return Random element
	 */
	template <typename K, typename T>
	T random(std::map<K, T>& map)
	{
		int rand = Random::random(0, static_cast<int>(map.size() - 1));
		auto it = map.begin();
		std::advance(it, rand);
		auto rand_val = it->second;
		map.erase(it->first);
		return rand_val;
	}
	/**
	 * @brief Calculates the total amount of the tradables
	 * @tparam K Key type
	 * @tparam T Value type
	 * @param map Map
	 * @return Total amount
	 */
	template <typename K, typename T>
	int amount(const std::map<K, std::shared_ptr<T>>& map)
	{
		static_assert(std::is_base_of_v<Tradable, T>, "Type T must derive from Tradable");
		int amount{};
		for (auto& [key, val] : map)
		{
			amount += val->amount();
		}
		return amount;
	}

}

#endif // SOC_UTILS_MAP_H
