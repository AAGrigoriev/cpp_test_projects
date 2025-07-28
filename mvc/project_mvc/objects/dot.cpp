#include "dot.hpp"
#include <iostream>

void Dot::paint(std::shared_ptr<IGraphic> graphic) {
  BaseShape::paint(graphic);
  std::cout << "Paint Dot";
  graphic->fillRect(x, y, Height, Width);
}
