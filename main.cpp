#include "Logger.h"
#include "GameCore.h"
#include "Dungeon_map.h"




void main()
{

	// One time log preferences
	auto logger = Logger::GetInstance();

	auto logLevelStr = "INFO"; // or WARN, DEBUG, INFO
	auto logLevel = logger->GetLogLevel(logLevelStr);

	auto logFile = "applog.txt";

	auto logOutputStr = "CONSOLE"; // or CONSOLE
	auto logOutput = logger->GetLogOutput(logOutputStr);
	Logger::GetInstance()->SetLogPreferences(logFile, logLevel, logOutput);
	Logger::GetInstance()->Log(__FILE__, __LINE__, "********** Debut ***********************", LogLevel::INFO);
	Logger::GetInstance()->Log(__FILE__, __LINE__, "Version 1.0", LogLevel::INFO);
	GameCore mGameCore;
	Dungeon_map test;
	
	mGameCore.initGameCore();
	mGameCore.loopGameCore();
	mGameCore.endGameCore();

	Logger::GetInstance()->Log(__FILE__, __LINE__, "****************************************", LogLevel::INFO);
}