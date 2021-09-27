#include "mediaplayerbridge.h"

#include <qlazy.h>
#include <qcomponentcontainer.h>

#include <showboard.h>

#include <QMap>

MediaPlayerBridge::MediaPlayerBridge(QObject *parent)
    : QObject(parent)
{
}

MediaPlayerBridge *MediaPlayerBridge::get(const QByteArray & type)
{
    static QVector<QLazy> types;
    static QMap<QByteArray, QLazy*> playerTypes;
    if (playerTypes.empty()) {
         types = ShowBoard::containter().getExports<MediaPlayerBridge>(QPart::shared);
         for (auto & r : types) {
             QByteArray types = r.part()->attrMineType();
             for (auto & t : types.split(',')) {
                 playerTypes[t.trimmed()] = &r;
             }
         }
    }
    auto iter = playerTypes.find(type);
    if (iter == playerTypes.end())
        return nullptr;
    return iter.value()->get<MediaPlayerBridge>();
}
