#include "CollisionSample.h"
#include "Random.h"

void CollisionSample::CreateCircle() noexcept
{
    int currentID = 0;
    for (auto& circle: circles)
    {
        circle.bodyRef = _sampleWorld.CreateBody();
        auto& circleBody = _sampleWorld.GetBody(circle.bodyRef);
        circleBody.SetMass(1);
        const Math::Vec2F rndPos = Math::Vec2F(Math::Random::Range(100.f, Metrics::WIDTH - 100),
                                               Math::Random::Range(100.f, Metrics::HEIGHT - 100));
        circleBody.SetPosition(rndPos);
        circleBody.SetVelocity(Math::Vec2F(Math::Random::Range(-VelocityMaxOnStart, VelocityMaxOnStart),
                                           Math::Random::Range(-VelocityMaxOnStart, VelocityMaxOnStart)));
        const auto randomColor = Display::RandomColor();
        circle.color = randomColor;


        circle.colliderRef = _sampleWorld.CreateCollider(circle.bodyRef);
        auto& circleCollider = _sampleWorld.GetCollider(circle.colliderRef);
        circleCollider.ID = currentID++;;
        circleCollider._shape = Math::ShapeType::Circle;
        circleCollider.isTrigger = false;
        const auto bodyPosition = circleBody.Position();
        circleCollider.circleShape = Math::CircleF(bodyPosition, CircleRadius);
    }
}

void CollisionSample::RenderCircle(SDL_Renderer* renderer) noexcept
{
    for (auto& circle: circles)
    {
        auto& circleBody = _sampleWorld.GetBody(circle.bodyRef);
        Display::DrawCircle(renderer, circleBody.Position(), CircleRadius,
                            circle.color, CircleSegements);
    }
}

void CollisionSample::RenderNodes(SDL_Renderer* renderer) noexcept
{
    Display::DrawRectOutline(renderer, _sampleWorld.tree.nodes[0].bounds,
                             SDL_Color{100, 100, 100, 0}, 2);

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

void CollisionSample::DrawQuadTreeNodes(SDL_Renderer* renderer, Engine::QuadNode& node, const SDL_Color& color) noexcept
{
    Display::DrawRectOutline(renderer, node.bounds, color, 2);

    for (const auto& child: node.children)
    {
        if (child)
        { // Ensure the child node exists
            DrawQuadTreeNodes(renderer, *child, color);
        }
    }
}

void CollisionSample::ReverseForceOnBorder() noexcept
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
}

void CollisionSample::OnTriggerEnter(Engine::Collider colliderA, Engine::Collider colliderB) noexcept
{
    for (auto& circle: circles)
    {
        const auto circleCollider = _sampleWorld.GetCollider(circle.colliderRef);
        if (circleCollider == colliderA || circleCollider == colliderB)
        {
            circle.CollisionNbr = true;
        }
    }
}

void CollisionSample::OnTriggerExit(Engine::Collider colliderA, Engine::Collider colliderB) noexcept
{
    for (auto& circle: circles)
    {
        const auto circleCollider = _sampleWorld.GetCollider(circle.colliderRef);
        if (circleCollider == colliderA || circleCollider == colliderB)
        {
            circle.CollisionNbr = false;
        }
    }
}

void CollisionSample::OnCollisionEnter(Engine::Collider colliderA, Engine::Collider colliderB) noexcept
{
    const auto randomColor = Display::RandomColor();
    for (auto& object: circles)
    {
        auto objectCollider = _sampleWorld.GetCollider(object.colliderRef);
        if (objectCollider == colliderA || objectCollider == colliderB)
        {
            object.color = randomColor;
        }
    }
}

void CollisionSample::OnCollisionExit(Engine::Collider colliderA, Engine::Collider colliderB) noexcept
{

}

void CollisionSample::SampleSetUp() noexcept
{
    _sampleWorld.contactListener = this;
    CreateCircle();
}

void CollisionSample::SampleUpdate() noexcept
{
    for (auto& circle: circles)
    {
        auto& circleCollider = _sampleWorld.GetCollider(circle.colliderRef);
        const auto position = _sampleWorld.GetBody(circle.bodyRef).Position();
        circleCollider.circleShape = Math::CircleF(position, CircleRadius);
    }
    ReverseForceOnBorder();
}

void CollisionSample::SampleRender(SDL_Renderer* renderer) noexcept
{
    RenderCircle(renderer);
    RenderNodes(renderer);
}

void CollisionSample::SampleTearDown() noexcept
{
    _sampleWorld.contactListener = nullptr;
    circles.fill(Circle());
}





