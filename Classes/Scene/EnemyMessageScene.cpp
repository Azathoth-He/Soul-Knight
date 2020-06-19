#include"EnemyMessageScene.h"

USING_NS_CC;

Scene* EnemyMessage::scene(CCRenderTexture* sqr)
{
	Scene* scene = Scene::create();
	EnemyMessage* layer = EnemyMessage::create();
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

bool EnemyMessage::init()
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
		CC_CALLBACK_1(EnemyMessage::menuPreviousPageCallback, this));
	previousItem->setPosition(Vec2(visibleSize.width / 2 - 450, visibleSize.height / 2));

	MenuItemImage* nextItem = CCMenuItemImage::create(
		"next.png",
		"next.png",
		CC_CALLBACK_1(EnemyMessage::menuNextPageCallback, this));
	nextItem->setPosition(Vec2(visibleSize.width / 2 + 450, visibleSize.height / 2));

	MenuItemImage* exitItem = CCMenuItemImage::create(
		"pause/LittleEnd.png",
		"pause/LittleEnd1.png",
		CC_CALLBACK_1(EnemyMessage::menuExitCallback, this));
	exitItem->setPosition(Vec2(visibleSize.width - 100, visibleSize.height - 100));

	Menu* menu = Menu::create(previousItem, nextItem, exitItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 2);

	initData();

	return true;
}

void EnemyMessage::initData()
{
	page = 1;
	enemyData = cocos2d::FileUtils::getInstance()->getValueMapFromFile("hero_enemy\\EnemyData.plist");
	auto enemy1 = enemyData.at("enemy1").asValueMap();

	Sprite* _enemy1 = Sprite::create("hero_enemy/enemy1.png");
	_enemy1->setPosition(480, 340);
	addChild(_enemy1, 2, 201);

	Sprite* _enemy2 = Sprite::create("hero_enemy/enemy2.png");
	_enemy2->setPosition(480, 340);
	_enemy2->setVisible(false);
	addChild(_enemy2, 2, 202);

	Sprite* _enemy3 = Sprite::create("hero_enemy/enemy3.png");
	_enemy3->setPosition(480, 340);
	_enemy3->setVisible(false);
	addChild(_enemy3, 2, 203);

	Sprite* _enemy4 = Sprite::create("hero_enemy/enemy4.png");
	_enemy4->setPosition(480, 340);
	_enemy4->setVisible(false);
	addChild(_enemy4, 2, 204);

	Sprite* _enemy5 = Sprite::create("hero_enemy/enemy5.png");
	_enemy5->setPosition(480, 340);
	_enemy5->setVisible(false);
	addChild(_enemy5, 2, 205);

	Label* healthLabel = Label::createWithSystemFont("Health:", "Arial", 25);
	healthLabel->setPosition(Vec2(700, 500));
	addChild(healthLabel, 2);
	Label* attackLabel = Label::createWithSystemFont("Attack:", "Arial", 25);
	attackLabel->setPosition(Vec2(700, 400));
	addChild(attackLabel, 2);
	Label* attackRateLabel = Label::createWithSystemFont("AttackRate:", "Arial", 25);
	attackRateLabel->setPosition(Vec2(700, 300));
	addChild(attackRateLabel, 2);

	std::string _health = StringUtils::format("%d", enemy1["health"].asValueVector().at(0).asInt());
	Label* health = Label::createWithSystemFont(_health, "Arial", 25);
	health->setPosition(Vec2(750, 500));
	addChild(health, 2, 101);

	std::string _attack = StringUtils::format("%d", enemy1["attack"].asValueVector().at(0).asInt());
	Label* attack = Label::createWithSystemFont(_attack, "Arial", 25);
	attack->setPosition(Vec2(750, 400));
	addChild(attack, 2, 102);

	std::string _attackRate = StringUtils::format("%.2f", enemy1["attackRate"].asValueVector().at(0).asFloat());
	Label* attackRate = Label::createWithSystemFont(_attackRate, "Arial", 25);
	attackRate->setPosition(Vec2(800, 300));
	addChild(attackRate, 2, 103);
}

void EnemyMessage::updateData()
{
	std::string enemyName = StringUtils::format("enemy%d", page);
	auto enemy = enemyData.at(enemyName).asValueMap();

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
	Sprite* sprite = (Sprite*)this->getChildByTag(200 + page);
	sprite->setVisible(true);

	std::string _health = StringUtils::format("%d", enemy["health"].asValueVector().at(0).asInt());
	Label* healthLabel = (Label*)this->getChildByTag(101);
	healthLabel->setString(_health);

	std::string _attack = StringUtils::format("%d", enemy["attack"].asValueVector().at(0).asInt());
	Label* attackLabel = (Label*)this->getChildByTag(102);
	attackLabel->setString(_attack);

	std::string _attackRate = StringUtils::format("%.2f", enemy["attackRate"].asValueVector().at(0).asFloat());
	Label* attackRateLabel = (Label*)this->getChildByTag(103);
	attackRateLabel->setString(_attackRate);
}

void EnemyMessage::menuNextPageCallback(cocos2d::Ref* pSender)
{
	if (page == 5)
		page = 1;
	else
		page++;
	updateData();
}

void EnemyMessage::menuPreviousPageCallback(cocos2d::Ref* pSender)
{
	if (page == 1)
		page = 5;
	else
		page--;
	updateData();
}

void EnemyMessage::menuExitCallback(cocos2d::Ref* pSender)
{
	Director::getInstance()->popScene();
}