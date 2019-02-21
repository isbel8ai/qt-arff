#ifndef ARFFLEXER_H
#define ARFFLEXER_H

#include <QString>

#include "arfftoken.h"

class ArffScanner;

/**
 * @class ArffLexer arff_lexer.h
 * @brief Responsible for dividing the data inside 'arff' file into tokens
 */
class ArffLexer
{
public:
    /**
     * @brief Constructor
     * @param _file file to be read
     */
    ArffLexer(QString filepath);

    /**
     * @brief Destructor
     */
    ~ArffLexer();

    /**
     * @brief Reads the next token and returns its type
     * @return token
     */
    ArffToken nextToken();

    /** space */
    static const char SPACE;
    /** tab */
    static const char TAB;
    /** comment */
    static const char COMMENT;
    /** bracket open */
    static const char B_OPEN;
    /** bracket close */
    static const char B_CLOSE;
    /** single quote */
    static const char S_QUOTE;
    /** double quote */
    static const char D_QUOTE;
    /** comma */
    static const char COMMA;
    /** dealing with missing values */
    static const char MISS;

private:
    /**
     * @brief Helper function to read a string data
     * @return string data read
     *
     * This has the capability to read string with spaces
     * (when they are quoted)
     */
    QString readString();

    /**
     * @brief Skips the comments line
     * @return true if the current line was a comment, else false
     *
     * Note that when this function returns, the 'current' character
     * will be newline, just before the beginning of the line.
     */
    void skipComments();

    /**
     * @brief Skips the spaces
     *
     * Note that when this function returns, the 'current' character
     * will be a non-whitespace.
     */
    void skipSpaces();

    /**
     * @brief Find the next token begining
     *
     * Note that when this function returns, the 'current' character
     * will be the first character of a token.
     */
    void findTokenBegin();

    /**
     * @brief Checks whether the input character is a whitespace or not
     * @param c character or interest
     * @return true if it is a whitespace, else false
     */
    bool isSpace(char c) const;

    /**
     * @brief Checks whether the input character is a comment or not
     * @param c character or interest
     * @return true if it is a comment, else false
     */
    bool isComment(char c) const;

    /**
     * @brief Checks whether the input character is bracket open or not
     * @param c character of interest
     * @return true if it is, else false
     */
    bool isBracketOpen(char c) const;

    /**
     * @brief Checks whether the input character is bracket close or not
     * @param c character of interest
     * @return true if it is, else false
     */
    bool isBracketClose(char c) const;

    /**
     * @brief Checks whether the input character is single quote or not
     * @param c character of interest
     * @return true if it is, else false
     */
    bool isSquote(char c) const;

    /**
     * @brief Checks whether the input character is double quote or not
     * @param c character of interest
     * @return true if it is, else false
     */
    bool isDquote(char c) const;

    /**
     * @brief Checks whether the input character is comma or not
     * @param c character of interest
     * @return true if it is, else false
     */
    bool isComma(char c) const;

    /**
     * @brief Checks whether the input character is a '?' or not
     * @param c character of interest
     * @return true if it is, else false
     */
    bool isMissing(char c) const;

    /** the scanner */
    ArffScanner * scanner;
    /** variable to catch for '}' occurences */
    bool m_b_close;
};

#endif // ARFFLEXER_H
