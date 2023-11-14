#include "Display.h"
#include "Random.h"


void Display::DrawCircle(SDL_Renderer* renderer, Math::Vec2F position, float radius, SDL_Color circleColor,
                         int segments) noexcept
{
    std::vector<SDL_Vertex> vertices;
    std::vector<int> indices;

    for (int i = 0; i < segments; ++i)
    {
        float angle = 2.0f * Math::Pi * static_cast<float>(i) / static_cast<float>(segments);
        float x = position . X + radius * cos(angle);
        float y = position . Y + radius * sin(angle);
        vertices . push_back({{x, y}, circleColor, {1.0f, 1.0f}});
    }

    for (int i = 0; i < segments - 1; ++i)
    {
        indices . push_back(0);
        indices . push_back(i);
        indices . push_back(i + 1);
    }
    indices . push_back(0);
    indices . push_back(segments - 1);
    indices . push_back(0);

    SDL_RenderGeometry(renderer, nullptr, vertices . data(), vertices . size(),
                       indices . data(), indices . size());
}

void Display::DrawRect(SDL_Renderer* renderer, Math::RectangleF rect, SDL_Color rectColor) noexcept
{
    SDL_SetRenderDrawColor(renderer, rectColor . r, rectColor . g, rectColor . b, rectColor . a);
    SDL_Rect sdlRect;
    sdlRect . x = static_cast<int>(rect . MinBound() . X);
    sdlRect . y = static_cast<int>(rect . MinBound() . Y);
    sdlRect . w = static_cast<int>(rect . MaxBound() . X - rect . MinBound() . X);
    sdlRect . h = static_cast<int>(rect . MaxBound() . Y - rect . MinBound() . Y);
    SDL_RenderFillRect(renderer, &sdlRect);
}

void
Display::DrawRectOutline(SDL_Renderer* renderer, Math::RectangleF rect, SDL_Color rectColor, int outlineSize) noexcept
{
    SDL_Rect sdlRect;
    sdlRect . x = static_cast<int>(rect . MinBound() . X);
    sdlRect . y = static_cast<int>(rect . MinBound() . Y);
    sdlRect . w = static_cast<int>(rect . MaxBound() . X - rect . MinBound() . X);
    sdlRect . h = static_cast<int>(rect . MaxBound() . Y - rect . MinBound() . Y);

    SDL_SetRenderDrawColor(renderer, rectColor . r, rectColor . g, rectColor . b, rectColor . a);
    sdlRect . x = static_cast<int>(rect . MinBound() . X);
    sdlRect . y = static_cast<int>(rect . MinBound() . Y);
    sdlRect . w = static_cast<int>(rect . MaxBound() . X - rect . MinBound() . X);
    sdlRect . h = outlineSize;
    SDL_RenderFillRect(renderer, &sdlRect);

    sdlRect . h = outlineSize;
    sdlRect . y = static_cast<int>(rect . MaxBound() . Y - 1);
    SDL_RenderFillRect(renderer, &sdlRect);

    sdlRect . h = static_cast<int>(rect . MaxBound() . Y - rect . MinBound() . Y);
    sdlRect . w = outlineSize;
    sdlRect . x = static_cast<int>(rect . MinBound() . X);
    sdlRect . y = static_cast<int>(rect . MinBound() . Y);
    SDL_RenderFillRect(renderer, &sdlRect);

    sdlRect . w = outlineSize;
    sdlRect . x = static_cast<int>(rect . MaxBound() . X - 1);
    SDL_RenderFillRect(renderer, &sdlRect);
}

SDL_Color Display::RandomColor() noexcept
{
    SDL_Color randomColor = {
            static_cast<Uint8>(Math::Random::Range(0, 256)),
            static_cast<Uint8>(Math::Random::Range(0, 256)),
            static_cast<Uint8>(Math::Random::Range(0, 256)), 255
    };
    return randomColor;
}