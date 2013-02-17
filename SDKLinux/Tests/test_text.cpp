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
   
   
#include <stdio.h>
#include <string.h>
#include "test_text.h"
#include "../LFC/LFC.h"

TestText::TestText()
{
}

TestText::~TestText()
{
}

int TestText::PerformAnsi()
{
	Text a = "HÓLA";
	Text b = "Mundo\r\n";
	a = a + " cruel " + 5 + " " + b;
	StdOut::PrintLine(a);
	StdOut::PrintLine((Text)"Hola " + 5.25);
	
	NObject o;
	Text compnobject = "NObject";
	StdOut::PrintLine(o.ToText());
	if (compnobject != o.ToText()) {
		StdOut::PrintLine("NObject::ToText() error!!!");
		return -1;
	}
	
	if (a != a.ToText()) {
		StdOut::PrintLine("Text::ToText() error!!!");
		return -1;
	}
	
	const char *test1str = "HÓLA cruel 5 Mundo\r\n";
	if (a != test1str) {
		StdOut::PrintLine("Test 1 Error");
		return -1;
	}
	
	Text t1str = test1str;
	for (int i=0; i<a.Length(); i++) {
		printf("%C", a[i]);
		if (a[i] != t1str[i]) {
			StdOut::PrintLine("Test 2 Error\r\n");
		}
	}
	printf("\r\n");
	
	Text *u = new Text("u");
	Text *v = new Text("v");
	*u = *u + *v + 5 + "\r\n";
	StdOut::Print(*u);
	if (*u != "uv5\r\n") {
		printf("Test 3 Error\r\n");
		return -1;
	}
	delete u;
	delete v;
	
	a = "Este texto es una caca\r\n";
	b = a.SubText(11);
	StdOut::Print(b);
	if (b != "es una caca\r\n") {
		printf("Subtext(a); no funciona\r\n");
		return -1;
	}
	
	Text c = a.SubText(5, 5) + "\r\n";
	StdOut::Print(c);
	if (c != "texto\r\n") {
		printf("SubText(a, b); no funciona\r\n");
		return -1;
	}
	
	Text splitChars = ",";
	Text textToSplit = "1,2,3,4,5,6,7,8,9,";
	Collection<Text *> items = textToSplit.Split(",", false);
	for (int i=0; i<items.Count(); i++) {
		StdOut::PrintLine(*items[i]);
	}
	Collection<Text *> generatedItems;
	for (int i = 1; i < 10; i++)
		generatedItems.Add(new Text(i));
	generatedItems.Add(new Text());
	for (int i = 0; i < 9; i++) {	// El décimo item no se puede comparar porque es de longitud 0
		if (*items[i] != *generatedItems[i] || !items[i]->Equals(*generatedItems[i])) {
			StdOut::PrintLine("Error procesando y comparando items.");
			return -1;
		}
		if (!items[i]->StartsWith(*generatedItems[i]) || !items[i]->EndsWith(*generatedItems[i])) {
			StdOut::PrintLine("Error comprobando principios y finales de cadenas.");
			return -1;
		}
		delete items[i];
		delete generatedItems[i];
	}
	
	Text smallText = "Poco";
	Text largeText = "SuperCalifragilisticoEspiralidoso";
	if (!largeText.StartsWith("SuperC") || 
		!largeText.EndsWith("lidoso") || 
		smallText.StartsWith("Pocos") || 
		smallText.EndsWith("aPoco")) {
		StdOut::PrintLine("Error comparando principio y final.");
		return -1;
	}
	
	Text add = (Text)"Lucky " + true + " " + false + " " + 8 + " " + 7.0f + " " + 9.0 + "\r\n";
	StdOut::Print(add);
	if (add != "Lucky true false 8 7,000000 9,000000\r\n") {
		StdOut::PrintLine("La agregación no ha funcionado");
		return -1;
	}
	
	Text contains = "Jotiu";
	if (!contains.Contains("Jo") || !contains.Contains("tiu") || !contains.Contains("Jotiu") || contains.Contains("ota")) {
		StdOut::PrintLine("La contención no ha funcionado.");
		return -1;
	} 
	
	Collection<Text *> gta;
	Collection<Text *> gtb;
	for (char cc = 'a'; cc < 'z'; cc++) {
		gta.Add(new Text(cc));
		gtb.Add(new Text((char)(cc + 1)));
	}
	for (int i=0; i<gta.Count(); i++) {
		if (!(*gta[i] < *gtb[i])) {
			StdOut::PrintLine("La comparación no ha funcionado.");
			return -1;
		}
	}
	
	Text toTrim  = ";;;...   Hola   ;;;...";
	Collection<char> colTrim((char *)";. ");
	if (toTrim.TrimLeft(colTrim) != "Hola   ;;;..." ||
		toTrim.TrimRight(colTrim) != ";;;...   Hola" ||
		toTrim.Trim(colTrim) != "Hola")
	{
		StdOut::PrintLine("Trim no ha funcionado.");
		return -1;
	}
	
	Text treg = "4.5.6.7";
	if (!treg.CheckRegExpr("^[0-9].[0-9].[0-9].[0-9]$", true)) {
		StdOut::PrintLine("Text::CheckRegExpr error");
		return -1;
	}
	if (treg.CheckRegExpr("^a.[0-9].[0-9].[0-9]$", true)) {
		StdOut::PrintLine("Text::CheckRegExpr error");
		return -1;
	}
	
	Collection<Text *> creg = treg.GetRegExprMatches("[0-9]", true);
	for (int i=0; i<creg.Count(); i++) StdOut::PrintLine(*creg[i]);
	if (creg.Count() != 4) {
		StdOut::PrintLine("Text::GetRegExprMatches error");
		return -1;
	}
	if (*creg[0] != "4" || *creg[1] != "5" || *creg[2] != "6" || *creg[3] != "7") {
		StdOut::PrintLine("Text::GetRegExptMatches error");
		return -1;
	}
	
	return 0;
}

