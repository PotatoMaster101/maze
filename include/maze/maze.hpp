////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Simple maze generator written in C++17.
// https://github.com/PotatoMaster101/maze
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef MAZE_HPP
#define MAZE_HPP
#include <random>
#include <vector>
#include <set>
#include <utility>      // std::pair
#include <iterator>     // std::distance, std::advance
#include <cstddef>      // std::size_t
#include <cstdint>      // std::uint8_t

// Maze generator.
class maze {
public:
    // Member types.
    using size_type = std::size_t;
    using index_t = std::pair<size_type, size_type>;    // [y, x]
    using conn_t = std::pair<index_t, index_t>;

    // Constructors.
    maze(size_type row = 5, size_type col = 5)
        : rows_{row}, cols_{col}, maze_(row, std::vector<std::uint8_t>(col, 0)) {}

    // Getters.
    size_type rows() const noexcept { return rows_; }
    size_type cols() const noexcept { return cols_; }
    unsigned int seed() const noexcept { return seed_; }

    // Generates the maze.
    std::vector<conn_t> generate(const index_t& start = {0, 0});

private:
    size_type rows_;                                    // number of rows
    size_type cols_;                                    // number of columns
    std::vector<std::vector<std::uint8_t>> maze_;       // used for maze generation
    unsigned int seed_ = std::random_device{}();        // seed for rand engine

    // Determines whether the given index has up, down, left or right neighbours.
    bool upper(const index_t& i) const noexcept { return (i.first > 0); }
    bool lower(const index_t& i) const noexcept { return (i.first < rows_ - 1); }
    bool left(const index_t& i) const noexcept { return (i.second > 0); }
    bool right(const index_t& i) const noexcept { return (i.second < cols_ - 1); }

    // Determines whether the specified index has been visited.
    bool visited(const index_t& i) const noexcept { return maze_[i.first][i.second] != 0; }

    // Visits the specified index.
    void visit(const index_t& i) noexcept { maze_[i.first][i.second] = 1; }

    // Returns a set containing visited neighbours of the given index.
    std::set<index_t> visited_neighbours(const index_t& i) const;

    // Returns a set containing unvisited neighbours of the given index.
    std::set<index_t> unvisited_neighbours(const index_t& i) const;

    // Returns a random index from the given set of indexes. Removes the index once selected.
    index_t rand_index(std::set<index_t>& s) const;
};

// Returns a random iterator in the given iterator range.
template <class Iter, class Reng = std::mt19937>
Iter rand_iter(Iter begin, Iter end, unsigned int seed) {
    using diff_t = typename std::iterator_traits<Iter>::difference_type;
    Reng eng{seed};
    auto dist = std::distance(begin, end) - 1;
    std::uniform_int_distribution<diff_t> dis{0, (dist < 0 ? 0 : dist)};
    std::advance(begin, dis(eng));
    return begin;
}

#endif  // MAZE_HPP
