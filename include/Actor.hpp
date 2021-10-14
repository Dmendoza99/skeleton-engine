#pragma once
#include <Components.hpp>
class Actor : public ecs::EntityAlias<GraphicComponent, LogicComponent> {
  public:
	Actor() {}
	Actor(skeleton::GameDataRef Data, std::string Path);
	~Actor();
	void rotate(float Angle);
	void forward(float Speed);
	void backward(float Speed);
	void stop();
	void playAnimation(std::string Name);
};