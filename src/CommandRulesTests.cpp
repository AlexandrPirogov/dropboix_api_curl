#include <gtest/gtest.h>
#include <memory>
#include "Rules.h"

const std::string localPath = "/";
const std::string sourceFile = "/some.txt";

const std::string destPath = "/";

const std::string notExistinglocalPath = "~notexisting/directory";

TEST(CommandRulesTests, CreatingPathRulesWithSourceArg) {
    std::unique_ptr<PathRule> pathRule = std::make_unique<PathRule>(localPath);
    ASSERT_EQ(pathRule->validate(), PATHRULESTATUSES::SOURCE_DIRECTORY_EXISTS);
}

TEST(CommandRulesTests, CreatingPathRulesWithInvalidSourceArg) {
    std::unique_ptr<PathRule> pathRule = std::make_unique<PathRule>(notExistinglocalPath);
    ASSERT_EQ(pathRule->validate(), PATHRULESTATUSES::INVALID_PATH);
}
