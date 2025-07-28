#pragma once

#include "IShape.hpp"

struct BaseShape : IShape
{

protected:
    int x = 0;
    int y = 0;
    RGB color{0,0,0};

public:

    BaseShape(int X,int Y,RGB color);
    BaseShape()                  = default;
    virtual ~BaseShape()         = default;

    int          getX() override;
    int          getY() override;
    virtual void paint(std::shared_ptr<IGraphic> graphic) override;
};