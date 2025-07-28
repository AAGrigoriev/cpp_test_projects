#pragma once 

#include "forward_list"
#include "memory"

namespace Reader {
template <typename T>
class IObserver {
public:
  virtual ~IObserver(){};
  virtual void update(const T &data) = 0;
};

template <typename T>
class ISubject {
public:
  virtual ~ISubject(){};
  virtual void attach(const std::shared_ptr<IObserver<T>>& sh_ptr) = 0;
  virtual void detach(const std::shared_ptr<IObserver<T>>& sh_ptr) = 0;
  void notify(const T &data);

protected:
    std::forward_list<std::weak_ptr<IObserver<T>>> F_list;
};

template <typename T>
void ISubject<T>::notify(const T &data) {
auto begin = F_list.begin();
auto endIt = F_list.end();
while (begin != endIt) {
  auto sh_ptr_Observer = begin->lock();
  if (auto sh_ptr_Observer = begin->lock()) {
      sh_ptr_Observer->update(data);
  }
  ++begin;
}
}

} // namespace fileReader
