#include <iostream>
#include <cmath>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "stb_image.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Load Models
#include "SOIL2/SOIL2.h"


// Other includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "Texture.h"

// Function prototypes
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();

// Window dimensions
const GLuint WIDTH = 1920, HEIGHT = 1080;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Camera
Camera  camera(glm::vec3(50.0f, 50.0f, 50.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;
// Light attributes
glm::vec3 SpotPos(5.0f, 5.0f, -5.0f);
glm::vec3 SpotDir(0.0f, 1.0f, 0.0f);
bool active;

// Positions of the point lights
glm::vec3 pointLightPositions[] = {
	glm::vec3(-41.20f, 23.8f, -32.5f),
	glm::vec3(-58.43f, 23.8f, -32.5f),
	glm::vec3(-41.20f, 23.8f, 32.5f),
	glm::vec3(-58.43f, 23.8f, 32.5f)
};

glm::vec3 PosIni(-7.0f, 6.9f, 16.5f);
glm::vec3 PosIni2(-50.0f, 24.5f, 0.0f);

// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame
// Keyframes
float posX = PosIni.x, posY = PosIni.y, posZ = PosIni.z, rotRodIzq = 0;
float posX2 = PosIni2.x, posY2 = PosIni2.y, posZ2 = PosIni2.z;
float ERotZ = 0.0f;
float ARotY	= 0;
float rotPuerta = 0.0f;
#define MAX_FRAMES 20
#define MAX_FRAMES2 25
int i_max_steps = 128;
int i_max_steps2 = 128;
int i_curr_steps = 0;
int i_curr_steps2 = 0;
int P_caso =  0;

typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float posX;		//Variable para PosicionX
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para PosicionZ
	float incX;		//Variable para IncrementoX
	float incY;		//Variable para IncrementoY
	float incZ;		//Variable para IncrementoZ
	float rotRodIzq;
	float rotInc;

}FRAME;

typedef struct _frame2
{
	//Variables para GUARDAR Key Frames
	float posX;		//Variable para PosicionX
	float posZ;		//Variable para PosicionZ
	float incX;		//Variable para IncrementoX
	float incZ;		//Variable para IncrementoZ

	float ERotZ;
	float EIncRotZ;

	float ARotY;
	float AIncRotX;

}FRAME2;
FRAME KeyFrame[MAX_FRAMES];
FRAME2 KeyFrame2[MAX_FRAMES2];
int FrameIndex = 0;			//introducir datos
int FrameIndex2 = 0;			//introducir datos
bool play = true;
bool play2 = true;
bool P_Play = false;
bool puerta = false;
int playIndex = 0;
int playIndex2 = 0;
float rotTren = 0.0f;

void saveFrame2(void)
{
	//KeyFrame2 0
	KeyFrame2[FrameIndex2].posX = posX2;
	KeyFrame2[FrameIndex2].posZ = posZ2;
	KeyFrame2[FrameIndex2].ARotY = ARotY;
	KeyFrame2[FrameIndex2].ERotZ = ERotZ;
	FrameIndex2++;

	//KeyFrame2 0
	KeyFrame2[FrameIndex2].posX = -50.34f;
	KeyFrame2[FrameIndex2].posZ = 2.58f;
	KeyFrame2[FrameIndex2].ARotY = 0.0f;
	KeyFrame2[FrameIndex2].ERotZ = KeyFrame2[FrameIndex2 - 1].ERotZ + 180.0f;
	FrameIndex2++;

	//KeyFrame2 0
	KeyFrame2[FrameIndex2].posX = -51.33;
	KeyFrame2[FrameIndex2].posZ = 5.0f;
	KeyFrame2[FrameIndex2].ARotY = 0.0f;
	KeyFrame2[FrameIndex2].ERotZ = KeyFrame2[FrameIndex2 - 1].ERotZ + 180.0f;
	FrameIndex2++;

	//KeyFrame2 0
	KeyFrame2[FrameIndex2].posX = -52.92f;
	KeyFrame2[FrameIndex2].posZ = 7.07f;
	KeyFrame2[FrameIndex2].ARotY = 0.0f;
	KeyFrame2[FrameIndex2].ERotZ = KeyFrame2[FrameIndex2 - 1].ERotZ + 180.0f;
	FrameIndex2++;

	//KeyFrame2 0
	KeyFrame2[FrameIndex2].posX = -55.0f;
	KeyFrame2[FrameIndex2].posZ = 8.66f;
	KeyFrame2[FrameIndex2].ARotY = 0.0f;
	KeyFrame2[FrameIndex2].ERotZ = KeyFrame2[FrameIndex2 - 1].ERotZ + 180.0f;
	FrameIndex2++;

	//KeyFrame2 0
	KeyFrame2[FrameIndex2].posX = -57.41f;
	KeyFrame2[FrameIndex2].posZ = 9.65f;
	KeyFrame2[FrameIndex2].ARotY = 0.0f;
	KeyFrame2[FrameIndex2].ERotZ = KeyFrame2[FrameIndex2 - 1].ERotZ + 180.0f;
	FrameIndex2++;

	//KeyFrame2 0
	KeyFrame2[FrameIndex2].posX = -60.0f;
	KeyFrame2[FrameIndex2].posZ = 10.0f;
	KeyFrame2[FrameIndex2].ARotY = 0.0f;
	KeyFrame2[FrameIndex2].ERotZ = KeyFrame2[FrameIndex2 - 1].ERotZ + 180.0f;
	FrameIndex2++;

	//KeyFrame2 0
	KeyFrame2[FrameIndex2].posX = -62.58f;
	KeyFrame2[FrameIndex2].posZ = 9.65f;
	KeyFrame2[FrameIndex2].ARotY = 0.0f;
	KeyFrame2[FrameIndex2].ERotZ = KeyFrame2[FrameIndex2 - 1].ERotZ + 180.0f;
	FrameIndex2++;
	
	//KeyFrame2 0
	KeyFrame2[FrameIndex2].posX = -65.0f;
	KeyFrame2[FrameIndex2].posZ = 8.66f;
	KeyFrame2[FrameIndex2].ARotY = 0.0f;
	KeyFrame2[FrameIndex2].ERotZ = KeyFrame2[FrameIndex2 - 1].ERotZ + 180.0f;
	FrameIndex2++;

	//KeyFrame2 0
	KeyFrame2[FrameIndex2].posX = -67.07f;
	KeyFrame2[FrameIndex2].posZ = 7.07f;
	KeyFrame2[FrameIndex2].ARotY = 0.0f;
	KeyFrame2[FrameIndex2].ERotZ = KeyFrame2[FrameIndex2 - 1].ERotZ + 180.0f;
	FrameIndex2++;

	//KeyFrame2 0
	KeyFrame2[FrameIndex2].posX = -68.66f;
	KeyFrame2[FrameIndex2].posZ = -5.0f;
	KeyFrame2[FrameIndex2].ARotY = 0.0f;
	KeyFrame2[FrameIndex2].ERotZ = KeyFrame2[FrameIndex2 - 1].ERotZ + 180.0f;
	FrameIndex2++;

	//KeyFrame2 0
	KeyFrame2[FrameIndex2].posX = -69.65;
	KeyFrame2[FrameIndex2].posZ = 2.58f;
	KeyFrame2[FrameIndex2].ARotY = KeyFrame2[FrameIndex2 - 1].ARotY + 60.0f;
	KeyFrame2[FrameIndex2].ERotZ = KeyFrame2[FrameIndex2 - 1].ERotZ + 180.0f;
	FrameIndex2++;

	//KeyFrame2 0
	KeyFrame2[FrameIndex2].posX = -70.0f;
	KeyFrame2[FrameIndex2].posZ = 0.0f;	
	KeyFrame2[FrameIndex2].ARotY = KeyFrame2[FrameIndex2 - 1].ARotY + 60.0f;
	KeyFrame2[FrameIndex2].ERotZ = KeyFrame2[FrameIndex2 - 1].ERotZ + 180.0f;
	FrameIndex2++;

	//KeyFrame2 0
	KeyFrame2[FrameIndex2].posX = -69.65;
	KeyFrame2[FrameIndex2].posZ = -2.58f;
	KeyFrame2[FrameIndex2].ARotY = KeyFrame2[FrameIndex2 - 1].ARotY + 60.0f;
	KeyFrame2[FrameIndex2].ERotZ = KeyFrame2[FrameIndex2 - 1].ERotZ + 180.0f;
	FrameIndex2++;

	//KeyFrame2 0
	KeyFrame2[FrameIndex2].posX = -68.66f;
	KeyFrame2[FrameIndex2].posZ = -5.0f;
	KeyFrame2[FrameIndex2].ARotY = 180.0f;
	KeyFrame2[FrameIndex2].ERotZ = KeyFrame2[FrameIndex2 - 1].ERotZ + 180.0f;
	FrameIndex2++;

	//KeyFrame2 0
	KeyFrame2[FrameIndex2].posX = -67.07f;
	KeyFrame2[FrameIndex2].posZ = -7.07f;
	KeyFrame2[FrameIndex2].ARotY = 180.0f;
	KeyFrame2[FrameIndex2].ERotZ = KeyFrame2[FrameIndex2 - 1].ERotZ + 180.0f;
	FrameIndex2++;

	//KeyFrame2 0
	KeyFrame2[FrameIndex2].posX = -65.0f;
	KeyFrame2[FrameIndex2].posZ = -8.66f;
	KeyFrame2[FrameIndex2].ARotY = 180.0f;
	KeyFrame2[FrameIndex2].ERotZ = KeyFrame2[FrameIndex2 - 1].ERotZ + 180.0f;
	FrameIndex2++;

	//KeyFrame2 0
	KeyFrame2[FrameIndex2].posX = -62.58f;
	KeyFrame2[FrameIndex2].posZ = -9.65f;
	KeyFrame2[FrameIndex2].ARotY = 180.0f;
	KeyFrame2[FrameIndex2].ERotZ = KeyFrame2[FrameIndex2 - 1].ERotZ + 180.0f;
	FrameIndex2++;

	//KeyFrame2 0
	KeyFrame2[FrameIndex2].posX = -60.0f;
	KeyFrame2[FrameIndex2].posZ = -10.0f;
	KeyFrame2[FrameIndex2].ARotY = 180.0f;
	KeyFrame2[FrameIndex2].ERotZ = KeyFrame2[FrameIndex2 - 1].ERotZ + 180.0f;
	FrameIndex2++;

	//KeyFrame2 0
	KeyFrame2[FrameIndex2].posX = -57.41f;
	KeyFrame2[FrameIndex2].posZ = -9.65f;
	KeyFrame2[FrameIndex2].ARotY = 180.0f;
	KeyFrame2[FrameIndex2].ERotZ = KeyFrame2[FrameIndex2 - 1].ERotZ + 180.0f;
	FrameIndex2++;

	//KeyFrame2 0
	KeyFrame2[FrameIndex2].posX = -55.0f;
	KeyFrame2[FrameIndex2].posZ = -52.92f;
	KeyFrame2[FrameIndex2].ARotY = 180.0f;
	KeyFrame2[FrameIndex2].ERotZ = KeyFrame2[FrameIndex2 - 1].ERotZ + 180.0f;
	FrameIndex2++;

	//KeyFrame2 0
	KeyFrame2[FrameIndex2].posX = -52.92f;
	KeyFrame2[FrameIndex2].posZ = -7.07f;
	KeyFrame2[FrameIndex2].ARotY = KeyFrame2[FrameIndex2 - 1].ARotY + 60.0f;
	KeyFrame2[FrameIndex2].ERotZ = KeyFrame2[FrameIndex2 - 1].ERotZ + 180.0f;
	FrameIndex2++;

	//KeyFrame2 0
	KeyFrame2[FrameIndex2].posX = -51.33f;
	KeyFrame2[FrameIndex2].posZ = -5.0f;
	KeyFrame2[FrameIndex2].ARotY = KeyFrame2[FrameIndex2 - 1].ARotY + 60.0f;
	KeyFrame2[FrameIndex2].ERotZ = KeyFrame2[FrameIndex2 - 1].ERotZ + 180.0f;
	FrameIndex2++;

	//KeyFrame2 0
	KeyFrame2[FrameIndex2].posX = -50.34f;
	KeyFrame2[FrameIndex2].posZ = -2.58f;
	KeyFrame2[FrameIndex2].ARotY = KeyFrame2[FrameIndex2 - 1].ARotY + 60.0f;
	KeyFrame2[FrameIndex2].ERotZ = KeyFrame2[FrameIndex2 - 1].ERotZ + 180.0f;
	FrameIndex2++;
}
void saveFrame(void)
{
	//keyframe 0
	KeyFrame[FrameIndex].posZ = posZ;
	KeyFrame[FrameIndex].rotRodIzq = 20.0f;

	FrameIndex++;
	//keyframe 
	KeyFrame[FrameIndex].posZ = KeyFrame[FrameIndex - 1].posZ + 2;
	KeyFrame[FrameIndex].rotRodIzq = -20.0f;
	FrameIndex++;
	//keyframe 
	KeyFrame[FrameIndex].posZ = KeyFrame[FrameIndex - 1].posZ + 2;
	KeyFrame[FrameIndex].rotRodIzq = 20.0f;
	FrameIndex++;
	//keyframe 
	KeyFrame[FrameIndex].posZ = KeyFrame[FrameIndex - 1].posZ + 2;
	KeyFrame[FrameIndex].rotRodIzq = -20.0f;
	FrameIndex++;

	//keyframe
	KeyFrame[FrameIndex].posZ = KeyFrame[FrameIndex - 1].posZ + 2;
	KeyFrame[FrameIndex].rotRodIzq = 20.0f;
	FrameIndex++;
	//keyframe 
	KeyFrame[FrameIndex].posZ = KeyFrame[FrameIndex - 1].posZ + 2;
	KeyFrame[FrameIndex].rotRodIzq = -20.0f;
	FrameIndex++;
	//keyframe 
	KeyFrame[FrameIndex].posZ = KeyFrame[FrameIndex - 1].posZ + 2;
	KeyFrame[FrameIndex].rotRodIzq = 20.0f;
	FrameIndex++;
	//keyframe 
	KeyFrame[FrameIndex].posZ = KeyFrame[FrameIndex - 1].posZ + 2;
	KeyFrame[FrameIndex].rotRodIzq = -20.0f;
	FrameIndex++;

	//keyframe
	KeyFrame[FrameIndex].posZ = KeyFrame[FrameIndex - 1].posZ + 2;
	KeyFrame[FrameIndex].rotRodIzq = 20.0f;
	FrameIndex++;
	//keyframe 
	KeyFrame[FrameIndex].posZ = KeyFrame[FrameIndex - 1].posZ + 2;
	KeyFrame[FrameIndex].rotRodIzq = -20.0f;
	FrameIndex++;
	//keyframe 
	KeyFrame[FrameIndex].posZ = KeyFrame[FrameIndex - 1].posZ + 2;
	KeyFrame[FrameIndex].rotRodIzq = 20.0f;
	FrameIndex++;
	//keyframe 
	KeyFrame[FrameIndex].posZ = KeyFrame[FrameIndex - 1].posZ + 2;
	KeyFrame[FrameIndex].rotRodIzq = -20.0f;
	FrameIndex++;

	//keyframe
	KeyFrame[FrameIndex].posZ = KeyFrame[FrameIndex - 1].posZ + 2;
	KeyFrame[FrameIndex].rotRodIzq = 20.0f;
	FrameIndex++;
	//keyframe 
	KeyFrame[FrameIndex].posZ = KeyFrame[FrameIndex - 1].posZ + 2;
	KeyFrame[FrameIndex].rotRodIzq = -20.0f;
	FrameIndex++;
	//keyframe 
	KeyFrame[FrameIndex].posZ = KeyFrame[FrameIndex - 1].posZ + 2;
	KeyFrame[FrameIndex].rotRodIzq = 20.0f;
	FrameIndex++;
	//keyframe 
	KeyFrame[FrameIndex].posZ = KeyFrame[FrameIndex - 1].posZ + 2;
	KeyFrame[FrameIndex].rotRodIzq = -20.0f;
	FrameIndex++;
}

void resetElements2(void)
{
	posX2 = KeyFrame2[0].posX;
	posZ2 = KeyFrame2[0].posZ;
	ARotY = KeyFrame2[0].ARotY;
	ERotZ =  KeyFrame2[0].ERotZ;

}
void resetElements(void)
{
	posZ = KeyFrame[0].posZ;
	rotRodIzq = 0;

}

void interpolation2(void)
{
	KeyFrame2[playIndex2].incX = (KeyFrame2[playIndex2 + 1].posX - KeyFrame2[playIndex2].posX) / i_max_steps2;
	KeyFrame2[playIndex2].incZ = (KeyFrame2[playIndex2 + 1].posX - KeyFrame2[playIndex2].posX) / i_max_steps2;
	KeyFrame2[playIndex2].EIncRotZ = (KeyFrame2[playIndex2 + 1].ERotZ - KeyFrame2[playIndex2].ERotZ) / i_max_steps2;
	KeyFrame2[playIndex2].AIncRotX = (KeyFrame2[playIndex2 + 1].ARotY - KeyFrame2[playIndex2].ARotY) / i_max_steps2;

}
void interpolation(void)
{///borrar inncesaarias

	KeyFrame[playIndex].incX = (KeyFrame[playIndex + 1].posX - KeyFrame[playIndex].posX) / i_max_steps;
	KeyFrame[playIndex].incY = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;
	KeyFrame[playIndex].incZ = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;
	KeyFrame[playIndex].rotInc = (KeyFrame[playIndex + 1].rotRodIzq - KeyFrame[playIndex].rotRodIzq) / i_max_steps;
}

void animacion2()
{

	//Movimiento del personaje

	if (i_curr_steps2 >= i_max_steps2) //end of animation between frames?
	{
		playIndex2++;
		if (playIndex2 > FrameIndex2 - 2)	//end of total animation?
		{
			printf("termina anim\n");
			playIndex2 = 0;
			play = false;
		}
		else //Next frame interpolations
		{
			i_curr_steps2 = 0; //Reset counter
			//Interpolation
			interpolation2();
		}
	}
	else
	{
		//Draw animation
		posX2 += KeyFrame2[playIndex2].incX;
		posZ2 += KeyFrame2[playIndex2].incZ;
		ERotZ += KeyFrame2[playIndex2].EIncRotZ;
		ARotY += KeyFrame2[playIndex2].AIncRotX;		
		i_curr_steps2++;
	}
}
void animacion()
{

	//Movimiento del personaje

	if (i_curr_steps >= i_max_steps) //end of animation between frames?
	{
		playIndex++;
		if (playIndex > FrameIndex - 2)	//end of total animation?
		{
			printf("termina anim\n");
			playIndex = 0;
			play = false;
		}
		else //Next frame interpolations
		{
			i_curr_steps = 0; //Reset counter
			//Interpolation
			interpolation();
		}
	}
	else
	{
		//Draw animation
		posX += KeyFrame[playIndex].incX;
		posY += KeyFrame[playIndex].incY;
		posZ += KeyFrame[playIndex].incZ;

		rotRodIzq += KeyFrame[playIndex].rotInc;
		i_curr_steps++;
	}
}

int main()
{
	// Init GLFW
	glfwInit();

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "ProyectoFinalEQ7", nullptr, nullptr);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	// Set the required callback functions
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Define the viewport dimensions
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	GLfloat skyboxVertices[] = {
		// Positions
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
	};


	Shader lightingShader("Shaders/lighting.vs", "Shaders/lighting.frag");
	Shader lampShader("Shaders/lamp.vs", "Shaders/lamp.frag");
	Shader SkyBoxshader("Shaders/SkyBox.vs", "Shaders/SkyBox.frag");
	Shader animShader("Shaders/anim.vs", "Shaders/anim.fs");

	//Modelos pesados
	//Model ATM((char*)"Models/Ambiente/ATM/ATM.obj");
	//Model CESTO((char*)"Models/Ambiente/Cesto/Cesto.obj");
	//Model BASKET((char*)"Models/Ambiente/Balones/B_Basket.obj");
	//Model ARCADE((char*)"Models/Ambiente/Arcade/Arcade.obj");
	//Model SILLON((char*)"Models/Ambiente/Sillon/Sillon.obj");
	//Model TRICICLO((char*)"Models/Ambiente/Triciclo/Triciclo.obj");
	

	Model BICI((char*)"Models/Ambiente/Bici/Bici.obj");
	Model BOTE((char*)"Models/Ambiente/BoteBasura/BoteBasura.obj");
	//Model CAJA((char*)"Models/Ambiente/CajaRegistradora/CajaRegistradora.obj");
	Model UNO((char*)"Models/Ambiente/CajaUno/CajaUno.obj");
	Model EDIFICIO((char*)"Models/Ambiente/Edificio/Edificio.obj");
	Model TECHO((char*)"Models/Ambiente/Techo/Techo.obj");
	Model EXTINTOR((char*)"Models/Ambiente/Extintor/Extintor.obj");
	Model LAMPARA1((char*)"Models/Ambiente/Lampara/Lampara1.obj");
	Model LAMPARA2((char*)"Models/Ambiente/Lampara/Lampara2.obj");
	Model PUERTA((char*)"Models/Ambiente/Puerta/Puerta.obj");
	Model RECEPCION((char*)"Models/Ambiente/Recepcion/Recepcion.obj");
	Model SILLONL((char*)"Models/Ambiente/SillonL/SillonL.obj");
	Model TERMINAL((char*)"Models/Ambiente/Terminal/Terminal.obj");
	//Model PARKING((char*)"Models/Ambiente/Parking/Parking.obj");
	//Model CALLE((char*)"Models/Ambiente/Calle/Calle.obj");
	//Model FAROS((char*)"Models/Ambiente/Calle/Faros.obj");
	//Model ENTORNO((char*)"Models/Ambiente/Locales/Local.obj");
	//Model ENTORNO2((char*)"Models/Ambiente/Locales/Local3.obj");
	//Model ENTORNO3((char*)"Models/Ambiente/Locales/Local4.obj");
	//Model ENTORNO4((char*)"Models/Ambiente/Locales/Local5.obj");

	//Model Baguette((char*)"Models/Ambiente/Models/Baguette/Baguette.obj");
	//Model Bandeja((char*)"Models/Ambiente/Models/Bandeja/Bandeja.obj");
	//Model Bascula((char*)"Models/Ambiente/Models/Bascula/Bascula.obj");
	//Model Flecha((char*)"Models/Ambiente/Models/Bascula/FlechaBascula.obj");
	//Model Batidora((char*)"Models/Ambiente/Models/Batidora/Batidora.obj");
	//Model Caja2((char*)"Models/Ambiente/Models/CajaRegistradora2/CajaRegistradora.obj");
	//Model Candelabro((char*)"Models/Ambiente/Models/Candelabro/Candelabro.obj");
	//Model Panaderia((char*)"Models/Ambiente/Models/Casa/CasaTotal.obj");
	//Model Estante((char*)"Models/Ambiente/Models/Estante/Estante1.obj");
	//Model Estante2((char*)"Models/Ambiente/Models/Estante/Estantes2.obj");
	//Model Horno((char*)"Models/Ambiente/Models/Horno/Horno.obj");
	//Model Lena((char*)"Models/Ambiente/Models/Lena/Lena.obj");
	//Model Mesa((char*)"Models/Ambiente/Models/Mesa/Mesa.obj");
	//Model Mesa2((char*)"Models/Ambiente/Models/Mesa/MesaMadera.obj");
	//Model Pala((char*)"Models/Ambiente/Models/Pala/Palat.obj");
	//Model Pan((char*)"Models/Ambiente/Models/Pan/Pan.obj");
	//Model Piso2((char*)"Models/Ambiente/Models/Piso/Piso.obj");
	//Model Plato((char*)"Models/Ambiente/Models/PlatilloBatidora/PlatilloBatidora.obj");
	//Model PuertaTrasera((char*)"Models/Ambiente/Models/PuertaTrasera/PuertaTrasera.obj");
	//Model Repisa1((char*)"Models/Ambiente/Models/Repisa/Repisa1.obj");
	//Model Repisa2((char*)"Models/Ambiente/Models/Repisa/Repisa2.obj");
	//Model Repisa3((char*)"Models/Ambiente/Models/Repisa/Repisa3.obj");
	//Model Repisa4((char*)"Models/Ambiente/Models/Repisa/Repisa4.obj");
	//Model Torre((char*)"Models/Ambiente/Models/TorreEiffele/TorreEiffele.obj");
	//Model Ventanas((char*)"Models/Ambiente/Models/Ventanas/Ventanas.obj");

	//Model barra((char*)"Models/Ambiente/Modelos/Barra/barra.obj");
	//Model caja3((char*)"Models/Ambiente/Modelos/Caja_registradora/caja_registradora.obj");
	//Model cafe((char*)"Models/Ambiente/Modelos/Fachada/fachada.obj");
	//Model florero((char*)"Models/Ambiente/Modelos/Florero/florero.obj");
	//Model lamp((char*)"Models/Ambiente/Modelos/Lamparas/lampara.obj");
	//Model mext((char*)"Models/Ambiente/Modelos/Mesa_sillas_exterior/mesa_sillas_ext.obj");
	//Model mint((char*)"Models/Ambiente/Modelos/Mesas_sillas_interior/mesas_sillas_int.obj");
	//Model mueble((char*)"Models/Ambiente/Modelos/Mueble/mueble.obj");
	//Model piso((char*)"Models/Ambiente/Modelos/Piso/piso.obj");
	//Model pisoc((char*)"Models/Ambiente/Modelos/Piso/PisoCalle.obj");
	//Model swich((char*)"Models/Ambiente/Modelos/Swich/swich.obj");
	//Model taza((char*)"Models/Ambiente/Modelos/Taza/taza.obj");



	//MODELO ROBOT PARA KEYFRAMES
	Model ROBOT_T((char*)"Models/Ambiente/Robot/Robot_T.obj");
	Model ROBOT_C((char*)"Models/Ambiente/Robot/Robot_C.obj");
	Model ROBOT_BI((char*)"Models/Ambiente/Robot/Robot_BI.obj");
	Model ROBOT_BD((char*)"Models/Ambiente/Robot/Robot_BD.obj");
	Model ROBOT_PD((char*)"Models/Ambiente/Robot/Robot_PD.obj");
	Model ROBOT_PI((char*)"Models/Ambiente/Robot/Robot_PI.obj");

	//MODELO AVIONETA PARA KEYFRAMES
	Model A_AVIONETA((char*)"Models/Ambiente/Avioneta/Avioneta_K.obj");
	Model A_Helice((char*)"Models/Ambiente/Avioneta/Helice.obj");
	

	//TREN
	Model T_MQ((char*)"Models/Ambiente/Tren/Tren_Maq.obj");
	Model T_v1((char*)"Models/Ambiente/Tren/Tren_v1.obj");
	Model T_v2((char*)"Models/Ambiente/Tren/Tren_v2.obj");
	Model T_v3((char*)"Models/Ambiente/Tren/Tren_v3.obj");


	// First, set the container's VAO (and VBO)
	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Set texture units
	lightingShader.Use();
	//SkyBox
	GLuint skyboxVBO, skyboxVAO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

	// Load textures
	vector<const GLchar*> faces;
	faces.push_back("SkyBox/right.jpg");
	faces.push_back("SkyBox/left.jpg");
	faces.push_back("SkyBox/top.jpg");
	faces.push_back("SkyBox/bottom.jpg");
	faces.push_back("SkyBox/back.jpg");
	faces.push_back("SkyBox/front.jpg");

	GLuint cubemapTexture = TextureLoading::LoadCubemap(faces);

	glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 1000.0f);

	saveFrame();
	saveFrame2();


	// Game loop
	while (!glfwWindowShouldClose(window))
	{

		// Calculate deltatime of current frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		DoMovement();
		if (play) {
			animacion();
		}
		else {
			resetElements();
			//First Interpolation				
			//interpolation();

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		if (play2) {
			animacion2();
		}
		else {
			resetElements2();
			//First Interpolation				
			//interpolation();

			play2 = true;
			playIndex2 = 0;
			i_curr_steps2 = 0;
		}

		// Clear the colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// OpenGL options
		glEnable(GL_DEPTH_TEST);

		// Use cooresponding shader when setting uniforms/drawing objects
		lightingShader.Use();

		glUniform1i(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 0);
		glUniform1i(glGetUniformLocation(lightingShader.Program, "material.specular"), 1);

		GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
		glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);


		// Directional light
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 0.3f, 0.3f, 0.3f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.3f, 0.3f, 0.3f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 0.4f, 0.4f, 0.4f);


		// Point light 
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 1.0f, 1.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.22f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.20f);



		// Point light 2
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].ambient"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].diffuse"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].specular"), 1.0f, 1.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].linear"), 0.22f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].quadratic"), 0.20f);

		// Point light 3
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].position"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].ambient"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].diffuse"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].specular"), 1.0f, 1.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].linear"), 0.22f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].quadratic"), 0.20f);

		// Point light 4
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].position"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].ambient"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].diffuse"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].specular"), 1.0f, 1.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].linear"), 0.22f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].quadratic"), 0.20f);

		//SpotLight
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), SpotPos.x, SpotPos.y, SpotPos.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), SpotDir.x, SpotDir.y, SpotDir.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.14f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.07f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(12.0f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(15.0f)));

		// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 16.0f);

		// Create camera transformations
		glm::mat4 view;
		view = camera.GetViewMatrix();

		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
		GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glm::mat4 model(1);
		//Carga de modelo 
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		
		
		
		//CESTO.Draw(lightingShader);
		//BASKET.Draw(lightingShader);
		//ARCADE.Draw(lightingShader);
		//SILLON.Draw(lightingShader);
		//ATM.Draw(lightingShader);
		//TRICICLO.Draw(lightingShader);



		BICI.Draw(lightingShader);
		BOTE.Draw(lightingShader);
		//CAJA.Draw(lightingShader);
		EDIFICIO.Draw(lightingShader);
		TECHO.Draw(lightingShader);
		EXTINTOR.Draw(lightingShader);
		LAMPARA1.Draw(lightingShader);
		LAMPARA2.Draw(lightingShader);
		RECEPCION.Draw(lightingShader);
		SILLONL.Draw(lightingShader);
		TERMINAL.Draw(lightingShader);
		//PARKING.Draw(lightingShader);
		//CALLE.Draw(lightingShader);
		//FAROS.Draw(lightingShader);

		//Baguette.Draw(lightingShader);
		//Bandeja.Draw(lightingShader);
		//Bascula.Draw(lightingShader);
		//Flecha.Draw(lightingShader);
		//Batidora.Draw(lightingShader);
		//Caja2.Draw(lightingShader);
		//Candelabro.Draw(lightingShader);
		//Panaderia.Draw(lightingShader);
		//Estante.Draw(lightingShader);
		//Estante2.Draw(lightingShader);
		//Horno.Draw(lightingShader);
		//Lena.Draw(lightingShader);
		//Mesa.Draw(lightingShader);
		//Mesa2.Draw(lightingShader);
		//Pala.Draw(lightingShader);
		//Pan.Draw(lightingShader);
		//Piso2.Draw(lightingShader);
		//Plato.Draw(lightingShader);
		//PuertaTrasera.Draw(lightingShader);
		//Repisa1.Draw(lightingShader);
		//Repisa2.Draw(lightingShader);
		//Repisa3.Draw(lightingShader);
		//Repisa4.Draw(lightingShader);
		//Torre.Draw(lightingShader);
		//Ventanas.Draw(lightingShader);


		//barra.Draw(lightingShader);
		//caja3.Draw(lightingShader);
		//cafe.Draw(lightingShader);
		//florero.Draw(lightingShader);
		//lamp.Draw(lightingShader);
		//mext.Draw(lightingShader);
		//mint.Draw(lightingShader);
		//mueble.Draw(lightingShader);
		//piso.Draw(lightingShader);
		//swich.Draw(lightingShader);
		//pisoc.Draw(lightingShader);
		//taza.Draw(lightingShader);
		//ENTORNO.Draw(lightingShader);
		//ENTORNO2.Draw(lightingShader);
		//ENTORNO3.Draw(lightingShader);
		//ENTORNO4.Draw(lightingShader);


		//modelos repetidos
		model = glm::translate(model, glm::vec3(-22.7f, 7.35f, 27.67f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		UNO.Draw(lightingShader);


		model = glm::mat4(1);
		glm::mat4 tmp = model = glm::translate(model, glm::vec3(-14.88f, 5.4f, 56.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		UNO.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-5.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		UNO.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-5.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		UNO.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-5.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		UNO.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-5.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		UNO.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-5.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		UNO.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-5.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		UNO.Draw(lightingShader);


		model = glm::translate(tmp, glm::vec3(0.0f, 3.9f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		T_v3.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-1.5f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		T_v2.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-1.5f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		T_v1.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-1.5f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		T_MQ.Draw(lightingShader);

		model = glm::translate(model, glm::vec3(-1.5f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		T_v3.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-1.5f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		T_v2.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-1.5f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		T_v1.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-1.5f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		T_MQ.Draw(lightingShader);

		model = glm::translate(model, glm::vec3(-1.5f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		T_v3.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-1.5f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		T_v2.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-1.5f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		T_v1.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-1.5f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		T_MQ.Draw(lightingShader);

		model = glm::translate(model, glm::vec3(-1.5f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		T_v3.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-1.5f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		T_v2.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-1.5f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		T_v1.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-1.5f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		T_MQ.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-1.5f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		T_v3.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-1.5f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		T_v2.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-1.5f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		T_v1.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-1.5f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		T_MQ.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-1.5f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		T_v3.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-1.5f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		T_v2.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-1.5f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		T_v1.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-1.5f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		T_MQ.Draw(lightingShader);


		model = glm::translate(tmp, glm::vec3(0.0f, 9.1f, -1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		A_AVIONETA.Draw(lightingShader);
		A_Helice.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-4.5f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		A_AVIONETA.Draw(lightingShader);
		A_Helice.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-4.5f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		A_AVIONETA.Draw(lightingShader);
		A_Helice.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-4.5f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		A_AVIONETA.Draw(lightingShader);
		A_Helice.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-4.5f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		A_AVIONETA.Draw(lightingShader);
		A_Helice.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-4.5f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		A_AVIONETA.Draw(lightingShader);
		A_Helice.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(-4.5f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		A_AVIONETA.Draw(lightingShader);
		A_Helice.Draw(lightingShader);


		////////////////////////////////////////////////////////////////////////
		model = glm::mat4(1);
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		tmp = model = glm::translate(model, glm::vec3(14.88f, 5.4f, 56.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		UNO.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(5.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		UNO.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(5.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		UNO.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(5.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		UNO.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(5.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		UNO.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(5.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		UNO.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(5.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		UNO.Draw(lightingShader);


		model = glm::translate(tmp, glm::vec3(0.0f, 3.9f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		T_v3.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(1.5f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		T_v2.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(1.5f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		T_v1.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(1.5f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		T_MQ.Draw(lightingShader);

		model = glm::translate(model, glm::vec3(1.5f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		T_v3.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(1.5f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		T_v2.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(1.5f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		T_v1.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(1.5f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		T_MQ.Draw(lightingShader);

		model = glm::translate(model, glm::vec3(1.5f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		T_v3.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(1.5f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		T_v2.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(1.5f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		T_v1.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(1.5f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		T_MQ.Draw(lightingShader);

		model = glm::translate(model, glm::vec3(1.5f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		T_v3.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(1.5f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		T_v2.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(1.5f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		T_v1.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(1.5f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		T_MQ.Draw(lightingShader);

		model = glm::translate(model, glm::vec3(1.5f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		T_v3.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(1.5f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		T_v2.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(1.5f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		T_v1.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(1.5f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		T_MQ.Draw(lightingShader);

		model = glm::translate(model, glm::vec3(1.5f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		T_v3.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(1.5f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		T_v2.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(1.5f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		T_v1.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(1.5f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		T_MQ.Draw(lightingShader);


		model = glm::translate(tmp, glm::vec3(0.0f, 9.1f, -1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		A_AVIONETA.Draw(lightingShader);
		A_Helice.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(4.5f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		A_AVIONETA.Draw(lightingShader);
		A_Helice.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(4.5f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		A_AVIONETA.Draw(lightingShader);
		A_Helice.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(4.5f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		A_AVIONETA.Draw(lightingShader);
		A_Helice.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(4.5f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		A_AVIONETA.Draw(lightingShader);
		A_Helice.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(4.5f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		A_AVIONETA.Draw(lightingShader);
		A_Helice.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(4.5f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0.0f);
		A_AVIONETA.Draw(lightingShader);
		A_Helice.Draw(lightingShader);



		//////////////////PUERTA//////////////////
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-12.5f, 0.6f, -5.3f));
		model = glm::rotate(model, glm::radians(-rotPuerta), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
		PUERTA.Draw(lightingShader);

		
		////////////////////TREN/////////////////////
		tmp = glm::mat4(1.0f); //Temp
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-77.0f + 15*cos(glm::radians(-rotTren)), 0.6f, -19.75f + 15 * sin(glm::radians(-rotTren))));
		model = glm::rotate(model, glm::radians(rotTren), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
		T_MQ.Draw(lightingShader);
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-77.0f + 15 * cos(glm::radians(-rotTren+10)), 0.6f, -19.75f + 15 * sin(glm::radians(-rotTren+10))));
		model = glm::rotate(model, glm::radians(rotTren-10), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
		T_v1.Draw(lightingShader);
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-77.0f + 15 * cos(glm::radians(-rotTren+20)), 0.6f, -19.75f + 15 * sin(glm::radians(-rotTren+20))));
		model = glm::rotate(model, glm::radians(rotTren-20), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
		T_v2.Draw(lightingShader);
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-77.0f + 15 * cos(glm::radians(-rotTren+30)), 0.6f, -19.75f + 15 * sin(glm::radians(-rotTren+30))));
		model = glm::rotate(model, glm::radians(rotTren-30), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
		T_v3.Draw(lightingShader);


		////////////////ROBOT/////////////////////////
		tmp = glm::mat4(1.0f); //Temp
		model = tmp;
		model = glm::translate(model, glm::vec3(posX, posY, posZ));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		ROBOT_T.Draw(lightingShader);
		//Pierna Izq
		model = glm::translate(tmp, glm::vec3(0.15f, -0.9f, -0.05f));
		model = glm::translate(model, glm::vec3(posX, posY, posZ));
		model = glm::rotate(model, glm::radians(-rotRodIzq), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
		ROBOT_PI.Draw(lightingShader);
		//Pierna Der
		model = glm::translate(tmp, glm::vec3(-0.15f, -0.9f, -0.05f));
		model = glm::translate(model, glm::vec3(posX, posY, posZ));
		model = glm::rotate(model, glm::radians(rotRodIzq), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
		ROBOT_PD.Draw(lightingShader);
		//Brazo derecho
		model = glm::translate(tmp, glm::vec3(-0.5f, 0.2f, 0.0f));
		model = glm::translate(model, glm::vec3(posX, posY, posZ));
		model = glm::rotate(model, glm::radians(-rotRodIzq), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		ROBOT_BD.Draw(lightingShader);
		//	Brazo Izquierdo
		model = glm::translate(tmp, glm::vec3(0.5f, 0.2f, 0.0f));
		model = glm::translate(model, glm::vec3(posX, posY, posZ));
		model = glm::rotate(model, glm::radians(rotRodIzq), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		ROBOT_BI.Draw(lightingShader);
		//Cabeza
		model = glm::translate(tmp, glm::vec3(0.0f, 0.6f, 0.0f));
		model = glm::translate(model, glm::vec3(posX, posY, posZ));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
		ROBOT_C.Draw(lightingShader);


		/////////////////AVIONETA////////////////////////
		model = glm::mat4(1);
		glm::mat4 tmp2 = glm::mat4(1.0f); //Temp
		tmp2 = model = glm::translate(model, glm::vec3(posX2, posY2, posZ2));
		
		model = glm::rotate(model, glm::radians(45.0f+ARotY), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		A_AVIONETA.Draw(lightingShader);
		model = glm::rotate(model, glm::radians(ERotZ), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		A_Helice.Draw(lightingShader);

		glEnable(GL_BLEND);//Activa la funcionalidad para trabajar el canal alfa
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		glDisable(GL_BLEND);  //Desactiva el canal alfa 
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);

		glBindVertexArray(0);


		animShader.Use();

		glBindVertexArray(0);



		// Draw skybox as last
		glDepthFunc(GL_LEQUAL);  // Change depth function so depth test passes when values are equal to depth buffer's content
		SkyBoxshader.Use();
		view = glm::mat4(glm::mat3(camera.GetViewMatrix()));	// Remove any translation component of the view matrix
		glUniformMatrix4fv(glGetUniformLocation(SkyBoxshader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(SkyBoxshader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		// skybox cube
		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS); // Set depth function back to default
		// Swap the screen buffers
		glfwSwapBuffers(window);
	}


	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();



	return 0;
}

// Moves/alters the camera positions based on user input
void DoMovement()
{

	// Camera controls
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
	{
		camera.ProcessKeyboard(FORWARD, deltaTime);	}

	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime);
			}

	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
	{
		camera.ProcessKeyboard(LEFT, deltaTime);
	}

	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}

	if (puerta) {
		P_Play = true;
		switch (P_caso) {
			case 0: 
				if (rotPuerta < 90.0f) {
					rotPuerta += 3.0f;
				}
				else {
					puerta = false;
					P_Play = false;
					P_caso = 1;
				}
			break;
			case 1: 
				if (rotPuerta > 0.0f) {
					rotPuerta -= 3.0f;
				}
				else {
					puerta = false;
					P_Play = false;
					P_caso = 0;
				}
			break;
		}
	}
	rotTren += 0.5f;

}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}
	
	if (keys[GLFW_KEY_SPACE])
	{
		//animacion puerta
		if (!P_Play) {
			puerta = true;
		} 
		std::cout << camera.GetPosition().x << std::endl;
		std::cout << camera.GetPosition().y << std::endl;
		std::cout << camera.GetPosition().z << std::endl;
	}
}

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}