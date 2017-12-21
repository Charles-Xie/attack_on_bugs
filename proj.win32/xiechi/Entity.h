#ifndef _Entity_H_
#define _Entity_H_
#include"cocos2d.h"
USING_NS_CC;
class Entity :public Node
{
public:
	Entity();
	~Entity();
	Sprite *getSprite();//��ȡ����
	Sprite *getEffect();//��ȡ��Ч
	void bindSprite(Sprite *sprtie);//�󶨾���
	void bindEffect(Sprite *sprite);//����Ч
	Rect getBoundingBox();//��ȡ��ײ��Χ

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