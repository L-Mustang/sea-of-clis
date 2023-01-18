#ifndef SOC_RANDOM_RANDOM_H
#define SOC_RANDOM_RANDOM_H

namespace Soc::Random
{
	template <typename T>
	T randm(T low, T high)
	{
		static std::random_device seeder;
		static std::mt19937 gen(seeder());
		typename std::conditional<std::is_integral_v<T>,
			std::uniform_int_distribution<T>,
			std::uniform_real_distribution<T>
		>::type dis(low, high);
		return dis(gen);
	}
}

#endif //SOC_RANDOM_RANDOM_H
