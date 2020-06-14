#include"SecurityMapScene.h"

USING_NS_CC;

Scene* SecurityMap::createScene(HeroMessage* combatScene)
{
	return  SecurityMap::create(combatScene);
}

SecurityMap* SecurityMap::create(HeroMessage* combatScene)
{
	SecurityMap* layer = new(std::nothrow)SecurityMap;
	if (layer && layer->init(combatScene))
	{
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return NULL;
}

bool SecurityMap::init(HeroMessage* combatScene)
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->scheduleUpdate();

	_seMap = TMXTiledMap::create("map/securityMap.tmx");
	auto collision = _seMap->getLayer("collision");
	collision->setVisible(false);
	addChild(_seMap, 0, 100);


	_myMoney = combatScene->getMyMoney();
	_myHero = combatScene->getMyHero();

	_player = Sprite::create("hero_enemy/" + combatScene->getHeroName() + ".png");
	_player->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	addChild(_player, 2);

	_weapon = _myHero->initWeapon();
	_weapon->setPosition(Vec2(visibleSize.width / 2 + _player->getContentSize().width / 2
		- _weapon->getContentSize().width / 4, visibleSize.height / 2));
	addChild(_weapon, 2);

	initHRocker();
	initIcon();
	initStateBox();

	return true;
}

void SecurityMap::initIcon()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto money = Sprite::create("money.png");
	money->setContentSize(Size(65, 90));
	money->setPosition(Vec2(origin.x + visibleSize.width - 170, origin.y + visibleSize.height - 40));
	this->addChild(money, 1);

	std::string myMoney = StringUtils::format("%d", _myMoney);
	auto moneyLabel = Label::createWithSystemFont(myMoney, "Arial", 25);
	moneyLabel->setPosition(Vec2(origin.x + visibleSize.width - 100,
		origin.y + visibleSize.height - 38));
	moneyLabel->setTag(103);
	this->addChild(moneyLabel);

	auto drawLabel = Label::createWithSystemFont("Do you want to draw? Press J and pay 100",
		"Arial", 18);
	drawLabel->setPosition(Vec2(origin.x + 180,
		origin.y + visibleSize.height - 150));
	this->addChild(drawLabel, 3, 10);
	drawLabel->setVisible(false);

	auto weaponBox = Sprite::create("weaponBox.png");
	weaponBox->setPosition(Vec2(origin.x + visibleSize.width - 130, origin.y + 200));
	weaponBox->setOpacity(80);
	this->addChild(weaponBox, 3, 20);
	auto weapon = Sprite::create("weapon/" + _myHero->getMyWeapon().getWeaponName() + ".png");
	weapon->setPosition(Vec2(origin.x + visibleSize.width - 130, origin.y + 200));
	addChild(weapon, 3, 21);
}


void SecurityMap::initHRocker()
{
	_rocker = HRocker::createHRocker(Vec2(120,120));
	_rocker->startRocker(true);
	addChild(_rocker);
}


void SecurityMap::updateHeroPosition()
{
	if (_rocker->getAvailable())
	{
		auto oldPosition = _player->getPosition();
		auto angle = _rocker->getAngle();
		auto positionDelta = Vec2(cos(angle) * _myHero->getMoveSpeed() / 30/*FRAMES_PER_SECOND*/,
			sin(angle) * _myHero->getMoveSpeed() / 30/*FRAMES_PER_SECOND*/);
		auto newPosition = oldPosition + 5 * positionDelta;

		MapInformation mapInfo;
		bool isBorder = mapInfo.checkBorder((TMXTiledMap*)_seMap, newPosition);
		bool isDraw = mapInfo.checkDraw((TMXTiledMap*)_seMap, newPosition);

		if (isBorder);
		else
		{
			if (isDraw)
			{
				chooseToDraw(isDraw);
				_player->setPosition(oldPosition);
			}
			else
			{
				chooseToDraw(isDraw);
				_player->setPosition(newPosition);
			}
		}

		if (dir == 0)
			_weapon->setPosition(_player->getPosition() + Vec2(_player->getContentSize().width / 2
				- _weapon->getContentSize().width / 4, 0));
		else if (dir == 1)
			_weapon->setPosition(_player->getPosition() - Vec2(_player->getContentSize().width / 2 - 5
				, 0));

		this->setViewpointCenter(_player->getPosition());
	}
}

void SecurityMap::updateHeroDirction()
{
	if (_rocker->_aState)
	{
		dir = 1;
		_player->setFlipX(true);
		_weapon->setFlippedX(true);
	}
	if (_rocker->_dState)
	{
		dir = 0;
		_player->setFlipX(false);
		_weapon->setFlippedX(false);
	}
}

void SecurityMap::update(float dt)
{
	updateHeroPosition();
	updateHeroDirction();
	if (_rocker->_jState)
		heroAttack();
	updateHeroState();
	updateScene();
}

void SecurityMap::setViewpointCenter(Vec2 position)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//防止视图左边超出屏幕之外
	int x = MAX(position.x, visibleSize.width / 2);
	int y = MAX(position.y, visibleSize.height / 2);
	//防止视图右边超出屏幕之外
	x = MIN(x, (_seMap->getMapSize().width * _seMap->getTileSize().width) - visibleSize.width / 2);
	y = MIN(y, (_seMap->getMapSize().height * _seMap->getTileSize().height) - visibleSize.height / 2);

	//屏幕中心点
	Vec2 pointA = Vec2(visibleSize.width / 2, visibleSize.height / 2);
	//使精灵处于屏幕中心，移动地图目标位置
	Vec2 pointB = Vec2(x, y);

	//地图移动偏移量
	Vec2 offset = pointA - pointB;
	this->setPosition(offset);
}

