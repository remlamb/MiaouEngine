#pragma once

#include "Display.h"
#include "ContactListener.h"
#include "Sample.h"
#include "TriggerSample.h"
#include <array>

/**
 * @brief Represents a sample demonstrating collision detection and resolution between circles and rectangles.
 *
 * The CollisionWithRectSample class inherits from Engine::ContactListener and Engine::Sample,
 * providing a demonstration of collision events between circles and rectangles.
 *
 * Key Features:
 * - CirclesInTheWorld: The number of circles created in the sample world.
 * - CircleSegments: The number of segments to approximate a circle when rendering.
 * - CircleRadius: The radius of the circles in the sample.
 * - VelocityMaxOnStart: The maximum velocity of circles on start.
 * - BorderSizeForElements: The size of a fictive border where forces are reversed if circles hit it.
 * - RectsInTheWorld: The number of rectangles created in the sample world.
 * - rectMinBound: The minimum bounds of the rectangles.
 * - rectMaxBound: The maximum bounds of the rectangles.
 * - circles: An array of Circle objects representing the circles entities in the sample.
 * - rectangles: An array of Rect objects representing the rectangles entities in the sample.
 *
 * Methods:
 * - CreateObjects(): Creates circles and rectangles in the sample world, initializing bodies, colliders, and positions.
 * - RenderCircle(): Renders the circles in the sample world using SDL.
 * - RenderRect(): Renders the rectangles in the sample world using SDL.
 * - RenderNodes(): Renders the quadtree nodes in the sample world using SDL.
 * - DrawQuadTreeNodes(): Recursively draws the quad tree nodes.
 * - ReverseForceOnBorder(): Reverses the force of circles that hit the fictive borders of the window.
 * - OnTriggerEnter(), OnTriggerExit(), OnCollisionEnter(), OnCollisionExit(): Event handling methods.
 * - SampleSetUp(): Sets up the collision sample by associating the contact listener and creating circles and rectangles.
 * - SampleUpdate(): Updates the collision sample, applying forces, updating collider shapes, and handling collisions.
 * - SampleRender(): Renders the collision sample using SDL, drawing circles, rectangles, and quadtree nodes.
 * - SampleTearDown(): Tears down the sample.
 *
 * The CollisionWithRectSample class provides a practical illustration of collision detection and response
 * in a 2D world with dynamic elements, showcasing the interaction between different entities shapes.
 */
class CollisionWithRectSample : public Engine::ContactListener, public Sample
{
private :
    static constexpr int CircleSegements = 20;
    static constexpr int CircleRadius = 12;

    static constexpr Math::Vec2F rectMinBound = {1., 1.};
    static constexpr Math::Vec2F rectMaxBound = {20., 20.};

    static constexpr float VelocityMaxOnStart = 80.0f;
    static constexpr float BorderSizeForElements = 50.0f;

    static constexpr std::size_t RectsInTheWorld = 50;
    static constexpr std::size_t CirclesInTheWorld = 20;

public :

    std::array<Circle, CirclesInTheWorld> circles;
    std::array<Rect, RectsInTheWorld> rectangles;

    explicit CollisionWithRectSample() noexcept = default;

    /**
     * @brief Creates circles and rectangles in the sample world, initializing bodies, colliders, and positions.
     */
    void CreateObjects() noexcept;

    /**
     * @brief Renders the circles in the sample world using SDL.
     * @param renderer The SDL renderer.
     */
    void RenderCircle(SDL_Renderer *renderer) noexcept;

    /**
     * @brief Renders the rectangles in the sample world using SDL.
     * @param renderer The SDL renderer.
     */
    void RenderRect(SDL_Renderer *renderer) noexcept;

    /**
     * @brief Renders the quadtree nodes in the sample world using SDL.
     * @param renderer The SDL renderer.
     */
    void RenderNodes(SDL_Renderer *renderer) noexcept;

    /**
     * @brief Recursively draws the quad tree nodes.
     * @param renderer The SDL renderer.
     * @param node The quad tree node to draw.
     * @param color The color to use for drawing.
     */
    void DrawQuadTreeNodes(SDL_Renderer* renderer, Engine::QuadNode& node, const SDL_Color& color) noexcept;

    /**
     * @brief Reverses the force of circles that hit the fictive borders of the _window.
     */
    void ReverseForceOnBorder() noexcept;

    /**
     * @brief Handles the event when a trigger enters, incrementing the collision counter for affected circles.
     * @param colliderA The first collider.
     * @param colliderB The second collider.
     */
    void OnTriggerEnter(Engine::Collider colliderA,
                        Engine::Collider colliderB) noexcept override;

    /**
     * @brief Handles the event when a trigger enters, decrementing the collision counter for affected circles.
     * @param colliderA The first collider.
     * @param colliderB The second collider.
     */
    void OnTriggerExit(Engine::Collider colliderA,
                       Engine::Collider colliderB) noexcept override;

    /**
     * @brief Handles the event when a collision occurs, changing the color of affected circles and rectangles.
     * @param colliderA The first collider.
     * @param colliderB The second collider.
     */
    void OnCollisionEnter(Engine::Collider colliderA,
                          Engine::Collider colliderB) noexcept override;

    /**
     * @brief Handles the event when a collision exits.
     *
     * @param colliderA The first collider.
     * @param colliderB The second collider.
     */
    void OnCollisionExit(Engine::Collider colliderA,
                         Engine::Collider colliderB) noexcept override;

public :
    /**
     * @brief Sets up the collision sample by associating the contact listener and creating circles and rectangles.
     */
    void SampleSetUp() noexcept override;

    /**
     * @brief Updates the collision sample, applying forces, updating collider shapes, and handling collisions.
     */
    void SampleUpdate() noexcept override;

    /**
     * @brief Renders the collision sample using SDL, drawing circles, rectangles, and quadtree nodes.
     * @param renderer The SDL renderer.
     */
    void SampleRender(SDL_Renderer* renderer) noexcept override;

    /**
     * @brief Tears down the sample.
     */
    void SampleTearDown() noexcept override;

};