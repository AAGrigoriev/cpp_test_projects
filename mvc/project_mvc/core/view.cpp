#include "view.hpp"
#include "assert.h"

View::View(std::shared_ptr<Controller> contr, std::shared_ptr<Model> model)
    : contr(contr), model(model) {
  assert(model);
  assert(contr);

  simpleGraphic = std::make_shared<GraphicSimple>();
}

void View::button_open() {
  contr->open_document();
}

void View::button_new() {
  contr->open_document();
}

void View::button_save() {
  contr->save_document();
}

void View::button_add_dot() {
  contr->add_primitive(std::make_unique<DotFabrick>());
}

void View::button_add_circle() {
  contr->add_primitive(std::make_unique<CircleFabrick>());
}

void View::button_delete_circle() {
  contr->delete_primitive();
}

void View::button_delete_dot() {
  contr->delete_primitive();
}

void View::update() noexcept {
  model->draw(simpleGraphic);
}
