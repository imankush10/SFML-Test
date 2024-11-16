#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Collider.h"

class Player
{
public:
	Player(sf::Texture* texture, sf::Vector2u imageSize, float switchTime, float speed, float jumpHeight);
	~Player();

	void Draw(sf::RenderWindow& window);
	void Update(float deltaTime);

	sf::Vector2f GetPosition();
	Collider GetCollider();

	void OnCollision(sf::Vector2f direction);

private:
	sf::RectangleShape body;
	Animation animation;
	unsigned int row;
	float speed;
	unsigned int maxColumnCount = 0;
	bool faceRight;

	sf::Vector2f velocity;
	bool canJump;
	float jumpHeight;
};

