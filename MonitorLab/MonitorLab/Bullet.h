#ifndef BULLET_H
#define BULLET_H

class Bullet : public sf::Sprite
{
private:
	sf::Texture texture;
	bool removable;
public:
	Bullet(sf::Vector2f pos);
	~Bullet();
	void Update();
	bool IsRemovable();
	void SetRemovable(bool r);
};

#endif
