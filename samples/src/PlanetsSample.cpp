#include "PlanetsSample.h"
#include "Random.h"

void PlanetsSample::ApplyForceToPlanets() noexcept
{
    auto& sunBody = _sampleWorld.GetBody(sun.bodyRef);
    for (auto& planet: planets)
    {
        auto& planetBody = _sampleWorld.GetBody(planet.bodyRef);
        const Math::Vec2F distanceSunPlanet = sunBody.Position() - planetBody.Position();
        const float r = distanceSunPlanet.Length();

        const float gravitationnalForce = planet.G * (planetBody.Mass() * sunBody.Mass() / (r * r));
        const Math::Vec2F forceWithDirection = gravitationnalForce * distanceSunPlanet.Normalized();
        planetBody.AddForce(forceWithDirection);
    }
}

void PlanetsSample::CreateRandomSolarSystem() noexcept
{
    sun.bodyRef = _sampleWorld.CreateBody();
    sun.color = _sunColor;
    sun.radius = 4;

    auto& sunBody = _sampleWorld.GetBody(sun.bodyRef);
    const auto& sunPosition = Math::Vec2F(Metrics::WIDTH / 2, Metrics::HEIGHT / 2);
    sunBody.SetPosition(sunPosition);
    sunBody.SetMass(100000);
    const auto& sunMass = sunBody.Mass();

    for (auto& planet: planets)
    {
        planet.bodyRef = _sampleWorld.CreateBody();
        auto& planetBody = _sampleWorld.GetBody(planet.bodyRef);
        planetBody.SetMass(1);
        Math::Vec2F rndPos(Math::Random::Range(Metrics::WIDTH / 2 + 50, Metrics::WIDTH - 100),
                           Math::Random::Range(0 + 100.0f, Metrics::HEIGHT - 100.0f));
        planetBody.SetPosition(rndPos);
        const auto randomColor = Display::RandomColor();
        planet.color = randomColor;

        Math::Vec2F vecR = sunPosition - planetBody.Position();
        float r = vecR.Length();
        planetBody.SetVelocity(
                std::sqrt((planet.G * (static_cast<float >(sunMass) / r))) * Math::Vec2F(-vecR.Y, vecR.X).Normalized());

    }
}

void PlanetsSample::SampleSetUp() noexcept
{
    CreateRandomSolarSystem();
}

void PlanetsSample::SampleUpdate() noexcept
{
    ApplyForceToPlanets();
}

void PlanetsSample::SampleRender(SDL_Renderer* renderer) noexcept
{
    auto& sunBody = _sampleWorld.GetBody(sun.bodyRef);
    Display::DrawCircle(renderer, sunBody.Position(), sun.radius, sun.color, _CircleSegements);
    for (auto& planet: planets)
    {
        auto& planetBody = _sampleWorld.GetBody(planet.bodyRef);
        Display::DrawCircle(renderer, planetBody.Position(), planet.radius, planet.color, _CircleSegements);
    }
}

void PlanetsSample::SampleTearDown() noexcept
{
    _sampleWorld.contactListener = nullptr;
    planets.fill(Planet());
    sun = {};
}


