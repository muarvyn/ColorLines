#include <iostream>
#include <utility>
#include <boost/graph/properties.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include "dijkstra_search.hpp"

using namespace boost;

DijkstraSearch::DijkstraSearch(board_graph::vertex_descriptor start,
    weight_type weight_map[BoardDim::ROWS_NUM*BoardDim::COLUMNS_NUM])
    :indexmap(get(vertex_index, g))
{
    g2dg::edge_weight_map<board_graph> wmap(&weight_map[0],&weight_map[BoardDim::ROWS_NUM*BoardDim::COLUMNS_NUM]);
    pred.resize(num_vertices(g));
    dist.resize(num_vertices(g));
    iterator_property_map<std::vector<board_graph::vertex_descriptor>::iterator,
                          property_map<board_graph, vertex_index_t>::const_type>
        pred_pm(pred.begin(), get(vertex_index, g));
    iterator_property_map<std::vector<
        g2dg::edge_weight_map_traits<board_graph>::value_type>::iterator,
        property_map<board_graph, vertex_index_t>::const_type>
        dist_pm(dist.begin(), get(vertex_index, g));

    dijkstra_shortest_paths(g, start,
                            predecessor_map(pred_pm).
                            distance_map(dist_pm).
                            weight_map(wmap) );
/*
    property_map<board_graph, vertex_index_t>::type indexmap = get(vertex_index, g);
    std::cout << "Dijkstra search from vertex " << start << std::endl;
    typedef std::pair< g2dg::g2dg_vertex_iterator<int,int,BoardDim::ROWS_NUM,BoardDim::COLUMNS_NUM>,
      g2dg::g2dg_vertex_iterator<int,int,BoardDim::ROWS_NUM,BoardDim::COLUMNS_NUM> >
      vertex_range;
    vertex_range range = g2dg::vertices<board_graph>(g);
    board_graph::vertex_iterator vi=range.first, vi_end=range.second;
    for (boost::tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi) {
      board_graph::vertex_descriptor u = *vi;
      std::cout << "Vertex " << u << ": "
                << "parent "<< pred[indexmap[u]] << ", "
                << "distance " << dist[indexmap[u]]
                << std::endl;
    }
*/
}

std::pair<int,int> DijkstraSearch::getPredecessor(int r, int c)
{
    board_graph::vertex_descriptor p =
        pred[indexmap[board_graph::vertex_descriptor(r,c)]];
    return std::make_pair(p.first, p.second);
}

double DijkstraSearch::getDistance(int r, int c)
{
    return dist[indexmap[board_graph::vertex_descriptor(r,c)]];
}

