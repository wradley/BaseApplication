#pragma once
#include <string>
#include "ByteBuffer.h"

namespace App
{
	namespace FileSystem
	{
		ByteBuffer ReadBytes(const std::string &file);
		void WriteBytes(const std::string &file, const ByteBuffer &b);
	}
}
