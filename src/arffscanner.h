#ifndef ARFFSCANNER_H
#define ARFFSCANNER_H

#include <QFile>

/**
 * @class ArffScanner arff_scanner.h
 * @brief Class responsible for reading the 'arff' file
 */
class ArffScanner
{
public:
    /** Constructor */
    ArffScanner(QString filepath);

    /** Destructor*/
    ~ArffScanner();

    /**
     * @brief Return the next character in the stream
     * @return character
     */
    char next();

    /**
     * @brief Returns the currently read char from the file
     * @return current character
     */
    char current() const;

    /**
     * @brief Returns the previously read char from the file
     * @return previous character
     */
    char prev() const;

    /**
     * @brief Returns the current line position
     * @return current line
     */
    qint64 getLine() const;

    /**
     * @brief Returns the current column position
     * @return current column
     */
    qint64 getColumn() const;

    /**
     * @brief Give a nice error message along with file,line,col info
     * @param msg actual error message to be prepended with the above info
     * @return prepended 'meaningful' error message
     */
    QString error(QString msg) const;

    /**
     * @brief Checks whether the given character is newline or not
     * @param c the character
     * @return true if the character is newline, else false
     */
    bool isNewLine(char c) const;

     /**
     * @brief Whether the file has reached end or not
     * @return true if end-of-file, else false
     */
    bool eof() const;

private:
    /** file being read */
    QFile * source;

    /** current line being read */
    qint64 line;

    /** current position in the row being read */
    qint64 column;

    /** previous character read from the file */
    char previous;

    /** current character read from the file */
    char character;
};

#endif // ARFFSCANNER_H
