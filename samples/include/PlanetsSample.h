#pragma once

#include "Display.h"
#include "Metrics.h"
#include "Sample.h"
#include <array>

/**
 * @brief Represents a sample simulating a solar system with a sun and multiple planets.
 *
 * The PlanetsSample class inherits from the Sample class, providing a demonstration of gravitational forces
 * and planetary motion within a 2D space.
 *
 * Key Features:
 * - _PlanetsInTheWorld: The number of planets in the sample world.
 * - _CircleSegments: The number of segments to approximate a circle when rendering.
 * - sun: An instance of the Planet struct representing the sun.
 * - _sunColor: The color of the sun.
 * - planets: An array of Planet objects representing the planets in the sample world.
 *
 * Methods:
 * - ApplyForceToPlanets(): Applies gravitational force from the sun to all planets in the sample world.
 * - CreateRandomSolarSystem(): Creates a random solar system with a sun and multiple planets.
 * - SampleSetUp(): Sets up the sample by creating a random solar system.
 * - SampleUpdate(): Updates the sample by applying gravitational forces to planets.
 * - SampleRender(): Renders the sample using SDL, drawing the sun and planets.
 * - SampleTearDown(): Tears down the sample.
 *
 * The PlanetsSample class provides a visual representation of the interaction between celestial bodies,
 * illustrating the influence of gravitational forces on planetary motion.
 */
struct Planet
{
    Engine::BodyRef bodyRef;
    float radius = 1;
    float G = 100;
    SDL_Color color;
};

class PlanetsSample : public Sample
{
private :
    static constexpr int _CircleSegements = 20;
    static constexpr std::size_t _PlanetsInTheWorld = 800;
    static constexpr SDL_Color _sunColor = {230, 224, 124, 255};
public :
    std::array<Planet, _PlanetsInTheWorld> planets{};
    Planet sun = {};

    PlanetsSample() noexcept = default;

    /**
     * @brief Applies gravitational force from the sun to all planets in the sample world.
     *        Calculates gravitational force based on Newton's law of gravitation.
     */
    void ApplyForceToPlanets() noexcept;

    /**
     * @brief Creates a random solar system with a sun and multiple planets.
     *        Sets up initial positions, masses, velocities, and colors for the sun and planets.
     */
    void CreateRandomSolarSystem() noexcept;

    /**
     * @brief Sets up the sample by creating a random solar system.
     */
    void SampleSetUp() noexcept override;

    /**
     * @brief Updates the sample by applying gravitational forces to planets.
     */
    void SampleUpdate() noexcept override;

    /**
     * @brief Renders the sample using SDL, drawing the sun and planets.
     * @param renderer The SDL renderer.
     */
    void SampleRender(SDL_Renderer* renderer) noexcept override;

    /**
     * @brief Tears down the sample.
     */
    void SampleTearDown() noexcept override;

};