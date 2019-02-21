#include "arffitemmodel.h"

ArffItemModel::ArffItemModel(QObject *parent) :
    QAbstractItemModel(parent)
{
}

ArffItemModel::ArffItemModel(QAbstractItemModel *other, QObject *parent) :
    QAbstractItemModel(parent)
{
    int cols = other->columnCount();

    if (cols > 0) {
        for (int i = 0; i < other->rowCount(); ++i) {
            QVariantList inst;
            for (int j = 0; j < cols; ++j) {
                inst.append(other->index(i, j).data());
            }
            instances.append(inst);
        }
    }

    for (int i = 0; i < cols; ++i) {
        QString atname = other->headerData(i, Qt::Horizontal).toString();
        QVariant::Type qvtype = other->index(0, i).data().type();
        ArffAttribute::ArffAttributeType attype;

        switch (qvtype) {
        case QVariant::Bool:
        case QVariant::Int:
        case QVariant::UInt:
        case QVariant::LongLong:
        case QVariant::ULongLong:
        case QVariant::Double:
            attype = ArffAttribute::NUMERIC;
            break;
        case QVariant::Char:
        case QVariant::String:
            attype = ArffAttribute::STRING;
            break;
        case QVariant::Date:
        case QVariant::DateTime:
            attype = ArffAttribute::DATE;
            break;
        default:
            attype = ArffAttribute::UNKNOWN;
            break;
        }

        attributes.append(ArffAttribute(atname, attype));
    }
}

ArffItemModel::~ArffItemModel()
{
    instances.clear();
    attributes.clear();
}

QModelIndex ArffItemModel::index(int row, int column, const QModelIndex &parent) const
{
    return createIndex(row, column);
}

QModelIndex ArffItemModel::parent(const QModelIndex &child) const
{
    return QModelIndex();
}

int ArffItemModel::rowCount(const QModelIndex &parent) const
{
    return instances.size();
}

int ArffItemModel::columnCount(const QModelIndex &parent) const
{
    return attributes.size();
}

bool ArffItemModel::hasChildren(const QModelIndex &parent) const
{
    return false;
}

QVariant ArffItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Vertical) {
        return section;
    }
    return attributes[section].name();
}

QVariant ArffItemModel::data(const QModelIndex &index, int role) const
{
    return instances[index.row()][index.column()];
}

QString ArffItemModel::relationName()
{
    return relation;
}

void ArffItemModel::setRelationName(QString name)
{
    relation = name;
}

bool ArffItemModel::addAttribute(ArffAttribute attrib)
{
    if (instances.isEmpty()) {
        setHeaderData(columnCount(), Qt::Horizontal, attrib.name());
        attributes.append(attrib);
        return true;
    }
    return false;
}

void ArffItemModel::setAttribute(int column, ArffAttribute attrib)
{
    setHeaderData(column, Qt::Horizontal, attrib.name());
    attributes.replace(column, attrib);
}

ArffAttribute ArffItemModel::getAttribute(int column)
{
    return attributes[column];
}

bool ArffItemModel::addInstance(QVariantList instance)
{
    if (!attributes.isEmpty()) {
        instances.append(instance);
        return true;
    }
    return  false;
}

QVariantList ArffItemModel::getInstance(int row)
{
    return instances[row];
}
