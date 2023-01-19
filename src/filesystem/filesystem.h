#ifndef SOC_FILESYSTEN_FILESYSTEM_H
#define SOC_FILESYSTEN_FILESYSTEM_H

namespace Soc
{
	class Goods;
	class Harbor;


	namespace Filesystem {
		class Filesystem //NOLINT
		{
		public:
			virtual ~Filesystem() = default;
			virtual std::map<int, std::shared_ptr<Harbor>> harbors() = 0;
			virtual std::map<int, Goods> goods(int harbor_id) = 0;
		};
	}
}

#endif //SOC_FILESYSTEN_FILESYSTEM_H
