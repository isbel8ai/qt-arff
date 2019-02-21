#include <QDebug>

#include "arffparser.h"
#include "arffcreator.h"

int main()
{
    ArffParser parser("../data/iris.arff");
    ArffItemModel * dataset = parser.parse();

    for (int i = 0; i < dataset->columnCount(); ++i) {
        qDebug() << dataset->getAttribute(i).name();
    }

    for (int i = 0; i < dataset->rowCount(); ++i) {
        QString line;
        for (int j = 0; j < dataset->columnCount(); ++j) {
             line += dataset->getInstance(i)[j].toString() + "\t";
        }
        qDebug() << line;
    }

    ArffCreator::create(dataset, "../data/created.arff");

    delete dataset;

    return 0;
}
