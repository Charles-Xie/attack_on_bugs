#ifndef PAUSESCENE_H_
#define PAUSESCENE_H_
#include "cocos2d.h"
#include "TollgateScene.h"
#include "ui/CocosGUI.h"
#include "StartScene.h"
USING_NS_CC;
using namespace ui;
class PauseScene: public Layer
{
private:
	Button *restartButton;
	Button *resumeButton;
	Sprite * littleDevil;
public:
	PauseScene();
	~PauseScene();
	static Scene* scene();
	CREATE_FUNC(PauseScene);
	virtual bool init();
	virtual void onEnter();
	virtual void onExit() override;
	void createOprUi();
	void touchButtonResume(Object* object, ui::TouchEventType type);//�ص�������������ǰ��Ϸ����
};
#endif