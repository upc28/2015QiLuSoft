#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "LevelScene.h"
#include "ui/CocosGUI.h"


USING_NS_CC;
using namespace ui;

class GameScene : public cocos2d::Layer
{
protected:
	bool star1_collsion = false;
	bool star2_collsion = false;
	bool star3_collsion = false;
	bool isready=true;
	bool finish = false;
	Vec2 ballposition = Vec2(0, 0);
	Button* button = nullptr;
	Text* text1 = nullptr;
	cocos2d::Sprite* ball=nullptr;
	cocos2d::Sprite* star1 = nullptr;
	cocos2d::Sprite* star2 = nullptr;
	cocos2d::Sprite* star3 = nullptr;
	cocos2d::Sprite* point1 = nullptr;
	cocos2d::Sprite* point2 = nullptr;
	cocos2d::Sprite* point3 = nullptr;
	cocos2d::Sprite* point4 = nullptr;
	cocos2d::Sprite* point5 = nullptr;
	cocos2d::Sprite* point6 = nullptr;
	cocos2d::Sprite* point7 = nullptr;
	cocos2d::EventListenerTouchOneByOne* gamelistener = nullptr;
	int star_num = 0;
	int screenwidth, screenhight;
	cocos2d::Menu* menu = nullptr;
public:
    static cocos2d::Scene* createScene(int _currentlevel);
    virtual bool init();
	void update(float delta);
	void collision_check();
	void over();
	bool bounder_check();
	void bombanimate(Vec2 position);
	void win();
    CREATE_FUNC(GameScene);
};

#endif // __HELLOWORLD_SCENE_H__
