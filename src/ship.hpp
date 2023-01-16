#ifndef SHIP_HPP
#define SHIP_HPP

namespace Soc {
	class Ship
	{
	public:
		Ship(int id, std::string type, int price, int cargo, int cannons, int hp, int peculiarity);
		~Ship();
		Ship(const Ship& other);
		Ship(Ship&& other) noexcept;
		Ship& operator=(const Ship& other);
		Ship& operator=(Ship&& other) noexcept;

	private:
		int m_id;
		std::string m_type;
		int m_price;
		int m_cargo;
		int m_cannons;
		int m_hp;
		int m_peculiarity;
	};
}

#endif // SHIP_HPP
