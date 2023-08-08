#include <Engine.hpp>
#include <SplashScene.hpp>

namespace skeleton {

Engine::Engine(bool debug_mode) { this->debug_mode = debug_mode; }

void Engine::build_window(uint32_t width, uint32_t height, std::string Title,
						  std::string IconFile, bool fullscreen) {

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	SDL_Window *window = SDL_CreateWindow(
		Title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width,
		height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	SDL_Renderer *renderer =
		SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	locator.provide<SkeletonRenderer>(
		std::make_unique<SkeletonRenderer>(window, renderer));

	locator.provide<SkeletonAssetsManager>(
		std::make_unique<SkeletonAssetsManager>());

	locator.provide<SkeletonSceneManager>(
		std::make_unique<SkeletonSceneManager>());

	locator.get<SkeletonSceneManager>()->add_scene(
		std::make_unique<SplashScene>());
	// if (this->data->debug_mode)
	// 	ImGui::SFML::Init(this->data->render_window);

}

void Engine::run() {
	uint64_t NOW = SDL_GetPerformanceCounter();
	uint64_t LAST = 0;
	double deltaTime = 0;
	while (is_running) {
		locator.get<SkeletonSceneManager>()->process_scene_changes();

		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();

		deltaTime = (double)((NOW - LAST) * 1000 /
							 (double)SDL_GetPerformanceFrequency());

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			// if (this->data->debug_mode)
			// 	ImGui::SFML::ProcessEvent(event);
			locator.get<SkeletonSceneManager>()
				->get_active_scene()
				->handle_input(event);
			switch (event.type) {
				case SDL_QUIT: {
					is_running = false;
					break;
				}

				default: {
					break;
				}
			}
		}

		locator.get<SkeletonSceneManager>()->get_active_scene()->update(
			deltaTime);

		

		// if (this->data->debug_mode)
		// ImGui::SFML::Update(this->data->render_window,
		// 					deltaClock.restart());

		// this->data->render_window.clear(sf::Color(125, 125, 125));
		locator.get<SkeletonRenderer>()->clear();

		if (debug_mode)
			locator.get<SkeletonSceneManager>()
				->get_active_scene()
				->create_debug_window();

		locator.get<SkeletonSceneManager>()->get_active_scene()->draw();

		// if (this->data->debug_mode)
		// 	ImGui::SFML::Render(this->data->render_window);
		locator.get<SkeletonRenderer>()->update();
	}
	// ImGui::SFML::Shutdown();
	SDL_DestroyWindow(locator.get<SkeletonRenderer>()->window);
	SDL_Quit();
}
}; // namespace skeleton
