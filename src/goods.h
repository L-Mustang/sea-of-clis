#ifndef SOC_GOODS_H
#define SOC_GOODS_H

#include <tradable.h>

namespace Soc
{
	class Goods final : public Tradable
	{
	public:
		Goods(int id, std::string goods, int min_amount, int max_amount, int min_price, int max_price);

		[[nodiscard]] std::string goods() const;
		[[nodiscard]] int amount() const override;
		void amount(int amount) override;
		[[nodiscard]] int price() const override;
		void price(int price) override;
		[[nodiscard]] std::shared_ptr<Tradable> copy() const override;
	private:
		int m_id;
		std::string m_goods;
		int m_amount;
		int m_price;

		friend std::ostream& operator<<(std::ostream& os, const Goods& obj);
	};
}

#endif //SOC_GOODS_H
