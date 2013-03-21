/* 
* LFC Library - Linux toolkit
* 
* Copyright (C) 2012, 2013 Daniel Mosquera Villanueva 
* (milkatoffeecuco@gmail.com)
* This file is part of LFC Library.
* 
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2.1 of the License, or (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this library. If not, see <http://www.gnu.org/licenses/>.
*
**/
#include "testnumeric.h"
#include "../LFC/LFC.h"
#include <float.h>

TestNumeric::TestNumeric()
{
}

TestNumeric::~TestNumeric()
{
}

int TestNumeric::Perform()
{
	NBool b = false;
	
	NChar c = 'c';
	NShort s = 5001;
	NInt i = 2345678;
	NLong l = 200167896;
	NLongLong ll = 200167896345;
	
	NUChar uc = 'c';
	NUShort us = 5001;
	NUInt ui = 2345678;
	NULong ul = 200167896;
	NULongLong ull = 200167896345;

	NChar mc = -'c';
	NShort ms = -5001;
	NInt mi = -2345678;
	NLong ml = -200167896;
	NLongLong mll = -200167896345;
	
	NFloat f = -1234.5f;
	NDouble d = 128.765567;
	NLongDouble ld = -1e300l;
	
	try {
		if (b.Value() != false) throw new Exception("NBool error", __FILE__, __LINE__, __func__);
		
		if (c.Value() != 'c') throw new Exception("NChar error", __FILE__, __LINE__, __func__);
		if (s.Value() != 5001) throw new Exception("NShort error", __FILE__, __LINE__, __func__);
		if (i.Value() != 2345678) throw new Exception("NInt error", __FILE__, __LINE__, __func__);
		if (l.Value() != 200167896) throw new Exception("NLong error", __FILE__, __LINE__, __func__);
		if (ll.Value() != 200167896345) throw new Exception("NLongLong error", __FILE__, __LINE__, __func__);

		if (uc.Value() != 'c') throw new Exception("NUChar error", __FILE__, __LINE__, __func__);
		if (us.Value() != 5001) throw new Exception("NUShort error", __FILE__, __LINE__, __func__);
		if (ui.Value() != 2345678) throw new Exception("NUInt error", __FILE__, __LINE__, __func__);
		if (ul.Value() != 200167896) throw new Exception("NULong error", __FILE__, __LINE__, __func__);
		if (ull.Value() != 200167896345) throw new Exception("NULongLong error", __FILE__, __LINE__, __func__);
		
		if (mc.Value() != -'c') throw new Exception("NChar error", __FILE__, __LINE__, __func__);
		if (ms.Value() != -5001) throw new Exception("NShort error", __FILE__, __LINE__, __func__);
		if (mi.Value() != -2345678) throw new Exception("NInt error", __FILE__, __LINE__, __func__);
		if (ml.Value() != -200167896) throw new Exception("NLong error", __FILE__, __LINE__, __func__);
		if (mll.Value() != -200167896345) throw new Exception("NLongLong error", __FILE__, __LINE__, __func__);
		
		if (f.Value() != -1234.5f) throw new Exception("NFLoat error", __FILE__, __LINE__, __func__);
		if (d.Value() != 128.765567) throw new Exception("NDouble error", __FILE__, __LINE__, __func__);
		if (ld.Value() != -1e300l) throw new Exception("NLongDouble error", __FILE__, __LINE__, __func__);
		
		NBool b1;
		b1 = NBool::Parse("true");
		if (b1.Value() != true) throw new Exception("NBool::Parse error", __FILE__, __LINE__, __func__);
		b1 = NBool::Parse("false");
		if (b1.Value() != false) throw new Exception("NBool::Parse error", __FILE__, __LINE__, __func__);
		bool sb;
		if (NBool::TryParse("porca miseria!!!", sb)) throw new Exception("NBool cannot parse wrong string", __FILE__, __LINE__, __func__); 
		NBool b2(false);
		if (!b1.Equals(b2)) throw new Exception("NBool::Equals error", __FILE__, __LINE__, __func__);
		
		NLongLong nll1;
		NChar c1;
		for (int i=-128; i<=127; i++) {
			nll1 = (NLongLong)i;
			c1 = NChar::Parse(nll1.ToText());
			if (c1.Value() != nll1.Value()) throw new Exception("NChar::Value error", __FILE__, __LINE__, __func__);
			if (c1.ToText("%d") != nll1.ToText()) throw new Exception("NChar::ToText error", __FILE__, __LINE__, __func__);
		}
		char sc;
		if (NChar::TryParse("-129", sc)) { StdOut::PrintLine("NChar cannot parse '-129'"); return -1; }
		if (NChar::TryParse("128", sc)) { StdOut::PrintLine("NChar cannot parse '128'"); return -1; }
		if (NChar::MaxValue() != 127) throw new Exception("NChar::MaxValue error", __FILE__, __LINE__, __func__);
		if (NChar::MinValue() != -128) throw new Exception("NChar::MinValue error", __FILE__, __LINE__, __func__);
		c1 = NChar::Parse((Text)(int)'c');
		NChar c2('c');
		if (!c1.Equals(c2)) throw new Exception("NChar::Equals error", __FILE__, __LINE__, __func__);
		
		NShort s1;
		for (int i=-32768; i<=32767; i++) {
			nll1 = (NLongLong)i;
			s1 = NShort::Parse(nll1.ToText());
			if (s1.Value() != nll1.Value()) throw new Exception("NShort::Value error", __FILE__, __LINE__, __func__);
			if (s1.ToText() != nll1.ToText()) throw new Exception("NShort::ToText error", __FILE__, __LINE__, __func__);
		}
		short ss;
		if (NShort::TryParse("-32769", ss)) { StdOut::PrintLine("NShort cannot parse -32769"); return -1; }
		if (NShort::TryParse("32768", ss)) { StdOut::PrintLine("NShort cannot parse 32768"); return -1; }
		if (NShort::MaxValue() != 32767) throw new Exception("NShort::MaxValue error", __FILE__, __LINE__, __func__);
		if (NShort::MinValue() != -32768) throw new Exception("NShort::MinValue error", __FILE__, __LINE__, __func__);
		s1 = NShort::Parse("21");
		NShort s2(21);
		if (!s1.Equals(s2)) throw new Exception("NShort::Equals error", __FILE__, __LINE__, __func__);
		
		NInt i1;
		for (int i=-2147483648; i<2147483647; i++) {
			nll1 = (NLongLong)i;
			i1 = NInt::Parse(nll1.ToText());
			if (i1.Value() != nll1.Value()) throw new Exception("NInt::Value error", __FILE__, __LINE__, __func__);
			if (i1.ToText() != nll1.ToText()) throw new Exception("NInt::ToText error", __FILE__, __LINE__, __func__);
			if (i == NInt::MinValue() + 2000) i = -2000;
			if (i == 2000) i = NInt::MaxValue() - 2000;
		}
		int si;
		if (NInt::TryParse("-2147483649", si)) { StdOut::PrintLine("NInt cannot parse -2147453649"); return -1; }
		if (NInt::TryParse("2147483648", si)) { StdOut::PrintLine("NInt cannot parse 2147483648"); return -1; }
		if (NInt::MaxValue() != 2147483647) throw new Exception("NInt::MaxValue error", __FILE__, __LINE__, __func__);
		if (NInt::MinValue() != -2147483648) throw new Exception("NInt::MinValue error", __FILE__, __LINE__, __func__);
		i1 = NInt::Parse("4");
		NInt i2(4);
		if (!i1.Equals(i2)) throw new Exception("NInt::Equals error", __FILE__, __LINE__, __func__);
		
		NLong l1;
		for (long i=NLong::MinValue(); i<NLong::MaxValue(); i++) {
			nll1 = (NLongLong)i;
			l1 = NLong::Parse(nll1.ToText());
			if (l1.Value() != nll1.Value()) throw new Exception("NLong::Value error", __FILE__, __LINE__, __func__);
			if (l1.ToText() != nll1.ToText()) throw new Exception("NLong::ToText error", __FILE__, __LINE__, __func__);
			if (i == NLong::MinValue() + 2000) i = -2000;
			if (i == 2000) i = NLong::MaxValue() - 2000;
		}
		long sl;		
		if (NLong::TryParse("-9223372036854775809", sl)) { StdOut::PrintLine("NLong cannot parse -9223372036854775809"); return -1; }
		if (NLong::TryParse("9223372036854775808", sl)) { StdOut::PrintLine("NLong cannot parse 9223372036854775808"); return -1; }
		if (NLong::MaxValue() != 9223372036854775807L) throw new Exception("NLong::MaxValue error", __FILE__, __LINE__, __func__);
		if (NLong::MinValue() != -NLong::MaxValue() -1L) throw new Exception("NLong::MinValue error", __FILE__, __LINE__, __func__);
		l1 = NLong::Parse("34");
		NLong l2(34);
		if (!l1.Equals(l2)) throw new Exception("NLong::Equals error", __FILE__, __LINE__, __func__);
		
		NLongLong ll1;
		for (long long i=NLongLong::MinValue(); i<NLongLong::MaxValue(); i++) {
			nll1 = (NLongLong)i;
			ll1 = NLongLong::Parse(nll1.ToText());
			if (ll1.Value() != nll1.Value()) throw new Exception("NLongLong::Value error", __FILE__, __LINE__, __func__);
			if (ll1.ToText() != nll1.ToText()) throw new Exception("NLongLong::ToText error", __FILE__, __LINE__, __func__);
			if (i == NLongLong::MinValue() + 2000) i = -2000;
			if (i == 2000) i = NLongLong::MaxValue() - 2000;
		}
		long long sll;
		if (NLongLong::TryParse("-9223372036854775809L", sll)) { StdOut::PrintLine("NLongLong cannot parse -9223372036854775809"); return -1; }
		if (NLongLong::TryParse("9223372036854775808", sll)) { StdOut::PrintLine("NLongLong cannot parse 9223372036854775808"); return -1; }
		if (NLongLong::MaxValue() != 9223372036854775807L) throw new Exception("NLongLong::Maxvalue error", __FILE__, __LINE__, __func__);
		if (NLongLong::MinValue() != -NLongLong::MaxValue() - 1L) throw new Exception("NLongLong::MinValue error", __FILE__, __LINE__, __func__);
		ll1 = NLongLong::Parse("1222");
		NLongLong ll2(1222);
		if (!ll1.Equals(ll2)) throw new Exception("NLongLong::Equals error", __FILE__, __LINE__, __func__);
		
		NUChar uc1;
		for (long i = 0; i<NUChar::MaxValue(); i++) {
			nll1 = (NLongLong)i;
			uc1 = NUChar::Parse(nll1.ToText());
			if (uc1.Value() != nll1.Value()) throw new Exception("NUChar::Value error", __FILE__, __LINE__, __func__);
			if (uc1.ToText() != nll1.ToText()) throw new Exception("NUChar::ToText error", __FILE__, __LINE__, __func__);			
		}
		unsigned char sc1;
		if (NUChar::TryParse("-1", sc1)) { StdOut::PrintLine("NUChar cannot parse -1"); return -1; }
		if (NUChar::TryParse("256", sc1)) { StdOut::PrintLine("NUChar cannot parse 65536"); return -1; }
		if (NUChar::MinValue() != 0) throw new Exception("NUChar::MinValue error", __FILE__, __LINE__, __func__);
		if (NUChar::MaxValue() != 255) throw new Exception("NUChar::MaxValue error", __FILE__, __LINE__, __func__);
		uc1 = NUChar::Parse("22");
		NUChar uc2(22);
		if (!uc1.Equals(uc2)) throw new Exception("NUChar::Equals error", __FILE__, __LINE__, __func__);		
		
		NULongLong ull1;
		NUShort us1;
		for (unsigned long i = 0; i<NUShort::MaxValue(); i++) {
			ull1 = (NULongLong)i;
			us1 = NUShort::Parse(ull1.ToText());
			if (us1.Value() != ull1.Value()) throw new Exception("NUShort::Value error", __FILE__, __LINE__, __func__);
			if (us1.ToText() != ull1.ToText()) throw new Exception("NUShort::ToText error", __FILE__, __LINE__, __func__);
		}
		unsigned short ss1;
		if (NUShort::TryParse("-1", ss1)) { StdOut::PrintLine("NUShort cannot parse -1"); return -1; }
		if (NUShort::TryParse("65536", ss1)) { StdOut::PrintLine("NUShort cannor parse 65536"); return -1; }
		if (NUShort::MinValue() != 0) throw new Exception("NUShort::MinValue error", __FILE__, __LINE__, __func__);
		if (NUShort::MaxValue() != 65535) throw new Exception("NUShort::MaxValue error", __FILE__, __LINE__, __func__);
		us1 = NUShort::Parse("4000");
		NUShort us2(4000);
		if (!us1.Equals(us2)) throw new Exception("NUShort::Equals error", __FILE__, __LINE__, __func__);
		
		NUInt ui1;
		for (unsigned long i = 0; i<NUInt::MaxValue(); i++) {
			ull1 = (NULongLong)i;
			ui1 = NUInt::Parse(ull1.ToText());
			if (ui1.Value() != ull1.Value()) throw new Exception("NUInt::Value error", __FILE__, __LINE__, __func__);
			if (ui1.ToText() != ull1.ToText()) throw new Exception("NUInt::ToText error", __FILE__, __LINE__, __func__);
			if (i == 2000) i = NUInt::MaxValue() - 2000;
		}
		unsigned int si1;
		if (NUInt::TryParse("-1", si1)) { StdOut::PrintLine("NUInt cannot parse -1"); return -1; }
		if (NUInt::TryParse("4294967296", si1)) { StdOut::PrintLine("NUInt cannot parse -1"); return -1; }
		if (NUInt::MinValue() != 0) throw new Exception("NUInt::MinValue error", __FILE__, __LINE__, __func__);
		if (NUInt::MaxValue() != 4294967295U) throw new Exception("NUInt::MaxValue error", __FILE__, __LINE__, __func__);
		ui1 = NUInt::Parse("45000000");
		NUInt ui2(45000000);
		if (!ui1.Equals(ui2)) throw new Exception("NUInt::Equals error", __FILE__, __LINE__, __func__);
		
		NULong ul1;
		for (unsigned long i = 0; i<NULong::MaxValue(); i++) {
			ull1 = (NULongLong)i;
			ul1 = NULong::Parse(ull1.ToText());
			if (ul1.Value() != ull1.Value()) throw new Exception("NULong::Value error", __FILE__, __LINE__, __func__);
			if (ul1.ToText() != ull1.ToText()) throw new Exception("NULong::ToText error", __FILE__, __LINE__, __func__);
			if (i == 2000) i = NULong::MaxValue() - 2000;
		}
		unsigned long sul1;
		if (NULong::TryParse("-1", sul1)) { StdOut::PrintLine("NULong cannot parse -1"); return -1; }
		if (NULong::TryParse("18446744073709551616", sul1)) { StdOut::PrintLine("NULong cannot parse "); return -1; }
		if (NULong::MinValue() != 0) throw new Exception("NULong::MinValue error", __FILE__, __LINE__, __func__);
		if (NULong::MaxValue() != 18446744073709551615UL) throw new Exception("NULong::MaxValue error", __FILE__, __LINE__, __func__);
		ul1 = NULong::Parse("4000000001");
		NULong ul2(4000000001);
		if (!ul1.Equals(ul2)) throw new Exception("NULong::Equals error", __FILE__, __LINE__, __func__);
		
		NULongLong null1;
		for (unsigned long i = 0; i<NULongLong::MaxValue(); i++) {
			ull1 = (NULongLong)i;
			null1 = NULongLong::Parse(ull1.ToText());
			if (null1.Value() != ull1.Value()) throw new Exception("NULongLong::Value error", __FILE__, __LINE__, __func__);
			if (null1.ToText() != ull1.ToText()) throw new Exception("NULongLong::ToText error", __FILE__, __LINE__, __func__);
			if (i == 2000) i = NULong::MaxValue() - 2000;
		}
		unsigned long long sull1;
		if (NULongLong::TryParse("-1", sull1)) { StdOut::PrintLine("NULongLong cannot parse -1"); return -1; }
		if (NULongLong::TryParse("18446744073709551617", sull1)) { StdOut::PrintLine("NULongLong cannot parse 18446744073709551617"); return -1; }
		if (NULongLong::MinValue() != 0) throw new Exception("NULongLong::MinValue error", __FILE__, __LINE__, __func__);
		if (NULongLong::MaxValue() != 18446744073709551615UL) throw new Exception("NULongLong::MaxValue error", __FILE__, __LINE__, __func__);
		
		NFloat nf1;
		NFloat nf2;
		for (float i = -1e37; i<1e37; i += 1e30) {
			nf1 = (NFloat)i;
			nf2 = NFloat::Parse(nf1.ToText("%10.10e"));
			if (nf1.Value() != nf2.Value()) throw new Exception("NFloat::Value error", __FILE__, __LINE__, __func__);
			if (nf1.ToText("%10.10e") != nf2.ToText("%10.10e")) throw new Exception("NFloat::ToText error", __FILE__, __LINE__, __func__);
			if (i > -1e37 + 2000e30 && i < -2000e30) i = -2000e30;
			else if (i > 2000e30 && i < 1e37 - 2000e30) i = 1e37 - 2000e30;
		}
		for (float i = -1000; i<1000; i += 1) {
			nf1 = (NFloat)i;
			nf2 = NFloat::Parse(nf1.ToText());
			if (nf1.Value() != nf2.Value()) throw new Exception("NFloat::Value error", __FILE__, __LINE__, __func__);
			if (nf1.ToText() != nf2.ToText()) throw new Exception("NFloat::ToText error", __FILE__, __LINE__, __func__);
		}
		float sf1;
		StdOut::PrintLine(((NFloat)NFloat::MaxValue()).ToText("%10.40e"));
		if (NFloat::TryParse("-1e39", sf1)) throw new Exception("NFloat cannot parse 1e-38", __FILE__, __LINE__, __func__);
		if (NFloat::TryParse("1e39", sf1)) throw new Exception("NFloat cannot parse 1e38", __FILE__, __LINE__, __func__);
		if (NFloat::MinValue() != -3.4028234663852885981170418348451692544000e+38) throw new Exception("NFloat::MinValue error", __FILE__, __LINE__, __func__);
		if (NFloat::MaxValue() != 3.4028234663852885981170418348451692544000e+38) throw new Exception("NFloat::MaxValue error", __FILE__, __LINE__, __func__);
		if (!NFloat::IsFinite(4)) throw new Exception("NFloat::IsFinite error", __FILE__, __LINE__, __func__);
		if (NFloat::IsFinite(NFloat::PositiveInfinity())) throw new Exception("NFloat::IsFinite PI error", __FILE__, __LINE__, __func__);
		if (NFloat::IsFinite(NFloat::NegativeInfinity())) throw new Exception("NFloat::IsFinite NI error", __FILE__, __LINE__, __func__);
		if (NFloat::IsNaN(4)) throw new Exception("NFloat::IsNaN error", __FILE__, __LINE__, __func__);
		if (!NFloat::IsNaN(NFloat::NaN())) throw new Exception("NFloat::NaN error", __FILE__, __LINE__, __func__);
		nf1 = 5000.501f;
		nf2 = 5000.501f;
		if (!nf1.Equals(nf2)) throw new Exception("NFloat::Equals error", __FILE__, __LINE__, __func__);
		
		NDouble nd1;
		NDouble nd2;
		StdOut::PrintLine(((NDouble)NDouble::MaxValue()).ToText("%10.60e"));
		for (double i=-1e308; i<1e308; i+=1e293) {
			nd2 = (NDouble)i;
			nd1 = NDouble::Parse(nd2.ToText("%10.20e"));
			if (nd1.Value() != nd2.Value()) throw new Exception("NDouble::Value error", __FILE__, __LINE__, __func__);
			if (nd1.ToText("%10.20e") != nd2.ToText("%10.20e")) throw new Exception("NDouble::ToText error", __FILE__, __LINE__, __func__);
			if (i > -1e308 + 2000e293 && i < -2000e293) i = -2000e293;
			else if (i > 2000e293 && i < 1e308 - 2000e293) i = 1e308 - 2000e293;
		}
		for (double i=-2000; i<2000; i++) {
			nd2 = (NDouble)i;
			nd1 = NDouble::Parse(nd2.ToText());
			if (nd1.Value() != nd2.Value()) throw new Exception("NDouble::Value error", __FILE__, __LINE__, __func__);
			if (nd1.ToText() != nd2.ToText()) throw new Exception("NDouble::ToText error", __FILE__, __LINE__, __func__);
		}
		double sd1;
		if (NDouble::TryParse("-2e308", sd1)) { StdOut::PrintLine("NDouble cannot parse -2e308"); return -1; }
		if (NDouble::TryParse("2e308", sd1)) { StdOut::PrintLine("NDouble cannot parse 2e308"); return -1; }
		if (NDouble::MaxValue() != DBL_MAX) throw new Exception("NDouble::MaxValue error", __FILE__, __LINE__, __func__);
		if (NDouble::MinValue() != -DBL_MAX) throw new Exception("NDouble::MinValue error", __FILE__, __LINE__, __func__);
		if (!NDouble::IsFinite(4)) throw new Exception("NDouble::IsFinite error", __FILE__, __LINE__, __func__);
		if (NDouble::IsFinite(NDouble::PositiveInfinity())) throw new Exception("NDouble::IsFinite PI error", __FILE__, __LINE__, __func__);
		if (NDouble::IsFinite(NDouble::NegativeInfinity())) throw new Exception("NDouble::IsFinite NI error", __FILE__, __LINE__, __func__);
		if (NDouble::IsNaN(4)) throw new Exception("NDouble::IsNaN error", __FILE__, __LINE__, __func__);
		if (!NDouble::IsNaN(NDouble::NaN())) throw new Exception("NDouble::NaN error", __FILE__, __LINE__, __func__);
		nd1 = 45.9978;
		nd2 = NDouble::Parse("45,9978");
		if (!nd1.Equals(nd2)) throw new Exception("NDouble::Equals error", __FILE__, __LINE__, __func__);
		
		NLongDouble nld1;
		NLongDouble nld2;
		StdOut::PrintLine(((NLongDouble)NLongDouble::MaxValue()).ToText("%10.60Le"));
		for (long double i=-1e4932L; i<1e4932L; i+=1e4915L) {
			nld2 = (NLongDouble)i;
			nld1 = NLongDouble::Parse(nld2.ToText("%10.60Le"));
			if (nld1.Value() != nld2.Value()) throw new Exception("NLongDouble::Value error", __FILE__, __LINE__, __func__);
			if (nld1.ToText("%10.60Le") != nld2.ToText("%10.60Le")) throw new Exception("NLongDouble::ToText error", __FILE__, __LINE__, __func__);
			if (i > -1e4932L + 2000e4915L && i<2000e4915L) i = 2000e4915L;
			else if (i > 2000e4915L && i < 1e4932L - 2000e4915L) i = 1e4932L - 2000e4915L;
		}
		for (long double i=-2000; i<2000; i+=1) {
			nld2 = (NLongDouble)i;
			nld1 = NLongDouble::Parse(nld2.ToText());
			if (nld1.Value() != nld2.Value()) throw new Exception("NLongDouble::Value error", __FILE__, __LINE__, __func__);
			if (nld1.ToText() != nld2.ToText()) throw new Exception("NLongDouble::ToText error", __FILE__, __LINE__, __func__);
		}
		long double sld1;
		if (NLongDouble::TryParse("-2e4932", sld1)) throw new Exception("NLongDouble cannot parse -2e4932", __FILE__, __LINE__, __func__);
		if (NLongDouble::TryParse("2e4932", sld1)) throw new Exception("NLongDouble cannot parse 2e4932", __FILE__, __LINE__, __func__);
		if (NLongDouble::MaxValue() != LDBL_MAX) throw new Exception("NLongDouble::MaxValue error", __FILE__, __LINE__, __func__);
		if (NLongDouble::MinValue() != -LDBL_MAX) throw new Exception("NLongDouble::MinValue error", __FILE__, __LINE__, __func__);
		if (!NLongDouble::IsFinite(4)) throw new Exception("NFloat::IsFinite error", __FILE__, __LINE__, __func__);
		if (NLongDouble::IsFinite(NLongDouble::PositiveInfinity())) throw new Exception("NFloat::IsFinite PI error", __FILE__, __LINE__, __func__);
		if (NLongDouble::IsFinite(NLongDouble::NegativeInfinity())) throw new Exception("NFloat::IsFinite NI error", __FILE__, __LINE__, __func__);
		if (NLongDouble::IsNaN(4)) throw new Exception("NFloat::IsNaN error", __FILE__, __LINE__, __func__);
		if (!NLongDouble::IsNaN(NLongDouble::NaN())) throw new Exception("NFloat::NaN error", __FILE__, __LINE__, __func__);
		nld1 = 62.3456l;
		nld2 = NLongDouble::Parse("62,3456");
		if (!nld1.Equals(nld2)) throw new Exception("NLongDouble::Equals error", __FILE__, __LINE__, __func__);
		
		int kk = 1;
	} catch (Exception *e) {
		delete e;
	}

	return 0;
}

