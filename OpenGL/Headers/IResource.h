#pragma once

#include <string>

namespace Resources
{
	class IResource
	{
	public:
		virtual void Create(const char* path) = 0;
		virtual void Unload() = 0;
	};
}