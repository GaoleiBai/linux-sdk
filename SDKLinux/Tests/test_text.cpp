#include <stdio.h>
#include "test_text.h"
#include "../LFC/LFC.h"

TestText::TestText()
{
}

TestText::~TestText()
{
}

int TestText::Perform()
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
	
	return 0;
}
