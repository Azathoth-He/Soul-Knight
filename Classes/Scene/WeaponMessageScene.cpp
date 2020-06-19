#include"WeaponMessageScene.h"

USING_NS_CC;

Scene* WeaponMessage::scene(CCRenderTexture* sqr)
{
	Scene* scene = Scene::create();
	WeaponMessage* layer = WeaponMessage::create();
	scene->addChild(layer, 1);
	//使用截图的sqr纹理图片创建Sprite
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* back_spr = Sprite::createWithTexture(sqr->getSprite()->getTexture());
	back_spr->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
	//坐标系不同，Y轴翻转
	back_spr->setFlipY(true);
	//改变背景颜色
	back_spr->setColor(Color3B(105, 105, 105));
	scene->addChild(back_spr);
	return scene;
}

bool WeaponMessage::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = Sprite::create("mapBackground.png");
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	addChild(bg, 0);

	MenuItemImage* previousItem = CCMenuItemImage::create(
		"previous.png",
		"previous.png",
		CC_CALLBACK_1(WeaponMessage::menuPreviousPageCallback, this));
	previousItem->setPosition(Vec2(visibleSize.width / 2 - 450, visibleSize.height / 2));

	MenuItemImage* nextItem = CCMenuItemImage::create(
		"next.png",
		"next.png",
		CC_CALLBACK_1(WeaponMessage::menuNextPageCallback, this));
	nextItem->setPosition(Vec2(visibleSize.width / 2 + 450, visibleSize.height / 2));

	MenuItemImage* exitItem = CCMenuItemImage::create(
		"pause/LittleEnd.png",
		"pause/LittleEnd1.png",
		CC_CALLBACK_1(WeaponMessage::menuExitCallback, this));
	exitItem->setPosition(Vec2(visibleSize.width - 100, visibleSize.height - 100));

	Menu* menu = Menu::create(previousItem, nextItem, exitItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 2);

	initData();

	return true;
}

void WeaponMessage::initData()
{
	page = 1;
	weaponData = cocos2d::FileUtils::getInstance()->getValueMapFromFile("weapon\\weaponData.plist");
	auto weapon1 = weaponData.at("bow").asValueMap();

	Sprite* _weapon1 = Sprite::create("weapon/bow.png");
	_weapon1->setPosition(480, 340);
	addChild(_weapon1, 2, 201);

	Sprite* _weapon2 = Sprite::create("weapon/axe.png");
	_weapon2->setPosition(480, 340);
	_weapon2->setVisible(false);
	addChild(_weapon2, 2, 202);

	Sprite* _weapon3 = Sprite::create("weapon/pistol.png");
	_weapon3->setPosition(480, 340);
	_weapon3->setVisible(false);
	addChild(_weapon3, 2, 203);

	Sprite* _weapon4 = Sprite::create("weapon/sword.png");
	_weapon4->setPosition(480, 340);
	_weapon4->setVisible(false);
	addChild(_weapon4, 2, 204);

	Sprite* _weapon5 = Sprite::create("weapon/betterBow.png");
	_weapon5->setPosition(480, 340);
	_weapon5->setVisible(false);
	addChild(_weapon5, 2, 205);

	Sprite* _weapon6 = Sprite::create("weapon/betterSword.png");
	_weapon6->setPosition(480, 340);
	_weapon6->setVisible(false);
	addChild(_weapon6, 2, 206);

	Sprite* _weapon7 = Sprite::create("weapon/betterPistol.png");
	_weapon7->setPosition(480, 340);
	_weapon7->setVisible(false);
	addChild(_weapon7, 2, 207);

	Label* healthLabel = Label::createWithSystemFont("Attack:", "Arial", 25);
	healthLabel->setPosition(Vec2(700, 500));
	addChild(healthLabel, 2);
	Label* attackLabel = Label::createWithSystemFont("AttackRate:", "Arial", 25);
	attackLabel->setPosition(Vec2(700, 400));
	addChild(attackLabel, 2);
	Label* attackRateLabel = Label::createWithSystemFont("magicUse:", "Arial", 25);
	attackRateLabel->setPosition(Vec2(700, 300));
	addChild(attackRateLabel, 2);

	std::string _health = StringUtils::format("%d", weapon1["attack"].asValueVector().at(0).asInt());
	Label* health = Label::createWithSystemFont(_health, "Arial", 25);
	health->setPosition(Vec2(750, 500));
	addChild(health, 2, 101);

	std::string _attack = StringUtils::format("%.2f", weapon1["attackRate"].asValueVector().at(0).asFloat());
	Label* attack = Label::createWithSystemFont(_attack, "Arial", 25);
	attack->setPosition(Vec2(800, 400));
	addChild(attack, 2, 102);

	std::string _attackRate = StringUtils::format("%d", weapon1["magicUse"].asValueVector().at(0).asInt());
	Label* attackRate = Label::createWithSystemFont(_attackRate, "Arial", 25);
	attackRate->setPosition(Vec2(800, 300));
	addChild(attackRate, 2, 103);
}

