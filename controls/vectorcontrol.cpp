#include "vectorcontrol.h"

#include <QGraphicsSvgItem>
#include <QSvgRenderer>

VectorControl::VectorControl(ResourceView * res)
    : Control(res, {KeepAspectRatio, FullSelect, FixedOnCanvas})
{
}

ControlView *VectorControl::create(ControlView *parent)
{
    (void)parent;
#ifdef SHOWBOARD_QUICK
    return nullptr;
#else
    QGraphicsSvgItem * item = new QGraphicsSvgItem;
    return item;
#endif
}

void VectorControl::attached()
{
    loadData();
}

void VectorControl::onData(QByteArray data)
{
#ifdef SHOWBOARD_QUICK
#else
    QGraphicsSvgItem * item = static_cast<QGraphicsSvgItem*>(item_);
    QSvgRenderer * renderer = new QSvgRenderer(this);
    renderer->load(data);
    item->setSharedRenderer(renderer);
    if (renderer->animated()) {
        QObject::connect(renderer, &QSvgRenderer::repaintNeeded, item, [item]() {
            item->update();
        });
    }
#endif
}
