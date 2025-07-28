#pragma once

#include "graphic/graphic.hpp"
#include <memory>

struct IShape
{
    IShape() = default;
    virtual ~IShape() = default;

    virtual int getX() = 0;
    virtual int getY() = 0;
    virtual void paint(std::shared_ptr<IGraphic> graphic) = 0;
};