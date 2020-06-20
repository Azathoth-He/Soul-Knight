#include"BattleMapScene.h"

USING_NS_CC;

Scene* BattleMap::createScene(SecurityMap* combatScene)
{
	return  BattleMap::create(combatScene);
}

BattleMap* BattleMap::createByBattleMap(BattleMap* combatScene)
{
	BattleMap* layer = new(std::nothrow)BattleMap;
	if (layer && layer->initLevel2(combatScene))
	{
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return NULL;
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
	_factory = combatScene->_factory;
	_archer = combatScene->_archer;
	_paladin = combatScene->_paladin;
	_berserker = combatScene->_berserker;

	_myHero.setCurrentHealth(_myHero.getMaxHealth());
	_myHero.setCurrentMagic(_myHero.getMaxMagic());
	_myHero.setCurrentShiled(_myHero.getMaxShield());

	auto collision = _map->getLayer("collision");
	collision->setVisible(false);

	TMXObjectGroup* group = _map->getObjectGroup("object");
	ValueMap spawnPoint = group->getObject("hero");

	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();

	auto weaponName = _myHero.getMyWeapon()->getWeaponName();
	_myHero.getMyWeapon()->removeFromParentAndCleanup(true);
	_myHero.setMyWeapon(Weapon::create("weapon/" + weaponName + ".png"));
	_myHero.getMyWeapon()->setWeaponName(weaponName);
	_myHero.getMyWeapon()->initData();

	initHRocker();
	initIcon();
	initStateBox();
	initEnemy(9);
	initBox(3);

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

	_armature->setPosition(Vec2(x, y));
	addChild(_armature);

	combatScene->cleanup();

	return true;
}

bool BattleMap::initLevel2(BattleMap* combatScene)
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	scheduleUpdate();

	_map = TMXTiledMap::create("map/BattleMap2.0.tmx");
	addChild(_map, 0, 100);

	_myMoney = combatScene->getMyMoney();
	_myHero = combatScene->getMyHero();
	_factory = combatScene->_factory;
	_archer = combatScene->_archer;
	_paladin = combatScene->_paladin;
	_berserker = combatScene->_berserker;

	_myHero.setCurrentHealth(_myHero.getMaxHealth());
	_myHero.setCurrentMagic(_myHero.getMaxMagic());
	_myHero.setCurrentShiled(_myHero.getMaxShield());

	auto collision = _map->getLayer("collision");
	collision->setVisible(false);

	TMXObjectGroup* group = _map->getObjectGroup("object");
	ValueMap spawnPoint = group->getObject("hero");

	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();

	auto weaponName = _myHero.getMyWeapon()->getWeaponName();
	_myHero.getMyWeapon()->removeFromParentAndCleanup(true);
	_myHero.setMyWeapon(Weapon::create("weapon/" + weaponName + ".png"));
	_myHero.getMyWeapon()->setWeaponName(weaponName);
	_myHero.getMyWeapon()->initData();

	initHRocker();
	initIcon();
	initStateBox();
	initEnemy(14);
	initBox(3);

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

	_armature->setPosition(Vec2(x, y));
	addChild(_armature);

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
	money->setPosition(Vec2(origin.x + visibleSize.width - 200, origin.y + visibleSize.height - 40));
	this->addChild(money, 1, 102);

	std::string myMoney = StringUtils::format("%d", _myMoney);
	auto moneyLabel = Label::createWithSystemFont(myMoney, "Arial", 25);
	moneyLabel->setPosition(Vec2(origin.x + visibleSize.width - 130,
		origin.y + visibleSize.height - 38));
	moneyLabel->setTag(103);
	this->addChild(moneyLabel);

	auto weaponBox = Sprite::create("weaponBox.png");
	weaponBox->setPosition(Vec2(origin.x + visibleSize.width - 130, origin.y + 200));
	weaponBox->setOpacity(80);
	this->addChild(weaponBox, 3, 20);
	
	_myHero.getMyWeapon()->setPosition(Vec2(origin.x + visibleSize.width - 130, origin.y + 200));
	addChild(_myHero.getMyWeapon(), 3);


	MenuItemImage* pauseMenu = MenuItemImage::create(
		"pause/pause.png",
		"pause/pause.png",
		CC_CALLBACK_1(BattleMap::menuPauseCallBack, this)
	);
	pauseMenu->setPosition(Vec2(visibleSize.width - pauseMenu->getContentSize().width / 2,
		visibleSize.height - pauseMenu->getContentSize().height / 2));
	pauseMenu->setOpacity(0);
	Menu* pMenu = Menu::create(pauseMenu, NULL);
	pMenu->setPosition(Vec2::ZERO);
	pMenu->setTag(105);
	this->addChild(pMenu, 1);

	Sprite* pauseItem = Sprite::create("pause/pause.png");
	pauseItem->setPosition(Vec2(visibleSize.width - pauseItem->getContentSize().width / 2,
		visibleSize.height - pauseItem->getContentSize().height / 2));
	pauseItem->setTag(104);
	this->addChild(pauseItem);

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

void BattleMap::updateHeroState()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto xuetiao = this->getChildByTag(301);
	float propotion1 = (float)_myHero.getCurrentHealth() / (float)_myHero.getMaxHealth();
	xuetiao->setContentSize(Size(180 * propotion1, 19));
	xuetiao->setPosition(Vec2(90 + xuetiao->getContentSize().width / 2, visibleSize.height - 35) - _offset);

	auto lantiao = this->getChildByTag(302);
	float propotion2 = (float)_myHero.getCurrentMagic() / (float)_myHero.getMaxMagic();
	lantiao->setContentSize(Size(180 * propotion2, 19));
	lantiao->setPosition(Vec2(90 + lantiao->getContentSize().width / 2, visibleSize.height - 80) - _offset);

	auto hudun = this->getChildByTag(303);
	float propotion3 = (float)_myHero.getCurrentShiled() / (float)_myHero.getMaxShield();
	hudun->setContentSize(Size(180 * propotion3, 19));
	hudun->setPosition(Vec2(90 + hudun->getContentSize().width / 2, visibleSize.height - 125) - _offset);

	Label* healthLabel = (Label*)this->getChildByTag(401);
	std::string health = StringUtils::format("%d/%d", _myHero.getCurrentHealth(), _myHero.getMaxHealth());
	healthLabel->setString(health);
	healthLabel->setPosition(Vec2(180, visibleSize.height - 35) - _offset);

	Label* magicLabel = (Label*)this->getChildByTag(402);
	std::string magic = StringUtils::format("%d/%d", _myHero.getCurrentMagic(), _myHero.getMaxMagic());
	magicLabel->setString(magic);
	magicLabel->setPosition(Vec2(180, visibleSize.height - 80) - _offset);

	Label* shieldLabel = (Label*)this->getChildByTag(403);
	std::string shield = StringUtils::format("%d/%d", _myHero.getCurrentShiled(), _myHero.getMaxShield());
	shieldLabel->setString(shield);
	shieldLabel->setPosition(Vec2(180, visibleSize.height - 125) - _offset);

}

