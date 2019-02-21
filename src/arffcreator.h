#ifndef ARFFCREATOR_H
#define ARFFCREATOR_H

#include <QFile>

#include "arffitemmodel.h"

class ArffCreator
{
private:
    /** Constructor */
    ArffCreator();

public:
    /** create new arff */
    static void create(ArffItemModel * model, QString filepath);
};

#endif // ARFFCREATOR_H
