#include "Entity.h"

Entity::Entity()
{
	m_sprite = NULL;

//	inScreen = false;
}


Entity::~Entity()
{
}

Sprite* Entity::getSprite()
{
	return m_sprite;
}

Sprite* Entity::getEffect()
{
	return m_effect;
}

void Entity::bindSprite(Sprite* sprite)
{
	m_sprite = sprite;
	addChild(m_sprite, 1);
}

void Entity::bindEffect(Sprite *effect)
{
	m_effect = effect;
	addChild(m_effect);
}

Rect Entity::getBoundingBox()
{
	if (getSprite() == NULL) {
		return CCRectMake(0, 0, 0, 0);
	}
	Size spriteSize = getSprite()->getContentSize();
	Point entityPos = getPosition();

	return CCRectMake(
		entityPos.x - spriteSize.width / 2,
		entityPos.y - spriteSize.height / 2,
		spriteSize.width,
		spriteSize.height);

}