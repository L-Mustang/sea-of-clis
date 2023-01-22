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

		friend std::ostream& operator<<(std::ostream& os, const Cannons& obj);
	};
}

#endif //SOC_CANNONS_H
