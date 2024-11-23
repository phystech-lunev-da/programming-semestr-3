
#pragma once

#include <cstdlib>
#include <utility>

template <class T>
class Grid final
{
public:
    using value_type = T;
    using size_type = unsigned;

    class ProxyGrid
    {
    public:
        ProxyGrid() = delete;
        ProxyGrid(ProxyGrid const &) = delete;
        ProxyGrid(ProxyGrid const && source) noexcept : x_size(source.x_size), data(std::move(source.data)) {} 

        ProxyGrid(Grid<T> const & source, Grid::size_type index)
            : x_size(source.x_size), data(source.data + index * source.x_size) {}
        ProxyGrid(Grid<T> && source, Grid::size_type index)
            : x_size(source.x_size), data(source.data + index * source.x_size) {}

        T& operator[](size_type x_idx)
        {
            return data[x_idx];
        }

        ~ProxyGrid() {}

    private:
        size_type const x_size;
        T * const data;
    };

    Grid(size_type, size_type);
    Grid(T const &);
    Grid(size_type, size_type, T const &);
    Grid(size_type, size_type, T&&) noexcept;

    ~Grid();

    Grid(Grid const &source);
    Grid(Grid &&source) noexcept;

    Grid &operator=(Grid const &);
    Grid &operator=(Grid &&) noexcept;
    Grid &operator=(T const &t);

    T operator()(size_type, size_type) const;
    T &operator()(size_type, size_type);

    ProxyGrid operator[](size_type) const;

    size_type const& get_y_size() { return y_size; }
    size_type const& get_x_size() { return x_size; }

private:
    size_type const y_size, x_size;
    T * data;
};

class Vec2 {
public:
    Vec2(int x, int y) : x(x), y(y) {}
private:
    int x, y;
};

template<class T>
Grid<T>::Grid(T const & value) : Grid(1, 1, value) {}

template <class T>
Grid<T>::Grid(Grid<T>::size_type x_size, Grid<T>::size_type y_size) : y_size(y_size), x_size(x_size), data(new T[x_size * y_size]) {}

template <class T>
Grid<T>::Grid(size_type x_size, size_type y_size, T const & value) : y_size(y_size), x_size(x_size) {
    void *temp_data = operator new(sizeof(T) * x_size * y_size);

    for (size_type i = 0; i < y_size * x_size; i++)
    {
        T* obj = static_cast<T*>(temp_data + i * sizeof(T));
        *obj = T{value};
    }

    data = static_cast<T*>(temp_data);
}

template <class T>
Grid<T>::Grid(size_type x_size, size_type y_size, T && value) noexcept : y_size(y_size), x_size(x_size) {
    void *temp_data = operator new(sizeof(T) * x_size * y_size);
    for (size_type i = 0; i < y_size * x_size; i++)
    {
        T* obj = static_cast<T*>(temp_data + i * sizeof(T));
        std::swap(*obj, value);
    }
    data = static_cast<T*>(temp_data);
}

template <class T>
Grid<T>::~Grid()
{
    for (int i = 0; i < y_size * x_size; i++) {
        data[i].~T();
    }
}

template <class T>
Grid<T>::Grid(Grid<T> const &source) : y_size(source.y_size), x_size(source.x_size), data(new T[y_size * x_size])
{
    for (size_type i = 0; i < y_size * x_size; i++)
    {
        data[i] = source.data[i];
    }
}
template <class T>
Grid<T>::Grid(Grid<T> &&source) noexcept : y_size(source.y_size), x_size(source.x_size), data(std::move(source.data)) {}

template <class T>
Grid<T> &Grid<T>::operator=(Grid<T> const &source)
{
    if (this != &source) {
        *this = Grid<T>(source);
    }
    return *this;
}
template <class T>
Grid<T> &Grid<T>::operator=(Grid<T> &&source) noexcept
{
    std::swap(*this, source);
    return *this;
}

template <class T>
T Grid<T>::operator()(Grid<T>::size_type x_idx, Grid<T>::size_type y_idx) const
{
    return data[y_idx * x_size + x_idx];
}

template <class T>
T &Grid<T>::operator()(Grid<T>::size_type x_idx, Grid<T>::size_type y_idx)
{
    return data[y_idx * x_size + x_idx];
}

template <class T>
Grid<T> &Grid<T>::operator=(T const &t)
{
    for (auto it = data, end = data + x_size * y_size; it != end; ++it)
        *it = t;
    return *this;
}

template <class T>
typename Grid<T>::ProxyGrid Grid<T>::operator[](Grid<T>::size_type index) const
{
    return ProxyGrid(*this, index);
}