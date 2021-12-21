#include <gtest/gtest.h>
#include "utils.h"


TEST(StringUtilsTest, test0)
{
    const char* kHTTP11RequestHeader  = "GET / HTTP/1.1\r\n";
    const char* kHTTP11ResponseHeader = "HTTP/1.1 200 OK\r\n";

    EXPECT_EQ(StringUtils::StartWith(kHTTP11RequestHeader, "GET"), true);
    EXPECT_EQ(StringUtils::StartWith(kHTTP11RequestHeader, "HTTP"), false);
    EXPECT_EQ(StringUtils::StartWith(kHTTP11ResponseHeader, "GET"), false);
    EXPECT_EQ(StringUtils::StartWith(kHTTP11ResponseHeader, "HTTP"), true);
}

TEST(HttpRequestHeaderParseTest, test1)
{
    const char* kHttpRequestHeader = "GET /linux HTTP/1.1\r\n"
                                     "Host: 127.0.0.1:8000\r\n"
                                     "Connection: close\r\n"
                                     "User-Agent: Likai\r\n"
                                     "Accept-Encoding: gzip\r\n"
                                     "DNT: 1\r\n"
                                     "\r\n";

    const std::map<std::string, std::string> http_header{
        {"Accept-Encoding", "gzip"},
        {"Connection",      "close"},
        {"DNT",             "1"},
        {"Host",            "127.0.0.1:8000"},
        {"User-Agent",      "Likai"},
        {"http_method",     "GET"},
        {"http_version",    "1.1"},
        {"http_path",       "/linux"},
    };

    EXPECT_EQ(HttpUtils::ParseHttpHeaderFrom(kHttpRequestHeader, strlen(kHttpRequestHeader)), http_header);
}

int main()
{
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
