#include "Animation.h"

Animation::Animation(sf::Texture* texture, sf::Vector2u imageSize, float switchTime)
{
	this->switchTime = switchTime;
	this->imageSize = imageSize;

	uvRect.width = texture->getSize().x / imageSize.x;
	uvRect.height = texture->getSize().y / imageSize.y;
	totalTime = 0.0f;
	currentImage.x = 0;
}

Animation::~Animation()
{
}

void Animation::update(int row, float deltaTime, int maxColumnCount, bool faceRight)
{
	currentImage.y = row;

	totalTime += deltaTime;
	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;

		currentImage.x++;
		if (currentImage.x >= maxColumnCount)
		{
			currentImage.x = 0;
		}
	}
	uvRect.top = uvRect.height * currentImage.y;
	if (faceRight)
	{
		uvRect.left = currentImage.x * abs(uvRect.width);
		uvRect.width = abs(uvRect.width);
	}
	else
	{
		uvRect.left = (currentImage.x + 1) * abs(uvRect.width);
		uvRect.width = -abs(uvRect.width);
	}

}

void Animation::ResetFrame()
{
	currentImage.x = 0;
}
