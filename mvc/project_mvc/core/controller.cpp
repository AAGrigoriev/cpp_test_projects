#include "controller.hpp"
#include <assert.h>

Controller::Controller(std::shared_ptr<Model> model) {
  assert(model);

  this->model = model;
}

void Controller::open_document() {
  std::string new_file;
  /* Fill string */
  model->open(new_file);
}

void Controller::add_primitive(std::unique_ptr<IFabrick> f) {
  model->addPrimitive(f->create());
}

void Controller::delete_primitive() {}

void Controller::save_document() {
  model->save_document();
}
