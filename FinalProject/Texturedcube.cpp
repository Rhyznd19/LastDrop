#include "Texturedcube.h"

Texturedcube::Texturedcube(Shader* shader, Texture* diffuseTexture, Texture* specularTexture)
{
	this->shader = shader;
	this->diffuseTexture = diffuseTexture;
	this->specularTexture = specularTexture;
	vao = vbo = ebo = 0;
}


Texturedcube::~Texturedcube()
{

}

void Texturedcube::InitData()
{
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords, normal
		// front face
		-0.5, -0.5, 0.5,   0, 0,  0.0f,  0.0f,  1.0f, // 0
		 0.5, -0.5, 0.5,   1, 0,  0.0f,  0.0f,  1.0f, // 1
		 0.5,  0.5, 0.5,   1, 1,  0.0f,  0.0f,  1.0f, // 2
		-0.5,  0.5, 0.5,   0, 1,  0.0f,  0.0f,  1.0f, // 3

		// right face
		0.5,  0.5,  0.5,   0, 0,  1.0f,  0.0f,  0.0f, // 4
		0.5,  0.5, -0.5,   1, 0,  1.0f,  0.0f,  0.0f, // 5
		0.5, -0.5, -0.5,   1, 1,  1.0f,  0.0f,  0.0f, // 6
		0.5, -0.5,  0.5,   0, 1,  1.0f,  0.0f,  0.0f, // 7

		// back face
		-0.5,  -0.5, -0.5, 0, 0,  0.0f,  0.0f,  -1.0f, // 8 
		 0.5,  -0.5, -0.5, 1, 0,  0.0f,  0.0f,  -1.0f, // 9
		 0.5,   0.5, -0.5, 1, 1,  0.0f,  0.0f,  -1.0f, // 10
		-0.5,   0.5, -0.5, 0, 1,  0.0f,  0.0f,  -1.0f, // 11

		// left face
		-0.5, -0.5, -0.5,  0, 0, -1.0f,  0.0f,  0.0f, // 12
		-0.5, -0.5,  0.5,  1, 0, -1.0f,  0.0f,  0.0f, // 13
		-0.5,  0.5,  0.5,  1, 1, -1.0f,  0.0f,  0.0f, // 14
		-0.5,  0.5, -0.5,  0, 1, -1.0f,  0.0f,  0.0f, // 15

		// upper face
		 0.5, 0.5,  0.5,   0, 0,   0.0f,  1.0f,  0.0f, // 16
		-0.5, 0.5,  0.5,   1, 0,   0.0f,  1.0f,  0.0f, // 17
		-0.5, 0.5, -0.5,   1, 1,   0.0f,  1.0f,  0.0f, // 18
		 0.5, 0.5, -0.5,   0, 1,   0.0f,  1.0f,  0.0f, // 19

		 // bottom face
		 -0.5, -0.5, -0.5,  0, 0,   0.0f,  -1.0f,  0.0f, // 20
		  0.5, -0.5, -0.5,  1, 0,   0.0f,  -1.0f,  0.0f, // 21
		  0.5, -0.5,  0.5,  1, 1,   0.0f,  -1.0f,  0.0f, // 22
		 -0.5, -0.5,  0.5,  0, 1,   0.0f,  -1.0f,  0.0f, // 23
	};

	unsigned int indices[] = {
		// vertex order for triangles
		0,  1,  2,   0,  2,  3,   // front face
		4,  5,  6,   4,  6,  7,   // right face
		8,  9,  10,  8,  10, 11,  // back face
		12, 14, 13,  12, 15, 14,  // left face
		16, 18, 17,  16, 19, 18,  // upper face
		20, 22, 21,  20, 23, 22   // bottom face
	};

	// Generate vao, vbo, ebo
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	// Bind the Vertex Array Object first, 
	// then bind and set vertex buffer(s), 
	// and then configure vertex attributes(s).
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Create vertex attribute pointer in VAO
	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define normal pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Texturedcube::InitTexture()
{
	diffuseTexture->Init();
	specularTexture->Init();
}

void Texturedcube::Init()
{
	// Initialize buffers
	InitData();
	// Initalize texture
	InitTexture();
}


