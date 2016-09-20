#include "LevelScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"

#define BK_MUSIC "bkmusic.mp3"

using namespace CocosDenshion;

Scene* Level::createScene()
{
	auto scene = Scene::create();
	auto layer = Level::create();  
	scene->addChild(layer);
	return scene;
}

bool Level::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visiblesize = Director::getInstance()->getVisibleSize();
	screenWidth = visiblesize.width;   
	screenHeight = visiblesize.height;

	auto rootNode = CSLoader::createNode("LevelSelect.csb");
	addChild(rootNode);

	auto button = dynamic_cast<Button*>(rootNode->getChildByName("back"));
	button->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type)
	{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		replace();
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
	break;
	default:
	break;
	}
	});
	//auto level1 = dynamic_cast<Sprite*>(rootNode->getChildByName("level1"));

	successLevel = LevelUtils::readLevelFromFile();
	std::string imagepath = "";  
	Sprite* levelsprite = nullptr;
	for (int i = 0; i < 9;i++)
	{
		std::string nodename = StringUtils::format("level%d", i + 1);
		levelsprite = dynamic_cast<Sprite*>(rootNode->getChildByName(nodename));
		levelsprite->setScaleX(1.0);
		if (i<successLevel)
		{
			imagepath = "level.png";
			std::string str = StringUtils::format("%d", i + 1);
			auto num = Label::createWithSystemFont(str, "Monaco", 50, Size(70, 70), TextHAlignment::CENTER);
			num->setPosition(levelsprite->getPosition());
			this->addChild(num, 2);
		}  
		else
		{  
			imagepath = "level_unlock.png";
		}
		levelsprite->initWithFile(imagepath);
		levelsprite->setScale(1.8f);
		levelsprite->setTag(i + 1); 
	}
	/**********************/
	int star_num = 0;
	for (int i = 0; i < 9; i++)
	{
		star_num = LevelUtils::readlevelstarFromFile(i + 1);
		for (int j = 0; j < 3;j++)
		{
			std::string nodename = StringUtils::format("Sprite%d_%d", i + 1,j+1);
			levelsprite = dynamic_cast<Sprite*>(rootNode->getChildByName(nodename));
			if (j < star_num)
			{
				imagepath = "star.png";
			}
			else   
			{
				imagepath = "star0.png";
			}
			auto sprite_star_temp = Sprite::create(imagepath);
			sprite_star_temp->setPosition(levelsprite->getPosition());
			this->addChild(sprite_star_temp);
		}
	}
	/*********************/
	auto gamelistener = EventListenerTouchOneByOne::create();
	gamelistener->onTouchBegan = [=](Touch* touch, Event* event)
	{
		Vec2 touchlocation = touch->getLocation();
		Vec2 nodelocation = this->convertToNodeSpace(touchlocation);
		for (int i = 0; i < 9;i++)
		{
			auto str_temp = StringUtils::format("level%d", i + 1);
			auto tempsprite = dynamic_cast<Sprite*>(rootNode->getChildByName(str_temp));

			if (tempsprite->getBoundingBox().containsPoint(touchlocation))
			{
				if (tempsprite->getTag()==100)
				{
				}
				else if (tempsprite->getTag()<=successLevel&&tempsprite->getTag()>0)
				{
					Director::getInstance()->getEventDispatcher()->removeEventListener(gamelistener);
					SimpleAudioEngine::getInstance()->playBackgroundMusic(BK_MUSIC, true);
					auto transition = TransitionMoveInR::create(1.0f, GameScene::createScene(tempsprite->getTag()));
					Director::getInstance()->replaceScene(transition);
				}
				else;
			}
		}
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(gamelistener, this);
	return true;

}

void Level :: replace()
{
	Director::getInstance()->replaceScene(StartScene::createScene());
}