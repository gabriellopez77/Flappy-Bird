#include "../Dependencies/glad/glad.h"
#include "../Dependencies/glfw/glfw3.h"


#define STB_IMAGE_IMPLEMENTATION
#include "Shader.h"
#include "Texture.h"
#include "Player.h"
#include "GameObject.h"
#include "objects/Pipes.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);


double mousePosX;
double mousePosY;

int main() {

	glfwInit();
	glfwInitHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwInitHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwInitHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(gb::windowX, gb::windowY, "Flappy Bird - v0.0.1", NULL, NULL);

	// cria o contexto atual
	glfwMakeContextCurrent(window);

	// ativa o V-SYNC
	glfwSwapInterval(1);

	// carrega o glad
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	// callbacks
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);


	GameObject::shader = new Shader("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");
	GameObject::shader->use();

	GameObject::texture = new Texture("assets/textures/sprites.png", GL_RGBA);
	GameObject::create();

	gb::pipes.reserve(10);


	Player player = Player(63.f, 2, 487, 20, 20);
	player.size = glm::ivec2(80.f);

	GameObject background1 = GameObject(0, 0, 144, 256);
	background1.size = glm::ivec2(GAME_WIDTH, GAME_HEIGHT - 50);

	GameObject background2 = GameObject(0,0, 144, 256);
	background2.size = glm::ivec2(GAME_WIDTH, GAME_HEIGHT - 50);
	background2.position = glm::ivec2(background1.position.x + GAME_WIDTH, 0);

	GameObject ground = GameObject(292, 0, 168, 56);
	ground.size = glm::ivec2(GAME_WIDTH, 160);
	ground.position = glm::ivec2(0, GAME_HEIGHT - 160);

	GameObject money = GameObject(146, 258, 16, 16);
	money.size = glm::ivec2(36);
	money.position = glm::ivec2 (40, 40);


	float delay = 0.f;
	glClearColor(0.2f, 0.3f, 0.3f, 1.f);
	framebuffer_size_callback(window, gb::windowX, gb::windowY);
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		// delta time
		float currentFrame = static_cast<float>(glfwGetTime());
		gb::deltaTime = currentFrame - gb::lastFrame;
		gb::lastFrame = currentFrame;

		// inputs
		player.input(window);


		delay += gb::deltaTime;
		if (delay >= 3.f) {
			gb::pipes.push_back(new Pipes());
			delay = 0.f;
		}

		background1.position.x--;
		background2.position.x--;

		if (background1.position.x + GAME_WIDTH <= 0)
			background1.position.x = background2.position.x + GAME_WIDTH;

		else if (background2.position.x + GAME_WIDTH <= 0)
			background2.position.x = background1.position.x + GAME_WIDTH;

		background1.draw();
		background2.draw();
		Pipes::updatePipes();
		Pipes::drawPipes();
		player.update();
		player.draw();
		ground.draw();
		money.draw();
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int heigth) {
	glViewport(0.f, 0.f, width, heigth);
	gb::windowX = width;
	gb::windowY = heigth;

	glm::mat4 projection = glm::ortho(0.0f, (float)gb::windowX, (float)gb::windowY, 0.f, -1.0f, 1.f);
	GameObject::shader->setMat4(GameObject::shader->projectionLoc, projection);
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
	glfwGetCursorPos(window, &mousePosX, &mousePosY);
}