void BattleMap::update(float dt)
{
	updateHeroPosition();
	updateHeroDirction();
	updateHeroState();
	if (_rocker->_jState)
	{
		generateWeapon();
		heroAttack();
		changeWeapon();
	}
	updateOthers();
	attackHero();
	updateEnemy();
	getProp();
}

void BattleMap::updateHeroPosition()
{
	if (_rocker->getAvailable())
	{
		auto oldPosition = _armature->getPosition();
		auto angle = _rocker->getAngle();
		auto positionDelta = Vec2(cos(angle) * _myHero.getMoveSpeed() / 30/*FRAMES_PER_SECOND*/,
			sin(angle) * _myHero.getMoveSpeed() / 30/*FRAMES_PER_SECOND*/);
		auto newPosition = oldPosition + 5 * positionDelta;

		MapInformation mapInfo;
		bool isBorder = mapInfo.checkBorder((TMXTiledMap*)_map, newPosition);
		bool isNextStep = mapInfo.checkNextStep((TMXTiledMap*)_map, newPosition) && _killEnemy >= 5;
		bool isOver = mapInfo.checkNewScene((TMXTiledMap*)_map, newPosition) && _killEnemy >= 10;


		if (isNextStep)
			turnNextStep();
		else if (isOver)
			over();
		else if (isBorder);
		else
			_armature->setPosition(newPosition);
	}
	this->setViewpointCenter(_armature->getPosition());
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
	money->setPosition(Vec2(origin.x + visibleSize.width - 200, origin.y + visibleSize.height - 40) - _offset);

	std::string myMoney = StringUtils::format("%d", _myMoney);
	auto moneyLabel = (Label*)this->getChildByTag(103);
	moneyLabel->setString(myMoney);
	moneyLabel->setPosition(Vec2(origin.x + visibleSize.width - 130,
		origin.y + visibleSize.height - 38) - _offset);

	auto weaponBox = this->getChildByTag(20);
	weaponBox->setPosition(Vec2(origin.x + visibleSize.width - 130, origin.y + 200) - _offset);

	_myHero.getMyWeapon()->setPosition(Vec2(origin.x + visibleSize.width - 130, origin.y + 200) - _offset);

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

	auto pauseItem = this->getChildByTag(104);
	pauseItem->setPosition(Vec2(visibleSize.width - pauseItem->getContentSize().width / 2,
		visibleSize.height - pauseItem->getContentSize().height / 2) - _offset);

}

