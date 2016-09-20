#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
#include <cmath>
#include "SimpleAudioEngine.h"

#define STAR_MUSIC "stareffect.wav"
#define MENU_MUSIC "menueffect.wav"
#define BK_MUSIC "bkmusic.mp3"

//using namespace CocosDenshion;

static int currentlevel = 1;

using namespace CocosDenshion;
using namespace cocostudio::timeline;

Scene* GameScene::createScene(int _currentlevel)
{
	currentlevel = _currentlevel;
	auto scene = Scene::createWithPhysics();
    auto layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
	auto str_level = StringUtils::format("Level%d.csb", currentlevel);

    auto rootNode = CSLoader::createNode(str_level);
    addChild(rootNode);  
	
	
	Vec2 visiblesize = Director::getInstance()->getVisibleSize();
	screenwidth = visiblesize.x;
	screenhight = visiblesize.y;

	ball = dynamic_cast<Sprite*>(rootNode->getChildByName("ball"));
	auto body_ball = PhysicsBody::createCircle(ball->getContentSize().width / 2);
	body_ball->setGravityEnable(false);
	body_ball->setGroup(1);
	body_ball->setCollisionBitmask(0);
	body_ball->setCategoryBitmask(0);
	body_ball->getShape(0)->setRestitution(1.0f);
	body_ball->getShape(0)->setFriction(0);
	ball->setPhysicsBody(body_ball);

	ballposition = ball->getPosition();

	button = dynamic_cast<Button*>(rootNode->getChildByName("button"));
	//button->setPressedActionEnabled(true);
	button->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type)
	{
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			break;
		case cocos2d::ui::Widget::TouchEventType::MOVED:
			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			over();
			break;
		case cocos2d::ui::Widget::TouchEventType::CANCELED:
			break;
		default:
			break;
		}
	});
	int i = 1;
	while (1)
	{
		std::string str_wall = StringUtils::format("wall%d", i);
		auto wall = dynamic_cast<Sprite*>(rootNode->getChildByName(str_wall));
		if (wall==nullptr)
		{
			break;
		}
		PhysicsBody* body_wall = nullptr;
		if (currentlevel==8)
		{
			body_wall = PhysicsBody::createCircle(wall->getContentSize().width / 2);
		}
		else body_wall = PhysicsBody::createBox(Size(wall->getContentSize().width, wall->getContentSize().height));
		body_wall->setDynamic(false);
		body_wall->setGroup(1);
		body_wall->getShape(0)->setRestitution(1.0f);
		wall->setPhysicsBody(body_wall);
		wall->setVisible(true);
		
		if (currentlevel == 4)
		{
			auto move = MoveBy::create(3, Vec2(700, 0));
			auto move2 = MoveBy::create(3, Vec2(-700, 0));
			auto sequence = Sequence::create(move, move2, NULL);
			wall->runAction(RepeatForever::create(sequence));
		}
		if (currentlevel==5&&i==2)
		{
			auto move = MoveBy::create(4, Vec2(-500, 0));
			auto move2 = MoveBy::create(4, Vec2(500, 0));
			auto sequence = Sequence::create(move, move2, NULL);
			wall->runAction(RepeatForever::create(sequence));
		}
		if (currentlevel==6)
		{
			if (i == 1)
			{
				auto move = MoveBy::create(6, Vec2(-800, 0));
				auto move2 = MoveBy::create(6, Vec2(800, 0));
				auto sequence = Sequence::create(move, move2, NULL);
				wall->runAction(RepeatForever::create(sequence));
				wall->setScaleX(1.2f);
			}
			if (i==2)
			{
				auto move = MoveBy::create(4, Vec2(500, 0));
				auto move2 = MoveBy::create(4, Vec2(-500, 0));
				auto sequence = Sequence::create(move, move2, NULL);
				wall->runAction(RepeatForever::create(sequence));
			}
		}
		if (currentlevel==7&&i==1)
		{
			auto move = RotateBy::create(7, 360);
			wall->runAction(RepeatForever::create(move));
		}
		if (currentlevel==8)
		{
			auto move1 = MoveTo::create(3, Vec2(200, 716));
			auto move2 = MoveTo::create(3, Vec2(600, 716));
			auto move3 = MoveTo::create(3, Vec2(400, 970));
			wall->setScale(1.2f);
			if (i==1)
			{
				wall->runAction(RepeatForever::create(Sequence::create(move1, move2, move3,NULL)));
			}
			if (i == 2)
			{
				wall->runAction(RepeatForever::create(Sequence::create(move2, move3, move1,NULL)));
			}
			if (i == 3)
			{
				wall->runAction(RepeatForever::create(Sequence::create(move3, move1, move2,NULL)));
			}
		}
		i++;
	}
	
	star1 = dynamic_cast<Sprite*>(rootNode->getChildByName("star1"));
	star2 = dynamic_cast<Sprite*>(rootNode->getChildByName("star2"));
	star3 = dynamic_cast<Sprite*>(rootNode->getChildByName("star3"));
	if (currentlevel==9)
	{
		auto move1 = MoveBy::create(5, Vec2(600, 0));
		auto move2 = MoveBy::create(5, Vec2(-600, 0));
		auto move3 = MoveBy::create(2, Vec2(-300, 0));
		auto move4 = MoveBy::create(4, Vec2(600, 0));
		auto move5 = MoveTo::create(5, Vec2(700, 520));
		auto move6 = MoveTo::create(5, Vec2(100, 520));
		star1->runAction(RepeatForever::create(Sequence::create(move6, move5, NULL)));
		star2->runAction(RepeatForever::create(Sequence::create(move1, move2, NULL)));
		star3->runAction(RepeatForever::create(Sequence::create(move3, move4, move3, NULL)));
	}
	//star1->setTag(2);
	Vec2 starlocation = ball->getPosition();
	point1 = dynamic_cast<Sprite*>(rootNode->getChildByName("point1"));
	point1->setPosition(starlocation);
	point2 = dynamic_cast<Sprite*>(rootNode->getChildByName("point2"));
	point2->setPosition(starlocation);
	point3 = dynamic_cast<Sprite*>(rootNode->getChildByName("point3"));
	point3->setPosition(starlocation);
	point4 = dynamic_cast<Sprite*>(rootNode->getChildByName("point4"));
	point4->setPosition(starlocation);
	point5 = dynamic_cast<Sprite*>(rootNode->getChildByName("point5"));
	point5->setPosition(starlocation);
	point6 = dynamic_cast<Sprite*>(rootNode->getChildByName("point6"));
	point6->setPosition(starlocation);
	point7 = dynamic_cast<Sprite*>(rootNode->getChildByName("point7"));
	point7->setPosition(starlocation);

	gamelistener = EventListenerTouchOneByOne::create();
	
	gamelistener->onTouchBegan = [=](Touch* touch, Event* event)
	{
		Vec2 location = touch->getLocation();
		PhysicsShape* ps = body_ball->getShape(0);
		if (isready&&ps->containsPoint(location))
		{
			isready = false;
			return true;
		}
		return false;
	};
	gamelistener->onTouchMoved = [=](Touch* touch, Event* event)
	{
		Vec2 location = touch->getLocation();
		Vec2 distance = location - starlocation;
		point1->setPosition(Vec2(starlocation.x + distance.x / 7, starlocation.y + distance.y / 7));
		point2->setPosition(Vec2(starlocation.x + distance.x / 7 * 2, starlocation.y + distance.y / 7 * 2));
		point3->setPosition(Vec2(starlocation.x + distance.x / 7 * 3, starlocation.y + distance.y / 7 * 3));
		point4->setPosition(Vec2(starlocation.x + distance.x / 7 * 4, starlocation.y + distance.y / 7 * 4));
		point5->setPosition(Vec2(starlocation.x + distance.x / 7 * 5, starlocation.y + distance.y / 7 * 5));
		point6->setPosition(Vec2(starlocation.x + distance.x / 7 * 6, starlocation.y + distance.y / 7 * 6));
		point7->setPosition(location);
	};
	gamelistener->onTouchEnded = [=](Touch* touch, Event* event)
	{
		Vec2 distance = touch->getLocation() - starlocation;
		auto body_temp = ball->getPhysicsBody();	
		body_temp->setVelocity(distance);
		point1->setVisible(false);
		point2->setVisible(false);
		point3->setVisible(false);
		point4->setVisible(false);
		point5->setVisible(false);
		point6->setVisible(false);
		point7->setVisible(false);
		//gamelistener->setEnabled(false);
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(gamelistener, this);
	//SimpleAudioEngine::getInstance()->playBackgroundMusic(BK_MUSIC,true);
	this->scheduleUpdate();
    return true;
}


