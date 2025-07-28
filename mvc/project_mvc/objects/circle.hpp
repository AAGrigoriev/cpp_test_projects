#pragma once

#include "baseShape.hpp"

struct Circle : BaseShape
{
private:
    int radius = 0;

public:
    Circle(int X, int Y, int Radius, RGB color) : BaseShape(X, Y, color), radius(Radius) {}

    Circle() = default;
    virtual ~Circle() = default;

    int getRadius();

    virtual void paint(std::shared_ptr<IGraphic> graphic) override;
};
