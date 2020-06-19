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
	_archer = combatScene->_archer;
	_paladin = combatScene->_paladin;
	_berserker = combatScene->_berserker;

	_myHero.initWeapon();


	initArmature();
	initHRocker();
	initIcon();
	initStateBox();

	return true;
}

void SecurityMap::initArmature()
{
	_factory = dragonBones::CCFactory::getFactory();
	_armature = _factory->buildArmatureDisplay(_myHero.getHeroName());

	if (_myHero.getMyWeapon()->getWeaponName() == "betterBow")
		_armature->getArmature()->getSlot("weapon")->setDisplayIndex(0);
	else if (_myHero.getMyWeapon()->getWeaponName() == "betterSword")
		_armature->getArmature()->getSlot("weapon")->setDisplayIndex(1);
	else if (_myHero.getMyWeapon()->getWeaponName() == "axe")
		_armature->getArmature()->getSlot("weapon")->setDisplayIndex(2);
	else if (_myHero.getMyWeapon()->getWeaponName() == "betterPistol")
		_armature->getArmature()->getSlot("weapon")->setDisplayIndex(3);
	else if (_myHero.getMyWeapon()->getWeaponName() == "bow")
		_armature->getArmature()->getSlot("weapon")->setDisplayIndex(4);
	else if (_myHero.getMyWeapon()->getWeaponName() == "pistol")
		_armature->getArmature()->getSlot("weapon")->setDisplayIndex(5);
	else if (_myHero.getMyWeapon()->getWeaponName() == "sword")
		_armature->getArmature()->getSlot("weapon")->setDisplayIndex(6);

	_armature->setPosition(Vec2(300, 200));
	addChild(_armature);
}


void SecurityMap::initIcon()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto money = Sprite::create("money.png");
	money->setContentSize(Size(65, 90));
	money->setPosition(Vec2(origin.x + visibleSize.width - 200, origin.y + visibleSize.height - 40));
	this->addChild(money, 1);

	std::string myMoney = StringUtils::format("%d", _myMoney);
	auto moneyLabel = Label::createWithSystemFont(myMoney, "Arial", 25);
	moneyLabel->setPosition(Vec2(origin.x + visibleSize.width - 130,
		origin.y + visibleSize.height - 38));
	moneyLabel->setTag(103);
	this->addChild(moneyLabel);

	auto drawLabel = Label::createWithSystemFont("Do you want to draw? Press J and pay 200",
		"Arial", 18);
	drawLabel->setPosition(Vec2(origin.x + 180,
		origin.y + visibleSize.height - 150));
	this->addChild(drawLabel, 3, 10);
	drawLabel->setVisible(false);

	auto weaponBox = Sprite::create("weaponBox.png");
	weaponBox->setPosition(Vec2(origin.x + visibleSize.width - 130, origin.y + 200));
	weaponBox->setOpacity(80);
	this->addChild(weaponBox, 3, 20);

	_myHero.getMyWeapon()->setPosition(Vec2(origin.x + visibleSize.width - 130, origin.y + 200));
	_myHero.getMyWeapon()->setVisible(true);
	addChild(_myHero.getMyWeapon(), 3, 21);


	MenuItemImage* pauseMenu = MenuItemImage::create(
		"pause/pause.png",
		"pause/pause.png",
		CC_CALLBACK_1(SecurityMap::menuPauseCallBack, this)
	);
	pauseMenu->setPosition(Vec2(visibleSize.width - pauseMenu->getContentSize().width / 2,
		visibleSize.height - pauseMenu->getContentSize().height / 2));
	Menu* pMenu = Menu::create(pauseMenu, NULL);
	pMenu->setPosition(Vec2::ZERO);
	this->addChild(pMenu, 1);


	MenuItemImage* weaponMenu = MenuItemImage::create(
		"weaponMap.png",
		"weaponMap.png",
		CC_CALLBACK_1(SecurityMap::menuWeaponCallBack, this)
	);
	weaponMenu->setPosition(Vec2(950, 500));

	MenuItemImage* enemyMenu = MenuItemImage::create(
		"enemyMap.png",
		"enemyMap.png",
		CC_CALLBACK_1(SecurityMap::menuEnemyCallBack, this)
	);
	enemyMenu->setPosition(Vec2(1100, 500));
	Menu* mapMenu = Menu::create(weaponMenu, enemyMenu, NULL);
	mapMenu->setPosition(Vec2::ZERO);
	this->addChild(mapMenu, 1);
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
		auto oldPosition = _armature->getPosition();
		auto angle = _rocker->getAngle();
		auto positionDelta = Vec2(cos(angle) * _myHero.getMoveSpeed() / 30/*FRAMES_PER_SECOND*/,
			sin(angle) * _myHero.getMoveSpeed() / 30/*FRAMES_PER_SECOND*/);
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
				_armature->setPosition(oldPosition);
			}
			else
			{
				chooseToDraw(isDraw);
				
				_armature->setPosition(newPosition);
			}
		}
		/*
		if (dir == 0)
			_weapon->setPosition(_player->getPosition() + Vec2(_player->getContentSize().width / 2
				- _weapon->getContentSize().width / 4, 0));
		else if (dir == 1)
			_weapon->setPosition(_player->getPosition() - Vec2(_player->getContentSize().width / 2 - 5
				, 0));
				*/
		this->setViewpointCenter(_armature->getPosition());
	}
}

