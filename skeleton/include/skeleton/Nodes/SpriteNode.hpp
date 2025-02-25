#ifndef SKELETON_SPRITENODE_HPP
#define SKELETON_SPRITENODE_HPP
#include <memory>
#include <skeleton/core/ResourceManager.hpp>
#include <skeleton/core/Resource.hpp>
#include <skeleton/nodes/DrawableNode.hpp>
#include <string>
namespace skeleton {
class SpriteNode : public skeleton::nodes::DrawableNode {
public:
  SpriteNode() : DrawableNode() { this->name = "SpriteNode"; };
  SpriteNode(std::string source, double x, double y) : DrawableNode() {
    this->name = "SpriteNode";
    this->source = source;
    this->x = x;
    this->y = y;
    std::shared_ptr<skeleton::core::Resource> texture =
        skeleton::core::ResourceManager::get_instance().load_texture(source);
    this->resource_tag = texture.get()->tag;
  };

  void handle_draw() override {
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = 64;
    dest.h = 64;
    skeleton::graphics::Renderer::get_instance().draw_texture(
        this->resource_tag, nullptr, &dest);
  }

  void handle_update(double dt) override {}

  void handle_fixed_update(double dt) override {}

private:
  std::string source;
  size_t resource_tag;
};
#endif
} // namespace skeleton