void SecurityMap::chooseToDraw(bool isDraw)
{
	auto drawLabel = this->getChildByTag(10);
	if (isDraw)
		drawLabel->setVisible(true);
	else
		drawLabel->setVisible(false);
}

void SecurityMap::heroAttack()
{
	_nowTime = GetCurrentTime() / 1000.f;

	if ((_nowTime - _oldTime) >= _myHero->getMyWeapon().getAttackRate())
	{
		auto bullet = _myHero->attack();
		bullet->setPosition(_weapon->getPosition());
		bullet->setVisible(true);

		auto magic = _myHero->getCurrentMagic() - _myHero->getMyWeapon().getMagicUse();
		_myHero->setCurrentMagic(magic);

		if (dir == 1)
			bullet->setFlipX(true);
	
		//ActionInterval* rotateto = RotateTo::create(0.01, _rocker->getAngle);
		//bullet->runAction(rotateto);
		
		this->addChild(bullet);
		bullet->shootBullet(dir);

		_oldTime = GetCurrentTime() / 1000.f;
	}
}

void SecurityMap::initStateBox()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto box = Sprite::create("StateBox.jpg");
	box->setPosition(Vec2(box->getContentSize().width / 2,
		visibleSize.height - box->getContentSize().height / 2));
	box->setOpacity(90);
	this->addChild(box);

	auto healthImg = Sprite::create("health.png");
	healthImg->setContentSize(Size(90,125));
	healthImg->setPosition(Vec2(origin.x + 60, visibleSize.height - 40));
	healthImg->setOpacity(90);
	this->addChild(healthImg, 1);

	auto magicImg = Sprite::create("magic.png");
	magicImg->setContentSize(Size(85, 118));
	magicImg->setPosition(Vec2(origin.x + 55, visibleSize.height - 85));
	magicImg->setOpacity(90);
	this->addChild(magicImg, 1);

	auto shieldImg = Sprite::create("shield.png");
	shieldImg->setContentSize(Size(90, 125));
	shieldImg->setPosition(Vec2(origin.x + 57, visibleSize.height - 130));
	shieldImg->setOpacity(90);
	this->addChild(shieldImg, 1);

	auto reservoir1 = Sprite::create("xiecao.png");
	reservoir1->setContentSize(Size(180, 20));
	reservoir1->setPosition(Vec2(180, visibleSize.height - 35));
	reservoir1->setOpacity(90);
	this->addChild(reservoir1, 1);

	auto reservoir2 = Sprite::create("xiecao.png");
	reservoir2->setContentSize(Size(180, 20));
	reservoir2->setPosition(Vec2(180, visibleSize.height - 80));
	reservoir2->setOpacity(90);
	this->addChild(reservoir2, 1);

	auto reservoir3 = Sprite::create("xiecao.png");
	reservoir3->setContentSize(Size(180, 20));
	reservoir3->setPosition(Vec2(180, visibleSize.height - 125));
	reservoir3->setOpacity(90);
	this->addChild(reservoir3, 1);

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

void SecurityMap::updateHeroState()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto xuetiao = this->getChildByTag(301);
	float propotion1 = (float)_myHero->getCurrentHealth() / (float)_myHero->getMaxHealth();
	xuetiao->setContentSize(Size(180 * propotion1, 19));
	xuetiao->setPosition(Vec2(90 + xuetiao->getContentSize().width / 2, visibleSize.height - 35));

	auto lantiao = this->getChildByTag(302);
	float propotion2 = (float)_myHero->getCurrentMagic() / (float)_myHero->getMaxMagic();
	lantiao->setContentSize(Size(180 * propotion2, 19));
	lantiao->setPosition(Vec2(90 + lantiao->getContentSize().width / 2, visibleSize.height - 80));

	auto hudun = this->getChildByTag(303);
	float propotion3 = (float)_myHero->getCurrentShiled() / (float)_myHero->getMaxShield();
	hudun->setContentSize(Size(180 * propotion3, 19));
	hudun->setPosition(Vec2(90 + hudun->getContentSize().width / 2, visibleSize.height - 125));

	Label* healthLabel = (Label*)this->getChildByTag(401);
	std::string health = StringUtils::format("%d/%d", _myHero->getCurrentHealth(), _myHero->getMaxHealth());
	healthLabel->setString(health);

	Label* magicLabel = (Label*)this->getChildByTag(402);
	std::string magic = StringUtils::format("%d/%d", _myHero->getCurrentMagic(), _myHero->getMaxMagic());
	magicLabel->setString(magic);

	Label* shieldLabel = (Label*)this->getChildByTag(403);
	std::string shield = StringUtils::format("%d/%d", _myHero->getCurrentShiled(), _myHero->getMaxShield());
	shieldLabel->setString(shield);

}

void SecurityMap::updateScene()
{
	MapInformation mapInfo;
	bool isNew = mapInfo.checkNewScene((TMXTiledMap*)_seMap, _player->getPosition());

	if (isNew)
	{
		unscheduleUpdate();
		auto nextScene = BattleMap::createScene(this);
		Director::getInstance()->pushScene(nextScene);
	}

}