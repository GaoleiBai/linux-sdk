#include "math.h"
#include <math.h>

Math::Math()
{
}

Math::~Math()
{
}

double Math::PI()
{
	return M_PI;
}

double Math::E()
{
	return M_E;
}

double Math::Sin(double r)
{
	return sin(r);
}

double Math::Cos(double r)
{
	return cos(r);
}

double Math::Tan(double r)
{
	return tan(r);
}

double Math::ASin(double r)
{
	return asin(r);
}

double Math::ACos(double r)
{
	return acos(r);
}

double Math::ATan(double r)
{
	return atan(r);
}

double Math::ATan(double x, double y)
{
	return atan2(x, y);
}

double Math::SinH(double r)
{
	return sinh(r);
}

double Math::CosH(double r)
{
	return cosh(r);
}

double Math::TanH(double r)
{
	return tanh(r);
}
