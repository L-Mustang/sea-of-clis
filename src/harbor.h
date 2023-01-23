#ifndef SOC_HARBOR_H
#define SOC_HARBOR_H

namespace Soc {
	class Goods;

	class Harbor
	{
	public:
		Harbor(int id, std::string harbor);

		[[nodiscard]] int id() const;
		void id(int id);
		[[nodiscard]] std::string harbor() const;
		void harbor(std::string harbor);
		[[nodiscard]] const std::vector<std::shared_ptr<const Goods>>& goods() const;
		void goods_add(const std::shared_ptr<const Goods>& goods);
		void goods_take(const std::shared_ptr<const Goods>& goods);
		void distance(int distance);
		[[nodiscard]] int distance() const;
		void distance_remove(int distance);

	private:
		int m_id;
		int m_distance;
		std::string m_harbor;
		std::vector<std::shared_ptr<const Goods>> m_goods;

		friend std::ostream& operator<<(std::ostream& os, const Harbor& obj);
	};
}

#endif // SOC_HARBOR_H
