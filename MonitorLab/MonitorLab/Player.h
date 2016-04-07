#ifndef PLAYER_H
#define PLAYER_H

#include "Bullet.h"
#include "Enemy.h"

class Player : public sf::Sprite
{
private:
	sf::Texture texture;
	int health;
	int score;
	int numFrames;//The total number of frames in the sheet

				  /*How long does it take to move through each frame*/
	float animationTime;
	/*clock for moving through the sheet*/
	sf::Clock animationClock;

	/*texture rectangle stuff*/
	sf::Vector2i framePosition;
	sf::Vector2i frameSize;
	sf::IntRect frame;

	std::vector<Bullet*> bullets;

public:
	Player();
	~Player();
	void Update();
	void Strafe(int dir);
	void Shoot();
	void DrawBullets(sf::RenderTarget& window);
	void RemoveBullets();
	bool BulletEnemyCollisions(Enemy* e);
};

#endif
