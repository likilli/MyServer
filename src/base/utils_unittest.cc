#include <gtest/gtest.h>
#include "Utils.h"


const char* kHTTP11RequestHeader  = "GET / HTTP/1.1\r\n";
const char* kHTTP11ResponseHeader = "HTTP/1.1 200 OK\r\n";


TEST(StringUtilsTest, test0)
{
    EXPECT_EQ(StringUtils::StartWith(kHTTP11RequestHeader, "GET"), true);
    EXPECT_EQ(StringUtils::StartWith(kHTTP11RequestHeader, "HTTP"), false);
    EXPECT_EQ(StringUtils::StartWith(kHTTP11ResponseHeader, "GET"), false);
    EXPECT_EQ(StringUtils::StartWith(kHTTP11ResponseHeader, "HTTP"), true);
}

int main()
{
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
