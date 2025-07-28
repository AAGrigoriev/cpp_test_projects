#pragma once

#include "graphic/graphic.hpp"
#include "controller.hpp"
#include "model.hpp"
#include "observer/observer.hpp"

#include <memory>
class IView
{
public:
    IView()          = default;

    virtual ~IView() = default;

    virtual void button_open()          = 0;

    virtual void button_new()           = 0;

    virtual void button_save()          = 0;

    virtual void button_add_dot()       = 0;

    virtual void button_add_circle()    = 0;

    virtual void button_delete_dot()    = 0;

    virtual void button_delete_circle() = 0;
};

class View : public IView , public IObserver
{
public:
    View(std::shared_ptr<Controller> contr, std::shared_ptr<Model> model);

    virtual ~View() = default;

    virtual void button_open()          override;

    virtual void button_new()           override;

    virtual void button_save()          override;

    virtual void button_add_dot()       override;
 
    virtual void button_add_circle()    override;

    virtual void button_delete_dot()    override;

    virtual void button_delete_circle() override;

    virtual void update()               noexcept override;

private:

    std::shared_ptr<IGraphic>    simpleGraphic;

    std::shared_ptr<IController> contr;
    std::shared_ptr<IModel>      model;
};