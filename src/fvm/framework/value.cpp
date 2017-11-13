//
// Created by 王耀 on 2017/11/13.
//

#include <cstdlib>
#include <cstring>
#include <string>
#include "macro.h"
#include "value.h"

Value Value::clone() {
    Value copy = *this;
    if (iType == OP_TYPE_STRING) {
        copy.sStrLiteral = new char[strlen(this->sStrLiteral)+1];
        strcpy(copy.sStrLiteral, this->sStrLiteral);
    }
    return copy;
}

Value& Value::operator=(const Value &rhs) {
    if (this == &rhs)
        return *this;
    if (this->iType == OP_TYPE_STRING)
        delete []this->sStrLiteral;
    *this = rhs;
    if (rhs.iType == OP_TYPE_STRING) {
        this->sStrLiteral = new char[strlen(rhs.sStrLiteral) + 1];
        strcpy(this->sStrLiteral, rhs.sStrLiteral);
    }
}

int Value::toInt() {
    switch (iType) {
        case OP_TYPE_INT:
            return iIntLiteral;
        case OP_TYPE_FLOAT:
            return (int)fFloatLiteral;
        case OP_TYPE_STRING:
            return (int)strtol(sStrLiteral, nullptr, 10);
        default:
            return 0;
    }
}

float Value::toFloat() {
    switch (iType) {
        case OP_TYPE_INT:
            return (float)iIntLiteral;
        case OP_TYPE_FLOAT:
            return fFloatLiteral;
        case OP_TYPE_STRING:
            return strtof(sStrLiteral, nullptr);
        default:
            return 0.0;
    }
}

char * Value::toString() {
    char *pStr = nullptr;
    std::string strCoerce;
    switch (iType) {
        case OP_TYPE_INT:
            strCoerce = std::to_string(iIntLiteral);
            break;
        case OP_TYPE_FLOAT:
            strCoerce = std::to_string(fFloatLiteral);
            break;
        case OP_TYPE_STRING:
            strCoerce = std::string(sStrLiteral);
            break;
        default:
            strCoerce = "";
    }
    pStr = new char[strCoerce.length() + 1];
    strcpy(pStr, strCoerce.c_str());
    return pStr;
}