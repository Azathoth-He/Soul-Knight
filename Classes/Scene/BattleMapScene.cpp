#include"BattleMapScene.h"

USING_NS_CC;

Scene* BattleMap::createScene(SecurityMap* combatScene)
{
	return  BattleMap::create(combatScene);
}

BattleMap* BattleMap::create(SecurityMap* combatScene)
{
	BattleMap* layer = new(std::nothrow)BattleMap;
	if (layer && layer->init(combatScene))
	{
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return NULL;
}

bool BattleMap::init(SecurityMap* combatScene)
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	scheduleUpdate();

	_map= TMXTiledMap::create("map/BattleMap1.0.tmx");
	addChild(_map, 0, 100);

	_myMoney = combatScene->getMyMoney();
	_myHero = combatScene->getMyHero();

	TMXObjectGroup* group = _map->getObjectGroup("object");
	ValueMap spawnPoint = group->getObject("hero");

	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();

	_player = Sprite::create("hero_enemy/" + _myHero->getHeroName() + ".png");
	_player->setPosition(Vec2(x, y));
	addChild(_player, 2);

	_weapon = Sprite::create("weapon/" + _myHero->getMyWeapon().getWeaponName() + ".png");
	_weapon->setPosition(Vec2(x + _player->getContentSize().width / 2
		- _weapon->getContentSize().width / 4, y));
	addChild(_weapon, 2);

	initHRocker();
	initIcon();
	initStateBox();

	combatScene->cleanup();

	return true;
}

void BattleMap::initHRocker()
{
	_rocker = HRocker::createHRocker(Vec2(120, 120));
	_rocker->startRocker(true);
	addChild(_rocker);
}

void BattleMap::initIcon()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto money = Sprite::create("money.png");
	money->setContentSize(Size(65, 90));
	money->setPosition(Vec2(origin.x + visibleSize.width - 170, origin.y + visibleSize.height - 40));
	this->addChild(money, 1, 102);

	std::string myMoney = StringUtils::format("%d", _myMoney);
	auto moneyLabel = Label::createWithSystemFont(myMoney, "Arial", 25);
	moneyLabel->setPosition(Vec2(origin.x + visibleSize.width - 100,
		origin.y + visibleSize.height - 38));
	moneyLabel->setTag(103);
	this->addChild(moneyLabel);

	auto weaponBox = Sprite::create("weaponBox.png");
	weaponBox->setPosition(Vec2(origin.x + visibleSize.width - 130, origin.y + 200));
	weaponBox->setOpacity(80);
	this->addChild(weaponBox, 3, 20);
	auto weapon = Sprite::create("weapon/" + _myHero->getMyWeapon().getWeaponName() + ".png");
	weapon->setPosition(Vec2(origin.x + visibleSize.width - 130, origin.y + 200));
	addChild(weapon, 3, 21);
}

