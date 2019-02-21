#ifndef ARFFTOKEN_H
#define ARFFTOKEN_H

#include <QString>

/**
 * @class ArffToken arff_token.h
 * @brief An ARFF Token read by the ArffLexer class
 */
class ArffToken
{
public:

    /**
     * @enum ArffTokenType
     * @brief Tokens in the ARFF file
     */
    enum ArffTokenType {
        /** relation tag */
        RELATION = 0,
        /** attribute tag */
        ATTRIBUTE,
        /** data tag */
        DATA_TOKEN,
        /** missing */
        MISSING_TOKEN,
        /** numeric type */
        NUMERIC_TOKEN,
        /** string type */
        STRING_TOKEN,
        /** date type */
        DATE_TOKEN,
        /** value token (could be name, nominal, value) */
        VALUE_TOKEN,
        /** comma */
        COMMA_TOKEN,
        /** flower bracket open */
        BRKT_OPEN,
        /** flower bracket close */
        BRKT_CLOSE,
        /** end of file has been reached */
        END_OF_FILE,
        /** unknown type (usually an error) */
        UNKNOWN_TOKEN,
    };

    /**
     * @brief Constructor
     * @param _str the token string
     * @param _token the token enum
     */
    ArffToken(QString str, ArffTokenType token);

    /**
     * @brief Copy constructor
     * @param _src source object to copy from
     */
    ArffToken(const ArffToken& src);

    /**
     * @brief token string
     * @return string
     */
    QString toString() const;

    /**
     * @brief token enum
     * @return enum
     */
    ArffTokenType type() const;

    /**
     * @brief token value as a 32b integer
     * @return integer
     *
     * Note, this function is meaningful only if the token is of
     * 'numeric' type!
     */
    qint32 toInt32() const;

    /**
     * @brief token value as a 64b integer
     * @return integer
     *
     * Note, this function is meaningful only if the token is of
     * 'numeric' type!
     */
    qint64 toInt64() const;

    /**
     * @brief token value as a float
     * @return float
     *
     * Note, this function is meaningful only if the token is of
     * 'numeric' type!
     */
    float toFloat() const;

    /**
     * @brief token value as a double
     * @return double
     *
     * Note, this function is meaningful only if the token is of
     * 'numeric' type!
     */
    double toDouble() const;

    /**
     * @brief Utility function to convert ArffTokenEnum to string
     * @param type the enum value to be converted
     * @return desired string
     */
    static QString typeString(ArffTokenType type);

private:
    /** string */
    QString tkstring;
    /** enum */
    ArffTokenType tkenum;
};

#endif // ARFFTOKEN_H