void BattleMap::updateHeroDirction()
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

void BattleMap::heroAttack()
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
			bullet->shootBullet(dir, 0, _myHero.getMyWeapon()->getAttack(), _map);
			_bullets.pushBack((Bullet*)bullet);

			_oldTime = GetCurrentTime();
		}
	}
	else if (_myHero.getMyWeapon()->getMode() == 1)
	{
		_nowTime = GetCurrentTime();

		if ((_nowTime - _oldTime) >= _myHero.getMyWeapon()->getAttackRate() * 1000
			&& _myHero.getCurrentMagic() - _myHero.getMyWeapon()->getMagicUse() >= 0)
		{
			_armature->getAnimation()->play("meleeAttack", 1);
			_oldTime = GetCurrentTime();

			auto magic = _myHero.getCurrentMagic() - _myHero.getMyWeapon()->getMagicUse();
			_myHero.setCurrentMagic(magic);

			for (int i = 0; i < _enemies.size(); i++)
			{
				auto enemy = _enemies.at(i);
				enemy->beAttackedByweapon();
			}
		}
	}
}

void BattleMap::attackHero()
{
	for (int i = 0; i < _bullets.size(); i++)
	{
		Bullet* bullet = _bullets.at(i);
		if (bullet->_camp == 1 && bullet->isVisible())
		{
			Rect crHero = _armature->boundingBox();
			Rect crBullet = bullet->boundingBox();

			if (crHero.intersectsRect(crBullet))	//是否存在交集
			{
				if (_myHero.getCurrentShiled() > 0)
				{
					int shield = _myHero.getCurrentShiled() - bullet->_attack;
					if (shield < 0)
						shield = 0;
					_myHero.setCurrentShiled(shield);
					bullet->setVisible(false);
				}
				else if (_myHero.getCurrentShiled() <= 0)
				{
					int health = _myHero.getCurrentHealth() - bullet->_attack;
					if (health <= 0)
						heroDie();
					_myHero.setCurrentHealth(health);
					bullet->setVisible(false);
				}
			}
		}
	}
	for (int i = 0; i < _enemies.size(); i++)
	{
		Enemy* enemy = _enemies.at(i);
		if (enemy->getMode() == 1)
		{
			Rect crEnemy = enemy->boundingBox();
			Rect crHero = _armature->getBoundingBox();

			enemy->_nowTime = GetCurrentTime();

			if (crEnemy.intersectsRect(crHero) && enemy->isVisible() &&
				(_nowTime - enemy->_lastAttackTime) >= enemy->getAttackRate() * 1000)//是否存在交集
			{

				if (_myHero.getCurrentShiled() > 0)
				{
					int shield = _myHero.getCurrentShiled() - enemy->getAttack();
					if (shield < 0)
						shield = 0;
					_myHero.setCurrentShiled(shield);
				}
				else if (_myHero.getCurrentShiled() <= 0)
				{
					int health = _myHero.getCurrentHealth() - enemy->getAttack();
					if (health <= 0)
						heroDie();
					_myHero.setCurrentHealth(health);
				}
				
				enemy->_lastAttackTime = GetCurrentTime();
			}
		}
	}
}