void GameScene::update(float delta)
{
	if (bounder_check())
	{
		auto body = ball->getPhysicsBody();
		body->setVelocity(Vec2::ZERO);
		ball->setPosition(ballposition);
		point1->setPosition(ballposition);
		point2->setPosition(ballposition);
		point3->setPosition(ballposition);
		point4->setPosition(ballposition);
		point5->setPosition(ballposition);
		point6->setPosition(ballposition);
		point7->setPosition(ballposition);
		point1->setVisible(true);
		point2->setVisible(true);
		point3->setVisible(true);
		point4->setVisible(true);
		point5->setVisible(true);
		point6->setVisible(true);
		point7->setVisible(true);
		star1->setVisible(true);
		star2->setVisible(true);
		star_num = 0;
		star1_collsion = false;
		star2_collsion = false;
		isready = true;
	}
}

bool GameScene::bounder_check()
{
	collision_check();
	if (ball->getPosition().x >= screenwidth || ball->getPosition().y >= screenhight || ball->getPosition().x < 0 || ball->getPosition().y < 0)
	{
		return true;
	}
	return false;
}

void GameScene::collision_check()
{
	if (!star1_collsion&&ball->getBoundingBox().intersectsCircle(star1->getPosition(), 14.0f))
	{
		SimpleAudioEngine::getInstance()->playEffect(STAR_MUSIC, false);
		star1->setVisible(false);
		star1_collsion = true;
		bombanimate(star1->getPosition());
		star_num++;
	}
	if (!star2_collsion&&ball->getBoundingBox().intersectsCircle(star2->getPosition(), 14.0f))
	{
		SimpleAudioEngine::getInstance()->playEffect(STAR_MUSIC, false);
		star2->setVisible(false);
		star2_collsion = true;
		bombanimate(star2->getPosition());
		star_num++;
	}
	if (!star3_collsion&&ball->getBoundingBox().intersectsCircle(star3->getPosition(), 14.0f))
	{   
		SimpleAudioEngine::getInstance()->playEffect(STAR_MUSIC, false);
		star3->setVisible(false);
		star3_collsion = true;
		bombanimate(star3->getPosition());
		star_num++;
		finish = true;
		over();
	}
}

