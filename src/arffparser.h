#ifndef ARFFPARSER_H
#define ARFFPARSER_H

#include <QString>

#include "arfflexer.h"
#include "arffitemmodel.h"

/**
 * @class ArffParser arff_parser.h
 * @brief Main class for parsing ARFF files
 */
class ArffParser
{
public:
    /**
     * @brief Constructor
     * @param _file File to be parsed
     */
    ArffParser(QString filepath);

    /**
     * @brief Destructor
     */
    ~ArffParser();

    /**
     * @brief Main function for parsing the file
     * @return the 'ArffData' object after parsing the file
     *
     * Note that this pointer will still be owned by this class!
     */
    ArffItemModel * parse();

private:
    /**
     * @brief Reads the 'relation' token
     */
    void readRelation();

    /**
     * @brief Reads the attributes
     */
    void readAllAttributes();

    /**
     * @brief Reads one attribute
     */
    void readAttribute();

    /**
     * @brief Reads the data
     */
    void readInstances();

    /** lexer for generating tokens */
    ArffLexer * lexer;
    /** whether you have already parsed the file or not */
    bool parsed;
    /** the data parsed from the ARFF file */
    ArffItemModel * arffdata;
};

#endif // ARFFPARSER_H