void BattleMap::heroDie()
{
	auto scene = ChooseHero::createByBattleMap(this);
	auto reScene = TransitionCrossFade::create(1.0f, scene);
	this->cleanup();
	Director::getInstance()->pushScene(scene);
}

void BattleMap::initEnemy(int n)
{
	for (int i = 1; i <= n; i++)
	{
		std::string enemy = StringUtils::format("enemy%d", i);
		TMXObjectGroup* group = _map->getObjectGroup("object");
		ValueMap spawnPoint = group->getObject(enemy);

		float x = spawnPoint["x"].asFloat();
		float y = spawnPoint["y"].asFloat();

		float random = CCRANDOM_0_1();
		Enemy* _enemy;
		if (random >= 0.0 && random < 0.2)
			_enemy = Enemy::create("hero_enemy/enemy1.png", "enemy1", this);
		if (random >= 0.2 && random < 0.4)
			_enemy = Enemy::create("hero_enemy/enemy2.png", "enemy2", this);
		if (random >= 0.4 && random < 0.6)
			_enemy = Enemy::create("hero_enemy/enemy3.png", "enemy3", this);
		if (random >= 0.6 && random < 0.8)
			_enemy = Enemy::create("hero_enemy/enemy4.png", "enemy4", this);
		if (random >= 0.8 && random <= 1.0)
			_enemy = Enemy::create("hero_enemy/enemy5.png", "enemy5", this);
		_enemy->setPosition(Vec2(x, y));
		if (i > n - 8)
			_enemy->setIsAvailable(false);
		_enemies.pushBack((Enemy*)_enemy);
		addChild(_enemy);
	}
}

void BattleMap::updateEnemy()
{
	MapInformation mapInfo;
	bool is1 = mapInfo.check1((TMXTiledMap*)_map, _armature->getPosition());
	bool is2 = mapInfo.check2((TMXTiledMap*)_map, _armature->getPosition());

	if (is1)
	{
		for (int i = 1; i < _enemies.size()-4; i++)
		{
			Enemy* enemy = _enemies.at(i);
			enemy->setIsAvailable(true);
		}
	}
	if (is2)
	{
		for (int i = _enemies.size() - 4; i < _enemies.size(); i++)
		{
			Enemy* enemy = _enemies.at(i);
			enemy->setIsAvailable(true);
		}
	}
}

void BattleMap::menuPauseCallBack(cocos2d::Ref* pSender)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	CCRenderTexture* renderTexture = CCRenderTexture::create(visibleSize.width, visibleSize.height);
	//遍历当前类的所有子节点信息，画入renderTexture中。
	renderTexture->begin();
	this->visit();
	renderTexture->end();

	Director::getInstance()->pushScene(GamePause::scene(renderTexture));
}

