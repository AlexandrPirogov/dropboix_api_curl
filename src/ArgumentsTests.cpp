#include <gtest/gtest.h>
#include <memory>
#include "Arguments.h"

const std::vector<std::string> args = {"src_path", "dst_path"};
const std::vector<std::string> getValidArgs = {"/", "/"};
const std::vector<std::string> getInvalidArgs = {"/not/existing/dir", "/not/existsing/dir"};

TEST(ArgumentsTests, CreatingGetCommandArgumentsWithArguments) {
    std::unique_ptr<GetCommandArguments> arguments = std::make_unique<GetCommandArguments>(getValidArgs);
    ASSERT_EQ(arguments->size(), 2);
    ASSERT_EQ(arguments->at(0), getValidArgs[0]);
    ASSERT_EQ(arguments->at(1), getValidArgs[1]);
    ASSERT_EQ(arguments->validate(), true);
}

TEST(ArgumentsTests, CreatingGetCommandArgumentsWithInvalidArguments)
{
    std::unique_ptr<GetCommandArguments> arguments = std::make_unique<GetCommandArguments>(getInvalidArgs);
    //#TODO
   // ASSERT_DEATH(arguments->validate(), "");
}

