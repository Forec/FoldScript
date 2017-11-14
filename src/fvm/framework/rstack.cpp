//
// Created by 王耀 on 2017/11/11.
//

#include "rstack.h"

RuntimeStack::RuntimeStack() {
    reset();
    uiSize = 0;
}

RuntimeStack::~RuntimeStack() {
    reset();
}

void RuntimeStack::reset() {
    elems.clear();
    iFrameIndex = 0;
    uiTop = 0;
    exception = Value{};
}

void RuntimeStack::setSize(unsigned int size) {
    uiSize = size;
}

void RuntimeStack::setIFrameIndex(int frameIndex) {
    iFrameIndex = frameIndex;
}

void RuntimeStack::pushFrame(unsigned int size) {
    uiTop += size;
    iFrameIndex = uiTop;
}

void RuntimeStack::popFrame(unsigned int size) {
    uiTop -= size;
}

void RuntimeStack::fit() {
    if (elems.size() < uiSize)
        elems.resize(uiSize, Value());
}

unsigned int RuntimeStack::getSize() {
    return uiSize;
}

unsigned int RuntimeStack::getTopIndex() {
    return uiTop;
}

int RuntimeStack::resolveIndex(int iIndex) {
    return iIndex < 0 ? iIndex + iFrameIndex : iIndex;
}

Value &RuntimeStack::getValueRef(int iIndex) {
    int index = resolveIndex(iIndex);
    if (index < 0 || index > uiSize)
        return exception;
    fit();
    return elems.at((unsigned long)index);
}

Value RuntimeStack::getValue(int iIndex) {
    return getValueRef(iIndex);
}

bool RuntimeStack::setValue(int iIndex, const Value &val) {
    int rIndex = resolveIndex(iIndex);
    if (rIndex >= uiSize)
        return false;
    fit();
    elems[rIndex] = val;
    return true;
}

bool RuntimeStack::push(const Value &val) {
    if (uiTop >= uiSize)
        return false;
    fit();
    elems[uiTop++] = val;
    return true;
}

Value RuntimeStack::pop() {
    if (uiTop <= 0)
        return exception;
    return elems[--uiTop];
}