void BattleMap::getProp()
{
	for (int i = 0; i < _props.size(); i++)
	{
		Prop* prop = _props.at(i);
		Rect crProp = prop->boundingBox();
		Rect crHero = _armature->getBoundingBox();

		if (crProp.intersectsRect(crHero) && prop->isVisible())	//是否存在交集
		{
			int health = _myHero.getCurrentHealth() + prop->getAddHealth();
			if (health > _myHero.getMaxHealth())
				health = _myHero.getMaxHealth();
			_myHero.setCurrentHealth(health);

			int magic = _myHero.getCurrentMagic() + prop->getAddMagic();
			if (magic > _myHero.getMaxMagic())
				magic = _myHero.getMaxMagic();
			_myHero.setCurrentMagic(magic);

			int shield = _myHero.getCurrentShiled() + prop->getAddShield();
			if (shield > _myHero.getMaxShield())
				shield = _myHero.getMaxShield();
			_myHero.setCurrentShiled(shield);
			
			prop->setVisible(false);
		}
	}
}

void BattleMap::turnNextStep()
{
	unscheduleUpdate();
	auto nextScene = BattleMap::createByBattleMap(this);
	auto reScene = TransitionCrossFade::create(1.0f, nextScene);
	Director::getInstance()->pushScene(reScene);
}

void BattleMap::initBox(int n)
{
	for (int i = 1; i <= n; i++)
	{
		std::string num = StringUtils::format("box%d", i);
		TMXObjectGroup* group = _map->getObjectGroup("object");
		ValueMap spawnPoint = group->getObject(num);

		float x = spawnPoint["x"].asFloat();
		float y = spawnPoint["y"].asFloat();

		Sprite* box = Sprite::create("box.png");
		box->setPosition(x, y);

		_boxes.pushBack((Sprite*)box);
		addChild(box);
	}
}

void BattleMap::generateWeapon()
{
	for (int i = 0; i < _boxes.size(); i++)
	{
		Sprite* box = _boxes.at(i);

		Rect crBox = box->boundingBox();
		Rect crHero = _armature->getBoundingBox();

		Vec2 position = box->getPosition();
		if (crBox.intersectsRect(crHero) && box->isVisible())
		{
			float random = CCRANDOM_0_1();
			if (random >= 0.0 && random < 0.25)
			{
				Weapon* weapon = Weapon::create("weapon/betterBow.png");
				weapon->setWeaponName("betterBow");
				weapon->initData();
				weapon->setPosition(position + Vec2(50, 50));
				this->addChild(weapon);
				_weapons.pushBack((Weapon*)weapon);
			}
			else if (random < 0.5 && random >= 0.25)
			{
				Weapon* weapon = Weapon::create("weapon/betterPistol.png");
				weapon->setWeaponName("betterPistol");
				weapon->initData();
				weapon->setPosition(position + Vec2(50, 50));
				this->addChild(weapon);
				_weapons.pushBack((Weapon*)weapon);
			}
			else if (random < 0.75 && random >= 0.5)
			{
				Weapon* weapon = Weapon::create("weapon/betterSword.png");
				weapon->setWeaponName("betterSword");
				weapon->initData();
				weapon->setPosition(position + Vec2(50, 50));
				this->addChild(weapon);
				_weapons.pushBack((Weapon*)weapon);
			}
			else if (random <= 1.0 && random >= 0.75)
			{
				Weapon* weapon = Weapon::create("weapon/axe.png");
				weapon->setWeaponName("axe");
				weapon->initData();
				weapon->setPosition(position + Vec2(50, 50));
				this->addChild(weapon);
				_weapons.pushBack((Weapon*)weapon);
			}

			box->setVisible(false);
			Sprite* boxOpen = Sprite::create("boxOpen.png");
			boxOpen->setPosition(position);
			addChild(boxOpen);

		}
	}
}

void BattleMap::changeWeapon()
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

void BattleMap::over()
{
	auto scene = ChooseHero::createByBattleMap(this);
	auto reScene = TransitionCrossFade::create(1.0f, scene);
	this->cleanup();
	Director::getInstance()->pushScene(reScene);
}