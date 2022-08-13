#include <Components.hpp>
#include <ConsoleWidget.hpp>
#include <Systems.hpp>
#include <TestState.hpp>

TestState::TestState(skeleton::GameDataRef Data)
	: Data(Data), Systems(Actors) {}

void TestState::init() {
	setupLuaState();
	this->Systems.add<GraphicSystem>();
}

void TestState::setupLuaState() {
	L.open_libraries(sol::lib::base, sol::lib::math, sol::lib::string,
					 sol::lib::io, sol::lib::os);
	L.script_file("assets/scripts/test_state.lua");
	this->setupEngineUserTypes();
	sol::table gc = L["actor_parameters"]["graphic_parameters"];
	Actor actor = this->Actors.create<Actor>(this->Data, gc);

	sol::usertype<Actor> actor_type =
		L.new_usertype<Actor>("Actor", sol::constructors<Actor()>());
 
	actor_type["rotate"] = &Actor::rotate;
	actor_type["forward"] = &Actor::forward;
	actor_type["backward"] = &Actor::backward;
	actor_type["stop"] = &Actor::stop;
	actor_type["flip_horizontal"] = &Actor::flip_horizontal;
	actor_type["flip_vertical"] = &Actor::flip_vertical;
	actor_type["play_animation"] = &Actor::playAnimation;
	actor_type["position"] = &Actor::getPosition;

	sol::usertype<sf::Vector2f> sfVector2f = L.new_usertype<sf::Vector2f>(
		"vector2f",
		sol::constructors<sf::Vector2f(), sf::Vector2f(float, float)>(), "x",
		&sf::Vector2f::x, "y", &sf::Vector2f::y);

	L["actor"] = actor;
	skeleton::setLogger(L);
	this->on_update = L["on_update"];
	this->handle_input = L["handle_input"];
}

void TestState::handleInput(sf::Event event) { this->handle_input(event); }

void TestState::update(float dt) {
	this->Systems.update(dt);
	this->on_update(dt);
}

void TestState::drawDebugWindow() {

	ImGui::Begin("Test State");
	console.Draw("Console: Test State", &isOpen, L);
	this->Data->logEngine();
	ImGui::TextColored(ImVec4(1, 1, 0, 1), "Actors");
	ImGui::BeginChild("Scrolling");
	int count = 0;
	for (auto entity : Actors.with<GraphicComponent>()) {
		ImGui::Text("Actor %d: %s", count++,
					entity.get<GraphicComponent>().CurrentAnimation.c_str());
	}
	ImGui::EndChild();
	ImGui::End();
}

void TestState::draw(float dt) {
	for (auto entity : Actors.with<GraphicComponent>())
		this->Data->Window.draw(entity.get<GraphicComponent>().Sprite);
}
