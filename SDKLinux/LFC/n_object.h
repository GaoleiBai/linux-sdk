#ifndef NOBJECT_H
#define NOBJECT_H

template<typename T>
struct is_pointer { static const bool value = false; };    
template<typename T>
struct is_pointer<T*> { static const bool value = true; };

class Text;
class IFile;

class NObject {

public:
	NObject();
	virtual ~NObject();
	
	virtual Text ToText();
	virtual int Compare(const NObject &o);
	virtual void Serialize(const IFile &file);
	virtual NObject Deserialize(const IFile &file);
	
};

#endif // NOBJECT_H
