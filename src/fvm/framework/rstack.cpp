//
// Created by 王耀 on 2017/11/11.
//

#include "rstack.h"

RuntimeStack::RuntimeStack() {
    reset();
}

RuntimeStack::~RuntimeStack() {
    reset();
}

void RuntimeStack::reset() {
    elems.clear();
    iFrameIndex = 0;
    iTop = 0;
    uiSize = 0;
}

void RuntimeStack::setSize(unsigned int size) {
    uiSize = size;
}

void RuntimeStack::fit() {
    if (elems.size() < uiSize)
        elems.resize(uiSize);
}

unsigned int RuntimeStack::getSize() {
    return uiSize;
}

int RuntimeStack::resolveIndex(int iIndex) {
    return iIndex < 0 ? iIndex + iFrameIndex : iIndex;
}

Value RuntimeStack::getValue(int iIndex) {
    return elems[resolveIndex(iIndex)];
}

bool RuntimeStack::setValue(int iIndex, Value val) {
    int rIndex = resolveIndex(iIndex);
    if (rIndex >= uiSize)
        return false;
    fit();
    elems[rIndex] = val;
    return true;
}

bool RuntimeStack::push(Value val) {
    if (iTop >= uiSize)
        return false;
    fit();
    elems[iTop++] = val;
    return true;
}

Value RuntimeStack::pop() {
    if (iTop <= 0)
        return Value{0, 0, 0};
    return elems[--iTop];
}