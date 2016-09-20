#ifndef _PRESCENE_H_
#define _PRESCENE_H_

#include "cocos2d.h"
#include "StartScene.h"
class PreScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	void traslate(float dt);
	virtual bool init();
	CREATE_FUNC(PreScene);
};

#endif // __HELLOWORLD_SCENE_H__
