#include <stdio.h>
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
	Text a = "HOLA";
	Text b = "Mundo\r\n";
	a = a + " cruel " + 5 + " " + b;
	a.Print();
	
	const char *test1str = "HOLA cruel 5 Mundo\r\n";
	if (a != test1str) {
		printf("Test 1 Error\r\n");
		return -1;
	}
	
	for (int i=0; i<a.Length(); i++) {
		printf("%c", a[i]);
		if (a[i] != test1str[i]) {
			printf("Test 2 Error\r\n");
		}
	}
	printf("\r\n");
	
	Text *u = new Text("u");
	Text *v = new Text("v");
	*u = *u + *v + 5 + "\r\n";
	u->Print();
	if (*u != "uv5\r\n") {
		printf("Test 3 Error\r\n");
		return -1;
	}
	delete u;
	delete v;
	
	a = "Este texto es una caca\r\n";
	b = a.SubText(11);
	b.Print();
	if (b != "es una caca\r\n") return -1;
	
	Text c = a.SubText(5, 5) + "\r\n";
	c.Print();
	if (c != "texto\r\n") return -1;
	
	Collection<Text *> items;
	Text splitChars = ",";
	Text textToSplit = "1,2,3,4,5,6,7,8,9,";
	items = textToSplit.Split(items, splitChars, false);
	for (int i=0; i<items.Count(); i++) {
		items[i]->Print();
		printf("\r\n");
	}
	Collection<Text *> generatedItems;
	for (int i = 1; i < 10; i++)
		generatedItems.Add(new Text(i));
	generatedItems.Add(new Text());
	for (int i = 0; i < 10; i++) {
		if (*items[i] != *generatedItems[i] || !items[i]->Equals(*generatedItems[i])) {
			printf("Error procesando y comparando items.\r\n");
			return -1;
		}
		if (!items[i]->StartsWith(*generatedItems[i]) || !items[i]->EndsWith(*generatedItems[i])) {
			printf("Error comprobando principios y finales de cadenas.\r\n");
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
		printf("Error comparando principio y final.\r\n");
		return -1;
	}
	
	Text add;
	add += "Lucky ";
	add += true;
	add += " ";
	add += false;
	add += " ";
	add += 8;
	add += " ";
	add += 7.0f;
	add += " ";
	add += 9.0;
	add += "\r\n";
	add.Print();
	if (add != "Lucky true false 8 7.000000 9.000000\r\n") {
		printf("La agregación no ha funcionado\r\n");
		return -1;
	}
	
	Text contains = "Jotiu";
	if (!contains.Contains("Jo") || !contains.Contains("tiu") || !contains.Contains("Jotiu") || contains.Contains("ota")) {
		printf("La contención no ha funcionado.");
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
			printf("La comparación no ha funcionado.\r\n");
			return -1;
		}
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
	tsint.Print();
	tlint.Print();
	
	Text hm = L"Hola mundo.\r\n";
	Text hpm = "Hola";
	hpm = hpm + " mundo.\r\n";
	if (hm != hpm || hm > hpm || hm < hpm || !(hm >= hpm) || !(hm <= hpm )) {
		printf("Comparison didn't work!\r\n");
		return -1;
	}
	
	Text a = L"HOLA";
	Text b = L"Mundo\r\n";
	a = a + L" cruel " + 5 + L" " + b;
	a.Print();
	
	const wchar_t *test1str = L"HOLA cruel 5 Mundo\r\n";
	if (a != test1str) {
		printf("Test 1 Error\r\n");
		return -1;
	}
	
	for (int i=0; i<a.Length(); i++) {
		printf("%c", a[i]);
		if (a[i] != test1str[i]) {
			printf("Test 2 Error\r\n");
		}
	}
	printf("\r\n");
	
	Text *u = new Text(L"u");
	Text *v = new Text(L"v");
	*u = *u + *v + 5 + L"\r\n";
	u->Print();
	if (*u != L"uv5\r\n") {
		printf("Test 3 Error\r\n");
		return -1;
	}
	delete u;
	delete v;
	
	a = L"Este texto es una caca\r\n";
	b = a.SubText(11);
	b.Print();
	if (b != L"es una caca\r\n") return -1;
	
	Text c = a.SubText(5, 5) + L"\r\n";
	c.Print();
	if (c != L"texto\r\n") return -1;
	
	Collection<Text *> items;
	Text splitChars = L",";
	Text textToSplit = L"1,2,3,4,5,6,7,8,9,";
	items = textToSplit.Split(items, splitChars, false);
	for (int i=0; i<items.Count(); i++) {
		items[i]->Print();
		printf("\r\n");
	}
	Collection<Text *> generatedItems;
	for (int i = 1; i < 10; i++)
		generatedItems.Add(new Text(i));
	generatedItems.Add(new Text());
	for (int i = 0; i < 10; i++) {
		if (*items[i] != *generatedItems[i] || !items[i]->Equals(*generatedItems[i])) {
			printf("Error procesando y comparando items.\r\n");
			return -1;
		}
		if (!items[i]->StartsWith(*generatedItems[i]) || !items[i]->EndsWith(*generatedItems[i])) {
			printf("Error comprobando principios y finales de cadenas.\r\n");
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
	add.Print();
	if (add != L"Lucky true false 8 7.000000 9.000000\r\n") {
		printf("La agregación no ha funcionado\r\n");
		return -1;
	}
	
	Text contains = L"Jotiu";
	if (!contains.Contains(L"Jo") || !contains.Contains(L"tiu") || !contains.Contains(L"Jotiu") || contains.Contains(L"ota")) {
		printf("La contención no ha funcionado.\r\n");
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
			printf("La comparación no ha funcionado.\r\n");
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
		printf("Replacement doesn't work!!!\r\n");
		return -1;
	}
	
	return 0;
}
