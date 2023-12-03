#include "Application.h"


Application::Application()
{
	angle = 0;
}

Application::~Application()
{
}

void Application::InitCamera() {
	posCamX = 0.0f;
	posCamY = 1.5f;
	posCamZ = 3.0f;
	viewCamX = 0.0f;
	viewCamY = 1.0f;
	viewCamZ = 0.0f;
	upCamX = 0.0f;
	upCamY = 1.0f;
	upCamZ = 0.0f;
	CAMERA_SPEED = 0.002f;
	fovy = 45.0f;
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Application::setupPerspective()
{
	// Pass perspective projection matrix
	glm::mat4 projection = glm::perspective(fovy, (GLfloat)this->screenWidth / (GLfloat)this->screenHeight, 0.1f, 100.0f);
	shader->setMat4("projection", projection);
	shaderbiasa->setMat4("projection", projection);
}

void Application::setupCamera()
{

	// LookAt camera (position, target/direction, up)
	viewPos = glm::vec3(posCamX, posCamY, posCamZ);
	//glm::mat4 view = glm::lookAt(viewPos, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 view = glm::lookAt(glm::vec3(posCamX, posCamY, posCamZ), glm::vec3(viewCamX, viewCamY, viewCamZ), glm::vec3(upCamX, upCamY, upCamZ));
	shader->setMat4("view", view);
	shaderbiasa->setMat4("view", view);
}

void Application::setupLighting()
{
	lightX = 0.f;
	lightY = 3.25f;
	lightZ = -.5f;
	glm::vec3 lightPos = glm::vec3(lightX, lightY, lightZ);
	// set lighting attributes
	/*glm::vec3 lightPos = glm::vec3( 0, 1, 1);*/
	shader->setVec3("lightPos", lightPos);
	shader->setVec3("viewPos", viewPos);
	glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	shader->setVec3("lightColor", lightColor);

}

void Application::Init()
{

	// Build a lighting map shader
	shader = new Shader("cube.vert", "cube.frag");
	shader->Init();
	// Create instance of cube
	cube = new Cube(shader);
	cube->Init();

	// Build a lighting map shader
	shaderbiasa = new Shader("biasa.vert", "biasa.frag");
	shaderbiasa->Init();
	// Create instance of cube
	cube2 = new biasa(shaderbiasa);
	cube2->Init();
	
	InitCamera();

	// setup lighting
	
	
}

void Application::DeInit()
{
	delete cube;
	delete cube2;
}

void Application::Update(double deltaTime)
{
	angle += (float)((deltaTime * 0.f) / 1000);
	cube->SetRotation(angle, 0, 1, 0);
	cube2->SetRotation(angle, 0, 1, 0);
	 /*lightX = 7.0f * sin(glfwGetTime());
	 lightY = 1.f;
	 lightZ = 4.5f * cos(glfwGetTime());*/
	
}

void Application::Render()
{
	glViewport(0, 0, this->screenWidth, this->screenHeight);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SetBackgroundColor(1.0f, 1.0f, 1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_DEPTH_TEST);
	// setup perspective 
	setupPerspective();
	// setup camera
	setupCamera();
	setupLighting();

	//render object
	tembok();
	meja();
	rak();
	//rak 1
	botol(-.9f, 1.25f, -2.275f);
	botol(-.1f, 1.25f, -2.16f);
	botol2(.9f, 1.275f, -2.16f);
	botol2(-.4f, 1.275f, -2.2f);
	botol2(.35f, 1.275f, -2.1f);
	botol2(-1.25f, 1.275f, -2.3f);
	botol2(-.7f, 1.275f, -2.1f);
	botol3(.7f, 1.2f, -2.1f);
	botol3(.2f, 1.2f, -2.275f);

	//rak 2
	botol(-1.25f, 1.75f, -2.3f);
	botol(.15f, 1.75f, -2.1f);
	botol(.05f, 1.75f, -2.3f);
	botol(.85f, 1.75f, -2.2f);
	botol(.75f, 1.75f, -2.3f);
	botol2(-.75f, 1.75f, -2.3f);
	botol2(-.45f, 1.75f, -2.1f);
	botol2(-.25f, 1.75f, -2.3f);
	botol2(-.95f, 1.75f, -2.2f);
	botol2(.35f, 1.75f, -2.3f);
	botol3(-.15f, 1.675f, -2.2f);
	botol3(.45f, 1.675f, -2.2f);
	botol3(.55f, 1.675f, -2.1f);
	botol3(-.95f, 1.675f, -2.1f);
	botol3(-.65f, 1.675f, -2.1f);

	//rak2
	botol2(-1.25f, 1.75f, -2.2f);
	botol(.15f, 2.25f, -2.1f);
	botol2(.05f, 2.25f, -2.3f);
	botol(.85f, 2.25f, -2.2f);
	botol(.75f, 2.25f, -2.3f);
	botol(-.75f, 2.25f, -2.3f);
	botol2(-.45f, 2.25f, -2.1f);
	botol2(-.25f, 2.25f, -2.3f);
	botol2(-.95f, 2.25f, -2.2f);
	botol(.35f, 2.25f, -2.3f);
	botol3(-1.25f, 2.175f, -2.2f);
	botol3(-1.10f, 2.175f, -2.1f);
	botol3(-.75f, 2.175f, -2.1f);
	botol3(-.05f, 2.175f, -2.1f);
	botol3(.5f, 2.175f, -2.1f);

	//rak3
	botol(-1.25f, 2.75f, -2.3f);
	botol(.15f, 2.75f, -2.1f);
	botol(.05f, 2.75f, -2.3f);
	botol(.85f, 2.75f, -2.2f);
	botol(.75f, 2.75f, -2.3f);
	botol2(-.75f, 2.75f, -2.3f);
	botol2(-.45f, 2.75f, -2.1f);
	botol2(-.25f, 2.75f, -2.3f);
	botol2(-.95f, 2.75f, -2.2f);
	botol2(.35f, 2.75f, -2.3f);
	botol3(-.15f, 2.675f, -2.2f);
	botol3(.45f, 2.675f, -2.2f);
	botol3(.55f, 2.675f, -2.1f);
	botol3(-.95f, 2.675f, -2.1f);
	botol3(-.65f, 2.675f, -2.1f);

	//lampu
	cube->SetPosition(0.f, 3.65f, -.5f);
	cube->SetScale(.05f, 0.5f, .05f);
	cube->Draw();

	//pintu
	cube->SetColor(63.0f, 45.0f, 38.0f);
	cube->SetPosition(-2.8f, 1.6f, -2.4f);
	cube->SetScale(1.5f, 3.f, .1f);
	cube->Draw();

	cube->SetColor(208.0f, 155.0f, 105.0f);
	cube->SetPosition(-3.6f, 1.6f, -2.4f);
	cube->SetScale(.1f, 3.1f, .1f);
	cube->Draw();
	cube->SetPosition(-2.f, 1.6f, -2.4f);
	cube->SetScale(.1f, 3.1f, .1f);
	cube->Draw();
	cube->SetPosition(-2.8f, 3.15f, -2.4f);
	cube->SetScale(1.7f, .1f, .1f);
	cube->Draw();
	//gagang
	cube->SetColor(0, 0, 0);
	cube->SetPosition(-2.2f, 1.5f, -2.3f);
	cube->SetScale(.1f, .1f, .1f);
	cube->Draw();

	//tambalan bawah
	cube->SetColor(208.0f, 155.0f, 105.0f);
	cube->SetPosition(-3.9f, 0.f, 0.f);
	cube->SetScale(.1f, .1f, 5.f);
	cube->Draw();

	cube->SetPosition(3.9f, 0.f, 0.f);
	cube->SetScale(.1f, .1f, 5.f);
	cube->Draw();

	cube->SetPosition(0.f, 0.f, -2.4f);
	cube->SetScale(8.f, .1f, .1f);
	cube->Draw();


	//mesin
	cube->SetColor(128, 128, 128);
	cube->SetPosition(.75f, 1.25f, -.5f);
	cube->SetScale(.6f, .05f, .4f);
	cube->Draw();

	//bagian depan
	cube->SetColor(225, 225, 225);
	cube->SetPosition(.975f, 1.35f, -.4f);
	cube->SetScale(.05f, .25f, .05f);
	cube->Draw();
	cube->SetPosition(.925f, 1.5f, -.4f);
	cube->SetScale(.05f, .05f, .05f);
	cube->Draw();
	cube->SetPosition(.525f, 1.35f, -.4f);
	cube->SetScale(.05f, .25f, .05f);
	cube->Draw();
	cube->SetPosition(.575f, 1.5f, -.4f);
	cube->SetScale(.05f, .05f, .05f);
	cube->Draw();
	cube->SetPosition(.75f, 1.5525f, -.4f);
	cube->SetScale(.3f, .05f, .05f);
	cube->Draw();
	//keluaran
	cube->SetPosition(.86f, 1.5525f, -.525f);
	cube->SetScale(.05f, .05f, .25f);
	cube->Draw();
	cube->SetPosition(.86f, 1.525f, -.625f);
	cube->SetScale(.05f, .05f, .05f);
	cube->Draw();
	cube->SetPosition(.78f, 1.5525f, -.525f);
	cube->SetScale(.05f, .05f, .25f);
	cube->Draw();
	cube->SetPosition(.78f, 1.525f, -.625f);
	cube->SetScale(.05f, .05f, .05f);
	cube->Draw();
	cube->SetPosition(.72f, 1.5525f, -.525f);
	cube->SetScale(.05f, .05f, .25f);
	cube->Draw();
	cube->SetPosition(.72f, 1.525f, -.625f);
	cube->SetScale(.05f, .05f, .05f);
	cube->Draw();
	cube->SetPosition(.65f, 1.5525f, -.525f);
	cube->SetScale(.05f, .05f, .25f);
	cube->Draw();
	cube->SetPosition(.65f, 1.525f, -.625f);
	cube->SetScale(.05f, .05f, .05f);
	cube->Draw();
	//
	cube->SetColor(223, 255, 0);
	cube->SetPosition(.625f, 1.61f, -.525f);
	cube->SetScale(.03f, .07f, .03f);
	cube->Draw();
	cube->SetColor(222, 49, 99);
	cube->SetPosition(.70f, 1.61f, -.525f);
	cube->SetScale(.03f, .07f, .03f);
	cube->Draw();
	cube->SetColor(100, 149, 237);
	cube->SetPosition(.76f, 1.61f, -.525f);
	cube->SetScale(.03f, .07f, .03f);
	cube->Draw();
	cube->SetColor(64, 224, 208);
	cube->SetPosition(.84f, 1.61f, -.525f);
	cube->SetScale(.03f, .07f, .03f);
	cube->Draw();


	//bagian belakang kanan
	cube->SetColor(128, 128, 128);
	cube->SetPosition(1.02f, 1.35f, -.475f);
	cube->SetScale(.05f, .25f, .1f);
	cube->Draw();
	cube->SetPosition(.975f, 1.35f, -.475f);
	cube->SetScale(.05f, .35f, .1f);
	cube->Draw();
	cube->SetPosition(.925f, 1.375f, -.475f);
	cube->SetScale(.05f, .4f, .1f);
	cube->Draw();

	//kiri
	cube->SetPosition(.475f, 1.35f, -.475f);
	cube->SetScale(.05f, .25f, .05f);
	cube->Draw();
	cube->SetPosition(.525f, 1.35f, -.475f);
	cube->SetScale(.05f, .35f, .1f);
	cube->Draw();
	cube->SetPosition(.575f, 1.375f, -.475f);
	cube->SetScale(.05f, .4f, .1f);
	cube->Draw();

	
	kursi(-1.f, 0.f, 0.8f);
	kursi(0.f, 0.f, 0.8f);
	kursi(1.f, 0.f, 0.8f);
	alatmusik();


	cube2->SetColor(128, 128, 128);
	cube2->SetPosition(lightX, lightY, lightZ);
	cube2->SetScale(.3f, 0.3f, .3f);
	cube2->Draw();
	

	glDisable(GL_DEPTH_TEST);

}

void Application::alatmusik() {
	//alat musik
	cube->SetColor(208.0f, 155.0f, 105.0f);
	cube->SetPosition(3.f, 0.f, -1.825f);
	cube->SetScale(1.5f, 0.2f, 1.f);
	cube->Draw();

	//kiri
	cube->SetPosition(2.35f, .6f, -1.825f);
	cube->SetScale(.2f, 1.35f, 1.f);
	cube->Draw();

	//kanan
	cube->SetPosition(3.75f, .6f, -1.825f);
	cube->SetScale(.2f, 1.35f, 1.f);
	cube->Draw();

	//atas
	cube->SetPosition(3.65f, 1.3f, -1.825f);
	cube->SetScale(.2f, .15f, 1.f);
	cube->Draw();

	cube->SetPosition(2.45f, 1.3f, -1.825f);
	cube->SetScale(.2f, .15f, 1.f);
	cube->Draw();

	cube->SetPosition(2.55f, 1.4f, -1.825f);
	cube->SetScale(.2f, .15f, 1.f);
	cube->Draw();

	cube->SetPosition(3.55f, 1.4f, -1.825f);
	cube->SetScale(.2f, .15f, 1.f);
	cube->Draw();

	//atas
	cube->SetPosition(3.05f, 1.5f, -1.825f);
	cube->SetScale(1.f, .15f, 1.f);
	cube->Draw();

	//atas tengah
	cube->SetPosition(3.f, 1.1f, -1.825f);
	cube->SetScale(1.3f, .1f, 1.f);
	cube->Draw();


	//bagian tengah
	cube->SetColor(248, 200, 99);
	cube->SetPosition(3.05f, .8f, -1.7f);
	cube->SetScale(1.2f, .125f, 1.f);
	cube->Draw();

	cube->SetPosition(2.5f, .4f, -1.2f);
	cube->SetScale(.2f, .75f, .25f);
	cube->Draw();

	cube->SetPosition(3.6f, .4f, -1.2f);
	cube->SetScale(.2f, .75f, .25f);
	cube->Draw();

	cube->SetPosition(3.05f, 0.05f, -1.2f);
	cube->SetScale(1.25f, 0.1f, .25f);
	cube->Draw();

	//tiang
	cube->SetColor(255, 255, 255);
	cube->SetPosition(3.05f, 0.45f, -1.3f);
	cube->SetScale(.1f, .7f, .1f);
	cube->Draw();

	cube->SetPosition(3.4f, 0.45f, -1.3f);
	cube->SetScale(.1f, .7f, .1f);
	cube->Draw();

	cube->SetPosition(2.7f, 0.45f, -1.3f);
	cube->SetScale(.1f, .7f, .1f);
	cube->Draw();

	//belakang
	cube->SetColor(208.0f, 155.0f, 105.0f);
	cube->SetPosition(3.f, 0.5f, -1.9f);
	cube->SetScale(1.5f, .7f, .1f);
	cube->Draw();

}

void Application::tembok() {
	//belakang
	cube->SetColor(128, 128, 128);
	cube->SetScale(8.f, 4.5f, 0.1f);
	cube->SetPosition(0, 2.1, -2.5);
	cube->Draw();
	//samping
	cube->SetScale(0.1f, 4.5f, 5.f);
	cube->SetPosition(-4., 2.1, 0);
	cube->Draw();
	//samping
	cube->SetScale(0.1f, 4.5f, 5.f);
	cube->SetPosition(4., 2.1, 0);
	cube->Draw();
	//bawah
	cube->SetColor(128, 128, 128);
	cube->SetPosition(0.f, -0.1f, 0.0f);
	cube->SetScale(8.0f, 0.1f, 5.0f);
	cube->Draw();
	//atas
	cube->SetColor(128, 128, 128);
	cube->SetPosition(0.f, 4.3f, 0.0f);
	cube->SetScale(8.0f, 0.1f, 5.0f);
	cube->Draw();

}

void Application::rak() {
	//rak botol
	cube->SetColor(208.0f, 155.0f, 105.0f);
	cube->SetPosition(-0.2f, 1.1f, -2.2f);
	cube->SetScale(2.6f, 0.1f, 0.3f);
	cube->Draw();

	//rak botol 1
	cube->SetColor(208.0f, 155.0f, 105.0f);
	cube->SetPosition(-0.2f, 1.6f, -2.2f);
	cube->SetScale(2.6f, 0.1f, 0.3f);
	cube->Draw();

	//rak botol 2
	cube->SetColor(208.0f, 155.0f, 105.0f);
	cube->SetPosition(-0.2f, 2.1f, -2.2f);
	cube->SetScale(2.6f, 0.1f, 0.3f);
	cube->Draw();

	//rak botol 3
	cube->SetColor(208.0f, 155.0f, 105.0f);
	cube->SetPosition(-0.2f, 2.6f, -2.2f);
	cube->SetScale(2.6f, 0.1f, 0.3f);
	cube->Draw();

	//rak samping
	cube->SetColor(208.0f, 155.0f, 15.0f);
	cube->SetPosition(1.1f, 2.05f, -2.2f);
	cube->SetScale(0.1f, 2.f, 0.3f);
	cube->Draw();

	//rak samping
	cube->SetColor(208.0f, 155.0f, 15.0f);
	cube->SetPosition(-1.5f, 2.05f, -2.2f);
	cube->SetScale(0.1f, 2.f, 0.3f);
	cube->Draw();

	//rak belakang
	cube->SetColor(208.0f, 155.0f, 105.0f);
	cube->SetPosition(-0.2f, 2.05f, -2.345f);
	cube->SetScale(2.6f, 2.f, 0.01f);
	cube->Draw();
}

void Application::meja() {
	//botol
	cube->SetColor(124.0f, 252.0f, 0.0f);
	cube->SetPosition(0.075f, 1.25f, 0.05f);
	cube->SetScale(0.07f, 0.15f, 0.07f);
	cube->Draw();

	cube->SetPosition(0.075f, 1.35f, 0.05f);
	cube->SetScale(0.06f, 0.1f, 0.06f);
	cube->Draw();

	cube->SetPosition(0.075f, 1.4f, 0.05f);
	cube->SetScale(0.04f, 0.05f, 0.04f);
	cube->Draw();

	//gelas
	cube->SetColor(0.0f, 252.0f, 236.0f);
	cube->SetPosition(0.3f, 1.2f, 0.06f);
	cube->SetScale(0.08f, 0.1f, 0.01f);
	cube->Draw();

	cube->SetPosition(0.3f, 1.2f, 0.13f);
	cube->SetScale(0.08f, 0.1f, 0.01f);
	cube->Draw();

	cube->SetPosition(0.34f, 1.2f, 0.095f);
	cube->SetScale(0.01f, 0.1f, 0.08f);
	cube->Draw();

	cube->SetPosition(0.26f, 1.2f, 0.095f);
	cube->SetScale(0.01f, 0.1f, 0.08f);
	cube->Draw();

	cube->SetPosition(0.3f, 1.14f, 0.095f);
	cube->SetScale(0.08f, 0.09f, 0.08f);
	cube->Draw();
	//bawah1
	cube->SetColor(107.0f, 71.0f, 50.0f);
	cube->SetPosition(0.0f, 0.f, -0.05f);
	cube->SetScale(3.f, 0.1f, 0.15f);
	cube->Draw();

	cube->SetPosition(1.6f, 0.f, -0.125f);
	cube->SetScale(0.3f, 0.1f, .3f);
	cube->Draw();

	cube->SetPosition(1.825f, 0.f, -1.175f);
	cube->SetScale(0.15f, 0.1f, 2.1f);
	cube->Draw();

	//bawah2
	cube->SetColor(107.0f, 71.0f, 50.0f);
	cube->SetPosition(0.0f, 0.1f, -0.15f);
	cube->SetScale(3.f, 0.1f, 0.15f);
	cube->Draw();

	cube->SetPosition(1.575f, 0.1f, -0.225f);
	cube->SetScale(0.15f, 0.1f, .3f);
	cube->Draw();

	cube->SetPosition(1.725f, 0.1f, -1.225f);
	cube->SetScale(0.15f, 0.1f, 2.f);
	cube->Draw();

	//tengah depan
	cube->SetColor(63.0f, 45.0f, 38.0f);
	cube->SetPosition(0.0f, 0.65f, -0.3f);
	cube->SetScale(3.f, 1.f, 0.2f);
	cube->Draw();

	//samping
	cube->SetColor(63.0f, 45.0f, 38.0f);
	cube->SetPosition(1.55f, 0.65f, -1.35f);
	cube->SetScale(0.2f, 1.f, 2.f);
	cube->Draw();

	//desk depan
	cube->SetColor(208.0f, 155.0f, 105.0f);
	cube->SetPosition(0.0f, 1.2f, -0.55f);
	cube->SetScale(3.f, 0.1f, 0.7f);
	cube->Draw();

	//desk samping
	cube->SetColor(208.0f, 155.0f, 105.0f);
	cube->SetPosition(1.4f, 1.2f, -1.2f);
	cube->SetScale(.5f, 0.1f, 2.f);
	cube->Draw();

	//siku depan
	cube->SetColor(107.0f, 71.0f, 50.0f);
	cube->SetPosition(-1.575f, 0.6f, -0.4f);
	cube->SetScale(0.15f, 1.3f, 1.f);
	cube->Draw();


	//serving depan
	cube->SetColor(208.0f, 155.0f, 105.0f);
	cube->SetPosition(0.075f, 1.1f, 0.05f);
	cube->SetScale(3.15f, 0.1f, 0.5f);
	cube->Draw();


	//serving samping
	cube->SetColor(208.0f, 155.0f, 105.0f);
	cube->SetPosition(1.9f, 1.1f, -1.2f);
	cube->SetScale(0.5f, 0.1f, 2.f);
	cube->Draw();

	//siku belakang
	cube->SetColor(107.0f, 71.0f, 50.0f);
	cube->SetPosition(1.55f, 0.6f, -2.275f);
	cube->SetScale(0.8f, 1.3f, 0.15f);
	cube->Draw();
}

void Application::botol(float x, float y, float z) {
	cube->SetColor(255, 255, 255);
	cube->SetPosition(x, y, z);
	cube->SetScale(0.15f, .25f, 0.075f);
	cube->Draw();
	cube->SetColor(0, 0, 0);
	cube->SetPosition(x - .0375f, y + .15f, z);
	cube->SetScale(0.075f, .05f, 0.075f);
	cube->Draw();
}

void Application::botol2(float x, float y, float z) {
	cube->SetColor(208.0f, 155.0f, 165.0f);
	cube->SetPosition(x, y, z);
	cube->SetScale(0.225f, .25f, 0.075f);
	cube->Draw();
	cube->SetColor(0, 0, 0);
	cube->SetPosition(x, y + .15f, z);
	cube->SetScale(0.075f, .05f, 0.075f);
	cube->Draw();
}

void Application::botol3(float x, float y, float z) {
	cube->SetColor(0, 128, 128);
	cube->SetPosition(x, y, z);
	cube->SetScale(0.15f, .125f, 0.075f);
	cube->Draw();
	cube->SetColor(0, 0, 0);
	cube->SetPosition( x + .0375f, y + 0.09f, z);
	cube->SetScale(0.075f, .05f, 0.075f);
	cube->Draw();
}

void Application::kursi(float x, float y, float z) {
	cube->SetColor(108.0f, 103.0f, 96.0f);
	cube->SetPosition(x, y, z);
	cube->SetScale(0.5f, 0.1f, 0.5f);
	cube->Draw();

	cube->SetPosition(x, y + 0.4f, z);
	cube->SetScale(0.3f, 0.8f, 0.3f);
	cube->Draw();

	cube->SetColor(247.0f, 222.0f, 178.0f);
	cube->SetPosition(x, y + 0.85f, z);
	cube->SetScale(0.5f, 0.1f, 0.5f);
	cube->Draw();

	cube->SetColor(247.0f, 222.0f, 178.0f);
	cube->SetPosition(x, y + 1.f, z + 0.2f);
	cube->SetScale(0.5f, 0.4f, 0.1f);
	cube->Draw();
}

void Application::ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);


	// zoom camera
	// -----------
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		if (fovy < 90) {
			fovy += 0.0001f;
		}
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		if (fovy > 0) {
			fovy -= 0.0001f;
		}
	}

	// update camera movement 
	// -------------
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		MoveCamera(CAMERA_SPEED);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		MoveCamera(-CAMERA_SPEED);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		StrafeCamera(-CAMERA_SPEED);
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		StrafeCamera(CAMERA_SPEED);
	}

	// update camera rotation
	// ----------------------
	double mouseX, mouseY;
	double midX = screenWidth / 2;
	double midY = screenHeight / 2;
	float angleY = 0.0f;
	float angleZ = 0.0f;

	// Get mouse position
	glfwGetCursorPos(window, &mouseX, &mouseY);
	if ((mouseX == midX) && (mouseY == midY)) {
		return;
	}

	// Set mouse position
	glfwSetCursorPos(window, midX, midY);

	// Get the direction from the mouse cursor, set a resonable maneuvering speed
	angleY = (float)((midX - mouseX)) / 1000;
	angleZ = (float)((midY - mouseY)) / 1000;

	// The higher the value is the faster the camera looks around.
	viewCamY += angleZ * 2;

	// limit the rotation around the x-axis
	if ((viewCamY - posCamY) > 8) {
		viewCamY = posCamY + 8;
	}
	if ((viewCamY - posCamY) < -8) {
		viewCamY = posCamY - 8;
	}
	RotateCamera(-angleY);
}

void Application::MoveCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	// forward positive cameraspeed and backward negative -cameraspeed.
	posCamX = posCamX + x * speed;
	posCamZ = posCamZ + z * speed;
	viewCamX = viewCamX + x * speed;
	viewCamZ = viewCamZ + z * speed;
}

void Application::StrafeCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	float orthoX = -z;
	float orthoZ = x;

	// left positive cameraspeed and right negative -cameraspeed.
	posCamX = posCamX + orthoX * speed;
	posCamZ = posCamZ + orthoZ * speed;
	viewCamX = viewCamX + orthoX * speed;
	viewCamZ = viewCamZ + orthoZ * speed;
}

void Application::RotateCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	viewCamZ = (float)(posCamZ + glm::sin(speed) * x + glm::cos(speed) * z);
	viewCamX = (float)(posCamX + glm::cos(speed) * x - glm::sin(speed) * z);
}

int main(int argc, char** argv) {
	Application app = Application();
	app.Start("Cube Example", 
		1366, 768,
		false, 
		false);
}