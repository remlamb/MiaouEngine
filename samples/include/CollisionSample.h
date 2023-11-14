#pragma once

#include "Display.h"
#include "ContactListener.h"
#include "Sample.h"
#include "TriggerSample.h"
#include <array>

/**
 * @brief Represents a sample demonstrating collision detection and resolution using a QuadTree.
 *
 * The CollisionSample class inherits from Engine::ContactListener and Engine::Sample, combining
 * broad-phase collision detection with spatial partitioning and demonstration of event handling.
 *
 * Key Features:
 * - CirclesInTheWorld: The number of circles created in the sample world.
 * - CircleSegments: The number of segments to approximate a circle when rendering.
 * - CircleRadius: The radius of the circles in the sample.
 * - VelocityMaxOnStart: The maximum initial velocity of circles.
 * - BorderSizeForElements: The size of a fictive border where forces are reversed if circles hit it.
 * - circles: An array of Circle objects representing the entities in the sample.
 *
 * Methods:
 * - CreateCircle(): Creates circles in the sample world, initializing bodies, colliders, and positions.
 * - RenderCircle(): Renders the circles in the sample world using SDL.
 * - RenderNodes(): Renders the quad tree nodes in the sample world using SDL.
 * - DrawQuadTreeNodes(): Recursively draws the quad tree nodes.
 * - ReverseForceOnBorder(): Reverses the force of circles that hit the fictive borders of the window.
 * - OnTriggerEnter(), OnTriggerExit(), OnCollisionEnter(), OnCollisionExit(): Event handling methods.
 * - SampleSetUp(): Sets up the collision sample by associating the contact listener and creating circles.
 * - SampleUpdate(): Updates the collision sample, updating circle collider shapes and reversing forces on borders.
 * - SampleRender(): Renders the elements in the sample using SDL.
 * - SampleTearDown(): Tears down the sample.
 *
 * The CollisionSample class provides a practical illustration of collision detection and response
 * in a 2D world with a dynamic number of entities and efficient spatial partitioning using a QuadTree.
 */
class CollisionSample : public Engine::ContactListener, public Sample
{
private :
    static constexpr float VelocityMaxOnStart = 80.0f;
    static constexpr float BorderSizeForElements = 50.0f;
    static constexpr int CircleSegements = 20;
    static constexpr int CircleRadius = 12;

public :
    static constexpr std::size_t CirclesInTheWorld = 200;
    std::array<Circle, CirclesInTheWorld> circles;

    explicit CollisionSample() noexcept = default;


    /**
     * @brief Creates circles in the sample world, initializing bodies, colliders, and positions.
     */
    void CreateCircle() noexcept;

    /**
     * @brief Renders the circles in the sample world using SDL.
     * @param renderer The SDL renderer.
     */
    void RenderCircle(SDL_Renderer* renderer) noexcept;

    /**
     * @brief Renders the quad tree nodes in the sample world using SDL.
     * @param renderer The SDL renderer.
     */
    void RenderNodes(SDL_Renderer* renderer) noexcept;

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
     * @brief Handles the event when trigger colliders overlap.
     * @param colliderA The first collider.
     * @param colliderB The second collider.
     */
    void OnTriggerEnter(Engine::Collider colliderA,
                        Engine::Collider colliderB) noexcept override;

    /**
     * @brief Handles the event when trigger colliders stop overlapping.
     * @param colliderA The first collider.
     * @param colliderB The second collider.
     */
    void OnTriggerExit(Engine::Collider colliderA,
                       Engine::Collider colliderB) noexcept override;

    /**
     * @brief Handles the event when a collision occurs, changing the color of affected objects.
     * @param colliderA The first collider.
     * @param colliderB The second collider.
     */
    void OnCollisionEnter(Engine::Collider colliderA,
                          Engine::Collider colliderB) noexcept override;

    /**
     * @brief Handles the event when a collision exits.
     * @param colliderA The first collider.
     * @param colliderB The second collider.
     */
    void OnCollisionExit(Engine::Collider colliderA,
                         Engine::Collider colliderB) noexcept override;


public :
    /**
     * @brief Sets up the collision sample by associating the contact listener and creating circles.
     */
    void SampleSetUp() noexcept override;

    /**
     * @brief Updates the collision sample, updating circle collider shapes and reversing forces on borders.
     */
    void SampleUpdate() noexcept override;

    /**
     * @brief Renders the elements in the sample using SDL.
     * @param renderer The SDL renderer.
     */
    void SampleRender(SDL_Renderer* renderer) noexcept override;

    /**
     * @brief Tears down the sample.
     */
    void SampleTearDown() noexcept override;

};