#pragma once

#include "SDL.h"
#include "Vec2.h"
#include "Shape.h"
#include <vector>


namespace Display
{

    /**
     * @brief Draws a circle in the SDL renderer.
     *
     * @param renderer The SDL renderer.
     * @param position The center position of the circle.
     * @param radius The radius of the circle.
     * @param circleColor The color of the circle (SDL_Color).
     * @param segments The number of segments used for the shape of the circle.
     */
    void DrawCircle(SDL_Renderer* renderer, Math::Vec2F position, float radius, SDL_Color circleColor,
                    int segments) noexcept;

    /**
     * @brief Draws a filled rectangle in the SDL renderer.
     *
     * @param renderer The SDL renderer.
     * @param rect The coordinates of the rectangle (Math::RectangleF).
     * @param rectColor The color of the rectangle (SDL_Color).
     */
    void DrawRect(SDL_Renderer* renderer, Math::RectangleF rect, SDL_Color rectColor) noexcept;

    /**
     * @brief Draws the outline of a rectangle in the SDL renderer.
     *
     * @param renderer The SDL renderer.
     * @param rect The coordinates of the rectangle (Math::RectangleF).
     * @param rectColor The color of the rectangle outline (SDL_Color).
     * @param outlineSize The width of the outline.
     */
    void DrawRectOutline(SDL_Renderer* renderer, Math::RectangleF rect, SDL_Color rectColor, int outlineSize) noexcept;

    /**
     * @brief Generates a random SDL_Color.
     * The RandomColor function generates a random SDL_Color with random values for red, green, blue components within the range [0, 255].
     * The alpha component is set to 255 (fully opaque).
     * @return A randomly generated SDL_Color.
     */
    SDL_Color RandomColor() noexcept;
}
