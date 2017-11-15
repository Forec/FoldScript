//
// Created by 王耀 on 2017/10/8.
//

#include "labnode.h"

LabelNode::LabelNode() {
    iIndex = -1;
}

LabelNode::LabelNode(int index, unsigned int targetIndex, unsigned int funcIndex) {
    iIndex = index;
    uiTargetIndex = targetIndex;
    uiFuncIndex = funcIndex;
}