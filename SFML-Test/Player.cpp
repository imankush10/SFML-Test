#include "Player.h"
Player::Player(sf::Texture* texture, sf::Vector2u imageSize, float switchTime, float speed) :
    animation(texture, imageSize, switchTime)
{
    this->speed = speed;
    faceRight = true;
    row = 0;
    body.setSize(sf::Vector2f(100, 100));
    body.setPosition(sf::Vector2f(206.0f, 206.0f));
    body.setOrigin(body.getSize() / 2.0f);
    body.setTexture(texture);

};
Player::~Player()
{
};
sf::Vector2f Player::GetPosition()
{
    return body.getPosition();
}

Collider Player::GetCollider()
{
    return Collider(body);
}
void Player::Draw(sf::RenderWindow& window)
{
    window.draw(body);
}
void Player::Update(float deltaTime)
{
    sf::Vector2f movement(0.0f, 0.0f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        movement.x -= speed * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        movement.x += speed * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        movement.y -= speed * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        movement.y += speed * deltaTime;
    if (movement.x == 0.0f)
    {
        row = 0;
        maxColumnCount = 6;
    }
    else
    {
        row = 1;
        maxColumnCount = 8;
        bool previousFaceRight = faceRight;
        faceRight = movement.x > 0.0f;
        if (previousFaceRight != faceRight)
            animation.ResetFrame();
    }
    animation.update(row, deltaTime, maxColumnCount, faceRight);
    body.setTextureRect(animation.uvRect);
    body.move(movement);
}