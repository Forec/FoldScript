//
// Created by 王耀 on 2017/11/14.
//

#include <gtest/gtest.h>
#include "utils.h"

TEST(UtilsTest, UtilsTest_Timestamp_Test) {
    EXPECT_EQ(0, getCurrentTimestamp());
}