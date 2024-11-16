#include<SFML/Graphics.hpp>
#include "Player.h"
#include "Platform.h"
#include <vector>

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

    Player player(&playerTexture, sf::Vector2u(12, 10), 0.1, 150.0f, 130.0f);
    Collider c = player.GetCollider();

    std::vector<Platform> platforms;

    platforms.push_back(Platform(nullptr, sf::Vector2f(1920, 100), sf::Vector2f(0, 550)));
    platforms.push_back(Platform(nullptr, sf::Vector2f(150, 50), sf::Vector2f(400, 420)));
    platforms.push_back(Platform(nullptr, sf::Vector2f(20, 1080), sf::Vector2f(20, 550)));
    platforms.push_back(Platform(nullptr, sf::Vector2f(100, 40), sf::Vector2f(100, 350)));

    float deltaTime = 0.0f;
    sf::Clock clock;

    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();

        player.Update(deltaTime);
        sf::Vector2f direction;

        for (Platform& platform : platforms)
        {
            if (platform.GetCollider().CheckCollision(c, 1.0f, direction))
                player.OnCollision(direction);
        }

        view.setCenter(player.GetPosition());

        sf::Event e;
        while (window.pollEvent(e))
        {
            switch (e.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                ResizeWidth(window, view);
                break;
            }
        }
        window.clear(sf::Color::Cyan);

        player.Draw(window);
        for (Platform& platform : platforms)
        {
            platform.Draw(window);
        }

        player.GetCollider().DebugDraw(window, sf::Color::Red);      // Player boundary
        
        window.setView(view);
        window.display();
    }
}