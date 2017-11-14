//
// Created by 王耀 on 2017/11/14.
//

#include <gtest/gtest.h>
#include "hostapi.h"

TEST(HostAPITest, HostAPITest_OPERATION_Test) {
    HostAPICallTable table;
    EXPECT_EQ(0, table.getSize());
    table.append("HELLO");
    EXPECT_EQ(1, table.getSize());
    EXPECT_EQ("HELLO", table.getCall(0));
    EXPECT_EQ("NOP", table.getCall(12));
}