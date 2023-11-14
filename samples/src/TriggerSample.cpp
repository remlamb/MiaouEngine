#include "TriggerSample.h"
#include "Random.h"

void TriggerSample::CreateObjects() noexcept
{
    int currentID = 0;
    for (auto& circle: circles)
    {
        circle.bodyRef = _sampleWorld.CreateBody();
        auto& circleBody = _sampleWorld.GetBody(circle.bodyRef);
        circleBody.SetMass(1);
        Math::Vec2F rndPos(Math::Random::Range(100.f, Metrics::WIDTH - 100),
                           Math::Random::Range(100.f, Metrics::HEIGHT - 100));
        circleBody.SetPosition(rndPos);

        circleBody.SetVelocity(Math::Vec2F(Math::Random::Range(-VelocityMaxOnStart, VelocityMaxOnStart),
                                           Math::Random::Range(-VelocityMaxOnStart, VelocityMaxOnStart)));
        circle.color = noTriggerColor;

        circle.colliderRef = _sampleWorld.CreateCollider(circle.bodyRef);
        auto& circleCollider = _sampleWorld.GetCollider(circle.colliderRef);
        circleCollider.ID = currentID++;
        circleCollider._shape = Math::ShapeType::Circle;
        circleCollider.isTrigger = true;
        const auto circleBodyPosition = circleBody.Position();
        circleCollider.circleShape = Math::CircleF(circleBodyPosition, CircleRadius);
    }

    for (auto& rect: rectangles)
    {
        rect.bodyRef = _sampleWorld.CreateBody();
        auto& rectBody = _sampleWorld.GetBody(rect.bodyRef);
        rectBody.SetMass(1);
        Math::Vec2F rndPos(Math::Random::Range(100.f, Metrics::WIDTH - 100),
                           Math::Random::Range(100.f, Metrics::HEIGHT - 100));
        rectBody.SetPosition(rndPos);

        rectBody.SetVelocity(Math::Vec2F(Math::Random::Range(-VelocityMaxOnStart, VelocityMaxOnStart),
                                         Math::Random::Range(-VelocityMaxOnStart, VelocityMaxOnStart)));
        rect.color = noTriggerColor;

        rect.colliderRef = _sampleWorld.CreateCollider(rect.bodyRef);
        auto& rectCollider = _sampleWorld.GetCollider(rect.colliderRef);
        rectCollider.ID = currentID++;
        rectCollider._shape = Math::ShapeType::Rectangle;
        rectCollider.isTrigger = true;
        const auto rectangleBodyPosition = rectBody.Position();
        rectCollider.rectangleShape = Math::RectangleF(rectangleBodyPosition,
                                                       rectangleBodyPosition + rectMaxBound -
                                                       rectMinBound);
    }
}

void TriggerSample::RenderCircle(SDL_Renderer* renderer) noexcept
{
    for (auto& circle: circles)
    {
        auto& circleBody = _sampleWorld.GetBody(circle.bodyRef);
        Display::DrawCircle(renderer, circleBody.Position(), CircleRadius, circle.color, CircleSegements);
    }
}

void TriggerSample::RenderRect(SDL_Renderer* renderer) noexcept
{
    for (auto& rect: rectangles)
    {
        auto& rectCollider = _sampleWorld.GetCollider(rect.colliderRef);
        Display::DrawRect(renderer, rectCollider.rectangleShape, rect.color);
    }
}

void TriggerSample::RenderNodes(SDL_Renderer* renderer) noexcept
{
    Display::DrawRectOutline(renderer, _sampleWorld.tree.nodes[0].bounds, SDL_Color{100, 100, 100, 0}, 2);
    if (_sampleWorld.tree.nodes[0].children[0])
    {
        for (const auto& child: _sampleWorld.tree.nodes[0].children)
        {
            if (child != nullptr)
            {
                DrawQuadTreeNodes(renderer, *child, SDL_Color{100, 100, 100, 0});
            }
        }
    }
}

void TriggerSample::DrawQuadTreeNodes(SDL_Renderer* renderer, Engine::QuadNode& node, const SDL_Color& color) noexcept
{
    Display::DrawRectOutline(renderer, node.bounds, color, 2);
    for (const auto& child: node.children)
    {
        if (child)
        {
            DrawQuadTreeNodes(renderer, *child, color);
        }
    }
}

