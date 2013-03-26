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
#include "helpclass.h"
#include <string.h>

HelpClass::HelpClass()
{
	nbool = true;
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
	
	nnbool = new NBool(true);
	nnchar = new NChar('c');
	nnwchar = new NWChar(L'd');
	nnshort = new NShort(-22000);
	nnint = new NInt(-34000);
	nnlong = new NLong(-22000000000);
	nnlonglong = new NLongLong(-44000000000000L);
	nnuchar = new NUChar('c');
	nnushort = new NUShort(44000);
	nnuint = new NUInt(88000);
	nnulong = new NULong(44000000000);
	nnulonglong = new NULongLong(88000000000000L);
	nnfloat = new NFloat(-1e15f);
	nndouble = new NDouble(-1e40);
	nnlongdouble = new NLongDouble(-1e400L);
	nnsize = new NSize(400, 300);
	nnpoint = new NPoint(3, 4);
	nnrectangle = new NRectangle(4, 5, 6, 7);
	nncolor = new NColor(1, 0, 0, 0.5);
	
	Collection<Text *> variasPalabras = ((Text)"Esto es una prueba de varias palabras").Split(" ", false);
	
	nobjectcollection = new NObjectCollection();
	nobjectcollection->Add(new Text(atext));
	nobjectcollection->Add(new DateTime(adatetime));
	nobjectcollection->Add(new Text("Pedro"));
	nobjectcollection->Add(new Text("José Luis"));
	nobjectcollection->Add(new NBool(true));
	nobjectcollection->Add(new NChar('c'));
	nobjectcollection->Add(new NWChar(L'd'));
	nobjectcollection->Add(new NShort(-22000));
	nobjectcollection->Add(new NInt(-34000));
	nobjectcollection->Add(new NLong(-22000000000));
	nobjectcollection->Add(new NLongLong(-44000000000000L));
	nobjectcollection->Add(new NUChar('c'));
	nobjectcollection->Add(new NUShort(44000));
	nobjectcollection->Add(new NUInt(88000));
	nobjectcollection->Add(new NULong(44000000000));
	nobjectcollection->Add(new NULongLong(88000000000000L));
	nobjectcollection->Add(new NFloat(-1e15f));
	nobjectcollection->Add(new NDouble(-1e40));
	nobjectcollection->Add(new NLongDouble(-1e400L));
	nobjectcollection->Add(new NSize(500, 600));
	nobjectcollection->Add(new NPoint(100,200));
	nobjectcollection->Add(new NRectangle(300, 400, 500, 600));
	nobjectcollection->Add(new NColor(0, 1, 0, 0.25));
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
	
	delete nnbool;
	delete nnchar;
	delete nnwchar;
	delete nnshort;
	delete nnint;
	delete nnlong;
	delete nnlonglong;
	delete nnuchar;
	delete nnushort;
	delete nnuint;
	delete nnulong;
	delete nnulonglong;
	delete nnfloat;
	delete nndouble;
	delete nnlongdouble;
	delete nnsize;
	delete nnpoint;
	delete nnrectangle;
	delete nncolor;
	
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
	((Serializator *)&s)->Put(nbool);
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
	
	((Serializator *)&s)->Put(*nnbool);
	((Serializator *)&s)->Put(*nnchar);
	((Serializator *)&s)->Put(*nnwchar);
	((Serializator *)&s)->Put(*nnshort);
	((Serializator *)&s)->Put(*nnint);
	((Serializator *)&s)->Put(*nnlong);
	((Serializator *)&s)->Put(*nnlonglong);
	((Serializator *)&s)->Put(*nnuchar);
	((Serializator *)&s)->Put(*nnushort);
	((Serializator *)&s)->Put(*nnuint);
	((Serializator *)&s)->Put(*nnulong);
	((Serializator *)&s)->Put(*nnulonglong);
	((Serializator *)&s)->Put(*nnfloat);
	((Serializator *)&s)->Put(*nndouble);
	((Serializator *)&s)->Put(*nnlongdouble);
	((Serializator *)&s)->Put(*nnsize);
	((Serializator *)&s)->Put(*nnpoint);
	((Serializator *)&s)->Put(*nnrectangle);
	((Serializator *)&s)->Put(*nncolor);
	
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
	NBool *oldnnbool = nnbool;
	NChar *oldnnchar = nnchar;
	NWChar *oldnnwchar = nnwchar;
	NShort *oldnnshort = nnshort;
	NInt *oldnnint = nnint;
	NLong *oldnnlong = nnlong;
	NLongLong *oldnnlonglong = nnlonglong;
	NUChar *oldnnuchar = nnuchar;
	NUShort *oldnnushort = nnushort;
	NUInt *oldnnuint = nnuint;
	NULong *oldnnulong = nnulong;
	NULongLong *oldnnulonglong = nnulonglong;
	NFloat *oldnnfloat = nnfloat;
	NDouble *oldnndouble = nndouble;
	NLongDouble *oldnnlongdouble = nnlongdouble;
	NSize *oldnnsize = nnsize;
	NPoint *oldnnpoint = nnpoint;
	NRectangle *oldnnrectangle = nnrectangle;
	NColor *oldnncolor = nncolor;
	
	nbool = ((Serializator *)&s)->GetBool();
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
	
	nnbool = (NBool *)((Serializator *)&s)->GetNObject();
	nnchar = (NChar *)((Serializator *)&s)->GetNObject();
	nnwchar = (NWChar *)((Serializator *)&s)->GetNObject();
	nnshort = (NShort *)((Serializator *)&s)->GetNObject();
	nnint = (NInt *)((Serializator *)&s)->GetNObject();
	nnlong = (NLong *)((Serializator *)&s)->GetNObject();
	nnlonglong = (NLongLong *)((Serializator *)&s)->GetNObject();
	nnuchar = (NUChar *)((Serializator *)&s)->GetNObject();
	nnushort = (NUShort *)((Serializator *)&s)->GetNObject();
	nnuint = (NUInt *)((Serializator *)&s)->GetNObject();
	nnulong = (NULong *)((Serializator *)&s)->GetNObject();
	nnulonglong = (NULongLong *)((Serializator *)&s)->GetNObject();
	nnfloat = (NFloat *)((Serializator *)&s)->GetNObject();
	nndouble = (NDouble *)((Serializator *)&s)->GetNObject();
	nnlongdouble = (NLongDouble *)((Serializator *)&s)->GetNObject();
	nnsize = (NSize *)((Serializator *)&s)->GetNObject();
	nnpoint = (NPoint *)((Serializator *)&s)->GetNObject();
	nnrectangle = (NRectangle *)((Serializator *)&s)->GetNObject();
	nncolor = (NColor *)((Serializator *)&s)->GetNObject();
	
	atext = (Text *)((Serializator *)&s)->GetNObject();
	adatetime = (DateTime *)((Serializator *)&s)->GetNObject();

	nobjectcollection = (NObjectCollection *)((Serializator *)&s)->GetNObject();
	nobjectdictionary = (NObjectDictionary *)((Serializator *)&s)->GetNObject();
	abuffer = (Buffer *)((Serializator *)&s)->GetNObject();
	atextbuffer = (TextBuffer *)((Serializator *)&s)->GetNObject();
	
	if (nbool != true || 
		nchar != 1 || nshort != 2 || nint != 3 || nlong != 4 || nlonglong != 5 ||
		nuchar != 6 || nushort != 7 || nuint != 8 || nulong != 9 || nulonglong != 10 ||
		nfloat != 11 || ndouble != 12 || nlongdouble != 13)
		{
			throw new Exception("Numbers not propertly deserializated", __FILE__, __LINE__, __func__);
		}
	
	if (nnbool->Value() != true) throw new Exception("NBool::Deserialize error", __FILE__, __LINE__, __func__);
	if (nnchar->Value() != 'c') throw new Exception("NChar::Deserialize error", __FILE__, __LINE__, __func__);
	if (nnwchar->Value() != L'd') throw new Exception("NWChar::Deserialize error", __FILE__, __LINE__, __func__);
	if (nnshort->Value() != -22000) throw new Exception("NShort::Deserialize error", __FILE__, __LINE__, __func__);
	if (nnint->Value() != -34000) throw new Exception("NInt::Deserialize error", __FILE__, __LINE__, __func__);
	if (nnlong->Value() != -22000000000) throw new Exception("NLong::Deserialize error", __FILE__, __LINE__, __func__);
	if (nnlonglong->Value() != -44000000000000) throw new Exception("NLongLong::Deserialize error", __FILE__, __LINE__, __func__);
	if (nnuchar->Value() != 'c') throw new Exception("NUChar::Deserialize error", __FILE__, __LINE__, __func__);
	if (nnushort->Value() != 44000) throw new Exception("NUShort::Deserialize error", __FILE__, __LINE__, __func__);
	if (nnuint->Value() != 88000) throw new Exception("NUInt::Deserialize error", __FILE__, __LINE__, __func__);
	if (nnulong->Value() != 44000000000) throw new Exception("NULong::Deserialize error", __FILE__, __LINE__, __func__);
	if (nnulonglong->Value() != 88000000000000L) throw new Exception("NULongLong::Deserialize error", __FILE__, __LINE__, __func__);
	if (nnfloat->Value() != -1e15f) throw new Exception("NFloat::Deserialize error", __FILE__, __LINE__, __func__);
	if (nndouble->Value() != -1e40) throw new Exception("NDouble::Deserialize error", __FILE__, __LINE__, __func__);
	if (nnlongdouble->Value() != -1e400L) throw new Exception("NLongDouble::Deserialize error", __FILE__, __LINE__, __func__);
	if (nnsize->GetWidth() != 400) throw new Exception("NNSize::Deserialize error", __FILE__, __LINE__, __func__);
	if (nnsize->GetHeight() != 300) throw new Exception("NNSize::Deserialize error", __FILE__, __LINE__, __func__);
	if (nnpoint->GetX() != 3) throw new Exception("NPoint::Deserialize error", __FILE__, __LINE__, __func__);
	if (nnpoint->GetY() != 4) throw new Exception("NPoint::Deserialize error", __FILE__, __LINE__, __func__);
	if (nnrectangle->GetX() != 4) throw new Exception("NRectangle::Deserialize error", __FILE__, __LINE__, __func__);
	if (nnrectangle->GetY() != 5) throw new Exception("NRectangle::Deserialize error", __FILE__, __LINE__, __func__);
	if (nnrectangle->GetWidth() != 6) throw new Exception("NRectangle::Deserialize error", __FILE__, __LINE__, __func__);
	if (nnrectangle->GetHeight() != 7) throw new Exception("NRectangle::Deserialize error", __FILE__, __LINE__, __func__);
	if (nncolor->R() != 1 || nncolor->G() != 0 || nncolor->B() != 0 || nncolor->A() != 0.5)
		throw new Exception("NColor::Deserialize error", __FILE__, __LINE__, __func__);
	
	if (oldnnbool->Value() != nnbool->Value()) throw new Exception("NBool::Deserialize error", __FILE__, __LINE__, __func__);
	if (oldnnchar->Value() != nnchar->Value()) throw new Exception("NChar::Deserialize error", __FILE__, __LINE__, __func__);
	if (oldnnwchar->Value() != nnwchar->Value()) throw new Exception("NWChar::Deserialize error", __FILE__, __LINE__, __func__);
	if (oldnnshort->Value() != nnshort->Value()) throw new Exception("NShort::Deserialize error", __FILE__, __LINE__, __func__);
	if (oldnnint->Value() != nnint->Value()) throw new Exception("NInt::Deserialize error", __FILE__, __LINE__, __func__);
	if (oldnnlong->Value() != nnlong->Value()) throw new Exception("NLong::Deserialize error", __FILE__, __LINE__, __func__);
	if (oldnnlonglong->Value() != nnlonglong->Value()) throw new Exception("NLongLong::Deserialize error", __FILE__, __LINE__, __func__);
	if (oldnnuchar->Value() != nnuchar->Value()) throw new Exception("NUChar::Deserialize error", __FILE__, __LINE__, __func__);
	if (oldnnushort->Value() != nnushort->Value()) throw new Exception("NUShort::Deserialize error", __FILE__, __LINE__, __func__);
	if (oldnnuint->Value() != nnuint->Value()) throw new Exception("NUInt::Deserialize error", __FILE__, __LINE__, __func__);
	if (oldnnulong->Value() != nnulong->Value()) throw new Exception("NULong::Deserialize error", __FILE__, __LINE__, __func__);
	if (oldnnulonglong->Value() != nnulonglong->Value()) throw new Exception("NULongLong::Deserialize error", __FILE__, __LINE__, __func__);
	if (oldnnfloat->Value() != nnfloat->Value()) throw new Exception("NFloat::Deserialize error", __FILE__, __LINE__, __func__);
	if (oldnndouble->Value() != nndouble->Value()) throw new Exception("NDouble::Deserialize error", __FILE__, __LINE__, __func__);
	if (oldnnlongdouble->Value() != nnlongdouble->Value()) throw new Exception("NLongDouble::Deserialize error", __FILE__, __LINE__, __func__);
	if (oldnnsize->GetWidth() != nnsize->GetWidth()) throw new Exception("NSize::Deserialize error", __FILE__, __LINE__, __func__);
	if (!oldnnpoint->Equals(*nnpoint)) throw new Exception("NPoint::Deserialize error", __FILE__, __LINE__, __func__);
	if (!oldnnrectangle->Equals(*nnrectangle)) throw new Exception("NRectangle::Deserialize error", __FILE__, __LINE__, __func__);
	if (!oldnncolor->Equals(*nncolor)) throw new Exception("NColor::Deserilize error", __FILE__, __LINE__, __func__);
	
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
	delete oldnnbool;
	delete oldnnchar;
	delete oldnnwchar;
	delete oldnnshort;
	delete oldnnint;
	delete oldnnlong;
	delete oldnnlonglong;
	delete oldnnuchar;
	delete oldnnushort;
	delete oldnnuint;
	delete oldnnulong;
	delete oldnnulonglong;
	delete oldnnfloat;
	delete oldnndouble;
	delete oldnnlongdouble;
	delete oldnnsize;
	delete oldnnpoint;
	delete oldnnrectangle;
	delete oldnncolor;
}

