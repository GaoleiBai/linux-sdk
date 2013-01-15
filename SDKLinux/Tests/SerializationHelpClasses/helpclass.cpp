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
	nobjectcollection->Add(new Text(atext));
	nobjectcollection->Add(new DateTime(adatetime));
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
	nobjectcollection->DeleteAndClear();
	nobjectdictionary->DeleteAndClear();
	delete atext;
	delete adatetime;
	delete nobjectcollection;
	delete nobjectdictionary;
	delete abuffer;
	delete atextbuffer;
}

NObject *HelpClass::NewInstance()
{
	return new HelpClass();
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
	((Serializator *)&s)->Put(ndouble);
	((Serializator *)&s)->Put(nlongdouble);
	((Serializator *)&s)->Put(*atext);
	((Serializator *)&s)->Put(*adatetime);
	((Serializator *)&s)->Put(*nobjectcollection);
	((Serializator *)&s)->Put(*nobjectdictionary);
	((Serializator *)&s)->Put(*abuffer);
	((Serializator *)&s)->Put(*atextbuffer);
}

void HelpClass::Deserialize(const Serializator &s)
{
	Text *oldtext = atext;
	DateTime *olddatetime = adatetime;
	NObjectCollection *oldnobjectcollection = nobjectcollection;
	NObjectDictionary *oldnobjectdictionary = nobjectdictionary;
	Buffer *oldbuffer = abuffer;
	TextBuffer *oldtextbuffer = atextbuffer;
	
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
	nfloat = ((Serializator *)&s)->GetFloat();
	ndouble = ((Serializator *)&s)->GetDouble();
	nlongdouble = ((Serializator *)&s)->GetLongDouble();
	atext = (Text *)((Serializator *)&s)->GetNObject();
	adatetime = (DateTime *)((Serializator *)&s)->GetNObject();
	nobjectcollection = (NObjectCollection *)((Serializator *)&s)->GetNObject();
	nobjectdictionary = (NObjectDictionary *)((Serializator *)&s)->GetNObject();
	abuffer = (Buffer *)((Serializator *)&s)->GetNObject();
	atextbuffer = (TextBuffer *)((Serializator *)&s)->GetNObject();
	
	if (nchar != 1 || nshort != 2 || nint != 3 || nlong != 4 || nlonglong != 5 ||
		nuchar != 6 || nushort != 7 || nuint != 8 || nulong != 9 || nulonglong != 10 ||
		nfloat != 11 || ndouble != 12 || nlongdouble != 13)
		{
			throw new Exception("Numbers not propertly deserializated", __FILE__, __LINE__, __func__);
		}
	
	if (*oldtext != *atext) 
		throw new Exception("Text not propertly deserializated", __FILE__, __LINE__, __func__);
	if (*olddatetime != *adatetime)
		throw new Exception("DateTime not propertly deserializated", __FILE__, __LINE__, __func__);
	if (oldnobjectcollection->ToText() != nobjectcollection->ToText())
		throw new Exception("NObjectCollection not propertly deserializated", __FILE__, __LINE__, __func__);
	if (oldnobjectdictionary->ToText() != nobjectdictionary->ToText())
		throw new Exception("NObjectDictionary not propertly deserializated", __FILE__, __LINE__, __func__);
	if (*oldbuffer != *abuffer)
		throw new Exception("Buffer not propertly deserializated", __FILE__, __LINE__, __func__);
	if (oldtextbuffer->ToText() != atextbuffer->ToText())
		throw new Exception("TextBuffer not propertly deserializated", __FILE__, __LINE__, __func__);
		
	oldnobjectcollection->DeleteAndClear();
	oldnobjectdictionary->DeleteAndClear();
	delete oldtext;
	delete olddatetime;
	delete oldnobjectcollection;
	delete oldnobjectdictionary;
	delete oldbuffer;
	delete oldtextbuffer;
}

