#pragma once

#include <glad/glad.h>

#include <iostream>
#include <fstream>
#include <string>

// Get current filename macro.
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

// Formatted log output.
#define Log(logType, message) Core::Debug::LogSystem::Print(logType, __FILENAME__, __LINE__, message);

// Assert macro.
#define Assert(condition, message) if (condition == 0) { Core::Debug::LogSystem::PrintAssert(__FILENAME__, __LINE__, message); throw std::runtime_error(message); }

namespace Core::Debug
{
	enum class LogType { ERROR, WARNING, INFO };

	class LogSystem
	{
	public:
		static void Print      (const LogType& logType, const char* fileName, const int& line, const std::string& message);
		static void PrintAssert(const char* fileName, const int& line, const std::string& message);

	private:
		static const std::string GetTimestamp();
	};
}

void APIENTRY glDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);