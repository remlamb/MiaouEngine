#include "SampleManager.h"

void SampleManager::ImguiInit() noexcept
{
    if (_sceneLaunchName == _items[0])
    {
        _planetsManager.SetUp();
    }
    else if (_sceneLaunchName == _items[1])
    {
        _triggerSample.SetUp();
    }
    else if (_sceneLaunchName == _items[2])
    {
        _collisionSample.SetUp();
    }
    else if (_sceneLaunchName == _items[3])
    {
        _collisionStaticSample.SetUp();
    }
    else if (_sceneLaunchName == _items[4])
    {
        _collisionWithRectSample.SetUp();
    }
    else
    {

    }

    ImGui::CreateContext();
    ImGui::StyleColorsClassic();
    ImGui_ImplSDL2_InitForSDLRenderer(_window, _renderer);
    ImGui_ImplSDLRenderer2_Init(_renderer);
}

ErrorCode SampleManager::InitSDL() noexcept
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        return ErrorCode::SDLInitError;
    }

    _window = SDL_CreateWindow("MiaouEngine",
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               Metrics::WIDTH,
                               Metrics::HEIGHT,
                               SDL_WINDOW_SHOWN);

    if (!_window)
    {
        SDL_Quit();
        return ErrorCode::SDLWindowCreateError;
    }

    _renderer = SDL_CreateRenderer(_window,
                                   -1,
                                   SDL_RENDERER_ACCELERATED);

    if (!_renderer)
    {
        SDL_DestroyWindow(_window);
        SDL_Quit();
        return ErrorCode::SDLRendererCreateError;
    }

    ImguiInit();
    return ErrorCode::Success;
}

void SampleManager::ImguiUpdate() noexcept
{
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    if (_sceneWindow)
    {
        ImGui::Begin("Welcome to MiaouEngine!");

        ImGui::Text("Choose your");
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(0.5f, 0.9f, 0.65f, 1.0f), "Demo Scene");
        ImGui::SameLine();
        ImGui::Text(":");

        ImGui::Combo("##", &_item_current, _items, IM_ARRAYSIZE(_items));

        ImGui::SameLine();
        if (ImGui::Button("Launch"))
        {
            auto oldScene = _sceneLaunchName;
            _sceneLaunchName = _items[_item_current];
            if (oldScene == _items[0])
            {
                _planetsManager.TearDown();
            }
            else if (oldScene == _items[1])
            {
                _triggerSample.TearDown();
            }
            else if (oldScene == _items[2])
            {
                _collisionSample.TearDown();
            }
            else if (oldScene == _items[3])
            {
                _collisionStaticSample.TearDown();
            }
            else if (oldScene == _items[4])
            {
                _collisionWithRectSample.TearDown();
            }
            else
            {

            }


            if (_sceneLaunchName == _items[0])
            {
                _planetsManager.SetUp();
            }
            else if (_sceneLaunchName == _items[1])
            {
                _triggerSample.SetUp();
            }
            else if (_sceneLaunchName == _items[2])
            {
                _collisionSample.SetUp();
            }
            else if (_sceneLaunchName == _items[3])
            {
                _collisionStaticSample.SetUp();
            }
            else if (_sceneLaunchName == _items[4])
            {
                _collisionWithRectSample.SetUp();
            }
            else
            {

            }
        }

        ImGui::Spacing();
        ImGui::Text("%s is currently playing", _sceneLaunchName);

        ImGui::Spacing();
        ImGui::Checkbox("Description", &_descriptionWindow);
        ImGui::End();
    }

    if (_descriptionWindow)
    {
        ImGui::Begin("Scenes Description");
        for (int i = 0; i < _itemsSize; i++)
        {
            ImGui::TextColored(ImVec4(0.5f, 0.9f, 0.65f, 1.0f), "%s", _items[i]);
            ImGui::Text("%s", _itemsDescription[i]);
            ImGui::Spacing();
        }
        ImGui::End();
    }

    if (_sceneLaunchName == _items[0])
    {
        _planetsManager.SetUpdate();
    }
    else if (_sceneLaunchName == _items[1])
    {
        _triggerSample.SetUpdate();
    }
    else if (_sceneLaunchName == _items[2])
    {
        _collisionSample.SetUpdate();
    }
    else if (_sceneLaunchName == _items[3])
    {
        _collisionStaticSample.SetUpdate();
    }
    else if (_sceneLaunchName == _items[4])
    {
        _collisionWithRectSample.SetUpdate();
    }
    else
    {

    }
}

void SampleManager::Update() noexcept
{
    ImguiUpdate();
}

void SampleManager::Run() noexcept
{
    bool quit = false;
    while (!quit)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            ImGui_ImplSDL2_ProcessEvent(&e);
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }
        Update();
        Render();
#ifdef TRACY_ENABLE
        FrameMark;
#endif
    }
}

void SampleManager::ImguiRender() noexcept
{
    ImGui::Render();
    if (_sceneLaunchName == _items[0])
    {
        _planetsManager.SampleRender(_renderer);
    }
    else if (_sceneLaunchName == _items[1])
    {
        _triggerSample.SampleRender(_renderer);
    }
    else if (_sceneLaunchName == _items[2])
    {
        _collisionSample.SampleRender(_renderer);
    }
    else if (_sceneLaunchName == _items[3])
    {
        _collisionStaticSample.SampleRender(_renderer);
    }
    else if (_sceneLaunchName == _items[4])
    {
        _collisionWithRectSample.SampleRender(_renderer);
    }
    else
    {

    }
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
}

void SampleManager::Render() noexcept
{
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);
    ImguiRender();
    SDL_RenderPresent(_renderer);
}

void SampleManager::ImguiDeInit() noexcept
{
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void SampleManager::DeInit() noexcept
{
    ImguiDeInit();
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}