void WeaponMessage::updateData()
{
	ValueMap weapon;
	if (page == 1)
		weapon = weaponData.at("bow").asValueMap();
	else if (page == 2)
		weapon = weaponData.at("axe").asValueMap();
	else if (page == 3)
		weapon = weaponData.at("pistol").asValueMap();
	else if (page == 4)
		weapon = weaponData.at("sword").asValueMap();
	else if (page == 5)
		weapon = weaponData.at("betterBow").asValueMap();
	else if (page == 6)
		weapon = weaponData.at("betterSword").asValueMap();
	else if (page == 7)
		weapon = weaponData.at("betterPistol").asValueMap();

	Sprite* sprite1 = (Sprite*)this->getChildByTag(201);
	sprite1->setVisible(false);
	Sprite* sprite2 = (Sprite*)this->getChildByTag(202);
	sprite2->setVisible(false);
	Sprite* sprite3 = (Sprite*)this->getChildByTag(203);
	sprite3->setVisible(false);
	Sprite* sprite4 = (Sprite*)this->getChildByTag(204);
	sprite4->setVisible(false);
	Sprite* sprite5 = (Sprite*)this->getChildByTag(205);
	sprite5->setVisible(false);
	Sprite* sprite6 = (Sprite*)this->getChildByTag(206);
	sprite6->setVisible(false);
	Sprite* sprite7 = (Sprite*)this->getChildByTag(207);
	sprite7->setVisible(false);
	Sprite* sprite = (Sprite*)this->getChildByTag(200 + page);
	sprite->setVisible(true);

	std::string _health = StringUtils::format("%d", weapon["attack"].asValueVector().at(0).asInt());
	Label* healthLabel = (Label*)this->getChildByTag(101);
	healthLabel->setString(_health);

	std::string _attack = StringUtils::format("%.2f", weapon["attackRate"].asValueVector().at(0).asFloat());
	Label* attackLabel = (Label*)this->getChildByTag(102);
	attackLabel->setString(_attack);

	std::string _attackRate = StringUtils::format("%d", weapon["magicUse"].asValueVector().at(0).asInt());
	Label* attackRateLabel = (Label*)this->getChildByTag(103);
	attackRateLabel->setString(_attackRate);
}

void WeaponMessage::menuNextPageCallback(cocos2d::Ref* pSender)
{
	if (page == 7)
		page = 1;
	else
		page++;
	updateData();
}

void WeaponMessage::menuPreviousPageCallback(cocos2d::Ref* pSender)
{
	if (page == 1)
		page = 7;
	else
		page--;
	updateData();
}

void WeaponMessage::menuExitCallback(cocos2d::Ref* pSender)
{
	Director::getInstance()->popScene();
}