#include <gtest/gtest.h>
#include <memory>
#include "ArgumentsFactory.h"

const std::string getCommand = "get";
const std::string putCommand = "put";
const std::string invalidCommand = "invalidCommand";
const std::vector<std::string> getCommandWithArgs{"/", "/"};
const std::vector<std::string> putCommandWithArgs{"/", "/"};

TEST(ArgumentsTests, CreatingGetArguments) {
    std::unique_ptr<ArgumentsFactory> argumentsFactory = std::make_unique<ArgumentsFactory>();
    std::unique_ptr<Arguments> arg = std::move(argumentsFactory->createArgumentInstance(getCommand, getCommandWithArgs));
    ASSERT_TRUE(argumentsFactory->create_status());
}


TEST(ArgumentsTests, CreatingWithInvalidCommand) {
    std::unique_ptr<ArgumentsFactory> argumentsFactory = std::make_unique<ArgumentsFactory>();
    std::unique_ptr<Arguments> arg = std::move(argumentsFactory->createArgumentInstance(invalidCommand, putCommandWithArgs));
    ASSERT_FALSE(argumentsFactory->create_status());
}

