////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Simple maze generator written in C++17.
//
// Author: PotatoMaster101
// Date:   30/05/2020
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>        // std::merge
#include <iterator>         // std::inserter
#include "maze/maze.hpp"

// Generates the maze.
std::vector<maze::conn_t> maze::generate(const index_t& start) {
    std::vector<maze::conn_t> ret;
    std::set<index_t> untouched{start};

    while (!untouched.empty()) {
        auto current = rand_index(untouched);
        auto nei = visited_neighbours(current);
        if (!(nei.empty())) {       // connect with random visited neighbour
            auto rand_neigh = rand_index(nei);
            ret.emplace_back(rand_neigh, current);
            visit(rand_neigh);
        }

        visit(current);
        nei = unvisited_neighbours(current);
        if (!(nei.empty())) {       // add unvisited for the next iteration
            std::merge(untouched.begin(), untouched.end(), nei.begin(), nei.end(),
                        std::inserter(untouched, untouched.begin()));
        }
    }
    return ret;
}

// Returns a set containing visited neighbours of the given index.
std::set<maze::index_t> maze::visited_neighbours(const maze::index_t& i) const {
    std::set<index_t> ret;
    if (upper(i) && visited({i.first - 1, i.second}))
        ret.emplace(i.first - 1, i.second);
    if (lower(i) && visited({i.first + 1, i.second}))
        ret.emplace(i.first + 1, i.second);
    if (left(i) && visited({i.first, i.second - 1}))
        ret.emplace(i.first, i.second - 1);
    if (right(i) && visited({i.first, i.second + 1}))
        ret.emplace(i.first, i.second + 1);
    return ret;
}

// Returns a set containing unvisited neighbours of the given index.
std::set<maze::index_t> maze::unvisited_neighbours(const maze::index_t& i) const {
    std::set<index_t> ret;
    if (upper(i) && !visited({i.first - 1, i.second}))
        ret.emplace(i.first - 1, i.second);
    if (lower(i) && !visited({i.first + 1, i.second}))
        ret.emplace(i.first + 1, i.second);
    if (left(i) && !visited({i.first, i.second - 1}))
        ret.emplace(i.first, i.second - 1);
    if (right(i) && !visited({i.first, i.second + 1}))
        ret.emplace(i.first, i.second + 1);
    return ret;
}

// Returns a random index from the given set of indexes. Removes the index once selected.
maze::index_t maze::rand_index(std::set<maze::index_t>& s) const {
    auto iter = rand_iter(s.begin(), s.end(), seed_);
    auto idx = *iter;
    s.erase(iter);
    return idx;
}
