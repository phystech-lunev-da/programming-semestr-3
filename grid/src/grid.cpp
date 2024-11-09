
#include "grid.hpp"

#include <vector>

template <typename T>
Grid<T>::Grid(Grid<T>::size_type y_size, Grid<T>::size_type x_size) : y_size(y_size), x_size(x_size), data(new T[y_size * x_size]) {}

template <typename T>
Grid<T>::Grid(size_type y_size, size_type x_size, T const &value) : y_size(y_size), x_size(x_size), data(new T[y_size * x_size])
{
    for (size_type i = 0; i < y_size * x_size; i++)
    {
        data[i] = value;
    }
}

template <typename T>
Grid<T>::~Grid()
{
    delete[] data;
}

template <typename T>
Grid<T>::Grid(Grid<T> const &source) : y_size(source.y_size), x_size(source.x_size), data(new T[y_size * x_size])
{
    for (size_type i = 0; i < y_size * x_size; i++)
    {
        data[i] = source.data[i];
    }
}
template <typename T>
Grid<T>::Grid(Grid<T> &&source) noexcept : y_size(source.y_size), x_size(source.x_size), data(std::move(source.data)) {}

template <typename T>
Grid<T> &Grid<T>::operator=(Grid<T> &source)
{
    y_size = source.y_size;
    x_size = source.x_size;
    for (size_type i = 0; i < y_size * x_size; i++)
    {
        data[i] = source.data[i];
    }
    return *this;
}
template <typename T>
Grid<T> &Grid<T>::operator=(Grid<T> &&source) noexcept
{
    std::swap(x_size, source.y_size);
    std::swap(x_size, source.x_size);
    std::swap(data, source.data);

    return *this;
}

template <typename T>
T Grid<T>::operator()(Grid<T>::size_type y_idx, Grid<T>::size_type x_idx) const
{
    return data[y_idx * x_size + x_idx];
}

template <typename T>
T &Grid<T>::operator()(Grid<T>::size_type y_idx, Grid<T>::size_type x_idx)
{
    return data[y_idx * x_size + x_idx];
}

template <typename T>
Grid<T> &Grid<T>::operator=(T const &t)
{
    for (auto it = data, end = data + x_size * y_size; it != end; ++it)
        *it = t;
    return *this;
}

template <typename T>
typename Grid<T>::ProxyGrid Grid<T>::operator[](Grid<T>::size_type index) const
{
    return ProxyGrid(*this, index);
}

template class Grid<float>;