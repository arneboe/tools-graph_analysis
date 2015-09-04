#ifndef GRAPH_ANALYSIS_GUI_ITEMS_FEATURE_HPP
#define GRAPH_ANALYSIS_GUI_ITEMS_FEATURE_HPP

#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsTextItem>
#include <QTextCursor>
#include <QMouseEvent>
#include <QMimeData>
#include <QDrag>

#include <graph_analysis/Vertex.hpp>
#include <graph_analysis/PortVertex.hpp>
#include <iostream>

namespace graph_analysis {
namespace gui {

class NodeItem;
class GraphWidget;

namespace items {

/**
 * \file Feature.hpp
 * \class Feature
 * \brief A feature can be added to a node item, however it directly maps to a
 * vertex in a graph
 * \details specific to the diagram editor widget: editable text representation (disregards the ENTER key)
 */
class Feature : public QGraphicsTextItem
{
private:
    // managing graph widget
    GraphWidget* mpGraphWidget;
    // Associated grapelement
    GraphElement::Ptr mpGraphElement;

public:
    /**
     * \brief constructor
     * \param label text to be displayed
     * \param item parent NodeItem implementing instance
     * \param graphWidget managing widget
     */
    Feature(const std::string& label, QGraphicsItem* item, GraphWidget *graphWidget = 0, GraphElement::Ptr element);

    /**
     * \brief toggles direct editing options of the displayed text
     * \param on boolean flag - true when the editing mode is to be turned on; false otherwise
     * \param selectAll boolean flag - true when in editing mode the whole text shall be initially automatically selected; false otherwise
     */
    void setTextInteraction(bool on, bool selectAll = false);

    /// getter method: retrieves the assigned ID
    GraphElement::Ptr getGraphElement() { return mpGraphElement; }

protected:
    /// qt mouse double-click callback
    void mouseDoubleClickEvent(::QGraphicsSceneMouseEvent* event);
    /// qt key pressing callback
    void keyPressEvent(::QKeyEvent* event);
    /// qt mouse move callback
    void mouseMoveEvent(::QGraphicsSceneMouseEvent *event);
//    /// qt mouse press callback
//    void mousePressEvent(::QGraphicsSceneMouseEvent *event);
    /// qt mouse drag start callback
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    /// qt mouse drag move callback
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    /// qt dropping callback
    void dropEvent(QGraphicsSceneDragDropEvent *event);
    /// qt item changed callback
    QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant& value);
};

} // end namespace items
} // end namespace gui
} // end namespace graph_analysis
#endif // GRAPH_ANALYSIS_GUI_ITEMS_LABEL_HPP