void SecurityMap::updateHeroDirction()
{
	if (_rocker->_aState)
	{
		dir = 1;
		_armature->setScaleX(-1);
	}
	if (_rocker->_dState)
	{
		dir = 0;
		_armature->setScaleX(1);
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
	changeWeapon();
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
	_nowTime = GetCurrentTime();
	if (isDraw && _rocker->_jState && _nowTime - _lastDrawTime > 2 * 1000)
	{
		_lastDrawTime = GetCurrentTime();
		generateWeapon();
	}
}

void SecurityMap::heroAttack()
{
	if (_myHero.getMyWeapon()->getMode() == 2)
	{
		_nowTime = GetCurrentTime();

		if ((_nowTime - _oldTime) >= _myHero.getMyWeapon()->getAttackRate() * 1000
			&& _myHero.getCurrentMagic() - _myHero.getMyWeapon()->getMagicUse() >= 0)
		{
			auto bullet = _myHero.remoteAttack();
			bullet->setPosition(_armature->getPosition());
			bullet->setVisible(true);

			auto magic = _myHero.getCurrentMagic() - _myHero.getMyWeapon()->getMagicUse();
			_myHero.setCurrentMagic(magic);

			if (dir == 1)
				bullet->setFlipX(true);
			this->addChild(bullet);
			bullet->shootBullet(dir, 0, _myHero.getMyWeapon()->getAttack(), _seMap);

			_oldTime = GetCurrentTime();
		}
	}
	else if (_myHero.getMyWeapon()->getMode() == 1)
	{
		_nowTime = GetCurrentTime();

		if ((_nowTime - _oldTime) >= _myHero.getMyWeapon()->getAttackRate() * 1000
			&& _myHero.getCurrentMagic() - _myHero.getMyWeapon()->getMagicUse() >= 0)
		{
			auto magic = _myHero.getCurrentMagic() - _myHero.getMyWeapon()->getMagicUse();
			_myHero.setCurrentMagic(magic);

			_armature->getAnimation()->play("meleeAttack", 1);
			_oldTime = GetCurrentTime();
		}
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

	std::string health = StringUtils::format("%d/%d", _myHero.getCurrentHealth(), _myHero.getMaxHealth());
	auto healthLabel = Label::createWithSystemFont(health, "Arial", 25);
	healthLabel->setPosition(Vec2(180, visibleSize.height - 35));
	this->addChild(healthLabel, 1, 401);

	std::string magic = StringUtils::format("%d/%d", _myHero.getCurrentMagic(), _myHero.getMaxMagic());
	auto magicLabel = Label::createWithSystemFont(magic, "Arial", 25);
	magicLabel->setPosition(Vec2(180, visibleSize.height - 80));
	this->addChild(magicLabel, 1, 402);

	std::string shield = StringUtils::format("%d/%d", _myHero.getCurrentShiled(), _myHero.getMaxShield());
	auto shieldLabel = Label::createWithSystemFont(shield, "Arial", 25);
	shieldLabel->setPosition(Vec2(180, visibleSize.height - 125));
	this->addChild(shieldLabel, 1, 403);
}

void SecurityMap::updateHeroState()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto xuetiao = this->getChildByTag(301);
	float propotion1 = (float)_myHero.getCurrentHealth() / (float)_myHero.getMaxHealth();
	xuetiao->setContentSize(Size(180 * propotion1, 19));
	xuetiao->setPosition(Vec2(90 + xuetiao->getContentSize().width / 2, visibleSize.height - 35));

	auto lantiao = this->getChildByTag(302);
	float propotion2 = (float)_myHero.getCurrentMagic() / (float)_myHero.getMaxMagic();
	lantiao->setContentSize(Size(180 * propotion2, 19));
	lantiao->setPosition(Vec2(90 + lantiao->getContentSize().width / 2, visibleSize.height - 80));

	auto hudun = this->getChildByTag(303);
	float propotion3 = (float)_myHero.getCurrentShiled() / (float)_myHero.getMaxShield();
	hudun->setContentSize(Size(180 * propotion3, 19));
	hudun->setPosition(Vec2(90 + hudun->getContentSize().width / 2, visibleSize.height - 125));

	Label* healthLabel = (Label*)this->getChildByTag(401);
	std::string health = StringUtils::format("%d/%d", _myHero.getCurrentHealth(), _myHero.getMaxHealth());
	healthLabel->setString(health);

	Label* magicLabel = (Label*)this->getChildByTag(402);
	std::string magic = StringUtils::format("%d/%d", _myHero.getCurrentMagic(), _myHero.getMaxMagic());
	magicLabel->setString(magic);

	Label* shieldLabel = (Label*)this->getChildByTag(403);
	std::string shield = StringUtils::format("%d/%d", _myHero.getCurrentShiled(), _myHero.getMaxShield());
	shieldLabel->setString(shield);

	std::string myMoney = StringUtils::format("%d", _myMoney);
	auto moneyLabel = (Label*)this->getChildByTag(103);
	moneyLabel->setString(myMoney);
	moneyLabel->setPosition(Vec2(visibleSize.width - 130, visibleSize.height - 38));

}

void SecurityMap::updateScene()
{
	MapInformation mapInfo;
	bool isNew = mapInfo.checkNewScene((TMXTiledMap*)_seMap, _armature->getPosition());

	if (isNew)
	{
		unscheduleUpdate();
		auto nextScene = BattleMap::createScene(this);
		Director::getInstance()->pushScene(nextScene);
	}

}

void SecurityMap::generateWeapon()
{
	if (_myMoney >= 200)
	{
		_myMoney -= 200;
		float random = CCRANDOM_0_1();
		if (random >= 0.5 && random < 0.7)
		{
			Weapon* weapon = Weapon::create("weapon/bow.png");
			weapon->setWeaponName("bow");
			weapon->initData();
			weapon->setPosition(Vec2(100 + random * 1000, 250));
			this->addChild(weapon);
			_weapons.pushBack((Weapon*)weapon);
		}
		else if (random < 0.5 && random >= 0.3)
		{
			Weapon* weapon = Weapon::create("weapon/pistol.png");
			weapon->setWeaponName("pistol");
			weapon->initData();
			weapon->setPosition(Vec2(100 + random * 1000, 250));
			this->addChild(weapon);
			_weapons.pushBack((Weapon*)weapon);
		}
		else if (random < 0.3 && random >= 0.2)
		{
			Weapon* weapon = Weapon::create("weapon/sword.png");
			weapon->setWeaponName("sword");
			weapon->initData();
			weapon->setPosition(Vec2(100 + random * 1000, 250));
			this->addChild(weapon);
			_weapons.pushBack((Weapon*)weapon);
		}
		else if (random < 0.8 && random >= 0.7)
		{
			Weapon* weapon = Weapon::create("weapon/axe.png");
			weapon->setWeaponName("axe");
			weapon->initData();
			weapon->setPosition(Vec2(100 + random * 1000, 250));
			this->addChild(weapon);
			_weapons.pushBack((Weapon*)weapon);
		}
		else if (random < 0.9 && random >= 0.8)
		{
			Weapon* weapon = Weapon::create("weapon/betterBow.png");
			weapon->setWeaponName("betterBow");
			weapon->initData();
			weapon->setPosition(Vec2(100 + random * 1000, 250));
			this->addChild(weapon);
			_weapons.pushBack((Weapon*)weapon);
		}
		else if (random <= 1.0 && random >= 0.9)
		{
			Weapon* weapon = Weapon::create("weapon/betterPistol.png");
			weapon->setWeaponName("betterPistol");
			weapon->initData();
			weapon->setPosition(Vec2(100 + random * 1000, 250));
			this->addChild(weapon);
			_weapons.pushBack((Weapon*)weapon);
		}
		else if (random <= 0.2 && random >= 0)
		{
			Weapon* weapon = Weapon::create("weapon/betterSword.png");
			weapon->setWeaponName("betterSword");
			weapon->initData();
			weapon->setPosition(Vec2(100 + random * 1000, 250));
			this->addChild(weapon);
			_weapons.pushBack((Weapon*)weapon);
		}
	}
	else
	{
		
		
	}
}

void SecurityMap::changeWeapon()
{
	_nowTime = GetCurrentTime();
	for (int i = 0; i < _weapons.size(); i++)
	{
		auto weapon = _weapons.at(i);
		Rect crWeapon = weapon->boundingBox();
		Rect crHero = _armature->getBoundingBox();

		if (crWeapon.intersectsRect(crHero))	//是否存在交集
		{
			if (_rocker->_jState && _nowTime - _lastChangeTime > 2 * 1000)
			{
				auto position1 = weapon->getPosition();
				auto position2 = _myHero.getMyWeapon()->getPosition();
				auto tampWeapon = _myHero.getMyWeapon();
				_myHero.setMyWeapon(weapon);
				_myHero.getMyWeapon()->setPosition(position2);
				weapon = tampWeapon;
				weapon->setPosition(position1);
				_weapons.pushBack(weapon);
				if (_myHero.getMyWeapon()->getWeaponName() == "betterBow")
					_armature->getArmature()->getSlot("weapon")->setDisplayIndex(0);
				else if (_myHero.getMyWeapon()->getWeaponName() == "betterSword")
					_armature->getArmature()->getSlot("weapon")->setDisplayIndex(1);
				else if (_myHero.getMyWeapon()->getWeaponName() == "axe")
					_armature->getArmature()->getSlot("weapon")->setDisplayIndex(2);
				else if (_myHero.getMyWeapon()->getWeaponName() == "betterPistol")
					_armature->getArmature()->getSlot("weapon")->setDisplayIndex(3);
				else if (_myHero.getMyWeapon()->getWeaponName() == "bow")
					_armature->getArmature()->getSlot("weapon")->setDisplayIndex(4);
				else if (_myHero.getMyWeapon()->getWeaponName() == "pistol")
					_armature->getArmature()->getSlot("weapon")->setDisplayIndex(5);
				else if (_myHero.getMyWeapon()->getWeaponName() == "sword")
					_armature->getArmature()->getSlot("weapon")->setDisplayIndex(6);
				_lastChangeTime = GetCurrentTime();
			}
		}
	}
}

void SecurityMap::menuPauseCallBack(cocos2d::Ref* pSender)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	CCRenderTexture* renderTexture = CCRenderTexture::create(visibleSize.width, visibleSize.height);
	//遍历当前类的所有子节点信息，画入renderTexture中。
	renderTexture->begin();
	this->visit();
	renderTexture->end();

	Director::getInstance()->pushScene(GamePause::scene(renderTexture));
}

void SecurityMap::menuWeaponCallBack(cocos2d::Ref* pSender)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	CCRenderTexture* renderTexture = CCRenderTexture::create(visibleSize.width, visibleSize.height);
	//遍历当前类的所有子节点信息，画入renderTexture中。
	renderTexture->begin();
	this->visit();
	renderTexture->end();
	Director::getInstance()->pushScene(WeaponMessage::scene(renderTexture));
}

void SecurityMap::menuEnemyCallBack(cocos2d::Ref* pSender)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	CCRenderTexture* renderTexture = CCRenderTexture::create(visibleSize.width, visibleSize.height);
	//遍历当前类的所有子节点信息，画入renderTexture中。
	renderTexture->begin();
	this->visit();
	renderTexture->end();
	Director::getInstance()->pushScene(EnemyMessage::scene(renderTexture));
}