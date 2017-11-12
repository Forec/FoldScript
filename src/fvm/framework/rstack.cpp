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
}

void RuntimeStack::setSize(unsigned int size) {
    uiSize = size;
    elems.resize(uiSize);
}

unsigned int RuntimeStack::getSize() {
    return uiSize;
}