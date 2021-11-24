#pragma once

#include "../../HeaderFile/Game.h"

class CFileManager
{
public:
	CFileManager();
	~CFileManager();


public:
	FILE* fptr;
	long length;
	char* buf;

public:
	char* filetobuf(const char* file)
	{
		fopen_s(&fptr, file, "rb");
		if (!fptr)
			return NULL;

		fseek(fptr, 0, SEEK_END);
		length = ftell(fptr);

		buf = (char*)malloc(length + 1);

		fseek(fptr, 0, SEEK_SET);
		fread(buf, length, 1, fptr);
		fclose(fptr);

		buf[length] = 0;
		return buf;
	}

};
