#include "arfftoken.h"

ArffToken::ArffToken(QString str, ArffTokenType token) :
    tkstring(str), tkenum(token) {
}

ArffToken::ArffToken(const ArffToken& src) :
    tkstring(src.tkstring), tkenum(src.tkenum) {
}

QString ArffToken::toString() const {
    return tkstring;
}

ArffToken::ArffTokenType ArffToken::type() const {
    return tkenum;
}

qint32 ArffToken::toInt32() const {
    /*if(tkenum != VALUE_TOKEN) {
        THROW("ArffToken::token_int64 token is not '%s', it's '%s'!",
              "VALUE_TOKEN", typeString(tkenum).c_str());
    }*/
    return tkstring.toInt();
}

qint64 ArffToken::toInt64() const {
    /*if(tkenum != VALUE_TOKEN) {
        THROW("ArffToken::token_int64 token is not '%s', it's '%s'!",
              "VALUE_TOKEN", typeString(tkenum).c_str());
    }*/
    return tkstring.toLongLong();
}

float ArffToken::toFloat() const {
    /*if(tkenum != VALUE_TOKEN) {
        THROW("ArffToken::token_int64 token is not '%s', it's '%s'!",
              "VALUE_TOKEN", typeString(tkenum).c_str());
    }*/
    return tkstring.toFloat();
}

double ArffToken::toDouble() const {
    /*if(tkenum != VALUE_TOKEN) {
        THROW("ArffToken::token_int64 token is not '%s', it's '%s'!",
              "VALUE_TOKEN", typeString(tkenum).c_str());
    }*/
    return tkstring.toDouble();
}

QString ArffToken::typeString(ArffToken::ArffTokenType type) {
    switch(type) {
    case ArffToken::RELATION:       return "RELATION";
    case ArffToken::ATTRIBUTE:      return "ATTRIBUTE";
    case ArffToken::DATA_TOKEN:     return "DATA_TOKEN";
    case ArffToken::MISSING_TOKEN:  return "MISSING_TOKEN";
    case ArffToken::NUMERIC_TOKEN:  return "NUMERIC_TOKEN";
    case ArffToken::STRING_TOKEN:   return "STRING_TOKEN";
    case ArffToken::DATE_TOKEN:     return "DATE_TOKEN";
    case ArffToken::VALUE_TOKEN:    return "VALUE_TOKEN";
    case ArffToken::COMMA_TOKEN:    return "COMMA_TOKEN";
    case ArffToken::BRKT_OPEN:      return "BRKT_OPEN";
    case ArffToken::BRKT_CLOSE:     return "BRKT_CLOSE";
    case ArffToken::END_OF_FILE:    return "END_OF_FILE";
    default:                        return "UNKNOWN";
    }
}