int TestText::PerformWide()
{
	short int sint = 1000;
	long int lint = 200000000000l;
	
	Text tsint = sint;
	Text tlint = lint;
	tsint = tsint + L"\r\n" + 5;
	tsint += L"\r\n";
	tlint += L"\r\n";
	StdOut::Print(tsint);
	StdOut::Print(tlint);
	
	Text hm = L"Hola mundo.\r\n";
	Text hpm = "Hola";
	hpm = hpm + " mundo.\r\n";
	if (hm != hpm || hm > hpm || hm < hpm || !(hm >= hpm) || !(hm <= hpm )) {
		printf("Comparison didn't work!\r\n");
		return -1;
	}
	
	Text localeup = hm.ToUpper();
	Text localelow = hm.ToLower();
	
	
	Text a = L"HOLA";
	Text b = L"Mundo\r\n";
	a = a + L" cruel " + 5 + L" " + b;
	StdOut::Print(a);
	
	const wchar_t *test1str = L"HOLA cruel 5 Mundo\r\n";
	if (a != test1str) {
		StdOut::Print("Test 1 Error\r\n");
		return -1;
	}
	
	for (int i=0; i<a.Length(); i++) {
		printf("%c", a[i]);
		if (a[i] != test1str[i]) {
			StdOut::Print("Test 2 Error\r\n");
		}
	}
	printf("\r\n");
	
	Text *u = new Text(L"u");
	Text *v = new Text(L"v");
	*u = *u + *v + 5 + L"\r\n";
	StdOut::PrintLine(*u);
	if (*u != L"uv5\r\n") {
		printf("Test 3 Error\r\n");
		return -1;
	}
	delete u;
	delete v;
	
	a = L"Este texto es una caca\r\n";
	b = a.SubText(11);
	StdOut::Print(b);
	if (b != L"es una caca\r\n") return -1;
	
	Text c = a.SubText(5, 5) + L"\r\n";
	StdOut::Print(c);
	if (c != L"texto\r\n") return -1;
	
	Text splitChars = L",";
	Text textToSplit = L"1,2,3,4,5,6,7,8,9,";
	Collection<Text *> items = textToSplit.Split(splitChars, false);
	for (int i=0; i<items.Count(); i++) {
		StdOut::PrintLine(items[i]);
	}
	Collection<Text *> generatedItems;
	for (int i = 1; i < 10; i++)
		generatedItems.Add(new Text(i));
	generatedItems.Add(new Text());
	for (int i = 0; i < 9; i++) {
		if (*items[i] != *generatedItems[i] || !items[i]->Equals(*generatedItems[i])) {
			StdOut::Print("Error procesando y comparando items.\r\n");
			return -1;
		}
		if (!items[i]->StartsWith(*generatedItems[i]) || !items[i]->EndsWith(*generatedItems[i])) {
			StdOut::Print("Error comprobando principios y finales de cadenas.\r\n");
			return -1;
		}
		delete items[i];
		delete generatedItems[i];
	}
	
	Text smallText = L"Poco";
	Text largeText = L"SuperCalifragilisticoEspiralidoso";
	if (!largeText.StartsWith(L"SuperC") || 
		!largeText.EndsWith(L"lidoso") || 
		smallText.StartsWith(L"Pocos") || 
		smallText.EndsWith(L"aPoco")) {
		printf("Error comparando principio y final.\r\n");
		return -1;
	}
	
	Text add;
	add += L"Lucky ";
	add += true;
	add += " ";
	add += false;
	add += " ";
	add += 8;
	add += " ";
	add += 7.0f;
	add += " ";
	add += 9.0;
	add += L"\r\n";
	StdOut::Print(add);
	if (add != L"Lucky true false 8 7,000000 9,000000\r\n") {
		StdOut::Print("La agregación no ha funcionado\r\n");
		return -1;
	}
	
	Text contains = L"Jotiu";
	if (!contains.Contains(L"Jo") || !contains.Contains(L"tiu") || !contains.Contains(L"Jotiu") || contains.Contains(L"ota")) {
		StdOut::Print("La contención no ha funcionado.\r\n");
		return -1;
	}
	
	Collection<Text *> gta;
	Collection<Text *> gtb;
	for (wchar_t cc = L'a'; cc < L'z'; cc++) {
		gta.Add(new Text(cc));
		gtb.Add(new Text((wchar_t)(cc + 1)));
	}
	for (int i=0; i<gta.Count(); i++) {
		if (!(*gta[i] < *gtb[i]) || 
			!(*gta[i] <= *gtb[i]) || 
			!(*gtb[i] >= *gta[i]) || 
			!(*gtb[i] > *gta[i])) {
			StdOut::Print("La comparación no ha funcionado.\r\n");
			return -1;
		}
	}
	
	Text ss("."), tt(" ");
	Text replacement = "a b c d e f g h i j ";
	Text rrr = replacement.Replace(" ", ",");
	Text sss = rrr.Replace(L",", L".");
	Text ttt = sss.Replace(ss, tt);
	Text uuu = replacement.Replace(",", ".");
	Text vvv = replacement.Replace("a", "b");
	if (replacement != ttt) {
		StdOut::Print("Replacement doesn't work!!!\r\n");
		return -1;
	}
	
	Text toTrim  = L";;;...   Hola   ;;;...";
	Collection<wchar_t> colTrim;
	colTrim.AddRange((wchar_t *)L";. ");
	if (toTrim.TrimLeft(colTrim) != L"Hola   ;;;..." ||
		toTrim.TrimRight(colTrim) != L";;;...   Hola" ||
		toTrim.Trim(colTrim) != L"Hola")
	{
		StdOut::Print("Trim no ha funcionado.\r\n");
		return -1;
	}
	
	const char *mbs = "En la imágen se ve que el camión tiene cañas en las ruedas.\r\n";
	Locale::SetLocale("");
	Text tombs(mbs);
	StdOut::Print(tombs);
	char cadena[1000];
	tombs.GetAnsiString(cadena, 1000);
	if (strcmp(mbs, cadena) != 0) {
		StdOut::Print("GetAnsiString didn't work.\r\n");
		return -1;
	}
	
	Text cmpA = "aaa";
	Text cmpB = "bbb";
	Text cmpC = "aaa";
	printf("%d\r\n", cmpA.Compare(cmpB));
	printf("%d\r\n", cmpB.Compare(cmpA));
	printf("%d\r\n", cmpC.Compare(cmpA));
	printf("%d\r\n", cmpC.Compare("aaa"));
	printf("%d\r\n", cmpC.Compare(L"aaa"));
	if (cmpA.Compare(cmpB) > 0 || cmpB.Compare(cmpA) < 0 || 
		cmpA.Compare(cmpB) >= 0 || cmpB.Compare(cmpA) <= 0 ||
		cmpC.Compare(cmpA) != 0 || !(cmpC.Compare("aaa") == 0))
	{
		StdOut::PrintLine("Compare doesn't work!");
		return -1;
	}
	
	return 0;
}