void TriggerSample::ReverseForceOnBorder() noexcept
{
    for (auto& circle: circles)
    {
        auto& circleBody = _sampleWorld.GetBody(circle.bodyRef);
        const auto position = circleBody.Position();
        const auto velocity = circleBody.Velocity();

        if (position.X >= Metrics::WIDTH - BorderSizeForElements)
        {
            circleBody.SetPosition(Math::Vec2F(Metrics::WIDTH - BorderSizeForElements, position.Y));
            circleBody.SetVelocity(Math::Vec2F(-velocity.X, velocity.Y));
        }

        if (position.X <= 0 + BorderSizeForElements)
        {
            circleBody.SetPosition(Math::Vec2F(BorderSizeForElements, position.Y));
            circleBody.SetVelocity(Math::Vec2F(-velocity.X, velocity.Y));
        }

        if (position.Y >= Metrics::HEIGHT - BorderSizeForElements)
        {
            circleBody.SetPosition(Math::Vec2F(position.X, Metrics::HEIGHT - BorderSizeForElements));
            circleBody.SetVelocity(Math::Vec2F(velocity.X, -velocity.Y));
        }

        if (position.Y <= 0 + BorderSizeForElements)
        {
            circleBody.SetPosition(Math::Vec2F(position.X, 0 + BorderSizeForElements));
            circleBody.SetVelocity(Math::Vec2F(velocity.X, -velocity.Y));
        }

    }

    for (auto& rect: rectangles)
    {
        auto& circleBody = _sampleWorld.GetBody(rect.bodyRef);

        const auto position = circleBody.Position();
        const auto velocity = circleBody.Velocity();

        if (position.X >= Metrics::WIDTH - BorderSizeForElements)
        {
            circleBody.SetPosition(Math::Vec2F(Metrics::WIDTH - BorderSizeForElements, position.Y));
            circleBody.SetVelocity(Math::Vec2F(-velocity.X, velocity.Y));
        }

        if (position.X <= 0 + BorderSizeForElements)
        {
            circleBody.SetPosition(Math::Vec2F(BorderSizeForElements, position.Y));
            circleBody.SetVelocity(Math::Vec2F(-velocity.X, velocity.Y));
        }

        if (position.Y >= Metrics::HEIGHT - BorderSizeForElements)
        {
            circleBody.SetPosition(Math::Vec2F(position.X, Metrics::HEIGHT - BorderSizeForElements));
            circleBody.SetVelocity(Math::Vec2F(velocity.X, -velocity.Y));
        }

        if (position.Y <= 0 + BorderSizeForElements)
        {
            circleBody.SetPosition(Math::Vec2F(position.X, 0 + BorderSizeForElements));
            circleBody.SetVelocity(Math::Vec2F(velocity.X, -velocity.Y));
        }
    }
}

void TriggerSample::OnTriggerEnter(Engine::Collider colliderA, Engine::Collider colliderB) noexcept
{
    for (auto& circle: circles)
    {
        auto circleCollider = _sampleWorld.GetCollider(circle.colliderRef);
        if (circleCollider == colliderA || circleCollider == colliderB)
        {
            circle.CollisionNbr++;
        }
    }
    for (auto& rectangle: rectangles)
    {
        auto rectangleCollider = _sampleWorld.GetCollider(rectangle.colliderRef);
        if (rectangleCollider == colliderA || rectangleCollider == colliderB)
        {
            rectangle.CollisionNbr++;
        }
    }
}

void TriggerSample::OnTriggerExit(Engine::Collider colliderA, Engine::Collider colliderB) noexcept
{
    for (auto& circle: circles)
    {
        auto circleCollider = _sampleWorld.GetCollider(circle.colliderRef);
        if (circleCollider == colliderA || circleCollider == colliderB)
        {
            circle.CollisionNbr--;
        }
    }
    for (auto& rectangle: rectangles)
    {
        auto rectangleCollider = _sampleWorld.GetCollider(rectangle.colliderRef);
        if (rectangleCollider == colliderA || rectangleCollider == colliderB)
        {
            rectangle.CollisionNbr--;
        }
    }
}

void TriggerSample::OnCollisionEnter(Engine::Collider colliderA, Engine::Collider colliderB) noexcept
{

}

void TriggerSample::OnCollisionExit(Engine::Collider colliderA, Engine::Collider colliderB) noexcept
{

}

void TriggerSample::SampleSetUp() noexcept
{
    _sampleWorld.contactListener = this;
    CreateObjects();
}

void TriggerSample::SampleUpdate() noexcept
{
    for (auto& circle: circles)
    {
        auto& circleCollider = _sampleWorld.GetCollider(circle.colliderRef);
        const auto circleBodyPosition = _sampleWorld.GetBody(circle.bodyRef).Position();
        circleCollider.circleShape = Math::CircleF(circleBodyPosition, CircleRadius);
        if (circle.CollisionNbr > 0)
        {
            circle.color = onTriggerColor;
        }
        else
        {
            circle.color = noTriggerColor;
        }
    }

    for (auto& rect: rectangles)
    {
        auto& rectCollider = _sampleWorld.GetCollider(rect.colliderRef);
        const auto rectangleBodyPosition = _sampleWorld.GetBody(rect.bodyRef).Position();
        rectCollider.rectangleShape = Math::RectangleF(rectangleBodyPosition,
                                                       rectangleBodyPosition + rectMaxBound - rectMinBound);
        if (rect.CollisionNbr > 0)
        {
            rect.color = onTriggerColor;
        }
        else
        {
            rect.color = noTriggerColor;
        }
    }
    ReverseForceOnBorder();
}

void TriggerSample::SampleRender(SDL_Renderer* renderer) noexcept
{
    RenderCircle(renderer);
    RenderRect(renderer);
    RenderNodes(renderer);
}

void TriggerSample::SampleTearDown() noexcept
{
    _sampleWorld.contactListener = nullptr;
    circles.fill(Circle());
    rectangles.fill(Rect());
}

