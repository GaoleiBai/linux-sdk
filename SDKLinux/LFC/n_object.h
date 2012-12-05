#ifndef NOBJECT_H
#define NOBJECT_H

template<typename T>
struct is_pointer { static const bool value = false; };    
template<typename T>
struct is_pointer<T*> { static const bool value = true; };

class NObject {

public:
	NObject();
	~NObject();

};

#endif // NOBJECT_H
