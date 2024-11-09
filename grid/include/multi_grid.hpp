
#pragma once

#include <cstdlib>
#include <utility>
#include <concepts>
#include <initializer_list>

#include "grid.hpp"

template <typename value_type, unsigned size_type>
class MultiGrid
{
public:
    template<typename ... T> requires(sizeof...(T) == size_type - 1u) && (std::same_as<T, unsigned> && ...)
    MultiGrid(unsigned first_size, T... sizes) : size(first_size), grids(new MultiGrid<value_type, size_type - 1u>[first_size]) {}

    template <typename... T> requires(sizeof...(T) == size_type - 1u) && (std::same_as<T, unsigned> && ...)
    MultiGrid(value_type const &&value, unsigned first_size, T... sizes)
        : size(first_size),
          grids(new MultiGrid<value_type, size_type - 1u>[first_size])
    {
        for (unsigned i = 0; i < first_size; i++) {
            grids[i] = MultiGrid<value_type, size_type - 1u>(first_size, sizes...);
        }
    }

    ~MultiGrid();

    MultiGrid(MultiGrid<value_type, size_type> const &source);
    MultiGrid(MultiGrid<value_type, size_type> &&source);

    MultiGrid<value_type, size_type> &operator=(MultiGrid<value_type, size_type> &);
    MultiGrid<value_type, size_type> &operator=(MultiGrid<value_type, size_type> &&);
    MultiGrid<value_type, size_type> &operator=(value_type &);
    MultiGrid<value_type, size_type> &operator=(value_type const &&);

    template <typename... T>
        requires(sizeof...(T) == size_type - 1u) && (std::same_as<T, unsigned> && ...)
    value_type operator()(unsigned first_idx, T... idxs) const
    {
        return grids[first_idx](idxs...);
    }

    template <typename... T>
        requires(sizeof...(T) == size_type - 1u) && (std::same_as<T, unsigned> && ...)
    value_type &operator()(unsigned first_idx, T... idxs)
    {
        return grids[first_idx](idxs...);
    }

    MultiGrid<value_type, size_type - 1u> operator[](unsigned) const;

    unsigned get_size() const { return size; }

private:
    unsigned size;
    MultiGrid<value_type, size_type - 1u> *grids;
};

template <typename value_type>
class MultiGrid<value_type, 1u>
{
public:
    MultiGrid(unsigned size) : size(size), data(new value_type[size]) {}

    MultiGrid(value_type const &&value, unsigned size) : size(size), data(new value_type[size]) {
        for (unsigned i = 0; i < size; i++) {
            data[i] = value;
        }
    }

    ~MultiGrid();

    MultiGrid(MultiGrid<value_type, 1u> const &source);
    MultiGrid(MultiGrid<value_type, 1u> &&source);

    MultiGrid<value_type, 1u> &operator=(MultiGrid<value_type, 1u> &);
    MultiGrid<value_type, 1u> &operator=(MultiGrid<value_type, 1u> &&);
    MultiGrid<value_type, 1u> &operator=(value_type &);
    MultiGrid<value_type, 1u> &operator=(value_type const &&);

    value_type operator()(unsigned) const;
    value_type &operator()(unsigned);

    value_type operator[](unsigned) const;
    value_type &operator[](unsigned);

    unsigned get_size() const { return size; }

private:
    unsigned const size;
    value_type * data;
};

template <typename value_type, unsigned size_type>
MultiGrid<value_type, size_type>::~MultiGrid()
{
    delete[] grids;
}

template <typename value_type, unsigned size_type>
MultiGrid<value_type, size_type>::MultiGrid(MultiGrid<value_type, size_type> const &source)
    : size(source.get_size()),
      grids(new MultiGrid<value_type, size_type - 1>[size]())
{
    for (unsigned i = 0; i < size; i++)
    {
        grids[i] = source.grids[i];
    }
}

template <typename value_type, unsigned size_type>
MultiGrid<value_type, size_type>::MultiGrid(MultiGrid<value_type, size_type> &&source)
    : size(source.get_size()),
      grids(std::move(source.grids)) {}

template <typename value_type, unsigned size_type>
MultiGrid<value_type, size_type> &MultiGrid<value_type, size_type>::operator=(MultiGrid<value_type, size_type> &source)
{
    size = source.size;
    for (unsigned i = 0; i < size; i++)
    {
        grids[i] = source.grids[i];
    }
    return *this;
}

template <typename value_type, unsigned size_type>
MultiGrid<value_type, size_type> &MultiGrid<value_type, size_type>::operator=(MultiGrid<value_type, size_type> &&source)
{
    size = std::move(source.size);
    grids = std::move(source.grids);
    return *this;
}

template <typename value_type, unsigned size_type>
MultiGrid<value_type, size_type> &MultiGrid<value_type, size_type>::operator=(value_type &value)
{
    for (unsigned i = 0; i < size; i++)
    {
        grids[i] = value;
    }
}

template <typename value_type, unsigned size_type>
MultiGrid<value_type, size_type> &MultiGrid<value_type, size_type>::operator=(value_type const &&value)
{
    for (unsigned i = 0; i < size; i++)
    {
        grids[i] = value;
    }
}

template <typename value_type, unsigned size_type>
MultiGrid<value_type, size_type - 1u> MultiGrid<value_type, size_type>::operator[](unsigned index) const
{
    return grids[index];
}

template <typename value_type>
MultiGrid<value_type, 1u>::~MultiGrid()
{
    delete[] data;
}

template <typename value_type>
MultiGrid<value_type, 1u>::MultiGrid(MultiGrid<value_type, 1u> const &source) : size(source.size), data(new value_type[size])
{
    for (unsigned i = 0u; i < size; i++)
    {
        data[i] = source.data[i];
    }
}
template <typename value_type>
MultiGrid<value_type, 1u>::MultiGrid(MultiGrid<value_type, 1u> &&source) : size(source.size), data(std::move(source.data)) {}

template <typename value_type>
MultiGrid<value_type, 1u> &MultiGrid<value_type, 1u>::operator=(MultiGrid<value_type, 1u> &source)
{
    size = source.size;
    for (unsigned i = 0u; i < size; i++)
    {
        data[i] = source.data[i];
    }
    return *this;
}

template <typename value_type>
MultiGrid<value_type, 1u> &MultiGrid<value_type, 1u>::operator=(MultiGrid<value_type, 1u> &&source)
{
    size = std::move(source.size);
    data = std::move(source.data);

    return *this;
}

template <typename value_type>
MultiGrid<value_type, 1u> &MultiGrid<value_type, 1u>::operator=(value_type &value)
{
    for (unsigned i = 0; i < size; i++)
    {
        data[i] = value;
    }
}

template <typename value_type>
MultiGrid<value_type, 1u> &MultiGrid<value_type, 1u>::operator=(value_type const &&value)
{
    for (unsigned i = 0; i < size; i++)
    {
        data[i] = value;
    }
}

template <typename value_type>
value_type MultiGrid<value_type, 1u>::operator()(unsigned index) const
{
    return data[index];
}

template <typename value_type>
value_type &MultiGrid<value_type, 1u>::operator()(unsigned index)
{
    return data[index];
}

template <typename value_type>
value_type MultiGrid<value_type, 1u>::operator[](unsigned index) const
{
    return data[index];
}

template <typename value_type>
value_type &MultiGrid<value_type, 1u>::operator[](unsigned index)
{
    return data[index];
}