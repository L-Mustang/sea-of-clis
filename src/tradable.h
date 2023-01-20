#ifndef SOC_TRADABLE_H
#define SOC_TRADABLE_H

namespace Soc
{
	class Tradable
	{
	public:
		virtual ~Tradable() = default;
		[[nodiscard]] virtual int amount() const = 0;
		virtual void amount(int amount) = 0;
		[[nodiscard]] virtual int price() const = 0;
	};
}

#endif //SOC_TRADABLE_H
