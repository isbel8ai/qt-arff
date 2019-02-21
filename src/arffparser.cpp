#include "arffparser.h"
#include "arfftoken.h"
#include "arffattribute.h"

ArffParser::ArffParser(QString filepath) :
        lexer(NULL), parsed(false), arffdata(NULL) {
    lexer = new ArffLexer(filepath);
}

ArffParser::~ArffParser() {
    if(lexer) {
        delete lexer;
    }
}

ArffItemModel *ArffParser::parse() {
    if(arffdata) {
        return arffdata;
    }

    arffdata = new ArffItemModel();
    readRelation();
    readAllAttributes();
    readInstances();
    parsed = true;
    return arffdata;
}

void ArffParser::readRelation() {
    // @relation
    ArffToken tkrelation = lexer->nextToken();
    if(tkrelation.type() != ArffToken::RELATION) {
        /*THROW("%s: First token must be of 'RELATION'! It is '%s'",
              "ArffParser::_read_relation",
              toString(tkrelation.token_enum()).c_str());*/
        return;
    }
    // name
    ArffToken tkname = lexer->nextToken();
    if(tkname.type() != ArffToken::VALUE_TOKEN) {
        /*THROW("%s: RELATION token must be followed by %s! It is '%s'",
              "ArffParser::_read_relation", "VALUE_TOKEN",
              toString(tkname.token_enum()).c_str());*/
        return;
    }
    arffdata->setRelationName(tkname.toString());
}

void ArffParser::readAllAttributes() {
    ArffToken tok = lexer->nextToken();
    while (tok.type() != ArffToken::DATA_TOKEN && tok.type() != ArffToken::END_OF_FILE) {
        if(tok.type() != ArffToken::ATTRIBUTE) {
            /*THROW("%s: First token must be of 'ATTRIBUTE'! It is '%s'",
                  "ArffParser::_read_attrs", toString(type).c_str());*/
            return;
        }
        readAttribute();
        tok = lexer->nextToken();
    }
}

void ArffParser::readAttribute() {
    // name
    ArffToken name = lexer->nextToken();
    if(name.type() != ArffToken::VALUE_TOKEN) {
        /*THROW("%s: 'ATTRIBUTE' must be followed by a '%s'! It is '%s'",
              "ArffParser::_read_attr", "VALUE_TOKEN",
              toString(name.token_enum()).c_str());*/
        return;
    }
    // type
    ArffAttribute::ArffAttributeType atype = ArffAttribute::UNKNOWN;
    switch(lexer->nextToken().type()) {
    case ArffToken::NUMERIC_TOKEN:
        atype = ArffAttribute::NUMERIC;
        break;
    case ArffToken::STRING_TOKEN:
        atype = ArffAttribute::STRING;
        break;
    case ArffToken::DATE_TOKEN:
        atype = ArffAttribute::DATE;
        break;
    case ArffToken::BRKT_OPEN:
        atype = ArffAttribute::NOMINAL;
        break;
    default:
        /*THROW("%s: Bad attribute type for name=%s attr-type=%s!",
              "ArffParser::_read_attr", name.token_str().c_str(),
              toString(ate).c_str());*/
        return;
    }

    ArffAttribute natt(name.toString(), atype);

    // nominal type
    if(atype == ArffAttribute::NOMINAL) {
        ArffToken tok = lexer->nextToken();
        while(tok.type() != ArffToken::BRKT_CLOSE) {
            if(tok.type() == ArffToken::VALUE_TOKEN) {
                natt.addNominal(tok.toString());
            } else {
                /*THROW("%s: For nominal values expecting '%s' got '%s' token!",
              "ArffParser::_read_attr", "VALUE_TOKEN",
              toString(tok.toString()).c_str());*/
            }
            tok = lexer->nextToken();
            if (tok.type() == ArffToken::COMMA_TOKEN) {
                tok = lexer->nextToken();
            }
        }
    }

    arffdata->addAttribute(natt);
}

void ArffParser::readInstances() {
    int cols = arffdata->columnCount();
    ArffToken tok = lexer->nextToken();

    while(cols > 0 && tok.type() != ArffToken::END_OF_FILE) {
        QVariantList inst;
        for(int i = 0; i < cols; ++i) {
            if (tok.type() == ArffToken::COMMA_TOKEN) {
                tok = lexer->nextToken();
            }

            ArffToken::ArffTokenType tktype = tok.type();
            ArffAttribute::ArffAttributeType attype = arffdata->getAttribute(i).type();

            if((tktype != ArffToken::VALUE_TOKEN) && (tktype != ArffToken::MISSING_TOKEN)) {
                /*THROW("%s expects '%s' or '%s', it is '%s'!",
                      "ArffParser::_read_instances", "VALUE_TOKEN",
                      "MISSING_TOKEN", toString(tktype).c_str());*/
                return;
            }

            QVariant val;

            if(tktype == ArffToken::MISSING_TOKEN) {
                val = QVariant("?");
            } else if((attype == ArffAttribute::STRING) || (attype == ArffAttribute::NOMINAL)) {
                val = QVariant(tok.toString());
            } else if(attype == ArffAttribute::NUMERIC) {
                val = QVariant(tok.toString());
                val.convert(QVariant::Double);
            } else if(attype == ArffAttribute::DATE) {
                val = QVariant(tok.toString());
                val.convert(QVariant::Date);
            }
            inst.append(val);
            tok = lexer->nextToken();
        }
        arffdata->addInstance(inst);
    }
}

