#ifndef SOC_RANDOM_RANDOM_H
#define SOC_RANDOM_RANDOM_H

namespace Soc::Random
{
	/**
	 * @brief Generates a pseudo-random number using Mersenne Twister and the system's
	 * std::random_device implementation
	 * @tparam T Type of the to be generated numerical
	 * @param low Lower bound (inclusive)
	 * @param high Upper bound (inclusive)
	 * @return A pseudo-random number within the given bounds
	 */
	template <typename T>
	T random(T low, T high)
	{
		static std::random_device dev;
		static std::mt19937 gen(dev());
		std::conditional_t<std::is_integral_v<T>, std::uniform_int_distribution<T>, std::uniform_real_distribution<T>>
			dis(low, high); // check whether integral or real
		return dis(gen);
	}
}

#endif //SOC_RANDOM_RANDOM_H
