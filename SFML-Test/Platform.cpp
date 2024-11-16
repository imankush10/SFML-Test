#include "Platform.h"
Platform::Platform(sf::Texture* texture, sf::Vector2f imageSize, sf::Vector2f position)
{
    platform.setTexture(texture);
    platform.setSize(imageSize);
    platform.setPosition(position);
    platform.setOrigin(imageSize / 2.0f);
}
Platform::~Platform()
{
}
void Platform::Draw(sf::RenderWindow& window)
{
    window.draw(platform);
}
Collider Platform::GetCollider()
{
    return Collider(platform);
}
