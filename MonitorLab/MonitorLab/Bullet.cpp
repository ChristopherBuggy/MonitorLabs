#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet(sf::Vector2f pos)
{
	texture.loadFromFile("Assets/bullet.png");
	setTexture(texture);
	setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	setPosition(pos);
	removable = false;
}

Bullet::~Bullet()
{
	texture.~Texture();
}

void Bullet::Update()
{
	setPosition(getPosition().x, getPosition().y - 1);
	if (getPosition().y < -25)
		removable = true;
}

bool Bullet::IsRemovable()
{
	return removable;
}

void Bullet::SetRemovable(bool r)
{
	removable = r;
}
