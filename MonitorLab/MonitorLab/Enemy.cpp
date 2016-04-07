#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy()
{
	texture.loadFromFile("Assets/tank1.png");

	setTexture(texture);

	//scale(0.3, 0.3);
	scale(2, 2);

	setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);

	setPosition(rand() % SCREENWIDTH, -100);
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	setPosition(getPosition().x, getPosition().y + 2);
	//rotate(1);
}
