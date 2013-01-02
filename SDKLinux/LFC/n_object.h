#ifndef NOBJECT_H
#define NOBJECT_H

template<typename T>
struct is_pointer { static const bool value = false; };    
template<typename T>
struct is_pointer<T*> { static const bool value = true; };

class Text;

class NObject {

public:
	NObject();
	virtual ~NObject();
	
	Text ToText();

};

#endif // NOBJECT_H
