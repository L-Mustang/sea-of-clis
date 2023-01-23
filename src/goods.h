#ifndef SOC_GOODS_H
#define SOC_GOODS_H

#include <tradable.h>

namespace Soc
{
	class Goods final : public Tradable
	{
	public:
		/**
		 * @brief Constructor
		 * @param id Goods ID
		 * @param goods Name of the goods
		 * @param min_amount Minimum amount
		 * @param max_amount Maximum amount
		 * @param min_price Minimum price
		 * @param max_price Maximum price
		 */
		Goods(int id, std::string goods, int min_amount, int max_amount, int min_price, int max_price);

		/**
		 * @brief Returns the name of the goods
		 * @return Name of the goods
		 */
		[[nodiscard]] std::string goods() const;
		/**
		 * @brief Returns the amount of goods
		 * @return Amount of goods
		 */
		[[nodiscard]] int amount() const override;
		/**
		 * @brief Sets the amount of goods
		 * @param amount Amount of goods
		 */
		void amount(int amount) override;
		/**
		 * @brief Returns the price of the goods
		 * @return Price of the goods
		 */
		[[nodiscard]] int price() const override;
		/**
		 * @brief Sets the price of the goods
		 * @param price Price of the goods
		 */
		void price(int price) override;
		/**
		 * @brief Returns a deep copy of these goods
		 * @return Deep copy of this instance, in Tradable pointer
		 */
		[[nodiscard]] std::shared_ptr<Tradable> copy() const override;
	private:
		int m_id; // NOLINT
		std::string m_goods;
		int m_amount;
		int m_price;

		friend std::ostream& operator<<(std::ostream& os, const Goods& obj);
	};
}

#endif //SOC_GOODS_H
