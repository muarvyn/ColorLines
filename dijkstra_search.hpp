#ifndef DIJKSTRA_SEARCH_HPP
#define DIJKSTRA_SEARCH_HPP

#include <boost/graph/properties.hpp>
#include <grid2d_graph.hpp>
#include "basic_defs.hpp"

class DijkstraSearch
{
public:
    typedef g2dg::grid2d_graph<int, int, BoardDim::ROWS_NUM, BoardDim::COLUMNS_NUM>
        board_graph;
    typedef double weight_type;

    DijkstraSearch(board_graph::vertex_descriptor start,
        weight_type weight_map[BoardDim::ROWS_NUM*BoardDim::COLUMNS_NUM]);

    weight_type getDistance(int r, int c);
    std::pair<int,int> getPredecessor(int r, int c);

    inline
    const std::vector<board_graph::vertex_descriptor> & getPred()
    { return pred; }

    inline
    const std::vector<g2dg::edge_weight_map_traits<board_graph>::value_type>  getDist()
    { return dist; }

private:
    board_graph g;
    std::vector<board_graph::vertex_descriptor> pred;
    std::vector<g2dg::edge_weight_map_traits<board_graph>::value_type> dist;
    boost::property_map<board_graph, boost::vertex_index_t>::type indexmap;
};


#endif // DIJKSTRA_SEARCH_HPP
