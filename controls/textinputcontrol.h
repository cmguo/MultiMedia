#ifndef TextInputControl_H
#define TextInputControl_H

#include "core/control.h"

#include <QGraphicsTextItem>

class TextInputControl : public Control
{
    Q_OBJECT

    Q_PROPERTY(QString content WRITE setContent READ content)
    Q_PROPERTY(QColor color WRITE setColor READ color)

public:
    Q_INVOKABLE TextInputControl(ResourceView *res, Flags flags = None, Flags clearFlags = None);

    QColor color() const;

    void setColor(QColor color);

    QString content() const;

    void setContent(QString content);

protected:
    virtual QString toolsString(QByteArray const & parent) const override;

    virtual ControlView * create(ControlView * parent) override;

    virtual void attached() override;

    virtual void copy(QMimeData &data) override;
};

#endif // TextInputControl_H
