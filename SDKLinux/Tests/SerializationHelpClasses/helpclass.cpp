#include "helpclass.h"
#include <string.h>

HelpClass::HelpClass()
{
	nchar = 1;
	nshort = 2;
	nint = 3;
	nlong = 4;
	nlonglong = 5;
	nuchar = 6;
	nushort = 7;
	nuint = 8;
	nulong = 9;
	nulonglong = 10;
	nfloat = 11;
	ndouble = 12;
	nlongdouble = 13;
	atext = new Text("Hola mundo");
	adatetime = new DateTime(1977, 06, 03);
	
	Collection<Text *> variasPalabras = ((Text)"Esto es una prueba de varias palabras").Split(" ", false);
	
	nobjectcollection = new NObjectCollection();
	nobjectcollection->Add(atext);
	nobjectcollection->Add(adatetime);
	nobjectcollection->Add(new Text("Pedro"));
	nobjectcollection->Add(new Text("José Luis"));
	nobjectcollection->AddRange((Collection<NObject *>&)variasPalabras);
	
	nobjectdictionary = new NObjectDictionary();
	nobjectdictionary->SetKey(new Text("Manolo"), new Text("Machado"));
	nobjectdictionary->SetKey(new Text("Raul"), new Text("Perez"));
	nobjectdictionary->SetKey(new Text("Ana"), new Text("Polo"));
	nobjectdictionary->SetKey(new Text("Nerea"), new Text("González"));
	
	const char *eul = "En un lugar de la Mancha de cuyo nombre no quiero acordarme";
	abuffer = new Buffer(eul, strlen(eul));
	
	atextbuffer = new TextBuffer();
	atextbuffer->Append(nobjectcollection->ToText());
	atextbuffer->Append(nobjectdictionary->ToText());
}

HelpClass::~HelpClass()
{
	delete atext;
	delete adatetime;
	delete nobjectcollection;
	delete nobjectdictionary;
	delete abuffer;
	delete atextbuffer;
}

void HelpClass::Serialize(const Serializator &s)
{
	((Serializator *)&s)->Put(nchar);
	((Serializator *)&s)->Put(nshort);
	((Serializator *)&s)->Put(nint);
	((Serializator *)&s)->Put(nlong);
	((Serializator *)&s)->Put(nlonglong);
	((Serializator *)&s)->Put(nuchar);
	((Serializator *)&s)->Put(nushort);
	((Serializator *)&s)->Put(nuint);
	((Serializator *)&s)->Put(nulong);
	((Serializator *)&s)->Put(nulonglong);
	((Serializator *)&s)->Put(nfloat);
	((Serializator *)&s)->Put(nlong);
	((Serializator *)&s)->Put(nlonglong);
	((Serializator *)&s)->Put(*atext);
	((Serializator *)&s)->Put(*adatetime);
	((Serializator *)&s)->Put(*nobjectcollection);
	((Serializator *)&s)->Put(*nobjectdictionary);
	((Serializator *)&s)->Put(*abuffer);
	((Serializator *)&s)->Put(*atextbuffer);
}

NObject *HelpClass::Deserialize(const Serializator &s)
{
	nchar = ((Serializator *)&s)->GetChar();
	nshort = ((Serializator *)&s)->GetShort();
	nint = ((Serializator *)&s)->GetInt();
	nlong = ((Serializator *)&s)->GetLong();
	nlonglong = ((Serializator *)&s)->GetLongLong();
	nuchar = ((Serializator *)&s)->GetUChar();
	nushort = ((Serializator *)&s)->GetUShort();
	nuint = ((Serializator *)&s)->GetUInt();
	nulong = ((Serializator *)&s)->GetULong();
	nulonglong = ((Serializator *)&s)->GetULongLong();
	atext = (Text *)((Serializator *)&s)->GetNObject();
	adatetime = (DateTime *)((Serializator *)&s)->GetNObject();
	nobjectcollection = (NObjectCollection *)((Serializator *)&s)->GetNObject();
	nobjectdictionary = (NObjectDictionary *)((Serializator *)&s)->GetNObject();
	abuffer = (Buffer *)((Serializator *)&s)->GetNObject();
	atextbuffer = (TextBuffer *)((Serializator *)&s)->GetNObject();
}

