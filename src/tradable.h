#ifndef SOC_TRADABLE_H
#define SOC_TRADABLE_H

namespace Soc
{
	class Tradable // NOLINT
	{
	public:
		virtual ~Tradable() = default;
		/**
		 * @brief Returns the amount of the tradable
		 * @return Amount of the tradable
		 */
		[[nodiscard]] virtual int amount() const = 0;
		/**
		 * @brief Sets the amount of the tradable
		 * @amount Amount of the tradable
		 */
		virtual void amount(int amount) = 0;
		/**
		 * @brief Returns the price of the tradable
		 * @return price of the tradable
		 */
		[[nodiscard]] virtual int price() const = 0;
		/**
		 * @brief Sets the price of the tradable
		 * @amount Price of the tradable
		 */
		virtual void price(int price) = 0;
		/**
		 * @brief Returns a deep copy of this tradable
		 * @return Deep copy of this instance, in Tradable pointer
		 */
		[[nodiscard]] virtual std::shared_ptr<Tradable> copy() const = 0;
	};
}

#endif //SOC_TRADABLE_H
