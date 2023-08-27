#ifndef SPLASH_STATE_HPP
#define SPLASH_STATE_HPP

#include <Scene.hpp>
#include <SceneManager.hpp>
#include <ServiceLocator.hpp>
#include <SkeletonRenderer.hpp>

class SplashScene : public skeleton::Scene {

  public:
	SplashScene();
	~SplashScene();
	void on_init();
	void on_input(SDL_Event &event);
	void on_update(float dt);
	void on_draw();
	void on_destroy();
	void draw_debug_window();

  private:
	SDL_Surface *background;
	uint64_t start_time = SDL_GetPerformanceCounter();
	double time_to_change_scene = 5.0;
	sol::table config;
	sol::table splash;
	skeleton::ServiceLocator locator;
};

#endif