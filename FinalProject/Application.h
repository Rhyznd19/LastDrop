#pragma once

#include "RenderEngine.h"
#include "Cube.h"
#include "Texturedcube.h"
#include "biasa.h"
#include "Shader.h"

class Application :
    public RenderEngine
{
public:
    Application();
    ~Application();
private:
	float viewCamX, viewCamY, viewCamZ, upCamX, upCamY, upCamZ, posCamX, posCamY, posCamZ, CAMERA_SPEED, fovy;
	Shader *shadertest;
	Texture* cubeDiffTex, * cubeSpecTex;
	Shader *shader;
	Shader *shaderbiasa;
	Cube* cube; 
	biasa* cube2; 
	float angle;
	glm::vec3 viewPos;
	float lightX;
	float lightY;
	float lightZ;
	void setupPerspective();
	void setupCamera();
	void setupLighting(); 
	void botol(float x, float y, float z);
	void botol2(float x, float y, float z);
	void botol3(float x, float y, float z);
	void kursi(float x, float y, float z);
	void meja();
	void rak();
	void tembok();
	void alatmusik();
	virtual void Init();
	virtual void DeInit(); 
	virtual void Update(double deltaTime);
	virtual void Render();
	virtual void ProcessInput(GLFWwindow* window);
	void MoveCamera(float speed);
	void StrafeCamera(float speed);
	void RotateCamera(float speed);
	void InitCamera();
};

