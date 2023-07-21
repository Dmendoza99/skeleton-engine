#ifndef TEST_STATE_HPP
#define TEST_STATE_HPP

#include <Actor.hpp>
#include <Components.hpp>
#include <ConsoleWidget.hpp>
#include <OpenECS.hpp>
#include <SFML/Window/Event.hpp>
#include <State.hpp>
#include <Systems.hpp>
#include <sol.hpp>

class TestState : public skeleton::State {
  public:
	TestState(skeleton::GameDataRef data);
	void on_init();
	void on_input(sf::Event event);
	void on_update(float dt);
	void on_draw();
	void create_debug_window();
	void setupLuaState();

  private:
	sf::Sprite background;
	ecs::EntityManager Actors;
	ecs::SystemManager Systems = ecs::SystemManager(Actors);
	sol::function script_on_update;
	sol::function script_handle_input;
};

#endif