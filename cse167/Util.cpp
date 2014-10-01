#include "Util.h"
#include <stdio.h>
#include <iostream>
#include <string.h>

unsigned char* Util::loadPGM(char* filename, int & width, int & height){
	const int BUFSIZE = 128;
	FILE* fp;
	unsigned int read;
	unsigned char* rawData;
	char buf[3][BUFSIZE];
	char* retval_fgets;
	size_t retval_sscanf;

	if ((fp = fopen(filename, "rb")) == NULL)
	{
		std::cout << "A";
		return NULL;

	}

	// Read magic number:
	retval_fgets = fgets(buf[0], BUFSIZE, fp);
	if (retval_fgets == NULL)
	{
		fclose(fp);
		std::cout << "B";
		return NULL;
	}
	if (strncmp("P5", buf[0], 2) != 0)
	{
		std::cout << "C";
		fclose(fp);
		return NULL;
	}

	// Read width and height:
	do
	{
		retval_fgets = fgets(buf[0], BUFSIZE, fp);
		if (retval_fgets == NULL)
		{
			std::cout << "D";
			fclose(fp);
			return NULL;
		}
	} while (buf[0][0] == '#');
	retval_sscanf = sscanf(buf[0], "%s %s", buf[1], buf[2]);
	if (retval_sscanf != 2)
	{
		fclose(fp);
		std::cout << "E";
		return NULL;
	}
	width = atoi(buf[1]);
	height = atoi(buf[2]);

	// Read maxval:
	do
	{
		retval_fgets = fgets(buf[0], BUFSIZE, fp);
		if (retval_fgets == NULL)
		{
			fclose(fp);
			std::cout << "F";
			return NULL;
		}
	} while (buf[0][0] == '#');

	// Read image data:
	rawData = new unsigned char[width * height];
	read = fread(rawData, width * height, 1, fp);
	if (read != 1)
	{
		fclose(fp);
		delete[] rawData;
		std::cout << "G";
		return NULL;
	}

	fclose(fp);
	return rawData;
}