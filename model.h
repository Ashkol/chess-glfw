//#pragma once
#ifndef MODEL_H
#define MODEL_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "shader.h"
#include "mesh.h"
#include "stb_image.h"


unsigned int TextureFromFile(const char* path, const std::string &directory, bool gamma = false);

class Model
{
public:
    /*  Functions   */
    Model(std::string path)
    {
        loadModel(path);
    }
    Model(std::string path, std::string fallbackPath)
    {
        fallbackTexturePath = fallbackPath;
        loadModel(path);
    }
    void draw(Shader shader);
private:
    /*  Model Data  */
    std::vector<Mesh> meshes;
    std::string directory;
    /*  Functions   */
    void loadModel(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
        std::string typeName);
    /* Helper variables */
    std::string fallbackTexturePath;
};
#endif

