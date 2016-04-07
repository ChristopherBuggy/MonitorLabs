#include "stdafx.h"

Player::Player()
{
	texture.loadFromFile("Assets/playerPlaneSheet.png");

	setTexture(texture);

	setPosition(SCREENWIDTH / 2, 350);

	framePosition = sf::Vector2i(0, 0);
	frameSize = sf::Vector2i(61, 46);
	frame = sf::IntRect(framePosition, frameSize);
	setTextureRect(frame);
	animationTime = 0.05;
	animationClock.restart();
}

Player::~Player()
{
}

void Player::Update()
{
	if (animationClock.getElapsedTime().asSeconds() > animationTime)
	{
		if (framePosition.x < texture.getSize().x - frameSize.x)
			framePosition.x += frameSize.x;//move the frame forward

		else
		{
			framePosition.x = 0;
		}

		animationClock.restart();
	}

	//reset the texture rectangle
	frameSize = sf::Vector2i(texture.getSize().x / 3, texture.getSize().y);
	frame = sf::IntRect(framePosition, frameSize);
	setTextureRect(frame);
	setOrigin(frameSize.x / 2, frameSize.y / 2);


	/*boundaries*/
	if ((getPosition().x - frameSize.x / 2) > SCREENWIDTH)
		setPosition((0 + frameSize.x / 2), getPosition().y);
	if ((getPosition().x + frameSize.x / 2) < 0)
		setPosition((SCREENWIDTH - frameSize.x / 2), getPosition().y);

	//bullets
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets.at(i)->Update();
	}
	RemoveBullets();
}

void Player::Strafe(int dir)
{
	if (dir == 1)//right
	{
		setPosition(getPosition().x + 1, getPosition().y);
	}
	else if (dir == 2)//left
	{
		setPosition(getPosition().x - 1, getPosition().y);
	}
}

void Player::Shoot()
{
	Bullet* b = new Bullet(getPosition());
	bullets.push_back(b);
}

void Player::DrawBullets(sf::RenderTarget & window)
{
	for (int i = 0; i < bullets.size(); i++)
	{
		window.draw(*bullets.at(i));
	}
}

void Player::RemoveBullets()
{
	for (auto it = bullets.begin(); it != bullets.end();)
	{
		if ((*it)->IsRemovable())//if the bullet can be removed
		{
			delete * it;//delete the pointer
			it = bullets.erase(it);//erase the object(calls the objects destructor)
								   //std::cout << "Bullet removed" << std::endl;
		}
		else ++it;
	}
}

bool Player::BulletEnemyCollisions(Enemy * e)
{
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets.at(i)->getGlobalBounds().intersects(e->getGlobalBounds()))
		{
			bullets.at(i)->SetRemovable(true);
			return true;
		}
	}
	return false;
}
