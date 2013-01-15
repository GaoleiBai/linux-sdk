#ifndef NOBJECT_H
#define NOBJECT_H

template<typename T>
struct is_pointer { static const bool value = false; };    
template<typename T>
struct is_pointer<T*> { static const bool value = true; };

class Text;
class Serializator;

class NObject {

public:
	NObject();
	virtual ~NObject();
	
	virtual NObject *NewInstance();
	virtual Text ToText();
	virtual int Compare(const NObject &o);
	virtual void Serialize(const Serializator &s);
	virtual void Deserialize(const Serializator &s);
	
};

#endif // NOBJECT_H
