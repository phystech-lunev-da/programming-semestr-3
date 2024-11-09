
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
    MultiGrid() : size(0), grids(nullptr) {}

    template<typename FirstT, typename ... T> requires(sizeof...(T) == size_type - 1u) && (std::integral<FirstT>) && (std::integral<T> && ...)
    MultiGrid(FirstT first_size, T... sizes) : size(first_size), grids(new MultiGrid<value_type, size_type - 1u>[first_size]) {}

    template <typename FirstT, typename... T> requires(sizeof...(T) == size_type - 1u) && (std::integral<FirstT>) && (std::integral<T> && ...)
    MultiGrid(value_type value, FirstT first_size, T... sizes)
        : size(first_size),
          grids(new MultiGrid<value_type, size_type - 1u>[first_size])
    {
        for (unsigned i = 0; i < first_size; i++) {
            grids[i] = MultiGrid<value_type, size_type - 1u>(sizes...);
        }
    }

    ~MultiGrid();

    MultiGrid(MultiGrid<value_type, size_type> const &source);
    MultiGrid(MultiGrid<value_type, size_type> const &&source);

    MultiGrid<value_type, size_type> &operator=(const MultiGrid<value_type, size_type> &);
    MultiGrid<value_type, size_type> &operator=(MultiGrid<value_type, size_type> &&) noexcept;
    MultiGrid<value_type, size_type> &operator=(const value_type &);
    MultiGrid<value_type, size_type> &operator=(const value_type &&);

    template <typename FirstT, typename... T>
        requires(sizeof...(T) == size_type - 1u) && (std::integral<FirstT>) && (std::integral<T> && ...)
    value_type operator()(FirstT first_idx, T... idxs) const
    {
        return grids[first_idx](idxs...);
    }

    template <typename FirstT, typename... T>
        requires(sizeof...(T) == size_type - 1u) && (std::integral<FirstT>) && (std::integral<T> && ...)
    value_type &operator()(FirstT first_idx, T... idxs)
    {
        return grids[first_idx](idxs...);
    }

    MultiGrid<value_type, size_type - 1u> operator[](unsigned) const;

    unsigned get_size() const { return size; }

private:
    unsigned const size;
    MultiGrid<value_type, size_type - 1u> *grids;
};

template <typename value_type>
class MultiGrid<value_type, 1u>
{
public:
    MultiGrid() : size(0u), data(nullptr) {}

    MultiGrid(unsigned size) : size(size), data(new value_type[size]) {}

    MultiGrid(value_type value, unsigned size) : size(size), data(new value_type[size]) {
        for (unsigned i = 0; i < size; i++) {
            data[i] = value;
        }
    }

    ~MultiGrid();

    MultiGrid(MultiGrid<value_type, 1u> const & source);
    MultiGrid(MultiGrid<value_type, 1u> const && source);

    MultiGrid<value_type, 1u> &operator=(const MultiGrid<value_type, 1u> &);
    MultiGrid<value_type, 1u> &operator=(MultiGrid<value_type, 1u> &&) noexcept;
    MultiGrid<value_type, 1u> &operator=(const value_type &);
    MultiGrid<value_type, 1u> &operator=(const value_type &&);

    value_type operator()(unsigned) const;
    value_type &operator()(unsigned);

    value_type operator[](unsigned) const;
    value_type &operator[](unsigned);

    unsigned get_size() const { return size; }

private:
    unsigned size;
    value_type * data;
};

template <typename value_type, unsigned size_type>
MultiGrid<value_type, size_type>::~MultiGrid()
{
    delete[] grids;
}

template <typename value_type, unsigned size_type>
MultiGrid<value_type, size_type>::MultiGrid(MultiGrid<value_type, size_type> const &source)
    : size(source.get_size())
{
    grids = new MultiGrid<value_type, size_type-1u>[size];
    for (unsigned i = 0; i < size; i++)
    {
        grids[i] = source.grids[i];
    }
}

template <typename value_type, unsigned size_type>
MultiGrid<value_type, size_type>::MultiGrid(MultiGrid<value_type, size_type> const &&source)
    : size(source.get_size()),
      grids(std::move(source.grids)) {}

template <typename value_type, unsigned size_type>
MultiGrid<value_type, size_type> &MultiGrid<value_type, size_type>::operator=(const MultiGrid<value_type, size_type> &source)
{
    if (this != &source) {
        *this = MultiGrid<value_type, size_type>(source);
    }
    return *this;
}

template <typename value_type, unsigned size_type>
MultiGrid<value_type, size_type> &MultiGrid<value_type, size_type>::operator=(MultiGrid<value_type, size_type> &&source) noexcept
{
    std::swap(*this, source);
    return *this;
}

template <typename value_type, unsigned size_type>
MultiGrid<value_type, size_type> &MultiGrid<value_type, size_type>::operator=(value_type const &value)
{
    for (unsigned i = 0; i < size; i++)
    {
        grids[i] = value;
    }
    return *this;
}

template <typename value_type, unsigned size_type>
MultiGrid<value_type, size_type> &MultiGrid<value_type, size_type>::operator=(value_type const &&value)
{
    for (unsigned i = 0; i < size; i++)
    {
        grids[i] = value;
    }
    return *this;
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
MultiGrid<value_type, 1u>::MultiGrid(MultiGrid<value_type, 1u> const &&source) : size(source.size), data(std::move(source.data)) {}

template <typename value_type>
MultiGrid<value_type, 1u> &MultiGrid<value_type, 1u>::operator=(const MultiGrid<value_type, 1u> &source)
{
    size = source.size;
    for (unsigned i = 0u; i < size; i++)
    {
        data[i] = source.data[i];
    }
    return *this;
}

template <typename value_type>
MultiGrid<value_type, 1u> &MultiGrid<value_type, 1u>::operator=(MultiGrid<value_type, 1u> &&source) noexcept
{
    std::swap(*this, source);
    return *this;
}

template <typename value_type>
MultiGrid<value_type, 1u> &MultiGrid<value_type, 1u>::operator=(value_type const &value)
{
    for (unsigned i = 0; i < size; i++)
    {
        data[i] = value;
    }
    return *this;
}

template <typename value_type>
MultiGrid<value_type, 1u> & MultiGrid<value_type, 1u>::operator=(value_type const &&value)
{
    for (unsigned i = 0; i < size; i++)
    {
        data[i] = value;
    }
    return *this;
}

template <typename value_type>
value_type MultiGrid<value_type, 1u>::operator()(unsigned index) const
{
    return data[index];
}

template <typename value_type>
value_type & MultiGrid<value_type, 1u>::operator()(unsigned index)
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

template class MultiGrid<float, 2u>;
template class MultiGrid<float, 3u>;
template class MultiGrid<float, 4u>;
template class MultiGrid<float, 5u>;