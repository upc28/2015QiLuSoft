
#ifndef _LevelScene__
#define _LevelScene__

#include "cocos2d.h"
#include "LevelUtils.h"
#include "GameScene.h"
#include "StartScene.h"
USING_NS_CC;

class Level : public cocos2d::Layer
{
private:
    int successLevel = 3;  //
    int screenWidth , screenHeight; 
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
	void replace();
    CREATE_FUNC(Level);
};

#endif 

