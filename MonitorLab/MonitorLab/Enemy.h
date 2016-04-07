#ifndef ENEMY_H
#define ENEMY_H

class Enemy : public sf::Sprite
{
private:
	sf::Texture texture;
	int health;
public:
	Enemy();
	~Enemy();
	void Update();
};

#endif
