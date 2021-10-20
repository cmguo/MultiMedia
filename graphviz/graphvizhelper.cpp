#include "graphvizhelper.h"

#ifdef HAS_GRAPHVIZ
#include <graphviz/gvc.h>
#endif

// https://graphviz.org/pdf/libguide.pdf

QImage GraphvizHelper::load(const QByteArray &data)
{
#ifdef HAS_GRAPHVIZ
    GVC_t* gvc = gvContext();
    Agraph_t * g = agmemread(data);
    if (g == nullptr) {
        return QImage();
    }
    gvLayout(gvc, g, "dot");
    gvRenderFilename(gvc, g, "png", "graphvizhelper.png");
    gvFreeLayout(gvc, g);
    agclose(g);
    gvFreeContext(gvc);
    return QImage("graphvizhelper.png");
#else
    return QImage();
#endif
}
