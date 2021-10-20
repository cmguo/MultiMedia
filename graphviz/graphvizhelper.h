#ifndef GRAPHVIZHELPER_H
#define GRAPHVIZHELPER_H

#include <QByteArray>
#include <QImage>


class GraphvizHelper
{
public:
    static QImage load(QByteArray const & data);
};

#endif // GRAPHVIZHELPER_H
