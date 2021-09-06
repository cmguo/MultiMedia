#include "multimediaplugin.h"
#include "resources/resources.h"
#include "controls/controls.h"

MultiMediaPlugin::MultiMediaPlugin(QObject *parent)
    : QGenericPlugin(parent)
{
}

QObject *MultiMediaPlugin::create(const QString &, const QString &)
{
    return nullptr;
}
