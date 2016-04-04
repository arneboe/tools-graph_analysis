#ifndef GRAPH_ANALYSIS_TASK_GRAPH_TASK_TEMPLATE_HPP
#define GRAPH_ANALYSIS_TASK_GRAPH_TASK_TEMPLATE_HPP

#include <graph_analysis/Graph.hpp>

namespace graph_analysis
{
namespace task_graph
{
    class Task;

    class TaskTemplate
    {
        public:
            /**
             * The default constructor needs a filename to import a base graph model
             */
            TaskTemplate(const std::string &yamlFileName);

            ~TaskTemplate() {
                // Intentionally reset the shared ptr
                mpBaseGraph.reset();
            }

            /**
             * If called, a new instance of the stored BaseGraph is created.
             */
            BaseGraph::Ptr instantiateTask();

            /**
             * If called, creates a new instance and adds it to the given graph argument
             */
            void instantiateAndAddTask(BaseGraph::Ptr graph);

        private:
            std::string     mYamlFileName;
            BaseGraph::Ptr  mpBaseGraph;
    };

}
}
#endif
