#ifndef ENDSCENE_H_
#define ENDSCENE_H_
#include "cocos2d.h"
#include "TollgateScene.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;
class EndScene : public Layer
{
private:
	Button *startButton;
public:
	EndScene();
	~EndScene();
	static Scene* scene();
	CREATE_FUNC(EndScene);
	virtual bool init();
	void createStartButton();
	void showScore();
	void onEnter();
	static int score;
};
#endif
