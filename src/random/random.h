#ifndef SOC_RANDOM_RANDOM_H
#define SOC_RANDOM_RANDOM_H
#include <concepts>
namespace Soc::Random
{
	template <typename T>
	T random(T low, T high)
	{
		static std::random_device seeder;
		static std::mt19937 gen(seeder());
		std::conditional_t<std::is_integral_v<T>,
		                 std::uniform_int_distribution<T>,
		                 std::uniform_real_distribution<T>
		> dis(low, high);
		return dis(gen);
	}
}

#endif //SOC_RANDOM_RANDOM_H
