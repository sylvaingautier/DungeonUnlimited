#include "Logger.h"
#include "GameCore.h"






void main()
{
	
	// One time log preferences
	auto logger = Logger::GetInstance();

	auto logLevelStr = "INFO"; // or WARN, DEBUG, INFO
	auto logLevel = logger->GetLogLevel(logLevelStr);

	auto logFile = "applog.txt";

	auto logOutputStr = "CONSOLE"; // or CONSOLE
	auto logOutput = logger->GetLogOutput(logOutputStr);
	logger->SetLogPreferences(logFile, logLevel, logOutput);
	logger->Log(__FILE__, __LINE__, "********** Debut ***********************", LogLevel::INFO);
	GameCore mGameCore;
	
	mGameCore.initGameCore();
	mGameCore.loopGameCore();
	mGameCore.endGameCore();

	logger->Log(__FILE__, __LINE__, "****************************************", LogLevel::INFO);
}