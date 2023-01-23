#ifndef SOC_HARBOR_H
#define SOC_HARBOR_H

namespace Soc {
	class Goods;

	class Harbor
	{
	public:
		/**
		 * @brief Constructor
		 * @param id Harbor ID
		 * @param harbor Name of the harbor
		 */
		Harbor(int id, std::string harbor);

		/**
		 * @brief Returns the ID of the harbor
		 * @return Harbor ID
		 */
		[[nodiscard]] int id() const;
		/**
		 * @brief Sets the ID of the harbor
		 * @param id Harbor ID
		 */
		void id(int id);
		/**
		 * @brief Returns the name of the harbor
		 * @return Harbor name
		 */
		[[nodiscard]] std::string harbor() const;
		/**
		 * @brief Sets the distance to this harbor
		 * @param distance Distance
		 */
		void distance(int distance);
		/**
		 * @brief Returns the distance to this harbor
		 * @return distance Distance
		 */
		[[nodiscard]] int distance() const;
		/**
		 * @brief Removes the amount of distance from this harbor's distance
		 * @param distance Distance to be removed
		 */
		void distance_remove(int distance);

	private:
		int m_id;
		int m_distance;
		std::string m_harbor;

		friend std::ostream& operator<<(std::ostream& os, const Harbor& obj);
	};
}

#endif // SOC_HARBOR_H
