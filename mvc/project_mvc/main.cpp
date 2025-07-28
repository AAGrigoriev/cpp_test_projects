#include "core/controller.hpp"
#include "core/model.hpp"
#include "core/view.hpp"

int main() {
  auto model_vec = std::make_shared<Model>();
  auto cont_vec = std::make_shared<Controller>(model_vec);
  auto view_vec = std::make_shared<View>(cont_vec, model_vec);

  model_vec->subscribe(view_vec);
  view_vec->button_add_dot();
  model_vec->unsubscribe(view_vec);

  return 0;
}
