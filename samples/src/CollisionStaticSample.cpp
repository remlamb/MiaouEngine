#include "CollisionStaticSample.h"
#include "Random.h"

void CollisionStaticSample::CreateObjects() noexcept
{
    int currentID = 0;
    const auto possiblePos = Metrics::WIDTH / (CirclesInTheWorld + 1);
    float posIterator = 1;

    for (auto& circle: circles)
    {
        circle.bodyRef = _sampleWorld.CreateBody();
        auto& circleBody = _sampleWorld.GetBody(circle.bodyRef);
        circleBody.SetMass(1);
        const Math::Vec2F rndPos(posIterator * possiblePos,
                                 Math::Random::Range(BorderSizeForElements, Metrics::HEIGHT / 2));
        circleBody.SetPosition(rndPos);
        posIterator++;
        circleBody.SetVelocity(Math::Vec2F(0, ForceToApply));
        circleBody.type = Engine::BodyType::DYNAMIC;
        const auto randomColor = Display::RandomColor();
        circle.color = randomColor;

        circle.colliderRef = _sampleWorld.CreateCollider(circle.bodyRef);
        auto& circleCollider = _sampleWorld.GetCollider(circle.colliderRef);
        circleCollider.ID = currentID++;
        circleCollider._shape = Math::ShapeType::Circle;
        circleCollider.isTrigger = false;
        circleCollider.restitution = 0.3f;
        const auto bodyPosition = circleBody.Position();
        circleCollider.circleShape = Math::CircleF(bodyPosition, CircleRadius);
    }

    staticRect.bodyRef = _sampleWorld.CreateBody();
    auto& rectBody = _sampleWorld.GetBody(staticRect.bodyRef);
    rectBody.SetMass(1);
    rectBody.SetPosition(Math::Vec2F(BorderSizeForElements, Metrics::HEIGHT - 150.0f));
    rectBody.SetVelocity(Math::Vec2F(0, 0));
    rectBody.type = Engine::BodyType::STATIC;
    staticRect.color = groundColor;

    staticRect.colliderRef = _sampleWorld.CreateCollider(staticRect.bodyRef);
    auto& rectCollider = _sampleWorld.GetCollider(staticRect.colliderRef);
    rectCollider.ID = currentID++;
    rectCollider._shape = Math::ShapeType::Rectangle;
    const auto rectPosition = rectBody.Position();
    rectCollider.rectangleShape = Math::RectangleF(rectPosition, rectPosition + rectMaxBound - rectMinBound);
}

void CollisionStaticSample::RenderCircle(SDL_Renderer* renderer) noexcept
{
    for (auto& circle: circles)
    {
        auto& circleBody = _sampleWorld.GetBody(circle.bodyRef);
        Display::DrawCircle(renderer, circleBody.Position(), CircleRadius, circle.color, CircleSegements);
    }
}

void CollisionStaticSample::OnTriggerEnter(Engine::Collider colliderA, Engine::Collider colliderB) noexcept
{
    for (auto& circle: circles)
    {
        auto circleCollider = _sampleWorld.GetCollider(circle.colliderRef);
        if (circleCollider == colliderA || circleCollider == colliderB)
        {
            circle.CollisionNbr++;
        }
    }
}

void CollisionStaticSample::OnTriggerExit(Engine::Collider colliderA, Engine::Collider colliderB) noexcept
{
    for (auto& circle: circles)
    {
        auto circleCollider = _sampleWorld.GetCollider(circle.colliderRef);
        if (circleCollider == colliderA || circleCollider == colliderB)
        {
            circle.CollisionNbr--;
        }
    }
}

void CollisionStaticSample::OnCollisionEnter(Engine::Collider colliderA, Engine::Collider colliderB) noexcept
{
    const auto randomColor = Display::RandomColor();
    for (auto& circle: circles)
    {
        auto circleCollider = _sampleWorld.GetCollider(circle.colliderRef);
        if (circleCollider == colliderA || circleCollider == colliderB)
        {
            circle.color = randomColor;
        }
    }
}

void CollisionStaticSample::OnCollisionExit(Engine::Collider colliderA, Engine::Collider colliderB) noexcept
{

}

void CollisionStaticSample::SampleSetUp() noexcept
{
    _sampleWorld.contactListener = this;
    CreateObjects();
}

void CollisionStaticSample::SampleUpdate() noexcept
{
    for (auto& circle: circles)
    {
        auto& circleBody = _sampleWorld.GetBody(circle.bodyRef);
        circleBody.AddForce(Math::Vec2F(0, ForceToApply));

        const auto circleBodyPosition = _sampleWorld.GetBody(circle.bodyRef).Position();
        auto& circleCollider = _sampleWorld.GetCollider(circle.colliderRef);
        circleCollider.circleShape = Math::CircleF(_sampleWorld.GetBody(circle.bodyRef).Position(), CircleRadius);
    }

    const auto rectBodyPosition = _sampleWorld.GetBody(staticRect.bodyRef).Position();
    auto& rectCollider = _sampleWorld.GetCollider(staticRect.colliderRef);
    rectCollider.rectangleShape = Math::RectangleF(rectBodyPosition,
                                                   rectBodyPosition + rectMaxBound - rectMinBound);
}

void CollisionStaticSample::SampleRender(SDL_Renderer* renderer) noexcept
{
    auto& rectCollider = _sampleWorld.GetCollider(staticRect.colliderRef);
    Display::DrawRect(renderer, rectCollider.rectangleShape, staticRect.color);
    RenderCircle(renderer);
}

void CollisionStaticSample::SampleTearDown() noexcept
{
    _sampleWorld.contactListener = nullptr;
    circles.fill(Circle());
}
