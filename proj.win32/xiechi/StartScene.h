#ifndef STARTSCENE_H_
#define STARTSCENE_H_
#include "cocos2d.h"
#include "TollgateScene.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;
class StartScene : public Layer
{
private:
	Sprite *bgSprite;
	Button *startButtonEasy;
	Button *startButtonHard;
public:
	StartScene();
	~StartScene();
	static Scene* scene();
	CREATE_FUNC(StartScene);
	virtual bool init();
	void createStartButton();
	void newStartEasy(Object* object, ui::TouchEventType type);//�ص���������ʼ��Ϸ����
	void newStartHard(Object* object, ui::TouchEventType type);//�ص���������ʼ��Ϸ����
};
#endif
