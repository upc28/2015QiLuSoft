#include "LevelUtils.h"


 int LevelUtils::readLevelFromFile()
{
	int successlevel = UserDefault::getInstance()->getIntegerForKey("SuccessLevel");
	if (successlevel)
	{
		return successlevel;
	}
	return 1; //
} 


 void LevelUtils::writeLevelToFile(int level){
    UserDefault::getInstance()->setIntegerForKey("SuccessLevel", level);
}


 void LevelUtils::writelevelstarToFile(int level, int num)
 {
	 switch (level)
	 {
	 case 1:
		 UserDefault::getInstance()->setIntegerForKey("1",num);
		 break;
	 case 2:
		 UserDefault::getInstance()->setIntegerForKey("2",num);
		 break;
	 case 3:
		 UserDefault::getInstance()->setIntegerForKey("3",num);
		 break;
	 case 4:
		 UserDefault::getInstance()->setIntegerForKey("4",num);
		 break;
	 case 5:
		 UserDefault::getInstance()->setIntegerForKey("5",num);
		 break;
	 case 6:
		 UserDefault::getInstance()->setIntegerForKey("6",num);
		 break;
	 case 7:
		 UserDefault::getInstance()->setIntegerForKey("7",num);
		 break;
	 case 8:
		 UserDefault::getInstance()->setIntegerForKey("8",num);
		 break;
	 case 9:
		 UserDefault::getInstance()->setIntegerForKey("9",num);
		 break;
	 default:
		 break;
	 }
 }

int LevelUtils::readlevelstarFromFile(int level)
 {
	 int star_num = 0;
	 switch (level)
	 {
	 case 1:
		 star_num = UserDefault::getInstance()->getIntegerForKey("1");
		 break;
	 case 2:
		 star_num = UserDefault::getInstance()->getIntegerForKey("2");
		 break;
	 case 3:
		 star_num = UserDefault::getInstance()->getIntegerForKey("3");
		 break;
	 case 4:
		 star_num = UserDefault::getInstance()->getIntegerForKey("4");
		 break;
	 case 5:
		 star_num = UserDefault::getInstance()->getIntegerForKey("5");
		 break;
	 case 6:
		 star_num = UserDefault::getInstance()->getIntegerForKey("6");
		 break;
	 case 7:
		 star_num = UserDefault::getInstance()->getIntegerForKey("7");
		 break;
	 case 8:
		 star_num = UserDefault::getInstance()->getIntegerForKey("8");
		 break;
	 case 9:
		 star_num = UserDefault::getInstance()->getIntegerForKey("9");
		 break;
	 default:
		 break;
	 }
	 if (star_num)
	 {
		 return star_num;
	 }
	 return 0;
 }