#include "Player.h"

Player::Player(sf::Texture* texture, sf::Vector2u imageSize, float switchTime, float speed, float jumpHeight) :
    animation(texture, imageSize, switchTime)
{
    this->speed = speed;
    this->jumpHeight = jumpHeight;

    canJump = true;  
    velocity = sf::Vector2f(0.0f, 0.0f);  

    faceRight = true;
    row = 0;
    body.setSize(sf::Vector2f(100, 100));
    body.setPosition(sf::Vector2f(206.0f, 400.0f));
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
void Player::OnCollision(sf::Vector2f direction)
{
    if (direction.x < 0)
    {
        // right collision
        velocity.x = 0;
    }
    else if (direction.x > 0)
    {
        // left collision
        velocity.x = 0;
    }
    if (direction.y < 0)
    {
        // bottom collision
        velocity.y = 0;
        canJump = true;
    }
    else if (direction.y > 0)
    {
        // top collision
        velocity.y = 0;
    }
}
void Player::Draw(sf::RenderWindow& window)
{
    window.draw(body);
}
void Player::Update(float deltaTime)
{
    velocity.x = 0.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        velocity.x -= speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        velocity.x += speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canJump)
    {
        canJump = false;
        velocity.y = -sqrtf(2.0f * 981.0f * jumpHeight);
    }
    velocity.y += 981.0f * deltaTime;

    if (velocity.x == 0.0f)
    {
        if (!canJump)
        {
            row = 3;
            maxColumnCount = 12;
        }
        else
        {
            row = 0;
            maxColumnCount = 6;
        }
    }
    else
    {
        if (!canJump)
        {
            row = 3;
            maxColumnCount = 12;
        }
        else
        {
            row = 1;
            maxColumnCount = 8;
        }
        bool previousFaceRight = faceRight;
        faceRight = velocity.x > 0.0f;
        if (previousFaceRight != faceRight)
            animation.ResetFrame();
    }
    animation.update(row, deltaTime, maxColumnCount, faceRight);
    body.setTextureRect(animation.uvRect);
    body.move(velocity * deltaTime);
}