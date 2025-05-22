#ifndef PROPERTY_H
#define PROPERTY_H

#include <functional>
#include <vector>

template<typename T> class Property {

private:

    T _value{};
    std::vector<std::function<void(const T&)>> _listeners{};

public:

    Property() = default;

    explicit Property(const T& initial) : _value(initial) {}

    const T& Get() const { return _value; }

    void Set(const T& v) {
        if (v == _value) return;
        T old = _value;
        _value = v;
        for (auto& f : _listeners) {
            f(_value);
        }
    }

    void AddChangedListener(const std::function<void(const T&)>& f) {
        _listeners.push_back(f);
    }

};

#endif