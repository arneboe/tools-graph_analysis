#ifndef GRAPH_ANALYSIS_GRAPH_HPP
#define GRAPH_ANALYSIS_GRAPH_HPP

#include <graph_analysis/EdgeProperty.hpp>
#include <graph_analysis/VertexProperty.hpp>
#include <graph_analysis/Filter.hpp>

/**
 * The main namespace of this library
 */
namespace graph_analysis
{

/**
 * \brief General Graph template that should be implemented to wrap specific graph library
 * functionality
 * \tparam GraphType The underlying graph type of the wrapped library
 * \tparam VertexType The underlying vertex type of the wrapped library
 * \tparam EdgeType The underlying edge type of the wrapped library
 *
 */
template<typename GraphType, typename VertexType, typename EdgeType>
class BaseGraph
{
public:
    /**
     * \brief Default deconstructor
     */
    virtual ~BaseGraph() {}

    typedef VertexType Vertex;
    typedef EdgeType Edge;

    typedef BaseGraph<GraphType,VertexType,EdgeType> BaseGraphType;
    typedef GraphType RawGraphType;

    /**
     * Type definitions that allow adding task properties
     */
    typedef graph_analysis::EdgeProperty<BaseGraphType, EdgeType> EdgePropertyType;
    typedef graph_analysis::VertexProperty<BaseGraphType, VertexType> VertexPropertyType;

    typedef typename EdgePropertyType::Ptr EdgePropertyTypePtr;
    typedef typename VertexPropertyType::Ptr VertexPropertyTypePtr;

    /**
     * \brief Add a vertex
     * \return the created vertex
     */
    virtual Vertex addVertex() = 0;

    /**
     * \brief Assign a vertex property
     */
    virtual void assignVertexProperty(const Vertex& v, VertexPropertyTypePtr property) = 0;

    /**
     * \brief Add an edge
     * \return the created edge
     */
    virtual Edge addEdge(const Vertex& u, const Vertex& v) = 0;

    /**
     * \brief Assign an edge property
     */
    virtual void assignEdgeProperty(const Edge& e, EdgePropertyTypePtr property) = 0;

    /**
     * \brief Get the source vertex for this edge
     * \return Pointer to the vertex data
     */
    virtual VertexPropertyTypePtr getSourceVertex(const Edge& e) const = 0;

    /**
     * \brief Get the target vertex for this edge
     * \return Pointer to the vertex data
     */
    virtual VertexPropertyTypePtr getTargetVertex(const Edge& e) const = 0;

    /**
     * \brief Get access to the underlying graph
     * \return the underlying graph instance
     */
    GraphType& raw() { return mGraph; }

protected:
    // The underlying graph instance
    GraphType mGraph;
};

}
#endif // GRAPH_ANALYSIS_GRAPH_HPP
