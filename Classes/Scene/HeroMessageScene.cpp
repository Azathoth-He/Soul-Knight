#include"HeroMessageScene.h"

USING_NS_CC;

Scene* HeroMessage::createScene(const std::string hero, ChooseHero* scene)
{
	
	return HeroMessage::create(hero, scene);
}

HeroMessage* HeroMessage::create(const std::string hero, ChooseHero* scene)
{
	HeroMessage* layer = new(std::nothrow)HeroMessage;
	if (layer && layer->init(hero, scene))
	{
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return NULL;
}


bool HeroMessage::init(const std::string hero, ChooseHero* scene)
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	heroName = hero;
	myMoney = scene->getMoney();
	if (heroName == "Archer")
		myHero = scene->_archer;
	else if (heroName == "Paladin")
		myHero = scene->_paladin;
	else if (heroName == "Berserker")
		myHero = scene->_berserker;

	_archer = scene->_archer;
	_paladin = scene->_paladin;
	_berserker = scene->_berserker;

	auto bg = TMXTiledMap::create("map/heroMessagebg.tmx");
	bg->setPosition(Vec2(origin.x, origin.y));
	this->addChild(bg, 0);

	auto nameLabel = Label::createWithSystemFont(heroName, "Arial", 50);
	nameLabel->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - nameLabel->getContentSize().height / 2));
	this->addChild(nameLabel);

	auto heroImg = Sprite::create("hero_enemy/"+heroName+".png");
	heroImg->setContentSize(Size(100,116));
	heroImg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(heroImg, 1);

	auto healthImg = Sprite::create("health.png");
	healthImg->setContentSize(Size(90,125));
	healthImg->setPosition(Vec2(origin.x + 200, origin.y + 400));
	this->addChild(healthImg, 1);

	auto magicImg = Sprite::create("magic.png");
	magicImg->setContentSize(Size(85, 118));
	magicImg->setPosition(Vec2(origin.x + 195, origin.y + 340));
	this->addChild(magicImg,1);

	auto shieldImg = Sprite::create("shield.png");
	shieldImg->setContentSize(Size(90, 125));
	shieldImg->setPosition(Vec2(origin.x + 197, origin.y + 280));
	this->addChild(shieldImg, 1);

	auto xuetiao = Sprite::create("xuetiao.png");
	xuetiao->setContentSize(Size(8 * myHero.getMaxHealth(), 20));
	xuetiao->setTag(100);
	xuetiao->setPosition(Vec2(origin.x + 240 + xuetiao->getContentSize().width / 2, origin.y + 400));
	this->addChild(xuetiao, 1);

	auto lantiao = Sprite::create("lantiao.png");
	lantiao->setContentSize(Size(0.40 * myHero.getMaxMagic(), 20));
	lantiao->setTag(101);
	lantiao->setPosition(Vec2(origin.x + 240 + lantiao->getContentSize().width / 2, origin.y + 340));
	this->addChild(lantiao, 1);

	auto hudun = Sprite::create("hudun.png");
	hudun->setContentSize(Size(8 * myHero.getMaxShield(), 20));
	hudun->setTag(102);
	hudun->setPosition(Vec2(origin.x + 240 + hudun->getContentSize().width / 2, origin.y + 280));
	this->addChild(hudun, 1);


	auto money = Sprite::create("money.png");
	money->setContentSize(Size(65, 90));
	money->setPosition(Vec2(origin.x + visibleSize.width - 170, origin.y + visibleSize.height-40));
	this->addChild(money, 1);

	std::string _myMoney = StringUtils::format("%d", myMoney);
	auto moneyLabel = Label::createWithSystemFont(_myMoney, "Arial", 25);
	moneyLabel->setPosition(Vec2(origin.x + visibleSize.width - 100,
		origin.y + visibleSize.height - 38));
	moneyLabel->setTag(103);
	this->addChild(moneyLabel);

	MenuItemImage* upLevel = MenuItemImage::create(
		"upLevelButton.png",
		"upLevelButton1.png",
		CC_CALLBACK_0(HeroMessage::upLevelCallBack, this));
	upLevel->setPosition(Director::getInstance()->convertToGL(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - 180)));

	MenuItemImage* next = MenuItemImage::create(
		"next.png",
		"next1.png",
		CC_CALLBACK_0(HeroMessage::nextCallBack, this));
	
	next->setPosition(Director::getInstance()->convertToGL(Vec2(origin.x + visibleSize.width - 200,
		origin.y + visibleSize.height - 150)));


	Menu* menu = Menu::create(upLevel, next, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	std::string upLevelMoney = StringUtils::format("%d", myHero.getUpLevelMoney());
	auto moneyLabel1 = Label::createWithSystemFont(upLevelMoney, "Arial", 30);
	moneyLabel1->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + 180));
	moneyLabel1->Label::setTag(104);
	this->addChild(moneyLabel1);

	return true;
}

void HeroMessage::update(float dt)
{

	auto xuetiao = this->getChildByTag(100);
	xuetiao->setContentSize(Size(8 * myHero.getMaxHealth(), 20));
	xuetiao->setPosition(Vec2(240 + xuetiao->getContentSize().width / 2, 400));
	
	auto lantiao = this->getChildByTag(101);
	lantiao->setContentSize(Size(0.40 * myHero.getMaxMagic(), 20));
	lantiao->setPosition(Vec2(240 + lantiao->getContentSize().width / 2, 340));
	
	auto hudun = this->getChildByTag(102);
	hudun->setContentSize(Size(8 * myHero.getMaxShield(), 20));
	hudun->setPosition(Vec2(240 + hudun->getContentSize().width / 2, 280));

	std::string _myMoney = StringUtils::format("%d", myMoney);
	Label* moneyLabel = (Label*)this->getChildByTag(103);
	moneyLabel->setString(_myMoney);

	std::string upLevelMoney = StringUtils::format("%d", myHero.getUpLevelMoney());
	Label* moneyLabel1 = (Label*)this->getChildByTag(104);
	moneyLabel1->setString(upLevelMoney);
	
}

void HeroMessage::upLevelCallBack()
{
	if (myMoney >= myHero.getUpLevelMoney() && myHero.getLevel() < 9)
	{
		if (heroName == "Archer")
			_archer.levelUp();
		else if (heroName == "Paladin")
			_paladin.levelUp();
		else if (heroName == "Berserker")
			_berserker.levelUp();
		myMoney -= myHero.getUpLevelMoney();
		myHero.levelUp();
		this->scheduleOnce(schedule_selector(HeroMessage::update), 0.1f);
	}
}

void HeroMessage::nextCallBack()
{
	auto nextScene = SecurityMap::createScene(this);
	Director::getInstance()->replaceScene(nextScene);
}