#ifndef SOC_UTILS_MAP_H
#define SOC_UTILS_MAP_H

#include <tradable.h>
#include <random/random.h>

namespace Soc::Utils::Map
{
	template<typename K, typename T>
	void increment_add_if_not_found(K key, int amount, T val, std::map<K, std::shared_ptr<T>>& to)
	{
		static_assert(std::is_base_of_v<Tradable, T>, "Type T must derive from Tradable");
		if(to.contains(key)) // Check if key already exists in to.
		{
			to.at(key)->amount(to.at(key)->amount() + amount); // If so, increment
		}
		else // If not, insert copy and adjust amount
		{
			val.amount(amount);
			to.emplace(key, std::make_shared<T>(val));
		}
	}

	template<typename K, typename T>
	void decrement_remove_if_none(K key, int amount, std::map<K, std::shared_ptr<T>>& from)
	{
		static_assert(std::is_base_of_v<Tradable, T>, "Type T must derive from Tradable");
		if(from.at(key)->amount() <= amount)
		{
			from.erase(key); // If amount will be 0 or less in from, erase
		}
		else
		{
			from.at(key)->amount(from.at(key)->amount() - amount); // Else decrement key in from
		}
	}

	template<typename K, typename T>
	void transfer(K key, int amount, std::map<K, std::shared_ptr<T>>& from, std::map<K, std::shared_ptr<T>>& to)
	{
		static_assert(std::is_base_of_v<Tradable, T>, "Type T must derive from Tradable");
		if(to.contains(key)) // Check if key already exists in to.
		{
			to.at(key)->amount(to.at(key)->amount() + amount); // If so, increment
		}
		else
		{
			auto val = *from.at(key); // If not, insert by deep copy and adjust amount
			val.amount(amount);
			to.emplace(key, std::make_shared<T>(val));
		}

		if(from.at(key)->amount() <= amount)
		{
			from.erase(key); // If amount will be 0 or less in from, erase
		}
		else
		{
			from.at(key)->amount(from.at(key)->amount() - amount); // Else ecrement key in from
		}
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
	T random(const std::map<K, T>& map)
	{
		int rand = Random::random(0, static_cast<int>(map.size()-1));
		auto it = map.begin();
		std::advance(it, rand);
		return it->second;
	}

	template <typename K, typename T>
	int amount(const std::map<K, std::shared_ptr<T>>& map)
	{
		static_assert(std::is_base_of_v<Tradable, T>, "Type T must derive from Tradable");
		int amount{};
		for(auto& [key, val] : map)
		{
			amount += val->amount();
		}
		return amount;
	}

}
#endif // SOC_UTILS_MAP_H
