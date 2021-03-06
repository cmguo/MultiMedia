#include "strokecontrol.h"

#include "opengl/glstrokewidget.h"

#include "resources/strokes.h"

#include <QGraphicsProxyWidget>

StrokeControl::StrokeControl(ResourceView * res)
    : WidgetControl(res, FullLayout, DefaultFlags)
{
}

QWidget *StrokeControl::createWidget(ControlView *parent)
{
    (void) parent;
    QWidget * widget = new GLStrokeWidget();
    widget->resize(720, 405);
    widget->setAttribute(Qt::WA_NoSystemBackground);
    //widget->setAttribute(Qt::WA_AlwaysStackOnTop);
    return widget;
}
