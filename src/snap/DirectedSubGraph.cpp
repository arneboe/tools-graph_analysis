#include "DirectedSubGraph.hpp"
#include "DirectedGraph.hpp"

namespace graph_analysis {
namespace snap {

DirectedSubGraph::DirectedSubGraph(const DirectedGraph::Ptr& graph)
    : SubGraph(graph)
{}

} // end namespace snap
} // end namespace graph_analysis
