#include "Collider.h"

void Collider::DebugDraw(sf::RenderWindow& window, sf::Color color)
{
    sf::RectangleShape debugRect(body.getSize());
    debugRect.setOrigin(body.getOrigin());
    debugRect.setPosition(body.getPosition());
    debugRect.setFillColor(sf::Color::Transparent);
    debugRect.setOutlineThickness(1.0f);
    debugRect.setOutlineColor(color);

    window.draw(debugRect);
}

Collider::Collider(sf::RectangleShape& body) :
    body(body)
{
}

Collider::~Collider()
{
}

void Collider::Move(float dx, float dy)
{
    body.move(dx, dy);
}

sf::Vector2f Collider::GetPosition()
{
    return body.getPosition();
}

sf::Vector2f Collider::GetHalfSize()
{
    return body.getSize() / 2.0f;
}

bool Collider::CheckCollision(Collider& other, float push)
{
    sf::Vector2f otherPosition = other.GetPosition();
    sf::Vector2f otherHalfSize = other.GetHalfSize();
    sf::Vector2f thisPosition = GetPosition();
    sf::Vector2f thisHalfSize = GetHalfSize();

    float deltaX = otherPosition.x - thisPosition.x;
    float deltaY = otherPosition.y - thisPosition.y;

    // Add tolerance to the width check (adjust the 30.0f value as needed)
    float intersectX = std::abs(deltaX) - (thisHalfSize.x + otherHalfSize.x );
    float intersectY = std::abs(deltaY) - (thisHalfSize.y + otherHalfSize.y);

    // No collision if the intersect values are positive
    if (intersectX > 0.0f || intersectY > 0.0f)
        return false;

    // Clamp push to a range of [0, 1]
    push = std::min(std::max(push, 0.0f), 1.0f);

    // Resolve the collision on the axis with the smallest intersection depth
    if (std::abs(intersectX) < std::abs(intersectY))
    {
        if (deltaX > 0.0f)
        {
            Move(intersectX * (1.0f - push), 0.0f);
            other.Move(-intersectX * push, 0.0f);
        }
        else
        {
            Move(-intersectX * (1.0f - push), 0.0f);
            other.Move(intersectX * push, 0.0f);
        }
    }
    else
    {
        if (deltaY > 0.0f)
        {
            Move(0.0f, intersectY * (1.0f - push));
            other.Move(0.0f, -intersectY * push);
        }
        else
        {
            Move(0.0f, -intersectY * (1.0f - push));
            other.Move(0.0f, intersectY * push);
        }
    }
    return true;
}