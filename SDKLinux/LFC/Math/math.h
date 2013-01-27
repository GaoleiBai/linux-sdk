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

};

#endif // MATH_H
