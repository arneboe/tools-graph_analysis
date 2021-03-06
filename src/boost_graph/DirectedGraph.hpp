#ifndef GRAPH_ANALYSIS_BOOST_GRAPH_DIRECTED_GRAPH_HPP
#define GRAPH_ANALYSIS_BOOST_GRAPH_DIRECTED_GRAPH_HPP

#include "../Graph.hpp"
#include "../BaseGraph.hpp"
#include "../boost_graph/ArcIterator.hpp"
#include <boost/graph/adjacency_list.hpp>
#include <base-logging/Logging.hpp>

#include <boost/unordered_map.hpp>
#include <vector>
#include <iostream>

namespace graph_analysis {
/// not using boost namespace here to avoid collisions
namespace boost_graph {

//typedef boost::undirectedS GType;
//typedef boost::directedS GType;
typedef boost::bidirectionalS GType;

typedef boost::listS VRep;
typedef boost::vecS ERep;
// https://www.boost.org/doc/libs/1_60_0/libs/graph/doc/property.html
typedef boost::property< boost::vertex_index_t, std::size_t, Vertex::Ptr> VProp;
typedef boost::property< boost::edge_index_t, std::size_t, Edge::Ptr> EProp;

typedef boost::adjacency_list<VRep, ERep, boost::undirectedS, VProp, EProp> UndirectedGraph;
typedef boost::adjacency_list<VRep, ERep, GType, VProp, EProp> BidirectionalGraph;

typedef boost::graph_traits<BidirectionalGraph>::vertex_descriptor VertexDescriptor;
typedef boost::graph_traits<BidirectionalGraph>::vertex_iterator VertexIteratorImpl;
typedef boost::graph_traits<BidirectionalGraph>::vertices_size_type VertexIndex;
typedef std::pair<VertexIterator, VertexIterator> VertexRange;

typedef boost::graph_traits<BidirectionalGraph>::edge_descriptor EdgeDescriptor;
typedef boost::graph_traits<BidirectionalGraph>::edge_iterator EdgeIteratorImpl;
typedef std::pair<EdgeIterator, EdgeIterator> EdgeRange;

typedef boost::graph_traits<BidirectionalGraph>::adjacency_iterator AdjacencyIterator;
typedef std::pair<AdjacencyIterator, AdjacencyIterator> AdjacencyRange;

class DirectedGraph : public TypedGraph< BidirectionalGraph, graph_analysis::BaseGraph>
{
    friend class OutArcIterator<DirectedGraph>;
    friend class InArcIterator<DirectedGraph>;
public:
    DirectedGraph();
    virtual ~DirectedGraph();

    BaseGraph::Ptr copy() const;
    BaseGraph::Ptr newInstance() const;

    typedef shared_ptr<DirectedGraph> Ptr;
    typedef boost::unordered_map<GraphElementId, VertexDescriptor> VertexMap;
    typedef boost::unordered_map<GraphElementId, EdgeDescriptor> EdgeMap;

    Vertex::Ptr getVertex(GraphElementId id) const;
    Edge::Ptr getEdge(GraphElementId id) const;

    /**
     * Map wrapper type to internal vertex descriptor
     * \return vertex descriptor
     */
    VertexDescriptor getVertexDescriptor(const Vertex::Ptr& vertex) const;

    /**
     * Map wrapper type to internal edge descriptor
     * \return edge descriptor
     */
    EdgeDescriptor getEdgeDescriptor(const Edge::Ptr& edge) const;

    DirectedGraph(const DirectedGraph& other);

    void write(std::ostream& ostream = std::cout) const;

    /**
     * Get the vertex iterator for this implementation
     */
    VertexIterator::Ptr getVertexIterator() const;

    /**
     * Get the edge iterator for this implementation
     */
    EdgeIterator::Ptr getEdgeIterator() const;

    /**
     * Get EdgeIterator
     * \return Get Edge Iterator
     */
    EdgeIterator::Ptr getEdgeIterator(const Vertex::Ptr& vertex) const;

    /**
     * Get iterator of outgoing edges
     */
    graph_analysis::EdgeIterator::Ptr getOutEdgeIterator(const Vertex::Ptr& vertex) const;
    graph_analysis::EdgeIterator::Ptr getInEdgeIterator(const Vertex::Ptr& vertex) const;

    /**
     * Identifies the connected components
     */
    SubGraph::Ptr identifyConnectedComponents(const BaseGraph::Ptr& baseGraph) const;

    /**
     * Get the subgraph -- by default all vertices and edges of the
     * base graph are available (enabled)
     */
    SubGraph::Ptr createSubGraph(const BaseGraph::Ptr& baseGraph) const;

    /**
     * Get edges between two given vertices
     * \return List of edges from source to target
     * vertex
     */
    std::vector<Edge::Ptr> getEdges(VertexDescriptor source, VertexDescriptor target) const;

    std::vector<Edge::Ptr> getEdges(const Vertex::Ptr& source, const Vertex::Ptr& target) const;

protected:

    DirectedGraph::Ptr validateType(const BaseGraph::Ptr& baseGraph) const;

    /**
     * \brief Add a vertex
     * \return the id of the created vertex
     */
    virtual GraphElementId addVertexInternal(const Vertex::Ptr& vertex);

    /**
     * Remove a vertex from the internal graph representation
     */
    virtual void removeVertexInternal(const Vertex::Ptr&);

    /**
     * \brief Add an edge
     * \return the created edge
     */
    GraphElementId addEdgeInternal(const Edge::Ptr& edge, GraphElementId sourceVertexId, GraphElementId targetVertexId);

    /**
     * Remove an edge from the internal graph representation
     * \return Element id of this vertex within this graph
     */
    virtual void removeEdgeInternal(const Edge::Ptr&);

    // Property maps to store data associated with vertices and edges
    EdgeMap mEdgeMap;
    VertexMap mVertexMap;
    static std::map<GraphId, GraphElementId> msNewVertexId;
    static std::map<GraphId, GraphElementId> msNewEdgeId;
};

} // end namespace boost_graph
} // end namespace graph_analysis

#endif // GRAPH_ANALYSIS_BOOST_DIRECTED_GRAPH_HPP
