#include "nobjectregistry.h"
#include "Text/text.h"
#include "Devices/stdout.h"
#include <stdlib.h>
#include <typeinfo>

NObjectRegistry *NObjectRegistry::registry = NULL;

NObjectRegistry::NObjectRegistry()
{
	if (registry != NULL) 
		throw new Exception("Can only exist one registry at a time.", __FILE__, __LINE__, __func__);
	classes = new Dictionary<Text *, NObject *>(Text::COMPARER);
}

NObjectRegistry::~NObjectRegistry()
{
	delete classes;
}

void NObjectRegistry::Register(const NObject &o)
{
	if (registry == NULL) 
		registry = new NObjectRegistry();
	
	Text classname = typeid(o).name();
	if (!registry->classes->ExistsKey(&classname))
		registry->classes->SetKey(new Text(classname), (NObject *)new typeof(o));
}

NObject *NObjectRegistry::GetInstance(const Text &classname)
{
	if (registry == NULL)
		throw new Exception((Text)"Please call lfc_init() before using LFC library.", __FILE__, __LINE__, __func__);
	NObject *o = NULL;
	if (!registry->classes->GetKey((Text *)&classname, o))
		throw new Exception((Text)"Cannot instantiate " + classname + " because it is not propertly registered.", __FILE__, __LINE__, __func__);
	return new typeof(*o);
}

