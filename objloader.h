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
#include <boost/algorithm/string.hpp>




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
			fillVertArrays(&v, &vt, &vn, &file);
			getMeshArray(&v, &vt, &vn, &file);
			//std::smatch match;
			////std::regex expression("[0-9]*/[0-9]*/*[0-9]");
			//std::regex expression("[0-9]+");

			//int nCount = 0;
			//while (std::getline(file, line))
			//{
			//	if (line.rfind("f ", 0) == 0)
			//	{
			//		for (std::sregex_iterator i = std::sregex_iterator(line.begin(), line.end(), expression);
			//			i != std::sregex_iterator();
			//			++i)
			//		{

			//			match = *i;
			//			std::cout << std::stoi(match.str()) << " at position " << match.position() << '\n';
			//			std::cout << std::endl << std::stof(match.str()) << "___";
			//		}
			//		vn[nCount] = std::stof(match.str());
			//		nCount += 1;
			//	}
			//}

			//for (int i = 0; i < nCount; i++)
			//{
			//	std::cout << vn[i] << " ";
			//}

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
		*v = new float[verticesCount * 3];
		*vt = new float[texCoordsCount * 2];
		*vn = new float[normalsCount * 3];

		std::cout << normalsCount;

		file->clear();
		file->seekg(0, std::ios::beg);

	}

	void fillVertArrays(float** v, float** vt, float** vn, std::ifstream* file)
	{
		int verticesCount = 0;
		int texCoordsCount = 0;
		int normalsCount = 0;
		std::string line;
		std::smatch match;
		std::regex expression("[0-9]+");
		std::vector<std::string> temp;

		// Counting arrays size
		while (std::getline(*file, line))
		{
			if (line.rfind("v ", 0) == 0)
			{
				boost::split(temp, line, [](char c) {return c == ' '; });

				(*v)[verticesCount] = std::stof(temp[temp.size() - 3]);
				(*v)[verticesCount + 1] = std::stof(temp[temp.size() - 2]);
				(*v)[verticesCount + 2] = std::stof(temp[temp.size() - 1]);
				std::cout << (*v)[verticesCount] << " + " << (*v)[verticesCount + 1] << " + " << (*v)[verticesCount + 2] << std::endl;
				verticesCount += 3;
			}
			if (line.rfind("vt ", 0) == 0)
			{
				boost::split(temp, line, [](char c) {return c == ' '; });

				(*vt)[texCoordsCount] = std::stof(temp[temp.size() - 2]);
				(*vt)[texCoordsCount + 1] = std::stof(temp[temp.size() - 1]);
				//(*vt)[texCoordsCount + 2] = std::stof(line.substr(2));
				std::cout << (*vt)[texCoordsCount] << " + " << (*vt)[texCoordsCount + 1] << std::endl;
				texCoordsCount+=2;
			}
			if (line.rfind("vn ", 0) == 0)
			{
				boost::split(temp, line, [](char c) {return c == ' '; });

				(*vn)[normalsCount] = std::stof(temp[temp.size() - 3]);
				(*vn)[normalsCount + 1] = std::stof(temp[temp.size() - 2]);
				(*vn)[normalsCount + 2] = std::stof(temp[temp.size() - 1]);
				std::cout << (*vn)[normalsCount] << " + " << (*vn)[normalsCount + 1] << " + " << (*vn)[normalsCount + 2] << std::endl;
				normalsCount+=3;
			}
		}


		file->clear();
		file->seekg(0, std::ios::beg);

	}

	float* getMeshArray(float** v, float** vt, float** vn, std::ifstream* file)
	{
		std::string line;
		std::smatch match;
		std::regex expression("[0-9]+");
		std::vector<std::string> temp;
		int meshTrianglesCount = 0;
		float* meshArray;

		while (std::getline(*file, line))
		{
			if (line.rfind("f ", 0) == 0)
			{
				boost::split(temp, line, [](char c) {return c == ' ' || c =='/'; });
				meshTrianglesCount += temp.size() / 3 - 2;
				std::cout << "Triangles in face = " <<  meshTrianglesCount << std::endl;
			}
		}
		file->clear();
		file->seekg(0, std::ios::beg);
		// 3 floats for vertices, 3 for vertices normals, 2 for vertices texture coordinates
		meshArray = new float[meshTrianglesCount * 8];
		int meshArrayIndex = 0;

		while (std::getline(*file, line))
		{
			if (line.rfind("f ", 0) == 0)
			{
				boost::split(temp, line.substr(2), [](char c) {return c == ' ' || c == '/'; });
				assert(temp.size() % 3 == 0);
				
				// for each face
				for (int i = 0; i < temp.size() / 3 - 2; i++)
				{
					//std::cout << "vert" << (*v)[std::stoi(temp[i * 3])] << std::endl;
					meshArray[meshArrayIndex] = (*v)[std::stoi(temp[i * 3])];
					meshArray[meshArrayIndex + 1] = (*v)[std::stoi(temp[i * 3 + 1])];
					meshArray[meshArrayIndex + 2] = (*v)[std::stoi(temp[i * 3 + 2])];
					meshArray[meshArrayIndex + 3] = (*vn)[std::stoi(temp[i * 3])];
					meshArray[meshArrayIndex + 4] = (*vn)[std::stoi(temp[i * 3 + 1])];
					meshArray[meshArrayIndex + 5] = (*vn)[std::stoi(temp[i * 3 + 2])];
					meshArray[meshArrayIndex + 6] = (*vt)[std::stoi(temp[i * 2])];
					meshArray[meshArrayIndex + 7] = (*vt)[std::stoi(temp[i * 2 + 1])];

				}
			}
		}

		for (int i = 0; i < 8; i++)
		{
			//std::cout << *v[0] << std::endl;
			//std::cout << "vertex" << meshArray[meshArrayIndex + i] << std::endl;
		}

		return meshArray;
	}
};
#endif