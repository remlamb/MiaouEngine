#include "CollisionWithRectSample.h"
#include "Random.h"

void CollisionWithRectSample::CreateObjects() noexcept
{
    int currentID = 0;
    for (auto& circle: circles)
    {
        circle.bodyRef = _sampleWorld.CreateBody();
        auto& circleBody = _sampleWorld.GetBody(circle.bodyRef);
        circleBody.SetMass(1);
        Math::Vec2F rndPos = Math::Vec2F(Math::Random::Range(100.f, Metrics::WIDTH - 100),
                                         Math::Random::Range(100.f, Metrics::HEIGHT - 100));
        circleBody.SetPosition(rndPos);

        circleBody.SetVelocity(Math::Vec2F(Math::Random::Range(-VelocityMaxOnStart, VelocityMaxOnStart),
                                           Math::Random::Range(-VelocityMaxOnStart, VelocityMaxOnStart)));

        const auto randomColor = Display::RandomColor();
        circle.color = randomColor;


        circle.colliderRef = _sampleWorld.CreateCollider(circle.bodyRef);
        auto& circleCollider = _sampleWorld.GetCollider(circle.colliderRef);
        circleCollider.ID = currentID++;
        circleCollider._shape = Math::ShapeType::Circle;
        circleCollider.isTrigger = false;
        const auto& circlePosition = circleBody.Position();
        circleCollider.circleShape = Math::CircleF(circlePosition, CircleRadius);
    }

    for (auto& rect: rectangles)
    {
        const auto randomColor = Display::RandomColor();
        rect.color = randomColor;
        rect.bodyRef = _sampleWorld.CreateBody();
        auto& rectBody = _sampleWorld.GetBody(rect.bodyRef);
        rectBody.SetMass(1);
        rectBody.type = Engine::BodyType::DYNAMIC;
        Math::Vec2F rndPos(Math::Random::Range(100.f, Metrics::WIDTH - 100),
                           Math::Random::Range(100.f, Metrics::HEIGHT - 100));
        rectBody.SetPosition(rndPos);
        rectBody.SetVelocity(Math::Vec2F(Math::Random::Range(-VelocityMaxOnStart, VelocityMaxOnStart),
                                         Math::Random::Range(-VelocityMaxOnStart, VelocityMaxOnStart)));

        rect.colliderRef = _sampleWorld.CreateCollider(rect.bodyRef);
        auto& rectCollider = _sampleWorld.GetCollider(rect.colliderRef);
        rectCollider._shape = Math::ShapeType::Rectangle;
        rectCollider.ID = currentID++;

        const auto& rectanglePosition = rectBody.Position();
        rectCollider.rectangleShape = Math::RectangleF(rectanglePosition,
                                                       rectanglePosition + rectMaxBound -
                                                       rectMinBound);
    }
}

void CollisionWithRectSample::RenderCircle(SDL_Renderer* renderer) noexcept
{
    for (auto& circle: circles)
    {
        auto& circleBody = _sampleWorld.GetBody(circle.bodyRef);
        Display::DrawCircle(renderer, circleBody.Position(), CircleRadius, circle.color, CircleSegements);
    }
}

void CollisionWithRectSample::RenderNodes(SDL_Renderer* renderer) noexcept
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

void CollisionWithRectSample::DrawQuadTreeNodes(SDL_Renderer* renderer, Engine::QuadNode& node,
                                                const SDL_Color& color) noexcept
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

void CollisionWithRectSample::ReverseForceOnBorder() noexcept
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

void CollisionWithRectSample::OnTriggerEnter(Engine::Collider colliderA, Engine::Collider colliderB) noexcept
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

void CollisionWithRectSample::OnTriggerExit(Engine::Collider colliderA, Engine::Collider colliderB) noexcept
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

void CollisionWithRectSample::OnCollisionEnter(Engine::Collider colliderA, Engine::Collider colliderB) noexcept
{
    const auto randomColor = Display::RandomColor();

    if (colliderA._shape == Math::ShapeType::Circle || colliderB._shape == Math::ShapeType::Circle)
    {
        for (auto& circle: circles)
        {
            auto& circleCollider = _sampleWorld.GetCollider(circle.colliderRef);
            if (circleCollider == colliderA || circleCollider == colliderB)
            {
                circle.color = randomColor;
            }
        }
    }

    if (colliderA._shape == Math::ShapeType::Rectangle || colliderB._shape == Math::ShapeType::Rectangle)
    {
        for (auto& rect: rectangles)
        {
            const auto& rectCollider = _sampleWorld.GetCollider(rect.colliderRef);
            if (rectCollider == colliderA || rectCollider == colliderB)
            {
                rect.color = randomColor;
            }
        }
    }
}

void CollisionWithRectSample::OnCollisionExit(Engine::Collider colliderA, Engine::Collider colliderB) noexcept
{

}

void CollisionWithRectSample::SampleSetUp() noexcept
{
    _sampleWorld.contactListener = this;
    CreateObjects();
}

void CollisionWithRectSample::SampleUpdate() noexcept
{
    for (auto& circle: circles)
    {
        auto& circleCollider = _sampleWorld.GetCollider(circle.colliderRef);
        const auto circlePosition = _sampleWorld.GetBody(circle.bodyRef).Position();
        circleCollider.circleShape = Math::CircleF(circlePosition, CircleRadius);
    }

    for (auto& rect: rectangles)
    {
        auto& rectCollider = _sampleWorld.GetCollider(rect.colliderRef);
        const auto rectPosition = _sampleWorld.GetBody(rect.bodyRef).Position();
        rectCollider.rectangleShape = Math::RectangleF(rectPosition, rectPosition + rectMaxBound - rectMinBound);
    }
    ReverseForceOnBorder();
}

void CollisionWithRectSample::SampleRender(SDL_Renderer* renderer) noexcept
{
    RenderCircle(renderer);
    RenderRect(renderer);
    RenderNodes(renderer);
}

void CollisionWithRectSample::RenderRect(SDL_Renderer* renderer) noexcept
{
    for (auto& rect: rectangles)
    {
        auto& rectCollider = _sampleWorld.GetCollider(rect.colliderRef);
        Display::DrawRect(renderer, rectCollider.rectangleShape, rect.color);
    }
}

void CollisionWithRectSample::SampleTearDown() noexcept
{
    _sampleWorld.contactListener = nullptr;
    circles.fill(Circle());
    rectangles.fill(Rect());
}

