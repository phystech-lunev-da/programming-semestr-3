
#pragma once

#include <cstdlib>
#include <utility>

template <typename T>
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
    Grid(size_type, size_type, T const &);
    Grid(T const &);

    ~Grid();

    Grid(Grid const &source);
    Grid(Grid &&source) noexcept;

    Grid &operator=(Grid &);
    Grid &operator=(Grid &&) noexcept;
    Grid &operator=(T const &t);

    T operator()(size_type, size_type) const;
    T &operator()(size_type, size_type);

    ProxyGrid operator[](size_type) const;

    size_type get_y_size() const { return y_size; }
    size_type get_x_size() const { return x_size; }

private:
    size_type y_size, x_size;
    T * data;
};