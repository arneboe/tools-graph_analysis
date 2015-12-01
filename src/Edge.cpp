#include "Edge.hpp"

namespace graph_analysis {

Edge::Edge(const std::string& label)
    : GraphElement(label)
{}

Edge::Edge(const Vertex::Ptr& source, const Vertex::Ptr& target, const std::string& label)
    : GraphElement(label)
    , mSourceVertex(source)
    , mTargetVertex(target)
{}

Edge::Ptr Edge::clone() const
{
    Edge::Ptr edge( getClone() );
    edge->disassociateFromAll();
    return edge;
}

std::string Edge::getClassName() const
{
    return "graph_analysis::Edge";
}

std::string Edge::toString() const
{
    std::stringstream ss;
    ss << (getLabel().empty() ? getClassName() : getLabel());
    return ss.str();
}

std::vector<Vertex::Ptr> Edge::getInvolvedVertices(const Edge::Ptr& e0, const Edge::Ptr& e1)
{
    std::vector<Vertex::Ptr> vertices;
    Vertex::Ptr e0_source = e0->getSourceVertex();
    Vertex::Ptr e0_target = e0->getTargetVertex();
    if(e0_source == e1->getSourceVertex() || e0_source == e1->getTargetVertex())
    {
        // skip e0_source
    } else {
        vertices.push_back(e0_source);
    }

    if(e0_target == e1->getSourceVertex() || e0_target == e1->getTargetVertex())
    {
        // skip e0_target
    } else {
        vertices.push_back(e0_target);
    }

    vertices.push_back(e1->getSourceVertex());
    vertices.push_back(e1->getTargetVertex());

    return vertices;
}

bool Edge::areMeeting(const Edge::Ptr& e0, const Edge::Ptr& e1)
{
    return getInvolvedVertices(e0, e1).size() < 4;
}

}
