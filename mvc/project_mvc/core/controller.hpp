#pragma once

#include <memory>
#include "tools/tools.hpp"
#include "model.hpp"
#include "tools/fabrick.hpp"

class IController
{
public:
    IController() = default;
    virtual ~IController() = default;

    virtual void open_document() = 0;

    virtual void add_primitive(std::unique_ptr<IFabrick> f) = 0;

    virtual void delete_primitive() = 0;

    virtual void save_document() = 0;
};

class Controller : public IController
{
public:
    Controller(std::shared_ptr<Model> model);

    virtual ~Controller() = default;

    virtual void open_document() override;

    virtual void add_primitive(std::unique_ptr<IFabrick> f) override;

    virtual void delete_primitive() override;

    virtual void save_document() override;

private:
    std::shared_ptr<IModel> model;
};