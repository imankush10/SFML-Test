#include<SFML/Graphics.hpp>
#include "Player.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 640), "Samurai", sf::Style::Default);

	sf::Texture playerTexture;
	playerTexture.loadFromFile("samurai.png");

	Player player(&playerTexture, sf::Vector2u(12, 10), 0.2, 100.0f);

	float deltaTime = 0.0f;
	sf::Clock clock;

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();

		player.Update(deltaTime);
		sf::Event e;
		while (window.pollEvent(e))
		{
			switch (e.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			}
		}

		window.clear(sf::Color::White);
		player.Draw(window);
		window.display();
	}
}