void BattleMap::initStateBox()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto box = Sprite::create("StateBox.jpg");
	box->setPosition(Vec2(box->getContentSize().width / 2,
		visibleSize.height - box->getContentSize().height / 2));
	box->setOpacity(150);
	this->addChild(box, 1, 293);

	auto healthImg = Sprite::create("health.png");
	healthImg->setContentSize(Size(90, 125));
	healthImg->setPosition(Vec2(origin.x + 60, visibleSize.height - 40));
	healthImg->setOpacity(150);
	this->addChild(healthImg, 1, 294);

	auto magicImg = Sprite::create("magic.png");
	magicImg->setContentSize(Size(85, 118));
	magicImg->setPosition(Vec2(origin.x + 55, visibleSize.height - 85));
	magicImg->setOpacity(150);
	this->addChild(magicImg, 1, 295);

	auto shieldImg = Sprite::create("shield.png");
	shieldImg->setContentSize(Size(90, 125));
	shieldImg->setPosition(Vec2(origin.x + 57, visibleSize.height - 130));
	shieldImg->setOpacity(150);
	this->addChild(shieldImg, 1, 296);

	auto reservoir1 = Sprite::create("xiecao.png");
	reservoir1->setContentSize(Size(180, 20));
	reservoir1->setPosition(Vec2(180, visibleSize.height - 35));
	reservoir1->setOpacity(150);
	this->addChild(reservoir1, 1, 297);

	auto reservoir2 = Sprite::create("xiecao.png");
	reservoir2->setContentSize(Size(180, 20));
	reservoir2->setPosition(Vec2(180, visibleSize.height - 80));
	reservoir2->setOpacity(150);
	this->addChild(reservoir2, 1, 298);

	auto reservoir3 = Sprite::create("xiecao.png");
	reservoir3->setContentSize(Size(180, 20));
	reservoir3->setPosition(Vec2(180, visibleSize.height - 125));
	reservoir3->setOpacity(150);
	this->addChild(reservoir3, 1, 299);

	auto xuetiao = Sprite::create("xuetiao.png");
	xuetiao->setContentSize(Size(180, 19));
	xuetiao->setPosition(Vec2(180, visibleSize.height - 35));
	this->addChild(xuetiao, 1, 301);

	auto lantiao = Sprite::create("lantiao.png");
	lantiao->setContentSize(Size(180, 19));
	lantiao->setPosition(Vec2(180, visibleSize.height - 80));
	this->addChild(lantiao, 1, 302);

	auto hudun = Sprite::create("hudun.png");
	hudun->setContentSize(Size(180, 19));
	hudun->setPosition(Vec2(180, visibleSize.height - 125));
	this->addChild(hudun, 1, 303);

	std::string health = StringUtils::format("%d/%d", _myHero->getCurrentHealth(), _myHero->getMaxHealth());
	auto healthLabel = Label::createWithSystemFont(health, "Arial", 25);
	healthLabel->setPosition(Vec2(180, visibleSize.height - 35));
	this->addChild(healthLabel, 1, 401);

	std::string magic = StringUtils::format("%d/%d", _myHero->getCurrentMagic(), _myHero->getMaxMagic());
	auto magicLabel = Label::createWithSystemFont(magic, "Arial", 25);
	magicLabel->setPosition(Vec2(180, visibleSize.height - 80));
	this->addChild(magicLabel, 1, 402);

	std::string shield = StringUtils::format("%d/%d", _myHero->getCurrentShiled(), _myHero->getMaxShield());
	auto shieldLabel = Label::createWithSystemFont(shield, "Arial", 25);
	shieldLabel->setPosition(Vec2(180, visibleSize.height - 125));
	this->addChild(shieldLabel, 1, 403);
}

void BattleMap::updateHeroState()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto xuetiao = this->getChildByTag(301);
	float propotion1 = (float)_myHero->getCurrentHealth() / (float)_myHero->getMaxHealth();
	xuetiao->setContentSize(Size(180 * propotion1, 19));
	xuetiao->setPosition(Vec2(90 + xuetiao->getContentSize().width / 2, visibleSize.height - 35) - _offset);

	auto lantiao = this->getChildByTag(302);
	float propotion2 = (float)_myHero->getCurrentMagic() / (float)_myHero->getMaxMagic();
	lantiao->setContentSize(Size(180 * propotion2, 19));
	lantiao->setPosition(Vec2(90 + lantiao->getContentSize().width / 2, visibleSize.height - 80) - _offset);

	auto hudun = this->getChildByTag(303);
	float propotion3 = (float)_myHero->getCurrentShiled() / (float)_myHero->getMaxShield();
	hudun->setContentSize(Size(180 * propotion3, 19));
	hudun->setPosition(Vec2(90 + hudun->getContentSize().width / 2, visibleSize.height - 125) - _offset);

	Label* healthLabel = (Label*)this->getChildByTag(401);
	std::string health = StringUtils::format("%d/%d", _myHero->getCurrentHealth(), _myHero->getMaxHealth());
	healthLabel->setString(health);
	healthLabel->setPosition(Vec2(180, visibleSize.height - 35) - _offset);

	Label* magicLabel = (Label*)this->getChildByTag(402);
	std::string magic = StringUtils::format("%d/%d", _myHero->getCurrentMagic(), _myHero->getMaxMagic());
	magicLabel->setString(magic);
	magicLabel->setPosition(Vec2(180, visibleSize.height - 80) - _offset);

	Label* shieldLabel = (Label*)this->getChildByTag(403);
	std::string shield = StringUtils::format("%d/%d", _myHero->getCurrentShiled(), _myHero->getMaxShield());
	shieldLabel->setString(shield);
	shieldLabel->setPosition(Vec2(180, visibleSize.height - 125) - _offset);

}

