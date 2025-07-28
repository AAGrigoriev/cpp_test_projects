#pragma once
#include "baseShape.hpp"

struct Dot : BaseShape
{
private:
    int Height = 1;
    int Width = 1;

public:
    Dot(int X, int Y, RGB color) : BaseShape(X, Y, color) {}
    Dot() = default;
    virtual ~Dot() = default;

    virtual void paint(std::shared_ptr<IGraphic> graphic) override;
};
