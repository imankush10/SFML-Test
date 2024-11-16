#pragma once
#include <SFML/Graphics.hpp>
class Collider
{
public:
	Collider(sf::RectangleShape& body);
	~Collider();

	void Move(float dx, float dy);
	sf::Vector2f GetPosition();
	sf::Vector2f GetHalfSize();

	bool CheckCollision(Collider& other, float push);
	void DebugDraw(sf::RenderWindow& window, sf::Color color);

private:
	sf::RectangleShape& body;
};

