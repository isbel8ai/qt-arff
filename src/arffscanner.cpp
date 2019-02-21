#include <QFile>

#include "arffscanner.h"

ArffScanner::ArffScanner(QString filepath) :
     line(0), column(0), previous(0), character(0)
{
    source = new QFile(filepath);
    if (!source->open(QIODevice::ReadOnly)) {
        throw source->errorString();
    }
}

ArffScanner::~ArffScanner()
{
    source->close();
    delete source;
}

char ArffScanner::next()
{
    if (source->atEnd()) {
        character = -1;
        return -1;
    }

    if (isNewLine(character)) {
        ++line;
        column = 0;
    }

    ++column;
    previous = character;
    if(!source->getChar(&character)) {
        character = -1;  // you would have reached end-of-file?
    }

    if ((previous == '\n' && character == '\r') || (previous == '\r' && character == '\n')) {

    }

    return character;
}

char ArffScanner::current() const
{
    return character;
}

char ArffScanner::prev() const
{
    return previous;
}

qint64 ArffScanner::getLine() const
{
    return line;
}

qint64 ArffScanner::getColumn() const
{
    return column;
}

QString ArffScanner::error(QString msg) const
{
    return source->fileName() + ":" + QString::number(line) + ":"
            + QString::number(column) + " " + msg;
}

bool ArffScanner::isNewLine(char c) const
{
    return c == '\n' || c == '\r' || c == 0;
}

bool ArffScanner::eof() const
{
    return source->atEnd();
}
