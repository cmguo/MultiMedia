#ifndef MULTIMEDIAPLUGIN_H
#define MULTIMEDIAPLUGIN_H

#include <qcomponentfactoryinterface.h>

#include <QGenericPlugin>

class MultiMediaPlugin : public QGenericPlugin
        , public QComponentFactoryInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID ComponentFactory_iid FILE "MultiMedia.json")
    Q_INTERFACES(QComponentFactoryInterface)

public:
    explicit MultiMediaPlugin(QObject *parent = nullptr);

private:
    QObject *create(const QString &name, const QString &spec) override;
};

#endif // MULTIMEDIAPLUGIN_H
