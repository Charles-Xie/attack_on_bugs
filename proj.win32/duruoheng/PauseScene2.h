
#ifndef PauseScene_H
#define PauseScene_H
#include "cocos2d.h"
#include "Background2.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class PauseScene : public Layer
{
public:
	~PauseScene();
	static Scene* scene();
	CREATE_FUNC(PauseScene);
	virtual bool init();
	virtual void onExit() override;
	void createOprUi();
	Background* background = Background::create();
	void touchButtonStart(Object* object, ui::TouchEventType type);
};
#endif
