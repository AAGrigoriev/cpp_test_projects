#pragma once

#include <list>
#include <memory>

/**
 * \interface IObserver
 * @brief For notifications
 */
class IObserver
{
public:
    /**
    * @brief update derived classes
    */
    virtual void update() noexcept = 0;

    virtual ~IObserver() = default;
};

/**
 * \interface IObservable
 * @brief For monitoring
 */
class  IObservable
{
public:

    IObservable() = default;
    virtual ~IObservable() = default;

    void subscribe(std::shared_ptr<IObserver> obs) noexcept
    {
        m_Observers.push_back(obs);
    }

    void unsubscribe(std::shared_ptr<IObserver> obs) noexcept
    {
        m_Observers.remove_if([obs](std::weak_ptr<IObserver> &w_ptr) {
            return w_ptr.expired() || w_ptr.lock() == obs;
        });
    }

    void notify() noexcept
    {
        for (auto &w_ptr : m_Observers)
        {
            if (!w_ptr.expired())
            {
                w_ptr.lock()->update();
            }
        }
    }

private:
    std::list<std::weak_ptr<IObserver>> m_Observers;
};