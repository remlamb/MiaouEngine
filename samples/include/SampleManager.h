#pragma once

#include "TriggerSample.h"
#include "PlanetsSample.h"
#include "CollisionSample.h"
#include "CollisionStaticSample.h"
#include "CollisionWithRectSample.h"

#include <imgui.h>
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

/**
 * @brief Enumerates possible error codes for SDL initialization.
 *
 * The ErrorCode enum class defines various error codes that may occur during the initialization of SDL (Simple DirectMedia Layer).
 * - Success: Indicates successful initialization.
 * - SDLInitError: Indicates an error during SDL initialization.
 * - SDLWindowCreateError: Indicates an error when creating an SDL window.
 * - SDLRendererCreateError: Indicates an error when creating an SDL renderer.
 *
 * These error codes are used to provide detailed feedback on the success or failure of SDL-related operations.
 */
enum class ErrorCode
{
    Success,
    SDLInitError,
    SDLWindowCreateError,
    SDLRendererCreateError
};


/**
 * @brief Manages different scenes and provides an interactive interface for selecting and running specific demos.
 *
 * The SampleManager class orchestrates the initialization, updating, rendering, and teardown of various sample scenes.
 * It integrates ImGui for a user-friendly interface to choose scenes and displays descriptions of each scene.
 * The class handles SDL initialization, window creation, and rendering setup.
 *
 * Key Features:
 * - _window: SDL window pointer.
 * - _renderer: SDL renderer pointer.
 * - _triggerSample: Sample scene for trigger collisions.
 * - _planetsManager: Sample scene for planetary motion.
 * - _collisionSample: Sample scene for collision detection.
 * - _collisionStaticSample: Sample scene for static collisions.
 * - _collisionWithRectSample: Sample scene for collisions between circles and rectangles.
 * - _sceneWindow: Toggle for the main scene selection window.
 * - _descriptionWindow: Toggle for the scene description window.
 * - _itemsSize: Number of available scenes.
 * - _items: Names of available scenes.
 * - _itemsDescription: Descriptions of available scenes.
 * - _item_current: Index of the currently selected scene in imgui label.
 * - _sceneLaunchName: Name of the current scene.
 *
 * Methods:
 * - ImguiInit(): Initializes ImGui and sets up the active scene based on user choice.
 * - InitSDL(): Initializes SDL, creates a window, and sets up the renderer.
 * - ImguiUpdate(): Updates the ImGui interface, allowing users to choose scenes and launch them.
 * - Update(): Calls ImguiUpdate and updates the active scene.
 * - Run(): Main application loop that handles events, updates, and renders the application.
 * - ImguiRender(): Renders the ImGui interface and the active scene based on the user's choice.
 * - Render(): Clears and renders the SDL window with ImGui content and the active scene.
 * - ImguiDeInit(): Deinitializes ImGui.
 * - DeInit(): Deinitializes ImGui, SDL renderer, and window.
 *
 * The SampleManager class provides a flexible and interactive way to explore different scenes within the application.
 */
class SampleManager
{
public:
    /**
     * @brief Initializes ImGui, sets up the active scene based on user choice, and prepares for rendering.
     * This function is also determining the initial scene to launch.
     */
    void ImguiInit() noexcept;

    /**
     * @brief Initializes SDL, creates a window, and sets up the renderer.
     * @return ErrorCode::Success if initialization is successful, otherwise, returns an appropriate error code.
     */
    ErrorCode InitSDL() noexcept;

    /**
     * @brief Updates the ImGui interface, allowing users to choose scenes and launch them.
     */
    void ImguiUpdate() noexcept;

    /**
     * @brief Calls ImguiUpdate and updates the active scene.
     */
    void Update() noexcept;

    /**
     * @brief Main application loop that handles events, updates, and renders the application.
     */
    void Run() noexcept;

    /**
     * @brief Renders the ImGui interface and the active scene based on the user's choice.
     */
    void ImguiRender() noexcept;

    /**
     * @brief Clears and renders the SDL window with ImGui content and the active scene.
     */
    void Render() noexcept;

    /**
     * @brief Deinitializes ImGui.
     * This function handles the cleanup and deinitialization of ImGui resources, shutting down ImGui rendering.
     */
    void ImguiDeInit() noexcept;

    /**
     * @brief Deinitializes ImGui, SDL renderer, and window.
     */
    void DeInit() noexcept;

private :
    SDL_Window* _window;
    SDL_Renderer* _renderer;

    TriggerSample _triggerSample;
    PlanetsSample _planetsManager;
    CollisionSample _collisionSample;
    CollisionStaticSample _collisionStaticSample;
    CollisionWithRectSample _collisionWithRectSample;


    bool _sceneWindow = true;
    bool _descriptionWindow = false;

    static const int _itemsSize = 5;
    const char* _items[_itemsSize] = {
            "Solar System Scene", "Trigger Scene", "Collision Scene", "Collision Static Scene",
            "Collision Scene with Rectangle"
    };
    const char* _itemsDescription[_itemsSize] = {
            "The Planets Scene provides a visual\nrepresentation of the interaction\nbetween celestial bodies, illustrating\nthe influence of gravitational\nforces on planetary motion.",
            "The Trigger Scene provides a visual\nrepresentation of trigger collisions,\nobjects will change colour depending\non whether they overlap or not.\nRed != overlap.\nGreen == overlap.",
            "The Collision Scene provides a practical\nillustration of collision detection\nand response in a 2D world using a QuadTree.\nAlso two circles that collide\nwill take on the same new color.",
            "The Static Scene provides a practical \nillustration of collision detection\nand response in a 2D world with static\nand dynamic elements.\nContact response is based\non the collider restitution.",
            "The Scene provides a practical illustration\nof collision detection and response\nin a 2D world using a QuadTree.\nScene is showcasing the interaction\nbetween different entities shapes.\nTwo objects that collide will take\non the same new color."
    };

    int _item_current = 0;
    const char* _sceneLaunchName = _items[1];
};



