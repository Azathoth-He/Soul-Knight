#include"Weapons.h"

Weapon* Weapon::create(const std::string& filename)
{
	Weapon* weapon = new (std::nothrow) Weapon();
	if (weapon && weapon->initWithFile(filename))
	{
		weapon->autorelease();
		return weapon;
	}
	CC_SAFE_DELETE(weapon);
	return nullptr;
}

void Weapon::initData()
{
	cocos2d::ValueMap value = cocos2d::FileUtils::getInstance()->getValueMapFromFile("weapon\\weaponData.plist");
	auto weaponData = value.at(_weaponName).asValueMap();

	_attack = weaponData["attack"].asValueVector().at(0).asInt();
	_attackRate = weaponData["attackRate"].asValueVector().at(0).asFloat();
	_mode = weaponData["mode"].asValueVector().at(0).asInt();
	_magicUse = weaponData["magicUse"].asValueVector().at(0).asInt();
	_bulletNum = weaponData["bulletNum"].asValueVector().at(0).asInt();
	_bulletV = weaponData["bulletV"].asValueVector().at(0).asInt();
}