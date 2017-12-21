#ifndef Player_H
#define Player_H
#include "cocos2d.h"
USING_NS_CC;
class Player : public Node
{
public :
	Player();
	~Player();
	CREATE_FUNC(Player);
	virtual bool init();
	void moveToRight();
	void moveToLeft();
	void quickMove();
	void logic(float dt);
private:
	CC_SYNTHESIZE(int, m_iHP, iHP);
};
#endif
