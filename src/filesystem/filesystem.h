#ifndef SOC_FILESYSTEM_FILESYSTEM_H
#define SOC_FILESYSTEM_FILESYSTEM_H

namespace Soc
{
	class Goods;
	class Harbor;
	class Ship;
}

namespace Soc::Filesystem
{
	/**
	 * @brief Abstract class for a filesystem
	 */
	class Filesystem // NOLINT
	{
	public:
		virtual ~Filesystem() = default;
		/**
		 * @brief Gets all harbors from the filesystem
		 * @return Harbors
		 */

		[[nodiscard]] virtual std::map<int, std::shared_ptr<Harbor>> harbors() const = 0;
		/**
		 * @brief Gets the goods for a specific harbor from the filesystem
		 * @param harbor_id Harbor ID to get goods from
		 * @return Goods
		 */
		[[nodiscard]] virtual std::map<int, std::shared_ptr<Goods>> goods(int harbor_id) const = 0;
		/**
		 * @brief Gets all ships from the filesystem
		 * @return Ships
		 */
		[[nodiscard]] virtual std::map<int, std::shared_ptr<Ship>> ships() const = 0;
		/**
		 * @brief Sets correct distances to Harbors from a given Harbor
		 * @param harbor_id Harbor ID
		 * @param harbors Updated Harbors
		 */
		virtual void harbors_distances(int harbor_id, std::map<int, std::shared_ptr<Harbor>>& harbors) const = 0;
	};
}

#endif //SOC_FILESYSTEM_FILESYSTEM_H
