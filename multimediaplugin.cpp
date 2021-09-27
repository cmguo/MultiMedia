#include "multimediaplugin.h"
#include "resources/resources.h"
#include "controls/controls.h"
#include "video/exports.h"

MultiMediaPlugin::MultiMediaPlugin(QObject *parent)
    : QGenericPlugin(parent)
{
}

QObject *MultiMediaPlugin::create(const QString &, const QString &)
{
    return nullptr;
}
