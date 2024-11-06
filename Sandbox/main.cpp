#include "core/logging/Logger.h"
#include "core/logging/LoggerFactory.h"

int main()
{
    hive::Logger* logger = hive::LoggerFactory::createLogger(hive::LogOutputType::Console, hive::LogLevel::Debug);
    hive::Logger::init(logger);
    hive::Logger::log("Hi", hive::LogLevel::Error);

    return 0;
}