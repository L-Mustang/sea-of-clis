#ifndef SOC_HARBOR_H
#define SOC_HARBOR_H
#include <goods.h>

namespace Soc {
	class Goods;

	class Harbor
	{
	public:
		Harbor(int id = 0, std::string harbor = {});
		~Harbor();
		Harbor(const Harbor& other);
		Harbor(Harbor&& other) noexcept;
		Harbor& operator=(const Harbor& other);
		Harbor& operator=(Harbor&& other) noexcept;
		[[nodiscard]] int id() const;
		void id(int id);
		[[nodiscard]] std::string harbor() const;
		void harbor(std::string harbor);
		[[nodiscard]] const std::vector<std::shared_ptr<const Goods>>& goods() const;
		void goods_add(std::shared_ptr<const Goods> goods);
		void goods_take(const std::shared_ptr<const Goods>& goods);
		void distance(int distance);
		[[nodiscard]] int distance() const;
		void distance_remove(int distance);
	private:
		int m_id;
		int m_distance;
		std::string m_harbor;
		std::vector<std::shared_ptr<const Goods>> m_goods;

		friend std::ostream& operator<<(std::ostream& os, const Harbor& obj)
	{
		return os
			<< " Harbor: "
			<< std::right << std::setw(10) << obj.m_harbor << " |"
			<< " Distance: "
			<< std::right << std::setw(5) << obj.m_distance;
	}
	};
}

#endif // SOC_HARBOR_H
