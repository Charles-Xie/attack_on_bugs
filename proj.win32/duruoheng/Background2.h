#ifndef Background_H
#define Background_H
#include "cocos2d.h"
USING_NS_CC;
class Background : public Node
{
public:
	Background();
	~Background();
	CREATE_FUNC(Background);
	virtual bool init();
	void BackToGame();//由暂停到原场景
	void logic(float dt);
private:
	CC_SYNTHESIZE(int, m_iHP, iHP);
};
#endif

