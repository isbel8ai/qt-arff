#include "arffscanner.h"
#include "arfflexer.h"

const char ArffLexer::SPACE   = ' ';
const char ArffLexer::TAB     = '\t';
const char ArffLexer::COMMENT = '%';
const char ArffLexer::B_OPEN  = '{';
const char ArffLexer::B_CLOSE = '}';
const char ArffLexer::S_QUOTE = '\'';
const char ArffLexer::D_QUOTE = '"';
const char ArffLexer::COMMA   = ',';
const char ArffLexer::MISS    = '?';


ArffLexer::ArffLexer(QString filepath): scanner(NULL),
    m_b_close(false) {
    scanner = new ArffScanner(filepath);
}

ArffLexer::~ArffLexer() {
    if(scanner != NULL) {
        delete scanner;
    }
}

bool ArffLexer::isSpace(char c) const {
    return ((c == SPACE) || (c == TAB) || scanner->isNewLine(c));
}

bool ArffLexer::isComment(char c) const {
    return (c == COMMENT);
}

bool ArffLexer::isBracketOpen(char c) const {
    return (c == B_OPEN);
}

bool ArffLexer::isBracketClose(char c) const {
    return (c == B_CLOSE);
}

bool ArffLexer::isSquote(char c) const {
    return (c == S_QUOTE);
}

bool ArffLexer::isDquote(char c) const {
    return (c == D_QUOTE);
}

bool ArffLexer::isComma(char c) const {
    return (c == COMMA);
}

bool ArffLexer::isMissing(char c) const {
    return (c == MISS);
}

void ArffLexer::skipComments() {
    while(scanner->isNewLine(scanner->prev()) && isComment(scanner->current())) {
        while (scanner->next() > 0 && !scanner->isNewLine(scanner->prev()));
    }
}

void ArffLexer::skipSpaces() {
    while(isSpace(scanner->current())) {
        scanner->next();
    }
}

void ArffLexer::findTokenBegin()
{
    do {
        skipSpaces();
        skipComments();
    } while (isSpace(scanner->current()) || isComment(scanner->current()));
}

ArffToken ArffLexer::nextToken() {
    findTokenBegin();
    QString strorig = readString();
    QString strlow = strorig.toLower();
    ArffToken::ArffTokenType token = ArffToken::UNKNOWN_TOKEN;
    if(strlow == "@relation") {
        token = ArffToken::RELATION;
    }
    else if(strlow == "@attribute") {
        token = ArffToken::ATTRIBUTE;
    }
    else if(strlow == "@data") {
        token = ArffToken::DATA_TOKEN;
    }
    else if(strlow == "numeric" || strlow == "real") {
        token = ArffToken::NUMERIC_TOKEN;
    }
    else if(strlow == "string") {
        token = ArffToken::STRING_TOKEN;
    }
    else if(strlow == "date") {
        token = ArffToken::DATE_TOKEN;
    }
    else if(strlow == ",") {
        token = ArffToken::COMMA_TOKEN;
    }
    else if(strlow == "{") {
        token = ArffToken::BRKT_OPEN;
    }
    else if(strlow == "}") {
        token = ArffToken::BRKT_CLOSE;
    }
    else if(strlow =="?") {
        token = ArffToken::MISSING_TOKEN;
    }
    else if(strlow.isEmpty()) {
        token = ArffToken::END_OF_FILE;
    }
    else {
        token = ArffToken::VALUE_TOKEN;
    }
    return ArffToken(strorig, token);
}

QString ArffLexer::readString() {
    QString str;
    char c = scanner->current();
    if(c < 0) {
        return str;
    }
    else if(isBracketOpen(c)) {
        scanner->next();
        return "{";
    }
    else if(isBracketClose(c)) {
        scanner->next();
        return "}";
    }
    else if(isComma(c)) {
        scanner->next();
        return ",";
    }
    else if(isMissing(c)) {
        scanner->next();
        return "?";
    }
    else if(isSquote(c)) {
        while((c = scanner->next()) > 0 && !isSquote(c)) {
            str += c;
        }
        scanner->next();
    }
    else if(isDquote(c)) {
        while((c = scanner->next()) > 0 && !isDquote(c)) {
            str += c;
        }
        scanner->next();
    }
    else {
        while(c > 0 && !isSpace(c) && !isComma(c) && !isBracketClose(c)) {
            str += c;
            c = scanner->next();
        }
    }
    return str;
}

