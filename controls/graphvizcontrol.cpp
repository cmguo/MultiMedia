#include "graphvizcontrol.h"

#include <core/resourceview.h>
#include <core/resource.h>

#include <graphviz/graphvizhelper.h>

#include <QPixmap>

GraphvizControl::GraphvizControl(ResourceView *res)
    : ImageControl(res)
{
}

void GraphvizControl::attached()
{
    auto l = life();
    res_->resource()->getData().then([this, l] (QByteArray data) {
        if (l.isNull()) return;
        onData(data);
    }, [this, l](std::exception &) {
        if (l.isNull()) return;
        loadFailed();
    });
}

void GraphvizControl::onData(QByteArray data)
{
    QImage image = GraphvizHelper::load(data);
    setPixmap(QPixmap::fromImage(image));
}
