#ifndef ARFFATTRIBUTE_H
#define ARFFATTRIBUTE_H

#include <QStringList>

/**
 * @class ArffAttr arff_attr.h
 * @brief Class to represent an ARFF attribute
 */
class ArffAttribute
{
public:
    /**
     * @enum ArffAttributeType
     * @brief Attributes in the ARFF file
     */
    enum ArffAttributeType {
        /** unknown attributes */
        UNKNOWN = 0,
        /** numeric attributes */
        NUMERIC = 1,
        /** string attributes */
        STRING = 2,
        /** date attributes */
        DATE = 3,
        /** nominal attributes */
        NOMINAL = 4,
    };

    /**
     * @brief Constructor
     * @param name name of this attribute
     * @param type attribute type
     */
    ArffAttribute(QString name, ArffAttributeType type);

    /**
     * @brief Name of this attribute
     * @return name
     */
    QString name() const;

    /**
     * @brief Type of this attribute
     * @return type
     */
    ArffAttributeType type() const;

    /**
     * @brief add nominal value to this attribute
     */
    void addNominal(QString nominal);

    /**
     * @brief get nominal value list for this attribute
     */
    QStringList getNominals();

private:
    /** attribute name */
    QString attname;
    /** attribute type */
    ArffAttributeType  atttype;
    /** nominal values */
    QStringList nominals;
};

#endif // ARFFATTRIBUTE_H
