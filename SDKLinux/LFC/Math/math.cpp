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

double Math::Exp(double n)
{
	return exp(n);
}

void Math::GetSigExp(double n, double &significant, int &exponent)
{
	significant = frexp(n, &exponent);
}

double Math::FromSigExp(double significant, int exponent)
{
	return ldexp(significant, exponent);
}

double Math::Log(double n)
{
	return log(n);
}

double Math::Log10(double n)
{
	return log10(n);
}

void Math::GetIntFrac(double n, double &integer_part, double &fractional_part)
{
	fractional_part = modf(n, &integer_part);
}

double Math::Pow(double x, double y)
{
	return pow(x, y);
}

double Math::Sqrt(double n)
{
	return sqrt(n);
}

double Math::Ceil(double n)
{
	return ceil(n);
}

double Math::Floor(double n)
{
	return floor(n);
}

double Math::Abs(double n)
{
	return fabs(n);
}

double Math::Mod(double numerator, double denominator)
{
	return fmod(numerator, denominator);
}