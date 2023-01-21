#ifndef SOC_GOODS_H
#define SOC_GOODS_H

#include <tradable.h>

namespace Soc
{
	class Goods final : public Tradable
	{
	public:
		Goods(int id, std::string goods, int amount, int price);
		Goods(int id, std::string goods, int min_amount, int max_amount, int min_price, int max_price);
		Goods(const Goods& other);
		Goods(Goods&& other) noexcept;
		Goods& operator=(const Goods& other);
		Goods& operator=(Goods&& other) noexcept;
		~Goods() override;
		[[nodiscard]] std::string goods() const;
		[[nodiscard]] int amount() const override;
		void amount(int amount) override;
		[[nodiscard]] int price() const override;
		void price(int price) override;
	private:
		int m_id;
		std::string m_goods;
		int m_amount;
		int m_price;

		friend std::ostream& operator<<(std::ostream& os, const Goods& obj);
	};
}

#endif //SOC_GOODS_H
