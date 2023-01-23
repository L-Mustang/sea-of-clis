#ifndef SOC_SHIP_TYPE_H
#define SOC_SHIP_TYPE_H

namespace Soc {
	enum class Ship_type : int
	{
		invalid = 0,
		normal = 1,
		light = 2,
		heavy = 3
	};

	std::ostream& operator<<(std::ostream& os, const Ship_type& obj);
}

#endif // SOC_SHIP_TYPE_H
