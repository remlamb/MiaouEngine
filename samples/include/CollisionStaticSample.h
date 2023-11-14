#pragma once

#include "Display.h"
#include "ContactListener.h"
#include "Sample.h"
#include "TriggerSample.h"
#include <array>

/**
 * @brief Represents a sample demonstrating collision detection and resolution with static elements.
 *
 * The CollisionStaticSample class inherits from Engine::ContactListener and Engine::Sample,
 * providing a demonstration of collision events between dynamic circles and a static rectangle.
 *
 * Key Features:
 * - CirclesInTheWorld: The number of circles created in the sample world.
 * - CircleSegments: The number of segments to approximate a circle when rendering.
 * - CircleRadius: The radius of the circles in the sample.
 * - ForceToApply: The force applied to the circles on collision with the static rectangle.
 * - BorderSizeForElements: The size of a fictive border where forces are reversed if circles hit it.
 * - staticRect: The static rectangle in the sample world.
 * - rectMinBound: The minimum bounds of the static rectangle.
 * - rectMaxBound: The maximum bounds of the static rectangle.
 * - groundColor: The color of the ground/static rectangle.
 * - circles: An array of Circle objects representing the entities in the sample.
 *
 * Methods:
 * - CreateObjects(): Creates circles and a static rectangle in the sample world, initializing bodies, colliders, and positions.
 * - RenderCircle(): Renders the circles in the sample world using SDL.
 * - OnTriggerEnter(), OnTriggerExit(), OnCollisionEnter(), OnCollisionExit(): Event handling methods.
 * - SampleSetUp(): Sets up the collision static sample by associating the contact listener and creating circles and a static rectangle.
 * - SampleUpdate(): Updates the collision static sample, applying forces to circles and updating their collider shapes.
 * - SampleRender(): Renders the collision static sample using SDL, drawing the static rectangle and circles.
 * - SampleTearDown(): Tears down the sample.
 *
 * The CollisionStaticSample class provides a practical illustration of collision detection and response
 * in a 2D world with static and dynamic elements, showcasing the interaction between different entities.
 */
class CollisionStaticSample : public Engine::ContactListener, public Sample
{
private :
    static constexpr int CircleSegements = 20;
    static constexpr int CircleRadius = 12;

    static constexpr float ForceToApply = 200.0f;
    static constexpr float BorderSizeForElements = 50.0f;

    static constexpr std::size_t CirclesInTheWorld = 20;
public :
    std::array<Circle, CirclesInTheWorld> circles;

    Rect staticRect{};
    static constexpr Math::Vec2F rectMinBound = {BorderSizeForElements, 0.};
    static constexpr Math::Vec2F rectMaxBound = {Metrics::WIDTH - BorderSizeForElements, 100.0f}; //20
    static constexpr SDL_Color groundColor = {210, 210, 210, 255};

    explicit CollisionStaticSample() noexcept = default;

    /**
     * @brief Creates circles and a static rectangle in the sample world, initializing bodies, colliders, and positions.
     */
    void CreateObjects() noexcept;

    /**
     * @brief Renders the circles in the sample world using SDL.
     *
     * @param renderer The SDL renderer.
     */
    void RenderCircle(SDL_Renderer* renderer) noexcept;

    /**
     * @brief Handles the event when a trigger enters, incrementing the collision counter for affected circles.
     * @param colliderA The first collider.
     * @param colliderB The second collider.
     */
    void OnTriggerEnter(Engine::Collider colliderA,
                        Engine::Collider colliderB) noexcept override;

    /**
     * @brief Handles the event when a trigger exits, decrementing the collision counter for affected circles.
     *
     * @param colliderA The first collider.
     * @param colliderB The second collider.
     */
    void OnTriggerExit(Engine::Collider colliderA,
                       Engine::Collider colliderB) noexcept override;

    /**
     * @brief Handles the event when a collision occurs, changing the color of affected circles.
     *
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
     * @brief Sets up the collision static sample by associating the contact listener and creating circles and a static rectangle.
     */
    void SampleSetUp() noexcept override;

    /**
     * @brief Updates the collision static sample, applying forces to circles and updating their collider shapes.
     */
    void SampleUpdate() noexcept override;


    /**
     * @brief Renders the collision static sample using SDL, drawing the static rectangle and circles.
     * @param renderer The SDL renderer.
     */
    void SampleRender(SDL_Renderer* renderer) noexcept override;

    /**
     * @brief Tears down the sample.
     */
    void SampleTearDown() noexcept override;

};