#ifndef SKELETON_STATE_HPP
#define SKELETON_STATE_HPP

#include <ConsoleWidget.hpp>
#include <GameData.hpp>
#include <SDL2/SDL.h>
#include <Utils.hpp>
#include <memory>
#include <sol.hpp>

namespace skeleton {
class State {
  public:
	skeleton::GameDataRef data;
	sol::state L;
	// ConsoleWidget console;
	bool is_open = false;

	State(skeleton::GameDataRef data) { this->data = data; }
	// User's Functions
	virtual void on_init() = 0;
	virtual void on_input(SDL_Event &event) = 0;
	virtual void on_update(float dt) = 0;
	virtual void on_draw() = 0;
	virtual void create_debug_window() = 0;

	// Engine's Functions
	virtual void pause() {}
	virtual void resume() {}
	virtual void init() { on_init(); }
	virtual void draw() { on_draw(); }
	virtual void handle_input(SDL_Event &event) { on_input(event); }
	virtual void update(float dt) { this->on_update(dt); }

	virtual void set_engine_user_types() { skeleton::setEngineMetadata(L); }
};

typedef std::unique_ptr<State> StateRef;
}; // namespace skeleton

#endif