#pragma once

#include <glad/glad.h>
#include <SOIL/SOIL.h>
#include "Texture.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>

class Texturedcube
{
private:
	GLuint shadowmapShader, vbo, ebo, vao;
	Texture* diffuseTexture, * specularTexture;
	Shader* shader;
	glm::vec3 position, rotationAxis, scale;
	float angle;
	void InitData();
	void InitTexture();
public:
	Texturedcube(Shader* shader, Texture* diffuseTexture, Texture* specularTexture);
	~Texturedcube();
	void Init();
	void Draw();
	void SetPosition(float x, float y, float z);
	void SetScale(float sx, float sy, float sz);
	void SetRotation(float angle, float x, float y, float z);
};

