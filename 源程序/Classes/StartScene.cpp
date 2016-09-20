#include "StartScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio::timeline;

Scene* StartScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = StartScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool StartScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("Start.csb");

	addChild(rootNode);
	auto button = dynamic_cast<Button*>(rootNode->getChildByName("button"));
	button->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type)
	{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		next();
	default:
	break;
	}
	});
	auto end = dynamic_cast<Button*>(rootNode->getChildByName("end"));
	end->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type)
	{
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			exit();
			break;
		default:
			break;
		}
	});
	return true;
}

void StartScene::next()
{
	Director::getInstance()->replaceScene(Level::createScene());
}
void StartScene::exit()
{
	Director::getInstance()->end();
}