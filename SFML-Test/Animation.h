#pragma once
#include<SFML/Graphics.hpp>


class Animation
{
public:
	Animation(sf::Texture* texture, sf::Vector2u imageSize, float switchTime);
	~Animation();

	void update(int row, float deltaTime, int maxColumnCount, bool faceRight);
	void ResetFrame();
public:
	sf::IntRect uvRect;
private:
	sf::Vector2u currentImage;
	sf::Vector2u imageSize;

	float switchTime = 0.0f;
	float totalTime = 0.0f;

};

