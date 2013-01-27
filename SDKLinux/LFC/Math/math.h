#ifndef MATH_H
#define MATH_H

class Math {

public:
	Math();
	virtual ~Math();

	static double PI();
	static double E();
	
	static double Sin(double r);
	static double Cos(double r);
	static double Tan(double r);
	static double ASin(double r);
	static double ACos(double r);
	static double ATan(double r);
	static double ATan(double x, double y);
	static double SinH(double r);
	static double CosH(double r);
	static double TanH(double r);
	static double Exp(double n);
	static void GetSigExp(double n, double &significant, int &exponent);
	static double FromSigExp(double significant, int exponent);
	static double Log(double n);
	static double Log10(double n);
	static void GetIntFrac(double n, double &integer_part, double &fractional_part);
	static double Pow(double x, double y);
	static double Sqrt(double n);
	static double Ceil(double n);
	static double Floor(double n);
	static double Abs(double n);
	static double Mod(double numerator, double denominator);

};

#endif // MATH_H
