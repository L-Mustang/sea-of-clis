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
	class Filesystem // NOLINT
	{
	public:
		virtual ~Filesystem() = default;
		[[nodiscard]] virtual std::map<int, std::shared_ptr<Harbor>> harbors() const = 0;
		[[nodiscard]] virtual std::map<int, std::shared_ptr<Goods>> goods(int harbor_id) const = 0;
		[[nodiscard]] virtual std::map<int, std::shared_ptr<Ship>> ships() const = 0;
		virtual void harbors_distances(int harbor_id, std::map<int, std::shared_ptr<Harbor>>& harbors) const = 0;
	};
}

#endif //SOC_FILESYSTEM_FILESYSTEM_H
