#ifndef SOC_CANNONS_SMALL_H
#define SOC_CANNONS_SMALL_H

namespace Soc
{
	class Cannons_small
	{
	public:
		Cannons_small(std::string Cannons_small, int min_amount, int max_amount, int price);
		virtual ~Cannons_small();
		Cannons_small(const Cannons_small& other) = default;
		Cannons_small(Cannons_small&& other) noexcept = default;
		Cannons_small& operator=(const Cannons_small& other) = default;
		Cannons_small& operator=(Cannons_small&& other) noexcept = default;
		[[nodiscard]] virtual int amount() const;
		virtual void amount(int amount);
		[[nodiscard]] virtual int price() const;
		virtual void price(int price);
		virtual int damage() = 0;

	private:
		std::string m_cannons;
		int m_amount;
		int m_price;

		friend std::ostream& operator<<(std::ostream& os, const Cannons_small& obj)
		{
			return os
				<< " Cannons_small: "
				<< std::right << std::setw(25) << obj.m_cannons
				<< " Amount: "
				<< std::right << std::setw(3) << obj.m_amount
				<< " Price: "
				<< std::right << std::setw(5) << obj.m_price;
		}
	};
}

#endif //SOC_CANNONS_SMALL_H
