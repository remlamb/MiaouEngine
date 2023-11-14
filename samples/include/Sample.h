#pragma once

#include "World.h"
#include "Metrics.h"
#include "Timer.h"
#include "SDL.h"

/**
 * @class Sample
 * @brief Abstract base class representing a sample scenario with a physics simulation world.
 *
 * The Sample class serves as an abstract base class for specific sample scenarios with a physics simulation world.
 * It encapsulates common functionality such as setting up, updating, and tearing down the sample, as well as
 * providing hooks for specific sample implementations to perform setup, update, rendering, and teardown.
 *
 * The class has the following protected members:
 * - `Engine::World _sampleWorld`: The physics simulation world for the sample.
 * - `std::vector<Engine::BodyRef> _bodyRefs`: Vector storing body references used in the sample.
 * - `std::vector<Engine::ColliderRef> _colRefs`: Vector storing collider references used in the sample.
 * - `Engine::Timer _timer`: Timer for measuring elapsed time.
 *
 * The class provides the following public methods:
 * - `void SetUp() noexcept`: Sets up the sample by starting the _timer, initializing the sample world,
 *   and calling the specific sample setup function.
 * - `void SetUpdate() noexcept`: Performs the update for the sample by calling the specific sample update function
 *   and updating the sample world with the elapsed time from the _timer.
 * - `void TearDown() noexcept`: Tears down the sample by calling the specific sample teardown function,
 *   clearing stored body and collider references, and performing any necessary world teardown.
 * - `virtual ~Sample() noexcept = default`: Virtual destructor for proper cleanup in derived classes.
 *
 * The class also has the following protected virtual methods:
 * - `virtual void SampleSetUp() noexcept = 0`: Abstract method for specific sample setup.
 * - `virtual void SampleUpdate() noexcept = 0`: Abstract method for specific sample update.
 * - `virtual void SampleRender(SDL_Renderer *renderer) noexcept = 0`: Abstract method for specific sample rendering.
 * - `virtual void SampleTearDown() noexcept = 0`: Abstract method for specific sample teardown.
 *
 * This class provides a foundation for creating and managing physics simulation samples.
 */
class Sample
{
protected:
    Engine::World _sampleWorld;
    std::vector<Engine::BodyRef> _bodyRefs;
    std::vector<Engine::ColliderRef> _colRefs;
private:
    Engine::Timer _timer;

public:
    /**
     * @brief Sets up the sample by starting the _timer, initializing the sample world,
     *        and calling the specific sample setup function.
     */
    void SetUp() noexcept;

    /**
     * @brief Performs the update for the sample by calling the specific sample update function
     *        and updating the sample world with the elapsed time from the _timer.
     */
    void SetUpdate() noexcept;

    /**
     * @brief Tears down the sample by calling the specific sample teardown function,
     *        clearing stored body and collider references, and performing any necessary world teardown.
     */
    void TearDown() noexcept;

    virtual ~Sample() noexcept = default;

protected:
    virtual void SampleSetUp() noexcept = 0;

    virtual void SampleUpdate() noexcept = 0;

    virtual void SampleRender(SDL_Renderer* renderer) noexcept = 0;

    virtual void SampleTearDown() noexcept = 0;
};