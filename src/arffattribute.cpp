#include "arffattribute.h"

ArffAttribute::ArffAttribute(QString name, ArffAttributeType type):
        attname(name), atttype(type)
{
}

QString ArffAttribute::name() const
{
    return attname;
}

ArffAttribute::ArffAttributeType ArffAttribute::type() const
{
    return atttype;
}

void ArffAttribute::addNominal(QString nominal)
{
    nominals.append(nominal);
}

QStringList ArffAttribute::getNominals()
{
    return nominals;
}
