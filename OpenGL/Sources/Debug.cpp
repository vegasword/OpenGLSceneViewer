#include <sstream>
#include <fstream>
#include <time.h>
#include <vector>

#include <Matrix.h>
#include <UserInterface.h>
#include <Debug.h>

using namespace std;
using namespace Core::Debug;

// ===================================================================
// LogSystem public methods.
// ===================================================================

void LogSystem::Print(const LogType& logType, const char* fileName, const int& line, const std::string& message)
{
	ostringstream output;

	// Type string according to current log type.
	string type;
	switch(logType)
	{
		case LogType::ERROR:   type = "ERROR: ";    break;
		case LogType::WARNING: type = "WARNING: ";  break;
		case LogType::INFO:    type = "INFO: ";		break;
		default:			   type = "INFO: ";		break;
	}

	output << GetTimestamp() << type << fileName << " (line: " << line << "): " << message << "\n";
	UI::UserInterface::logBuffer.push_back(pair(logType, output.str()));
}

void LogSystem::PrintAssert(const char* fileName, const int& line, const std::string& message)
{
	Print(LogType::ERROR, fileName, line, message);
}

// ===================================================================
// LogSystem private methods.
// ===================================================================

const string LogSystem::GetTimestamp()
{
    time_t    now = time(NULL);
    struct tm tstruct;
    char      buf[80];

	// Get the time and fill the buffer with it.
    localtime_s(&tstruct, &now);
    strftime(buf, sizeof(buf), "[%Y-%m-%d %X] ", &tstruct);

    return buf;
}

// ===================================================================
// GL callbacks.
// ===================================================================

void APIENTRY glDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	ostringstream output;

	// Ignore non-significant error / warning codes.
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

	output << "---------------"							  << "\n";
	output << "Debug message (" << id << "): " << message << "\n";

	switch (source)
	{
	case GL_DEBUG_SOURCE_API:             output << "Source: API";		       break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   output << "Source: Window System";   break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER: output << "Source: Shader Compiler"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:     output << "Source: Third Party";	   break;
	case GL_DEBUG_SOURCE_APPLICATION:     output << "Source: Application";	   break;
	case GL_DEBUG_SOURCE_OTHER:           output << "Source: Other";           break;
	}
	
	output << "\n";

	switch (type)
	{
		case GL_DEBUG_TYPE_ERROR:               output << "Type: Error";				break;
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: output << "Type: Deprecated Behaviour"; break;
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  output << "Type: Undefined Behaviour";  break;
		case GL_DEBUG_TYPE_PORTABILITY:         output << "Type: Portability";		    break;
		case GL_DEBUG_TYPE_PERFORMANCE:         output << "Type: Performance";		    break;
		case GL_DEBUG_TYPE_MARKER:              output << "Type: Marker";			    break;
		case GL_DEBUG_TYPE_PUSH_GROUP:          output << "Type: Push Group";		    break;
		case GL_DEBUG_TYPE_POP_GROUP:           output << "Type: Pop Group";		    break;
		case GL_DEBUG_TYPE_OTHER:               output << "Type: Other";			    break;
	}
	
	output << "\n";

	switch (severity)
	{
		case GL_DEBUG_SEVERITY_HIGH:         output << "Severity: high";		 break;
		case GL_DEBUG_SEVERITY_MEDIUM:       output << "Severity: medium";	     break;
		case GL_DEBUG_SEVERITY_LOW:          output << "Severity: low";			 break;
		case GL_DEBUG_SEVERITY_NOTIFICATION: output << "Severity: notification"; break;
	}
	
	output << "\n\n";

	cout << output.str();
}
