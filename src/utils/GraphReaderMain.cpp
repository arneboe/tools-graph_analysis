#include <iostream>
#include "../VertexTypeManager.hpp"
#include "../GraphIO.hpp"

using namespace graph_analysis;

int main(int argc, char** argv)
{

    std::string filename;
    if(argc < 2)
    {
        std::cout << "usage: " << argv[0] << " <filename>" << std::endl;
        exit(EXIT_FAILURE);
    } else {
        filename = std::string(argv[1]);
    }

    BaseGraph::Ptr graph = BaseGraph::getInstance();
    io::GraphIO::read(filename, graph);

    VertexIterator::Ptr vertexIt = graph->getVertexIterator();
    while(vertexIt->next())
    {
        Vertex::Ptr vertex = vertexIt->current();
        std::cout << "Vertex: id: " << graph->getVertexId(vertex) << ", label: " << vertex->getLabel() <<
            ", class: " << vertex->getClassName() << std::endl;
    }

    exit(EXIT_SUCCESS);
}