void BattleMap::update(float dt)
{
	updateHeroPosition();
	updateHeroState();
	updateOthers();
}

void BattleMap::updateHeroPosition()
{
	if (_rocker->getAvailable())
	{
		auto oldPosition = _player->getPosition();
		auto angle = _rocker->getAngle();
		auto positionDelta = Vec2(cos(angle) * _myHero->getMoveSpeed() / 30/*FRAMES_PER_SECOND*/,
			sin(angle) * _myHero->getMoveSpeed() / 30/*FRAMES_PER_SECOND*/);
		auto newPosition = oldPosition + 5 * positionDelta;

		MapInformation mapInfo;
		bool isBorder = mapInfo.checkBorder((TMXTiledMap*)_map, newPosition);

		if (isBorder);
		else
			_player->setPosition(newPosition);

		if (dir == 0)
			_weapon->setPosition(_player->getPosition() + Vec2(_player->getContentSize().width / 2
				- _weapon->getContentSize().width / 4, 0));
		else if (dir == 1)
			_weapon->setPosition(_player->getPosition() - Vec2(_player->getContentSize().width / 2 - 5
				, 0));
	}
	this->setViewpointCenter(_player->getPosition());
}

void BattleMap::setViewpointCenter(Vec2 position)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//防止视图左边超出屏幕之外
	int x = MAX(position.x, visibleSize.width / 2);
	int y = MAX(position.y, visibleSize.height / 2);
	//防止视图右边超出屏幕之外
	x = MIN(x, (_map->getMapSize().width * _map->getTileSize().width) - visibleSize.width / 2);
	y = MIN(y, (_map->getMapSize().height * _map->getTileSize().height) - visibleSize.height / 2);

	//屏幕中心点
	Vec2 pointA = Vec2(visibleSize.width / 2, visibleSize.height / 2);
	//使精灵处于屏幕中心，移动地图目标位置
	Vec2 pointB = Vec2(x, y);

	_offset = pointA - pointB;
	this->setPosition(_offset);
}

void BattleMap::updateOthers()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite* bg = (Sprite*)_rocker->getChildByTag(30);
	bg->setPosition(Vec2(120, 120) - _offset);

	auto money = this->getChildByTag(102);
	money->setPosition(Vec2(origin.x + visibleSize.width - 170, origin.y + visibleSize.height - 40) - _offset);

	auto moneyLabel = this->getChildByTag(103);
	moneyLabel->setPosition(Vec2(origin.x + visibleSize.width - 100,
		origin.y + visibleSize.height - 38) - _offset);

	auto weaponBox = this->getChildByTag(20);
	weaponBox->setPosition(Vec2(origin.x + visibleSize.width - 130, origin.y + 200) - _offset);

	auto weapon = this->getChildByTag(21);
	weapon->setPosition(Vec2(origin.x + visibleSize.width - 130, origin.y + 200) - _offset);

	auto box = this->getChildByTag(293);
	box->setPosition(Vec2(box->getContentSize().width / 2,
		visibleSize.height - box->getContentSize().height / 2) - _offset);

	auto healthImg = this->getChildByTag(294);
	healthImg->setPosition(Vec2(origin.x + 60, visibleSize.height - 40) - _offset);

	auto magicImg = this->getChildByTag(295);
	magicImg->setPosition(Vec2(origin.x + 55, visibleSize.height - 85) - _offset);
	
	auto shieldImg = this->getChildByTag(296);
	shieldImg->setPosition(Vec2(origin.x + 57, visibleSize.height - 130) - _offset);

	auto reservoir1 = this->getChildByTag(297);
	reservoir1->setPosition(Vec2(180, visibleSize.height - 35) - _offset);

	auto reservoir2 = this->getChildByTag(298);
	reservoir2->setPosition(Vec2(180, visibleSize.height - 80) - _offset);

	auto reservoir3 = this->getChildByTag(299);
	reservoir3->setPosition(Vec2(180, visibleSize.height - 125) - _offset);
}