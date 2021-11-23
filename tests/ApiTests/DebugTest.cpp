#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Debug.hpp"
#include "string"

TEST(DebugTest, TestLog)
{
    testing::internal::CaptureStdout();
    spic::Debug::Log("basic test log");
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_THAT(output, ::testing::HasSubstr("basic test log"));
    ASSERT_THAT(output, ::testing::HasSubstr("INFO"));
}

TEST(DebugTest, TestLogError)
{
    testing::internal::CaptureStderr();
    spic::Debug::LogError("basic test error");
    std::string output = testing::internal::GetCapturedStderr();
    ASSERT_THAT(output, ::testing::HasSubstr("basic test error"));
    ASSERT_THAT(output, ::testing::HasSubstr("ERROR"));
}

TEST(DebugTest, TestLogWarning)
{
    testing::internal::CaptureStderr();
    spic::Debug::LogWarning("basic test warn");
    std::string output = testing::internal::GetCapturedStderr();
    ASSERT_THAT(output, ::testing::HasSubstr("basic test warn"));
    ASSERT_THAT(output, ::testing::HasSubstr("WARNING"));
}