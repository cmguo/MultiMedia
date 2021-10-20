#ifndef GRAPHVIZCONTROL_H
#define GRAPHVIZCONTROL_H

#include "imagecontrol.h"

#include <core/control.h>

class GraphvizControl : public ImageControl
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit GraphvizControl(ResourceView * res);

private:
    void attached() override;

    void onData(QByteArray data) override;
};

#endif // GRAPHVIZCONTROL_H
