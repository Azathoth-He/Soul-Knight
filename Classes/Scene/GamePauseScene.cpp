#include"GamePauseScene.h"
#include "SimpleAudioEngine.h" 

USING_NS_CC;

Scene* GamePause::scene(CCRenderTexture* sqr)
{
	Scene* scene = Scene::create();
	GamePause* layer = GamePause::create();
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

bool GamePause::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	auto bg = Sprite::create("pause/pauseBackground.png");
	bg->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
	addChild(bg, 0);
	
	//继续游戏
	MenuItemImage* continueItem = CCMenuItemImage::create(
		"pause/LittleStart.png",
		"pause/LittleStart1.png",
		CC_CALLBACK_1(GamePause::menuContinueCallback, this));
	continueItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 50));

	MenuItemImage* exitItem = CCMenuItemImage::create(
		"pause/LittleEnd.png",
		"pause/LittleEnd1.png",
		CC_CALLBACK_1(GamePause::menuExitCallback, this));
	exitItem->setPosition(Vec2(visibleSize.width / 2 - 120, visibleSize.height / 2 - 50));

	auto offMusic = MenuItemImage::create("StartGame/continueMusic.png", "StartGame/stopMusic.png");
	auto onMusic = MenuItemImage::create("StartGame/stopMusic.png", "StartGame/continueMusic.png");
	MenuItemToggle* musicMenu = MenuItemToggle::createWithCallback(
		CC_CALLBACK_1(GamePause::menuMusicCallBack, this),
		offMusic, onMusic, NULL
	);
	musicMenu->setPosition(Vec2(visibleSize.width / 2 + 120, visibleSize.height / 2 - 50));

	Menu* pMenu = Menu::create(continueItem, exitItem, musicMenu, NULL);
	pMenu->setPosition(Vec2::ZERO);
	this->addChild(pMenu, 2);
	return true;
}

void GamePause::menuContinueCallback(cocos2d::Ref* pSender)
{
	Director::getInstance()->popScene();

}

void GamePause::menuExitCallback(cocos2d::Ref* pSender)
{
	Director::getInstance()->end();
}

void GamePause::menuMusicCallBack(cocos2d::Ref* pSender)
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	if (audio->isBackgroundMusicPlaying())
	{
		audio->pauseBackgroundMusic();
	}
	else
	{
		audio->resumeBackgroundMusic();
	}
}