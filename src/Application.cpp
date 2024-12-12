#include "../Dependencies/glad/glad.h"
#include "../Dependencies/glfw/glfw3.h"


#define STB_IMAGE_IMPLEMENTATION
#include "Shader.h"
#include "Texture.h"
#include "GameObject.h"
#include "Global.h"
#include "objects/Player.h"
#include "objects/Pipes.h"
#include "objects/Text.h"
#include "objects/Button.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_click_callback(GLFWwindow* window, int button, int action, int mods);


Player* player;
int main() {

	glfwInit();
	glfwInitHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwInitHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwInitHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(gb::windowX, gb::windowY, "Flappy Bird - v0.0.1", NULL, NULL);
	gb::window = window;

	// cria o contexto atual
	glfwMakeContextCurrent(window);

	// ativa o V-SYNC
	glfwSwapInterval(1);

	// carrega o glad
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	// callbacks
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetMouseButtonCallback(window, mouse_click_callback);

	GameObject::shader = new Shader("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");
	GameObject::shader->use();

	GameObject::texture = new Texture("assets/textures/sprites.png", GL_RGBA);
	GameObject::create();

	gb::pipes.reserve(5);

	GameObject title = GameObject(351, 91, 89, 24);
	title.size = glm::ivec2(300, 100);
	title.position = glm::ivec2(SCREEN_WIDTH /2 - title.size.x /2, 50);

	Button play_button = Button(354, 118, 52, 29);
	play_button.size = glm::ivec2(156, 87);
	play_button.position = glm::ivec2(SCREEN_WIDTH / 2 - play_button.size.x /2, SCREEN_HEIGHT - 300);

	player = new Player(63.f, 2, 487, 20, 20);
	player->size = glm::ivec2(PLAYER_SIZE);
	player->position = PLAYER_START_POSITION;

	GameObject background1 = GameObject(0, 0, 144, 256);
	background1.size = glm::ivec2(SCREEN_WIDTH, SCREEN_HEIGHT - 50);

	GameObject background2 = GameObject(0,0, 144, 256);
	background2.size = glm::ivec2(SCREEN_WIDTH, SCREEN_HEIGHT - 50);
	background2.position = glm::ivec2(background1.position.x + SCREEN_WIDTH, 0);

	GameObject ground1 = GameObject(292, 0, 168, 56);
	ground1.size = glm::ivec2(SCREEN_WIDTH, 160);
	ground1.position = glm::ivec2(0, SCREEN_HEIGHT - 160);

	GameObject ground2 = GameObject(292, 0, 168, 56);
	ground2.size = glm::ivec2(SCREEN_WIDTH, 160);
	ground2.position = glm::ivec2(ground1.position.x + SCREEN_WIDTH, SCREEN_HEIGHT - 160);

	GameObject money = GameObject(194, 258, 16, 16);
	money.size = glm::ivec2(48);
	money.position = glm::ivec2 (20, 30);

	Text CoinCount = Text(0,0,0,0);
	CoinCount.size = glm::ivec2(30, 37);
	CoinCount.position = glm::ivec2(71, 35);

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
		player->input(window, Action::EMPTY);

		if (!gb::paused) {
			delay += gb::deltaTime;
			if (delay >= GEN_PIPES_DELAY) {
				gb::pipes.push_back(new Pipes());
				delay = 0.f;
				player->coinCount++;
				CoinCount.text = std::to_string(player->coinCount);
			}

			background1.position.x -= BACKGROUND_SPEED;
			background2.position.x -= BACKGROUND_SPEED;

			if (background1.position.x + SCREEN_WIDTH <= 0)
				background1.position.x = background2.position.x + SCREEN_WIDTH;

			else if (background2.position.x + SCREEN_WIDTH <= 0)
				background2.position.x = background1.position.x + SCREEN_WIDTH;

			ground1.position.x -= WORLD_SPEED;
			ground2.position.x -= WORLD_SPEED;

			if (ground1.position.x + SCREEN_WIDTH <= 0)
				ground1.position.x = ground2.position.x + SCREEN_WIDTH;

			else if (ground2.position.x + SCREEN_WIDTH <= 0)
				ground2.position.x = ground1.position.x + SCREEN_WIDTH;


			Pipes::updatePipes();
			player->update();
		}

		background1.draw();
		background2.draw();
		Pipes::drawPipes();
		player->draw();
		ground1.draw();
		ground2.draw();
		money.draw();
		CoinCount.draw();


		if (gb::paused) {
			play_button.update();
			play_button.draw();
			title.draw();
		}
		gb::clicked = false;
		gb::action = 0;

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
	glfwGetCursorPos(window, &gb::mousePosX, &gb::mousePosY);
}

void mouse_click_callback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		gb::clicked = true;
		gb::action = action;

		if (!gb::paused)
			player->input(gb::window, Action::JUMP);
	}
}