void Texturedcube::Draw()
{

	diffuseTexture->Use(GL_TEXTURE0);
	shader->setInt("material.diffuse", 0);
	specularTexture->Use(GL_TEXTURE1);
	shader->setInt("material.specular", 1);
	shader->setFloat("material.shininess", 10.0f);

	glBindVertexArray(vao);

	glm::vec3 cameraPos = glm::vec3(0, 3, 3);
	glm::vec3 cameraFront = glm::vec3(0, -1, -1);

	glm::vec3 cubePositions[] = {
	   glm::vec3(0.0f,  0.0f,  0.0f),
	   glm::vec3(2.0f,  5.0f, -15.0f),
	   glm::vec3(-1.5f, -2.2f, -2.5f),
	   glm::vec3(-3.8f, -2.0f, -12.3f),
	   glm::vec3(2.4f, -0.4f, -3.5f),
	   glm::vec3(-1.7f,  3.0f, -7.5f),
	   glm::vec3(1.3f, -2.0f, -2.5f),
	   glm::vec3(1.5f,  2.0f, -2.5f),
	   glm::vec3(1.5f,  0.2f, -1.5f),
	   glm::vec3(-1.3f,  1.0f, -1.5f)
	};
	// positions of the point lights
	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
	};

	shader->setVec3("dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
	shader->setVec3("dirLight.ambient", glm::vec3(0.05f, 0.05f, 0.05f));
	shader->setVec3("dirLight.diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
	shader->setVec3("dirLight.specular", glm::vec3(0.5f, 0.5f, 0.5f));
	// point light 1
	shader->setVec3("pointLights[0].position", pointLightPositions[0]);
	shader->setVec3("pointLights[0].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
	shader->setVec3("pointLights[0].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
	shader->setVec3("pointLights[0].specular", glm::vec3(1.0f, 1.0f, 1.0f));
	shader->setFloat("pointLights[0].constant", 1.0f);
	shader->setFloat("pointLights[0].linear", 0.09f);
	shader->setFloat("pointLights[0].quadratic", 0.032f);
	// point light 2
	shader->setVec3("pointLights[1].position", pointLightPositions[1]);
	shader->setVec3("pointLights[1].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
	shader->setVec3("pointLights[1].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
	shader->setVec3("pointLights[1].specular", glm::vec3(1.0f, 1.0f, 1.0f));
	shader->setFloat("pointLights[1].constant", 1.0f);
	shader->setFloat("pointLights[1].linear", 0.09f);
	shader->setFloat("pointLights[1].quadratic", 0.032f);
	// point light 3
	shader->setVec3("pointLights[2].position", pointLightPositions[2]);
	shader->setVec3("pointLights[2].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
	shader->setVec3("pointLights[2].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
	shader->setVec3("pointLights[2].specular", glm::vec3(1.0f, 1.0f, 1.0f));
	shader->setFloat("pointLights[2].constant", 1.0f);
	shader->setFloat("pointLights[2].linear", 0.09f);
	shader->setFloat("pointLights[2].quadratic", 0.032f);
	// point light 4
	shader->setVec3("pointLights[3].position", pointLightPositions[3]);
	shader->setVec3("pointLights[3].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
	shader->setVec3("pointLights[3].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
	shader->setVec3("pointLights[3].specular", glm::vec3(1.0f, 1.0f, 1.0f));
	shader->setFloat("pointLights[3].constant", 1.0f);
	shader->setFloat("pointLights[3].linear", 0.09f);
	shader->setFloat("pointLights[3].quadratic", 0.032f);
	// spotLight
	shader->setVec3("spotLight.position", cameraPos);
	shader->setVec3("spotLight.direction", cameraFront);
	shader->setVec3("spotLight.ambient", glm::vec3(0.0f, 0.0f, 0.0f));
	shader->setVec3("spotLight.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
	shader->setVec3("spotLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
	shader->setFloat("spotLight.constant", 1.0f);
	shader->setFloat("spotLight.linear", 0.09f);
	shader->setFloat("spotLight.quadratic", 0.032f);
	shader->setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
	shader->setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

	glm::mat4 model;
	model = glm::scale(scale);
	model = glm::translate(model, position);
	model = glm::rotate(model, angle, rotationAxis);

	shader->setMat4("model", model);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

void Texturedcube::SetPosition(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}

void Texturedcube::SetScale(float sx, float sy, float sz)
{
	scale.x = sx;
	scale.y = sy;
	scale.z = sz;
}

void Texturedcube::SetRotation(float angle, float x, float y, float z)
{
	this->angle = angle;
	rotationAxis.x = x;
	rotationAxis.y = y;
	rotationAxis.z = z;
}
