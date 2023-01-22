#ifndef SOC_CANNONS_H
#define SOC_CANNONS_H

#include <tradable.h>

namespace Soc
{
	class Cannons : public Tradable
	{
	public:
		Cannons(std::string cannons, int min_amount, int max_amount, int price);

		[[nodiscard]] std::string cannons() const;
		[[nodiscard]] int amount() const override;
		void amount(int amount) override;
		[[nodiscard]] int price() const override;
		void price(int price) override;
		virtual int damage() = 0;
	protected:
		std::string m_cannons;
		int m_amount;
		int m_price;

		friend std::ostream& operator<<(std::ostream& os, const Cannons& obj)
		{
			return os
				<< " Cannons: "
				<< std::right << std::setw(25) << obj.m_cannons << " |"
				<< " Amount: "
				<< std::right << std::setw(3) << obj.m_amount << " |"
				<< " Price: "
				<< std::right << std::setw(5) << obj.m_price;
		}
	};
}

#endif //SOC_CANNONS_H
