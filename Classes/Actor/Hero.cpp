#include"Hero.h"

bool Hero::initHeroData(std::string heroName)
{
	cocos2d::ValueMap value = cocos2d::FileUtils::getInstance()->getValueMapFromFile("hero_enemy\\HeroDataAtEachLevel.plist");
	_heroDataAtEachLevel = value.at(heroName).asValueMap();
	_upLevel = value.at("upLevel").asValueMap();

	_heroName = heroName;
	_level = 1;

	if (_heroName == "Archer")
		_moveSpeed = 26;
	else if (_heroName == "Paladin")
		_moveSpeed = 29;
	else if (_heroName == "Berserker")
		_moveSpeed = 32;

	_maxHealth = _heroDataAtEachLevel["health"].asValueVector().at(1).asInt();
	_maxMagic = _heroDataAtEachLevel["magic"].asValueVector().at(1).asInt();
	_maxShield = _heroDataAtEachLevel["shield"].asValueVector().at(1).asInt();
	_upLevelMoney = _upLevel["money"].asValueVector().at(1).asInt();

	_currentHealth = _maxHealth;
	_currentMagic = _maxMagic;
	_currentShiled = _maxShield;

	return true;
}

void Hero::initWeapon()
{
	if (_heroName == "Archer")
	{
		_myWeapon = Weapon::create("weapon/bow.png");
		_myWeapon->setWeaponName("bow");
		_myWeapon->initData();

	}
	else if (_heroName == "Berserker")
	{
		_myWeapon = Weapon::create("weapon/sword.png");
		_myWeapon->setWeaponName("sword");
		_myWeapon->initData();
	}
	else if (_heroName == "Paladin")
	{
		_myWeapon = Weapon::create("weapon/pistol.png");
		_myWeapon->setWeaponName("pistol");
		_myWeapon->initData();
	}
}

Bullet* Hero::remoteAttack()
{
	std::string fileName = StringUtils::format("weapon/bullet%d.png", _myWeapon->getBulletNum());
	Bullet* bullet = Bullet::create(fileName);
	bullet->setVelocity(Vec2(_myWeapon->getBulletV(), 0));
	return bullet;
}

void Hero::levelUp()
{
	_level++;
	_maxHealth = _heroDataAtEachLevel["health"].asValueVector().at(_level).asInt();
	_maxMagic = _heroDataAtEachLevel["magic"].asValueVector().at(_level).asInt();
	_maxShield = _heroDataAtEachLevel["shield"].asValueVector().at(_level).asInt();
	_upLevelMoney = _upLevel["money"].asValueVector().at(_level).asInt();

	_currentHealth = _maxHealth;
	_currentMagic = _maxMagic;
	_currentShiled = _maxShield;
}