#pragma once
#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <regex>

class ObjectLoader
{
public:
	float* load(std::string path)
	{
		std::string line;
		std::ifstream file;
		file.open(path);


		float* v = NULL; float* vt = NULL; float* vn = NULL;

		if (file.is_open())
		{
			setVertArraySize(&v, &vt, &vn, &file);
			std::smatch match;
			//std::regex expression("[0-9]*/[0-9]*/*[0-9]");
			std::regex expression("[0-9]+");

			int nCount = 0;
			while (std::getline(file, line))
			{
				if (line.rfind("f ", 0) == 0)
				{
					for (std::sregex_iterator i = std::sregex_iterator(line.begin(), line.end(), expression);
						i != std::sregex_iterator();
						++i)
					{
						
						match = *i;
						std::cout << std::stoi(match.str()) << " at position " << match.position() << '\n';
					}
					vn[nCount] = std::stof(match.str());
					nCount += 1;
					////std::regex_search(line, result, r);
				}
			}

			for (int i = 0; i < nCount; i++)
			{
				std::cout << vn[i] << " ";
			}

			file.close();
		}
		return 0;
		return NULL;
	}

private:
	void setVertArraySize(float** v, float** vt, float** vn, std::ifstream* file)
	{
		int verticesCount = 0;
		int texCoordsCount = 0;
		int normalsCount = 0;
		std::string line;

		// Counting arrays size
		while (std::getline(*file, line))
		{
			if (line.rfind("v ", 0) == 0)
			{
				verticesCount += 1;
			}
			if (line.rfind("vt ", 0) == 0)
			{
				texCoordsCount += 1;
			}
			if (line.rfind("vn ", 0) == 0)
			{
				normalsCount += 1;
			}
		}
		*v = new float[verticesCount];
		*vt = new float[texCoordsCount];
		*vn = new float[normalsCount];

		std::cout << normalsCount;

		file->clear();
		file->seekg(0, std::ios::beg);

	}
};

#endif