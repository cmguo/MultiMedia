#include "textinputcontrol.h"

#include <core/resourceview.h>
#include <core/optiontoolbuttons.h>

#include <QBrush>
#include <QGraphicsTextItem>
#include <QFont>
#include <QObject>
#include <QGraphicsPolygonItem>
#include <QGraphicsSceneMouseEvent>
#include <QMimeData>
#include <QUrl>
#include <QTextDocument>

static char const * toolstr =
        "color|颜色|Popup,OptionsGroup,NeedUpdate|;"
        ;

static ColorToolButtons colorButtons({Qt::white, Qt::black, Qt::red, Qt::green, Qt::blue, Qt::yellow});
REGISTER_OPTION_BUTTONS(TextInputControl, color, colorButtons)

TextInputControl::TextInputControl(ResourceView *res, Control::Flags flags, Control::Flags clearFlags) :
    Control(res, flags, clearFlags)
{
}

QColor TextInputControl::color() const
{
    QGraphicsTextItem *item = qgraphicsitem_cast<QGraphicsTextItem *>(item_);
    return item->defaultTextColor();
}

void TextInputControl::setColor(QColor color)
{
    QGraphicsTextItem *item = qgraphicsitem_cast<QGraphicsTextItem *>(item_);
    item->setDefaultTextColor(color);
}

QString TextInputControl::content() const
{
    QGraphicsTextItem *item = qgraphicsitem_cast<QGraphicsTextItem *>(item_);
    return item->toPlainText();
}

void TextInputControl::setContent(QString content)
{
    QGraphicsTextItem *item = qgraphicsitem_cast<QGraphicsTextItem *>(item_);
    item->setPlainText(content);
}

class DiagramTextItem : public QGraphicsTextItem
{
public:
    DiagramTextItem(QGraphicsItem *parent = nullptr);

protected:
    void focusOutEvent(QFocusEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

ControlView *TextInputControl::create(ControlView *)
{
    DiagramTextItem* item = new DiagramTextItem;
    connect(item->document(), &QTextDocument::contentsChanged, this, &TextInputControl::sizeChanged);
    return item;
}

void TextInputControl::attached()
{
    if (content().isEmpty())
        setContent(res_->url().path());
    loadFinished(true);
}

void TextInputControl::copy(QMimeData &data)
{
    Control::copy(data);
    data.setText(content());
}

QString TextInputControl::toolsString(const QByteArray &parent) const
{
    if (parent.isEmpty()) {
        return toolstr;
    }
    return nullptr;
}

//! [0]
DiagramTextItem::DiagramTextItem(QGraphicsItem *parent)
    : QGraphicsTextItem(parent)
{
    setFlag(QGraphicsItem::ItemAcceptsInputMethod);
    setFont(QFont("微软雅黑",12));
    setDefaultTextColor(Qt::white);
}

void DiagramTextItem::focusOutEvent(QFocusEvent *event)
{
    setTextInteractionFlags(Qt::NoTextInteraction);
    QGraphicsTextItem::focusOutEvent(event);
}

void DiagramTextItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    TextInputControl * control = qobject_cast<TextInputControl*>(Control::fromItem(this));
    if (control->flags().testFlag(Control::Selected)) {
        setTextInteractionFlags(Qt::TextEditorInteraction);
        setFocus();
    }
    QGraphicsTextItem::mousePressEvent(event);
}
