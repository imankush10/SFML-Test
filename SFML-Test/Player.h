#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"

class Player
{
public:
	Player(sf::Texture* texture, sf::Vector2u imageSize, float switchTime, float speed);
	~Player();

	void Draw(sf::RenderWindow& window);
	void Update(float deltaTime);
	sf::Vector2f GetPosition();

private:
	sf::RectangleShape body;
	Animation animation;
	unsigned int row;
	float speed;
	unsigned int maxColumnCount = 0;
	bool faceRight;
};

