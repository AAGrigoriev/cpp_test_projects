#include "baseShape.hpp"
#include <iostream>

BaseShape::BaseShape(int X, int Y, RGB Color) : x(X), y(Y), color(Color) {}

int BaseShape::getX() {
  return x;
}

int BaseShape::getY() {
  return y;
}

void BaseShape::paint(std::shared_ptr<IGraphic> graphic) {
  std::cout << "Base Paint\n";
  /*
      Some logic to init
  */
}
