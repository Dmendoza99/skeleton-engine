#ifndef RENDER_SERVICE_HPP
#define RENDER_SERVICE_HPP
#include "skeleton/core/Service.hpp"
#include <SDL.h>
namespace skeleton::graphics {
class IRenderer : public skeleton::core::Service {
public:
  IRenderer() = default;
  ~IRenderer() override = default;
  virtual void create_window(std::string title, int width, int height,
                             bool debug_mode) = 0;
  virtual void end() = 0;
  virtual void begin() = 0;
  virtual void shutdown() = 0;
  virtual void draw_rect(int x, int y, int w, int h, int r, int g, int b,
                         int a) = 0;
  virtual int get_window_width() = 0;
  virtual int get_window_height() = 0;
  virtual void set_draw_color(SDL_Color color) = 0;
  virtual void set_debug_mode(bool debug_mode) = 0;
  virtual void draw_texture(size_t key, SDL_Rect *src_rect,
                            SDL_Rect *dst_rect) = 0;
};
} // namespace skeleton::graphics
#endif
