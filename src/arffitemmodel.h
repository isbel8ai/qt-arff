#ifndef ARFFITEMMODEL_H
#define ARFFITEMMODEL_H

#include <QAbstractItemModel>

#include "arffattribute.h"

class ArffItemModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit ArffItemModel(QObject *parent = 0);
    explicit ArffItemModel(QAbstractItemModel * other, QObject *parent = 0);
    ~ArffItemModel();
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child = QModelIndex()) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    bool hasChildren(const QModelIndex &parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    void setRelationName(QString name);
    QString relationName();
    bool addAttribute(ArffAttribute attrib);
    void setAttribute(int column, ArffAttribute attrib);
    ArffAttribute getAttribute(int column);
    bool addInstance(QVariantList instance);
    QVariantList getInstance(int row);

private:
    QString relation;
    QList<ArffAttribute> attributes;
    QList<QVariantList> instances;

};

#endif // ARFFITEMMODEL_H
