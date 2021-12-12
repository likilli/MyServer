#include <gtest/gtest.h>
#include <iostream>
#include "Utils.h"


const char* kHttpRequestHeader = "GET / HTTP/1.1\r\n";


int main()
{
	EXPECT_EQ(StringUtils::StartWith("GET / HTTP/1.1", "GET"), true);
    EXPECT_EQ(StringUtils::StartWith("GET / HTTP/1.1", "HTTP"), false);
    EXPECT_EQ(StringUtils::StartWith("HTTP/1.1 200 OK", "GET"), false);
    EXPECT_EQ(StringUtils::StartWith("HTTP/1.1 200 OK", "HTTP"), true);

	return 0;
}
