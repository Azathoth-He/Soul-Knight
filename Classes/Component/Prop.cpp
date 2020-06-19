#include"Prop.h"

USING_NS_CC;

Prop* Prop::create(const std::string& filename)
{
	Prop* prop = new (std::nothrow) Prop();
	if (prop && prop->initWithFile(filename))
	{
		prop->autorelease();
		return prop;
	}
	CC_SAFE_DELETE(prop);
	return nullptr;
}
