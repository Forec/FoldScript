//
// Created by 王耀 on 2017/10/8.
//

#ifndef FOLDSCRIPT_ASM_LABNODE_H
#define FOLDSCRIPT_ASM_LABNODE_H

/*
 * LabelNode: 跳转标签节点
 * @iIndex: 标签索引
 * @iTargetIndex: 标签对应目标指令的索引
 * @iFuncIndex: 标签所属函数的索引
 */

class LabelNode {
private:
    int iIndex;
    unsigned int uiTargetIndex;
    unsigned int uiFuncIndex;
public:
    LabelNode();
    LabelNode(int index, unsigned int targetIndex, unsigned int funcIndex);

    int getIndex() { return iIndex; }
    int getTargetIndex() { return uiTargetIndex; }
};

#endif //FOLDSCRIPT_ASM_LABNODE_H
