#ifndef _LevelUtils_H_
#define _LevelUtils_H_

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class LevelUtils : public Ref
{
public:
    static int readLevelFromFile();
    static void writeLevelToFile(int level);
	static int readlevelstarFromFile(int level);
	static void writelevelstarToFile(int level, int num);
};


#endif 
