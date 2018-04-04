#pragma once
#include <string>
#include "ByteBuffer.h"

namespace App
{
	namespace FileSystem
	{
		ByteBuffer ReadBytes(const std::string &file);
		void WriteBytes(const std::string &file, const ByteBuffer &b);

		std::string ReadText(const std::string &file);
		void WriteText(const std::string &file, const std::string &text);
	}
}
