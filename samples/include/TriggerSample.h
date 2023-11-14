#pragma once

#include "Display.h"
#include "ContactListener.h"
#include "Sample.h"
#include <array>

/**
 * @brief Represents a sample demonstrating trigger collisions with circles and rectangles.
 *
 * The TriggerSample class inherits from the ContactListener and Sample classes, providing functionality
 * to handle trigger events, reverse forces on borders, and render objects in the sample world.
 *
 * Key Features:
 * - CirclesInTheWorld: The number of circles in the sample world.
 * - RectsInTheWorld: The number of rectangles in the sample world.
 * - CircleSegments: The number of segments to approximate a circle when rendering.
 * - CircleRadius: The radius of circles.
 * - rectMinBound, rectMaxBound: Minimum and maximum bounds for rectangles.
 * - VelocityMaxOnStart: Maximum velocity for objects on start.
 * - BorderSizeForElements: The size of the border to reverse forces on objects reaching the screen borders.
 * - noTriggerColor: Color for objects when they are not triggered.
 * - onTriggerColor: Color for objects when they are triggered.
 *
 * Methods:
 * - CreateObjects(): Creates a predefined number of circles and rectangles with trigger colliders, initializing their properties.
 * - RenderCircle(): Renders circles using the provided SDL renderer.
 * - RenderRect(): Renders rectangles using the provided SDL renderer.
 * - RenderNodes(): Renders quadtree nodes using the provided SDL renderer.
 * - DrawQuadTreeNodes(): Draws quadtree nodes recursively.
 * - ReverseForceOnBorder(): Reverses the force on objects that reach the fictive borders of the screen.
 * - OnTriggerEnter(): Handles trigger enter events by incrementing collision counters.
 * - OnTriggerExit(): Handles trigger exit events by decrementing collision counters.
 * - OnCollisionEnter(): Handles collision enter events (not implemented in this sample, only trigger objects).
 * - OnCollisionExit(): Handles collision exit events (not implemented in this sample, only trigger objects).
 * - SampleSetUp(): Sets up the sample by assigning the contact listener, creating objects, and initializing properties.
 * - SampleUpdate(): Updates the sample by handling collisions, updating object properties, and reversing forces on borders.
 * - SampleRender(): Renders the sample using the provided SDL renderer.
 * - SampleTearDown(): Tears down the sample by resetting the contact listener and clearing objects.
 *
 * The TriggerSample class provides a visual representation of trigger collisions and their effects on object properties.
 */
struct Circle
{
    Engine::BodyRef bodyRef;
    Engine::ColliderRef colliderRef;
    SDL_Color color;
    int CollisionNbr = 0;
};

struct Rect
{
    Engine::BodyRef bodyRef;
    Engine::ColliderRef colliderRef;
    SDL_Color color;
    int CollisionNbr = 0;
};

class TriggerSample : public Engine::ContactListener, public Sample
{
private :
    static constexpr int CircleSegements = 20;
    static constexpr int CircleRadius = 5;

    static constexpr Math::Vec2F rectMinBound = {1., 1.};
    static constexpr Math::Vec2F rectMaxBound = {10., 10.};

    static constexpr float VelocityMaxOnStart = 60.0f;
    static constexpr float BorderSizeForElements = 50.0f;

    static constexpr SDL_Color noTriggerColor = {163, 38, 46, 255};
    static constexpr SDL_Color onTriggerColor = {128, 230, 166, 255};

    static constexpr std::size_t RectsInTheWorld = 500;
    static constexpr std::size_t CirclesInTheWorld = 500;

public :

    std::array<Circle, CirclesInTheWorld> circles;
    std::array<Rect, RectsInTheWorld> rectangles;

    explicit TriggerSample() noexcept = default;

    /**
     * @brief Creates a predifined numbers of circles and rectangles with trigger colliders, initializing their properties.
     */
    void CreateObjects() noexcept;

    /**
     * @brief Renders circles using the provided SDL renderer.
     * @param renderer The SDL renderer used for rendering.
     */
    void RenderCircle(SDL_Renderer* renderer) noexcept;

    /**
     * @brief Renders rectangles using the provided SDL renderer.
     * @param renderer The SDL renderer used for rendering.
     */
    void RenderRect(SDL_Renderer* renderer) noexcept;

    /**
     * @brief Renders quadtree nodes using the provided SDL renderer.
     * @param renderer The SDL renderer used for rendering.
     */
    void RenderNodes(SDL_Renderer* renderer) noexcept;

    /**
 * @brief Draws quadtree nodes recursively.
 * @param renderer The SDL renderer used for rendering.
 * @param node The quadtree node to draw.
 * @param color The color to use for drawing the node outline.
 */
    void DrawQuadTreeNodes(SDL_Renderer* renderer, Engine::QuadNode& node, const SDL_Color& color) noexcept;

    /**
     * @brief Reverses the force on objects that reach the fictive borders of the screen.
     */
    void ReverseForceOnBorder() noexcept;

    /**
     * @brief Handles trigger enter events by incrementing collision counters.
     * @param colliderA The first collider involved in the trigger event.
     * @param colliderB The second collider involved in the trigger event.
     */
    void OnTriggerEnter(Engine::Collider colliderA,
                        Engine::Collider colliderB) noexcept override;

    /**
     * @brief Handles trigger exit events by decrementing collision counters.
     * @param colliderA The first collider involved in the trigger event.
     * @param colliderB The second collider involved in the trigger event.
     */
    void OnTriggerExit(Engine::Collider colliderA,
                       Engine::Collider colliderB) noexcept override;

    /**
     * @brief Handles collision enter events (not implemented in this sample (only trigger Objects)).
     * @param colliderA The first collider involved in the collision event.
     * @param colliderB The second collider involved in the collision event.
     */
    void OnCollisionEnter(Engine::Collider colliderA,
                          Engine::Collider colliderB) noexcept override;

    /**
     * @brief Handles collision exit events (not implemented in this sample (only trigger Objects)).
     * @param colliderA The first collider involved in the collision event.
     * @param colliderB The second collider involved in the collision event.
     */
    void OnCollisionExit(Engine::Collider colliderA,
                         Engine::Collider colliderB) noexcept override;

public :
    /**
     * @brief Sets up the sample by assigning the contact listener, creating objects, and initializing properties.
     */
    void SampleSetUp() noexcept override;

    /**
     * @brief Updates the sample by handling collisions, updating object properties, and reversing forces on borders.
     */
    void SampleUpdate() noexcept override;

    /**
     * @brief Renders the sample using the provided SDL renderer.
     * @param renderer The SDL renderer used for rendering.
     */
    void SampleRender(SDL_Renderer* renderer) noexcept override;

    /**
     * @brief Tears down the sample by resetting the contact listener and clearing objects.
     */
    void SampleTearDown() noexcept override;

};