#include <iostream>

// Project Files
#include "utils/logger.h"
#include "ast/ast_builder.h"

int main()
{
  auto &logger = logger::Logger::get_logger();
  ast::ConcreteBuilder builder;

  auto root = builder.literal("abc").build();

  logger->debug(builder.to_string());
}
