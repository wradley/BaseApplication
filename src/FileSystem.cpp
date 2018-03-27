#include "FileSystem.h"
#include <fstream>
#include <iostream>


App::ByteBuffer App::FileSystem::ReadBytes(const std::string &filename)
{
	ByteBuffer b;
	
	//open file
	std::ifstream infile;
	infile.open(filename, std::ios::binary | std::ios::in);

	//get length of file
	infile.seekg(0, infile.end);
	size_t length = infile.tellg();
	infile.seekg(0, infile.beg);

	//read file
	b.expandmax((uint32_t)length);
	infile.read((char*)b.head(), length);

	infile.close();

	return b;
}


void App::FileSystem::WriteBytes(const std::string &filename, const ByteBuffer &b)
{
	if (b.size() > 0)
	{
		std::ofstream ofile;
		ofile.open(filename, std::ios::binary | std::ios::out);
		ofile.write((char*)b.head(), b.size());
		ofile.close();
	}
}
