#pragma once
#include <stdarg.h>
#include <iostream>
#include <string>

void Log(const char* format, ...) {
	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
}