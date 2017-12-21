#ifndef _Entity_H_
#define _Entity_H_
#include"cocos2d.h"
USING_NS_CC;
class Entity :public Node
{
public:
	Entity();
	~Entity();
	Sprite *getSprite();//获取精灵
	Sprite *getEffect();//获取特效
	void bindSprite(Sprite *sprtie);//绑定精灵
	void bindEffect(Sprite *sprite);//绑定特效
	Rect getBoundingBox();//获取碰撞范围

	/*???????*/
	/*the following 3 functions need to be virtual*/
	virtual void show() = 0;
	virtual void hide() = 0;
	virtual void reset() = 0;

private:
	Sprite *m_sprite;
	Sprite *m_effect;

};
#endif