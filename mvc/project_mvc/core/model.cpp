#include "model.hpp"

void Model::save_document() {
  /* save to file (Serialize)*/
}

void Model::open(std::string& FilePath) {
  list_shapes.clear();

  filePath = FilePath;
  /* load from file */
  notify();
}

void Model::addPrimitive(std::unique_ptr<IShape> shape) {
  list_shapes.push_back(std::move(shape));
  notify();
}

void Model::deletePrimitive(std::unique_ptr<IShape> shape) {
  list_shapes.remove(shape);
  notify();
}

void Model::draw(std::shared_ptr<IGraphic> graphic) {
  for (auto& object : list_shapes) {
    object->paint(graphic);
  }
}
