
#ifndef TollgateScene_H
#define TollgateScene_H
#include "cocos2d.h"
#include "Player2.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
class TollgateScene : public Layer
{
public:
	~TollgateScene();
	static Scene* scene();
	CREATE_FUNC(TollgateScene);
	virtual bool init();
	virtual void onExit() override;
	void createOprUi();
	Player* m_player = Player::create();//实例对象
	void touchButton(Object* object, ui::TouchEventType type);//回调函数：切换到暂停场景
};
#endif