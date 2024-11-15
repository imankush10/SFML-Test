#include<SFML/Graphics.hpp>
#include "Player.h"

static const float VIEW_HEIGHT = 512;

void ResizeWidth(const sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(VIEW_HEIGHT, VIEW_HEIGHT), "Samurai", sf::Style::Default);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));

	sf::Texture playerTexture;
	playerTexture.loadFromFile("samurai.png");

	Player player(&playerTexture, sf::Vector2u(12, 10), 0.2, 100.0f);

	float deltaTime = 0.0f;
	sf::Clock clock;

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();

		player.Update(deltaTime);
		view.setCenter(player.GetPosition());
		sf::Event e;
		while (window.pollEvent(e))
		{
			switch (e.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized :
				ResizeWidth(window, view);
				break;
			}
		}

		window.clear(sf::Color::White);
		player.Draw(window);
		window.setView(view);
		window.display();
	}
}