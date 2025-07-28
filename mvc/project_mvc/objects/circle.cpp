#include "circle.hpp"
#include <iostream>

int Circle::getRadius() {
  return radius;
}

void Circle::paint(std::shared_ptr<IGraphic> graphic) {
  BaseShape::paint(graphic);

  std::cout << "Draw Oval\n";

  graphic->drawOval(x, y, radius);
}
