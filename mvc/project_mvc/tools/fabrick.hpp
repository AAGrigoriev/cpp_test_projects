#pragma once

#include <memory>
#include "objects/IShape.hpp"
#include "objects/dot.hpp"
#include "objects/circle.hpp"

class IFabrick
{
public:
    IFabrick() = default;
    virtual ~IFabrick() = default;

    virtual std::unique_ptr<IShape> create() noexcept = 0;
};

class DotFabrick : public IFabrick
{
public:
    DotFabrick() = default;
    virtual ~DotFabrick() = default;

    virtual std::unique_ptr<IShape> create() noexcept override
    {
        return std::make_unique<Dot>();
    }
};

class CircleFabrick : public IFabrick
{
public:
    CircleFabrick() = default;
    virtual ~CircleFabrick() = default;

    virtual std::unique_ptr<IShape> create() noexcept override
    {
        return std::make_unique<Circle>();
    }
};