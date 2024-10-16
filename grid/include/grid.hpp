
template <typename T>
class Grid final
{
public:
    using value_type = T;
    using size_type = unsigned;

    Grid(size_type, size_type);
    ~Grid();
    
    Grid(Grid const &source);
    Grid(Grid &&source);

    Grid &operator=(Grid &);
    Grid &operator=(Grid &&);
    Grid& operator=(T const &t);

    T operator()(size_type, size_type) const;
    T& operator()(size_type, size_type);
private:
    size_type const y_size, x_size;
    T *const data;
    
    size_type get_y_size() const { return y_size; }
    size_type get_x_size() const { return x_size; }
};