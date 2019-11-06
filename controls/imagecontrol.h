#ifndef IMAGECONTROL_H
#define IMAGECONTROL_H

#include "core/control.h"

class ImageControl : public Control
{
    Q_OBJECT
public:
    Q_INVOKABLE ImageControl(ResourceView *res);

protected:
    virtual QGraphicsItem * create(ResourceView * res);

    virtual void attached() override;
};

#endif // IMAGECONTROL_H
