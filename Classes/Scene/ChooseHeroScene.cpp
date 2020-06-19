#include"ChooseHeroScene.h"

USING_NS_CC;

Scene* ChooseHero::createScene(int money)
{
    return ChooseHero::create(money);
}

ChooseHero* ChooseHero::createByBattleMap(BattleMap* combatScene)
{
    ChooseHero* layer = new(std::nothrow)ChooseHero;
    if (layer && layer->init(combatScene->getMyMoney()) && layer->initHero(combatScene))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return NULL;
}

ChooseHero* ChooseHero::create(int money)
{
    ChooseHero* layer = new(std::nothrow)ChooseHero;
    if (layer && layer->init(money))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return NULL;
}

bool ChooseHero::init(int money)
{
    if (!Scene::init())
    {
        return false;
    }
    _money = money;
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    seMap = TMXTiledMap::create("map/securityMap0.tmx");
    addChild(seMap, 0, 100);


    MenuItemImage* archerImg = MenuItemImage::create(
        "hero_enemy/Archer.png",
        "",
        CC_CALLBACK_0(ChooseHero::chooseCallBack, this, "Archer"));
    archerImg->setPosition(Director::getInstance()->convertToGL(Vec2(1000, 340)));

    MenuItemImage* paladinImg = MenuItemImage::create(
        "hero_enemy/Paladin.png",
        "",
        CC_CALLBACK_0(ChooseHero::chooseCallBack, this, "Paladin"));
    paladinImg->setPosition(Director::getInstance()->convertToGL(Vec2(600, 400)));

    MenuItemImage* berserkerImg = MenuItemImage::create(
        "hero_enemy/Berserker.png",
        "",
        CC_CALLBACK_0(ChooseHero::chooseCallBack, this, "Berserker"));
    berserkerImg->setPosition(Director::getInstance()->convertToGL(Vec2(200, 500)));

    Menu* menu = Menu::create(archerImg,paladinImg,berserkerImg,NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    
    _archer.initHeroData("Archer");
    _paladin.initHeroData("Paladin");
    _berserker.initHeroData("Berserker");

    return true;
}

bool ChooseHero::initHero(BattleMap* combatScene)
{
    _archer = combatScene->_archer;
    _paladin = combatScene->_paladin;
    _berserker = combatScene->_berserker;

    return true;
}

void ChooseHero::chooseCallBack(const std::string hero)
{
    auto chooseSc = HeroMessage::createScene(hero, this);
    Director::getInstance()->replaceScene(chooseSc);
}