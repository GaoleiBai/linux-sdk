/* Copyright (C) 2012, 2013
   Daniel Mosquera Villanueva (daniel.m.v@terra.es)
   This file is part of LFC Library.

   LFC Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   LFC Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with LFC Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA. or see http://www.gnu.org/licenses/. */
   
   
#ifndef MATH_H
#define MATH_H

class Math {

public:

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
