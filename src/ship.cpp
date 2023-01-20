#include <ship.h>

namespace Soc
{
	std::ostream& operator<<(std::ostream& os, const Ship& obj)
	{
		return os
			<< " Type: "
			<< std::right << std::setw(17) << obj.m_type  << " |"
			<< " Price: "
			<< std::right << std::setw(7) << obj.m_price  << " |"
			<< " Cargo capacity: "
			<< std::right << std::setw(3) << obj.m_cargo_max  << " |"
			<< " Cannon slots: "
			<< std::right << std::setw(3) << obj.m_cannons_max  << " |"
			<< " HP: "
			<< std::right << std::setw(3) << obj.m_hp  << " |"
			<< " Weight: "
			<< std::right << std::setw(6) << obj.m_weight_class  << " |"
			<< " Size: "
			<< std::right << std::setw(6) << obj.size();
	}
}
