#pragma once

#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <iostream>

inline const std::string& GetGlfwError()
{
	const char* _error;
	glfwGetError(&_error);

	return _error;
}

inline void WriteToFile(const std::string& path, const std::string& content)
{
	std::ofstream _stream(path, std::ios_base::app);
	if (!_stream.is_open())
	{
		std::cerr << "Could not create / open File " << path << std::endl;
		return;
	}

	_stream << content;
	_stream.flush();
}