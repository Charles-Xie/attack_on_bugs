#include "Monster.h"
#include"SimpleAudioEngine.h"
using namespace CocosDenshion;

Monster::Monster()
{
}


Monster::~Monster()
{
}

bool Monster::init()
{
	Sprite *s = Sprite::create("wei.png");

	Sprite* effect = Sprite::create("hurt.png");
	effect->setScale(0.7);
	bindEffect(effect);
	effect->setLocalZOrder(2);

	monsterBody = PhysicsBody::createCircle(s->getContentSize().height * 0.25);
	monsterBody->setEnabled(false);
	monsterBody->setGravityEnable(false);
	monsterBody->setCollisionBitmask(0x00000000);
	monsterBody->setContactTestBitmask(0x01);

	setPhysicsBody(monsterBody);
	setTag(1);
	setVisible(false);
	setHasEffect(false);
	setMaxHP();

	createSlider();
	return true;
}

void Monster::show()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	if (getSprite() != NULL)
	{
		HPslider->setPercent(100);
		setVisible(true);
		monsterBody->setEnabled(true);

		Point start = this->getPosition(); //获取怪物位置
		Point direction = this->getDirection();//获取怪物移动向量
		Point center = Point(visibleSize.width / 2, visibleSize.height / 2);
		float fSpeed = 100;
		float distance = start.getDistance(center);
		float time = distance / fSpeed;
		auto move = MoveTo::create(time, center);
		runAction(move);
	}
}

void Monster::hide()
{
	getEffect()->setVisible(true);//受伤表情出现
	setHasEffect(true);
	stopAllActions();
	CallFunc *dead = CallFunc::create([this] {
		if (getSprite() != NULL)
		{
			monsterBody->setEnabled(false);
			setHasEffect(false);
			setVisible(false);
		}
	});
	Sequence *hide = Sequence::create(MoveBy::create(0.1f, -getDirection() * 20), dead, NULL);
	runAction(hide);
}

void Monster::getIntoTower()
{
	getEffect()->setVisible(true);//受伤表情出现
	setHasEffect(true);
	stopAllActions();
	getEffect()->setVisible(false);//受伤表情隐藏
	CallFunc *dead = CallFunc::create([this] {
		if (getSprite() != NULL)
		{
			monsterBody->setEnabled(false);
			setHasEffect(false);
			setVisible(false);
		}
	});
	CallFunc *hurt = CallFunc::create([this] {
	});
	//Sequence *hide = Sequence::create(hurt, dead, NULL);
	Sequence *hide = Sequence::create(RotateBy::create(0.25f, 180), hurt, dead, NULL);

	//Sequence *hide = Sequence::create(Twirl::create(1, Director::getInstance()->getVisibleSize() / 500, this->getPosition(), 3, 50), dead, NULL);
	runAction(hide);
	/*if (getSprite() != NULL)
	{
	setVisible(false);
	monsterBody->setEnabled(false);
	}*/

}

void Monster::reset()
{
	Size size = Director::getInstance()->getVisibleSize();
	getEffect()->setVisible(false);//受伤表情隐藏
	if (getSprite() != NULL)
	{

		bool out = false;

		do
		{
			setPosition(Point(CCRANDOM_0_1() * 1500 - 300, CCRANDOM_0_1() * 1200 - 300));
			Point Pos = this->getPosition();
			if ((Pos.x<0 || Pos.x>size.width) || (Pos.y<0 || Pos.y>size.height)) {
				out = true;
			}
		} while (!out);
	}
}

//获取方向向量

Point& Monster::getDirection()
{
	Size size = Director::getInstance()->getVisibleSize();

	Point start = this->getPosition();
	Point dest = Point(size.width / 2, size.height / 2);
	Point direction = (dest - start).getNormalized();
	return direction;
}

bool Monster::hasEffect()
{
	return m_hasEffect;
}

void Monster::setHasEffect(bool effect)
{
	m_hasEffect = effect;
}

void Monster::setMaxHP(int maxHP)
{
	monsterHP = monsterMaxHP = maxHP;
	//	HPslider->setPercent(100);
}

bool Monster::isDead()
{
	if (monsterHP == 0)
		return true;
	return false;
}

void Monster::isHurt()
{
	if (getSprite() != NULL&&monsterHP >= 1)
	{
		monsterHP -= 1;
		log("monster is hurt");
		int HPpercent = (int)(100 * monsterHP / monsterMaxHP);
		HPslider->setPercent(HPpercent);
		log("monster hp percent is %d", HPpercent);
	}
	if (isDead())
		hide();
}

int Monster::getMaxHP()
{
	return monsterMaxHP;
}

void Monster::createSlider()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	HPslider = Slider::create();
	HPslider->setTouchEnabled(false);
	HPslider->setMaxPercent(100);
	HPslider->setPercent(100);
	HPslider->loadBarTexture("Bar.png");//血量条递补
	HPslider->loadSlidBallTexturePressed("button.png");//血量条按钮
	HPslider->loadProgressBarTexture("ProgressBar.png");//血量条进度(内部)
	HPslider->setScale(0.02);
	addChild(HPslider, 2);
}