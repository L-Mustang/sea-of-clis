#ifndef SOC_CANNONS_H
#define SOC_CANNONS_H

#include <tradable.h>

namespace Soc
{
	class Cannons : public Tradable
	{
	public:
		/**
		 * @brief Constructor
		 * @param cannons Name of the the cannons
		 * @param min_amount Minimum amount
		 * @param max_amount Maximum amount
		 * @param price Price
		 */
		Cannons(std::string cannons, int min_amount, int max_amount, int price);

		/**
		 * @brief Returns the name of the cannons
		 * @return Name of cannons
		 */
		[[nodiscard]] std::string cannons() const;
		/**
		 * @brief Returns the amount of cannons
		 * @return Amount of cannons
		 */
		[[nodiscard]] int amount() const override;
		/**
		 * @brief Sets the amount of cannons
		 * @param amount Amount of cannons
		 */
		void amount(int amount) override;
		/**
		 * @brief Returns the price per piece of the cannons
		 * @return Price per piece of the cannons
		 */
		[[nodiscard]] int price() const override;
		/**
		 * @brief Sets the price per piece of the cannons
		 * @param price Price per piece
		 */
		void price(int price) override;
		/**
		 * @brief Returns the amount of damage this type of cannons will deal
		 * @return Amount of damage
		 */
		[[nodiscard]] virtual int damage() const = 0;
	protected:
		std::string m_cannons;
		int m_amount;
		int m_price;

		friend std::ostream& operator<<(std::ostream& os, const Cannons& obj);
	};
}

#endif //SOC_CANNONS_H
