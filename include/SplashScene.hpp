#ifndef SPLASH_STATE_HPP
#define SPLASH_STATE_HPP

#include "SkeletonSceneManager.hpp"
#include "TestScene.hpp"
#include <Scene.hpp>
#include <SceneManager.hpp>
#include <ServiceLocator.hpp>
#include <SkeletonRenderer.hpp>

class SplashScene : public skeleton::Scene {

  public:
	SplashScene(std::string tag);
	~SplashScene() override;
	void initialize() override;
	void handle_input(SDL_Event &event) override;
	void update(double dt) override;
	// void fixed_update(float dt) override;
	void draw() override;
	void destroy() override;
	void draw_debug_window() override;

  private:
	uint64_t start_time = SDL_GetPerformanceCounter();
	double time_to_change_scene = 5.0;
	sol::table config;
	sol::table splash;
	skeleton::ServiceLocator locator;
};

#endif
