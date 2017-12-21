#include "Skill.h"

Skill::Skill()
{
}


Skill::~Skill()
{
}
bool Skill::init()
{
	m_isCool = true;
	return true;
}

void Skill::onEnter()
{
	Node::onEnter();
}

void Skill::onExit()
{
	Node::onExit();
}


void Skill::coolDown()
{
	m_isCool = true;
}

//技能冷却
void Skill::skillCool()
{
	m_isCool = false;
	CCDelayTime* delay = CCDelayTime::create(7);  //大招冷却时间
	auto callfunc = CCCallFunc::create(this, callfunc_selector(Skill::coolDown));
	runAction(Sequence::create(delay, callfunc, NULL));//执行冷却
}



void Skill::effectExplosion()
{
	CCParticleExplosion* explosion = CCParticleExplosion::create();
	explosion->setTexture(CCTextureCache::sharedTextureCache()->addImage("fire.png"));
	explosion->setAutoRemoveOnFinish(true);
	explosion->setStartColor(Color4F::ORANGE);
	explosion->setSpeedVar(50);
	explosion->setSpeed(300);
	explosion->setPosition(m_meteor->getPosition());
	addChild(explosion);
}

bool Skill::isCool()
{
	return m_isCool;
}

Sequence* Skill::skill01(Point position)
{
	//加入击杀特效
	Size visibleSize = Director::getInstance()->getVisibleSize();

	CCScaleTo* scaleTo = CCScaleTo::create(0.05, 1.05);
	CCScaleTo* scaleTo2 = CCScaleTo::create(0.05, 1);
	CCScaleTo* scaleTo3 = CCScaleTo::create(0.05, 0.95);
	CCDelayTime* delay = CCDelayTime::create(1);
	auto callfunc = CCCallFunc::create(m_target, callfunc_selector(MonsterManager::killAll));
	auto sequence = CCSequence::create(delay, scaleTo3, scaleTo, scaleTo2, callfunc, NULL);//屏幕抖动特效

	if (m_isCool)
	{
		CCParticleMeteor* meteor = CCParticleMeteor::create();
		m_meteor = meteor;
		meteor->setTexture(CCTextureCache::sharedTextureCache()->addImage("pow1.png"));
		meteor->setScale(2);
		meteor->setPosition(visibleSize.width * 0.3, visibleSize.height * 0.7);
		meteor->setPosition(position);
		//meteor->setPosition(Point(-200 - CCRANDOM_0_1() * 300, 1000 + CCRANDOM_0_1() * 300));
		meteor->setAutoRemoveOnFinish(true);
		meteor->setDuration(1.0f);
		addChild(meteor);
		meteor->runAction(MoveBy::create(1, Point(1100, -1000)));//陨石特效

		CCDelayTime* delay2 = CCDelayTime::create(0.95);//大招产生效果延迟时间
		auto callfunc3 = CCCallFunc::create(this, callfunc_selector(Skill::effectExplosion));
		runAction(Sequence::create(delay2, callfunc3, NULL));//撞击爆炸特效



		log("is cooled?%d", m_isCool);
		skillCool();
	}
	else  sequence = Sequence::create(MoveBy::create(0, Point(0, 0)), NULL);
	return sequence;
}

void Skill::skill02(Point position)
{
	if (m_isCool)
	{
		Size visibleSize = Director::getInstance()->getVisibleSize();
		auto effect = CCParticleFlower::create();
		effect->setTexture(CCTextureCache::sharedTextureCache()->addImage("heart.png"));
		effect->setAutoRemoveOnFinish(true);
		effect->setDuration(0.3f);
		effect->setEmissionRate(500);
		effect->setTangentialAccelVar(100);
		effect->setPosition(position);
		addChild(effect);
		skillCool();
	}
}

void Skill::timeReset()
{
	Scheduler* scheduler = Director::sharedDirector()->getScheduler();
	scheduler->setTimeScale(1);
	log("time reset");
}

void Skill::skill03(Point position)
{
	if (m_isCool)
	{
		float decelerate = 0.5f;
		Scheduler* scheduler = Director::sharedDirector()->getScheduler();
		scheduler->setTimeScale(decelerate);

		FadeIn* fadein = FadeIn::create(0.1f);
		FadeOut* fadeout = FadeOut::create(0.5f);
		DelayTime* duration = DelayTime::create(3);//减速持续时间
		auto callfunc = CallFunc::create(this, callfunc_selector(Skill::timeReset));
		auto sequence = Sequence::create(fadein, duration, fadeout, callfunc, NULL);
		auto effect = CCParticleFlower::create();
		effect->setTexture(CCTextureCache::sharedTextureCache()->addImage("ice2.png"));
		effect->setAutoRemoveOnFinish(true);
		effect->setDuration(0.3f);

		effect->setPosition(position);
		effect->setScale(3);
		effect->setSpeedVar(50);
		effect->setEmissionRate(100000);

		addChild(effect);
		runAction(sequence);


		skillCool();
	}
	else return;

}