void GameScene::over()
{
	button->setTouchEnabled(false);
	Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(0);
	auto finishspirte = Sprite::create("finish.png");
	finishspirte->setPosition(screenwidth / 2, screenhight / 2);
	finishspirte->setScale(0.7f);
	this->addChild(finishspirte);

	std::string str_level = StringUtils::format("level%dpng.png", currentlevel);
	auto levellabel = Sprite::create(str_level);
	levellabel->setPosition(screenwidth / 2, screenhight / 2 + 136);
	this->addChild(levellabel); 

	

	auto selectitem = MenuItemImage::create("menu.png","menu.png",
		[=](Ref *sender)
	{
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		Director::getInstance()->replaceScene(TransitionMoveInL::create(1.0f,Level::createScene()));
	});
	selectitem->setScale(0.7f);
	selectitem->setPosition(screenwidth / 2 - 140, screenhight / 2 - 180);


	auto restartitem = MenuItemImage::create("restart.png", "restart.png",
		[=](Ref *sender)
	{
		auto transition = TransitionFade::create(1.0f, GameScene::createScene(currentlevel));
		Director::getInstance()->replaceScene(transition);
	});
	restartitem->setScale(0.7f);
	restartitem->setPosition(screenwidth / 2, screenhight / 2 - 180);


	auto nextitem = MenuItemImage::create("next.png", "next.png", [=](Ref *sender)
	{
		auto transition = TransitionPageTurn::create(1.0f, GameScene::createScene(currentlevel+1),false);
		Director::getInstance()->replaceScene(transition);
	});
	nextitem->setScale(0.7f);
	nextitem->setPosition(screenwidth / 2+140, screenhight / 2 - 180);
	if (finish&&currentlevel!=9)
	{
		win();
		menu = Menu::create(selectitem, restartitem, nextitem, NULL);
	}
	else{
		Sprite* pause = nullptr;
		if (currentlevel==9&&finish)
		{
			if (LevelUtils::readlevelstarFromFile(currentlevel) < star_num)
			{
				LevelUtils::writelevelstarToFile(currentlevel, star_num);
			}
			pause = Sprite::create("nextpng.png");
			pause->setPosition(screenwidth / 2, screenhight / 2 - 50);
		}
		else
		{
			pause = Sprite::create("pausepng.png");
			pause->setPosition(screenwidth / 2, screenhight / 2 - 50);
		}
		this->addChild(pause);
		menu = Menu::create(selectitem, restartitem, NULL);
	}
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);
}

