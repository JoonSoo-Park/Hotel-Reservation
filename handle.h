#ifndef HANDLE_H
#define HANDLE_H
#include <stdexcept>

template <class T>
class Handle {
public:
    Handle() : data(0) { }
    Handle(T* rhs) : data(rhs) { }
    Handle(const Handle& rhs) : data(0) { if (rhs.data) data = new T(*rhs.data); }
    Handle& operator=(const Handle&);
   ~Handle() {
       delete data;
   } 

    operator bool() const { return *data; }
    T& operator*() const;
    T* operator->() const;
private:
    T* data;
};

template <class T>
T& Handle<T>::operator*() const
{
    if (data) {
        return *data;
    }

    throw std::runtime_error("unbound Handle");
}

template <class T>
T* Handle<T>::operator->() const
{
    if (data) {
        return data;
    }

    throw std::runtime_error("unbound Handle");
}

template <class T>
Handle<T>& Handle<T>::operator=(const Handle& rhs)
{
    if (&rhs != this) {
        delete data;
        data = rhs.data ? rhs.data->clone() : 0;
    }

    return *this;
}

#endif