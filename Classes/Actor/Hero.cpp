#include"Hero.h"

Hero* Hero::create(std::string heroName)
{
	Hero* hero = new(std::nothrow)Hero;
	if (hero && hero->init(heroName))
	{
		//hero->autorelease();
		return hero;
	}
	CC_SAFE_DELETE(hero);
	return nullptr;
}

bool Hero::init(std::string heroName)
{
	if (!Sprite::init())
	{
		return false;
	}

	initHeroData(heroName);

	return true;
}

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

Sprite* Hero::initWeapon()
{
	if (_heroName == "Archer")
	{
		Sprite* initialWeapon = Sprite::create("weapon/betterBow.png");
		_myWeapon.setWeaponName("betterBow");
		_myWeapon.initData();
		return initialWeapon;
	}
	else if (_heroName == "Berserker")
	{
		Sprite* initialWeapon = Sprite::create("weapon/betterSword.png");
		_myWeapon.setWeaponName("betterSword");
		_myWeapon.initData();
		return initialWeapon;
	}
	else if (_heroName == "Paladin")
	{
		Sprite* initialWeapon = Sprite::create("weapon/betterPistol.png");
		_myWeapon.setWeaponName("betterPistol");
		_myWeapon.initData();
		return initialWeapon;
	}
}

Bullet* Hero::attack()
{
	std::string fileName = StringUtils::format("weapon/bullet%d.png", _myWeapon.getBulletNum());
	Bullet* bullet = Bullet::create(fileName);
	bullet->setVelocity(Vec2(_myWeapon.getBulletV(), 0));
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