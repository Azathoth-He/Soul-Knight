#include"ChooseHeroScene.h"

USING_NS_CC;

Scene* ChooseHero::createScene()
{
    return ChooseHero::create();
}

bool ChooseHero::init()
{
    if (!Scene::init())
    {
        return false;
    }

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
    

    return true;
}

void ChooseHero::chooseCallBack(const std::string hero)
{
    auto chooseSc = HeroMessage::createScene(hero);
    Director::getInstance()->replaceScene(chooseSc);
}