void GameScene::win()
{
	if (currentlevel == LevelUtils::readLevelFromFile())
	{
		LevelUtils::writeLevelToFile(currentlevel + 1);
	}
	if (LevelUtils::readlevelstarFromFile(currentlevel)<star_num)
	{
		LevelUtils::writelevelstarToFile(currentlevel, star_num);
	}
	auto sprit_win1 = Sprite::create("star0.png");
	sprit_win1->setPosition(screenwidth / 2 - 150, screenhight / 2 - 50);
	auto sprit_win2 = Sprite::create("star0.png");
	sprit_win2->setPosition(screenwidth / 2, screenhight / 2 - 50);
	auto sprit_win3 = Sprite::create("star0.png");
	sprit_win3->setPosition(screenwidth / 2+150, screenhight / 2 - 50);
	sprit_win1->setScale(1.5f);
	sprit_win2->setScale(1.5f);
	sprit_win3->setScale(1.5f);
	this->addChild(sprit_win1);
	this->addChild(sprit_win2);
	this->addChild(sprit_win3);
	for (int i = 0; i < star_num;i++)
	{
		auto sprit_win = Sprite::create("star.png");
		sprit_win->setScale(1.5f);
		if (i == 0)
		{
			sprit_win->setPosition(screenwidth / 2-150, screenhight / 2 - 50);
		}
		if (i==1)
		{
			sprit_win->setPosition(screenwidth / 2, screenhight / 2 - 50);
		}
		if (i == 2)
		{
			sprit_win->setPosition(screenwidth / 2+150, screenhight / 2 - 50);
		}
		this->addChild(sprit_win);
	}
	this->unscheduleUpdate();
}


void GameScene::bombanimate(Vec2 position)
{
	//Animation* blastanimation;
	auto explosition = ParticleExplosion::createWithTotalParticles(40);
	explosition->setPosition(position);
	explosition->setLife(0.5f);
	explosition->setStartRadius(15.0f);
	explosition->setStartRadiusVar(0);
	explosition->setEndRadius(35.0f);
	explosition->setEndRadiusVar(0);
	explosition->setStartColor(Color4F(0.98f,0.89f,0.34f,1.0f));
	explosition->setStartColorVar(Color4F(0, 0, 0, 0));
	explosition->setEndColor(Color4F(0.98f, 0.89f, 0.34f, 1.0f));
	explosition->setEndColorVar(Color4F(0, 0, 0, 0));
	this->addChild(explosition);
	
}