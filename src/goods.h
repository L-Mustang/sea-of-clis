#ifndef SOC_GOODS_H
#define SOC_GOODS_H

namespace Soc
{
	class Goods
	{
	public:
		Goods(int id, std::string goods, int amount, int price);
		~Goods();
		Goods(const Goods& other);
		Goods(Goods&& other) noexcept;
		Goods& operator=(const Goods& other);
		Goods& operator=(Goods&& other) noexcept;

	private:
		int m_id;
		std::string m_goods;
		int m_amount;
		int m_price;
	};
}

#endif //SOC_GOODS_H
