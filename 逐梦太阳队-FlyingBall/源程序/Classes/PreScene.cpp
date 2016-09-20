#include "PreScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* PreScene::createScene()
{
	auto scene = Scene::create();
	auto layer = PreScene::create();
	scene->addChild(layer);
	return scene;
}

// on "init" you need to initialize your instance
bool PreScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("PreLoad.csb");
	addChild(rootNode);
	  
	this->scheduleOnce(schedule_selector(PreScene::traslate),5.0f);

	return true;
}
void PreScene::traslate(float dt)
{
	//auto transition = TransitionSplitRows::create(1.5f, StartScene::createScene());
	Director::getInstance()->replaceScene(StartScene::createScene());
}