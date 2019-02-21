#include "arffcreator.h"

void ArffCreator::create(ArffItemModel *model, QString filepath)
{
    QFile arffile(filepath);

    if (!arffile.open(QIODevice::Truncate | QIODevice::WriteOnly)) {
        throw;
    }

    // comment
    arffile.write("% relation name ");
    arffile.write(model->relationName().toUtf8());
    arffile.write("\n");

    // relation
    arffile.write("@relation ");
    arffile.write(model->relationName().toUtf8());
    arffile.write("\n");

    // attributes
    for (int a = 0; a < model->columnCount(); ++a) {
        ArffAttribute att = model->getAttribute(a);
        arffile.write("@attribute ");
        arffile.write(att.name().toUtf8());
        arffile.write(" ");

        switch (att.type()) {
        case ArffAttribute::NOMINAL: {
            QStringList noms = att.getNominals();
            arffile.write("{");
            for (int v = 0; v < noms.size(); ++v) {
                arffile.write(noms[v].toUtf8());
                if (v < noms.size() - 1) {
                    arffile.write(",");
                }
            }
            arffile.write("}");
            break;
        }
        case ArffAttribute::NUMERIC:
            arffile.write("numeric");
            break;
        case ArffAttribute::DATE:
            arffile.write("date");
            break;
        default:
            arffile.write("string");
            break;
        }
        arffile.write("\n");
    }

    // data
    arffile.write("@data\n");

    // instances
    for (int i = 0; i < model->rowCount(); i++) {
        for (int j = 0; j < model->columnCount(); ++j) {
            arffile.write(model->index(i, j).data().toByteArray());
            if (j < model->columnCount() - 1) {
                arffile.write(",");
            }
        }
        arffile.write("\n");
    }

    arffile.close();
}
