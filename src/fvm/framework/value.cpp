//
// Created by 王耀 on 2017/11/13.
//

#include <cstdlib>
#include <cstring>
#include <string>
#include "macro.h"
#include "value.h"

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

std::string Value::toString() {
    std::string strCoerce;
    switch (iType) {
        case OP_TYPE_INT:
            strCoerce = std::to_string(iIntLiteral);
            break;
        case OP_TYPE_FLOAT:
            strCoerce = std::to_string(fFloatLiteral);
            break;
        case OP_TYPE_STRING:
            strCoerce = sStrLiteral;
            break;
        default:
            strCoerce = "";
    }
    return strCoerce;
}

int Value::toInstrIndex() {
    if (iType != OP_TYPE_INSTR_INDEX)
        return -1;
    return uiInstrIndex;
}