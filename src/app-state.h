#pragma once

#include "screen/page.h"

namespace synth {

using screen::Page;

class AppState {
private:
  Page page_ = Page::INDEX;
  bool is_screen_painted_ = false;
  
public:
  inline const Page& get_page() const { return page_; }
  inline void switch_page(Page next) {
    page_ = next;
    is_screen_painted_ = false;
  }

  inline bool should_paint_screen() const { return !is_screen_painted_; }
  inline void screen_painted() { is_screen_painted_ = true; }
};

} // namespace synth
