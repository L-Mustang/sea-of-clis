#ifndef SOC_SHIP_TYPE_H
#define SOC_SHIP_TYPE_H

namespace Soc {
	enum class Ship_type
	{
		normal = 0,
		light,
		heavy
	};

	inline std::ostream& operator <<(std::ostream& os, const Ship_type& obj)
	{
		switch (obj)
		{
		case Ship_type::normal:
			{
				os << "Normal";
				break;
			}
		case Ship_type::light:
			{
				os << "Light";
				break;
			}
		case Ship_type::heavy:
			{
				os << "Heavy";
				break;
			}
		}
		return os;
	}
}

#endif // SOC_SHIP_TYPE_H
