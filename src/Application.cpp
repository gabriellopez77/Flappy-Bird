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
#include "objects/Scenery.h"
#include "ui/Death_screen.h"
#include "ui/Start_screen.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_click_callback(GLFWwindow* window, int button, int action, int mods);
void mouse_move_callback(GLFWwindow* window, double xpos, double ypos);


int main() {
	glfwInit();
	glfwInitHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwInitHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwInitHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Flappy Bird - v0.0.5", NULL, NULL);
	gb::window = window;

	// cria o contexto opengl atual
	glfwMakeContextCurrent(window);

	// ativa o V-SYNC
	glfwSwapInterval(1);

	// carrega o glad
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	// definiçoes do opengl
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// GLFW callbacks
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetMouseButtonCallback(window, mouse_click_callback);
	glfwSetCursorPosCallback(window, mouse_move_callback);

	GameObject::shader = new Shader("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");
	GameObject::shader->use();

	GameObject::texture = new Texture("assets/textures/sprites.png", GL_RGBA);
	GameObject::texture->use();
	GameObject::create();

	// reserva o espaço dos pipes
	gb::pipes.reserve(5);

	GameObject screen_background = GameObject(292, 206, 16, 16);
	screen_background.size = glm::ivec2(SCREEN_WIDTH, SCREEN_HEIGHT);
	screen_background.alpha = 0.5f;

	Player* player = new Player(2, 487, 20,20);
	gb::player = player;
	player->size = glm::ivec2(PLAYER_SIZE);
	player->position = PLAYER_START_POSITION;
	player->collSize = glm::vec2(50, 45);

	GameObject money = GameObject(194, 258, 16, 16);
	money.size = glm::ivec2(48);
	money.position = glm::ivec2 (20, 30);

	Text coinCount = Text(138, 323, 6, 7, 10);
	coinCount.size = glm::ivec2(30, 35);
	coinCount.position = glm::ivec2(71, 35);

	Text playerScore = Text(292, 158, 12, 18, 16);
	playerScore.size = glm::ivec2(48, 72);
	playerScore.position = glm::vec2((SCREEN_WIDTH / 2) - (24 * playerScore.text.size()), 120);

	Scenery scene = Scenery();
	Start_screen start_screen = Start_screen();
	Death_screen death_screen = Death_screen();


	glClearColor(0.f, 0.f, 0.f, 1.f);
	framebuffer_size_callback(window, SCREEN_WIDTH, SCREEN_HEIGHT);
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		// define o ponteiro do mouse
		gb::cursorState = glfwCreateStandardCursor(GLFW_CENTER_CURSOR);

		// delta time
		float currentFrame = static_cast<float>(glfwGetTime());
		gb::deltaTime = currentFrame - gb::lastFrame;
		gb::lastFrame = currentFrame;

		// inputs
		player->input(Action::EMPTY);


		if (!gb::started) {
			player->update();
		}

		if (!gb::paused)
			scene.update();

		if (gb::beforeStart) {
			player->position.x += 4.f;
			if (player->position.x > (SCREEN_WIDTH / 2) - 150) {
				player->position.x = (SCREEN_WIDTH / 2) -150;
				gb::beforeStart = false;
				gb::started = true;

				playerScore.text = '0';
				coinCount.text = '0';
				gb::genPipesDelay = 0.f;
				std::cout << "OPAA\n";
			}
		}
		scene.drawBackground();

		if (gb::started && !gb::paused) {
			// geração dos pipes
			gb::genPipesDelay += gb::deltaTime;
			if (gb::genPipesDelay >= PIPES_GEN_DELAY) {
				gb::pipes.push_back(new Pipes());
				gb::genPipesDelay = 0.f;
			}

			player->scoreDelay += gb::deltaTime;
			if (player->scoreDelay >= 2.f) {
				player->scoreDelay = 0.f;
				player->score++;
				playerScore.text = std::to_string(player->score);
				playerScore.position.x = (SCREEN_WIDTH / 2) - (24 * playerScore.text.size());
			}

			// atualiza os pipes e o jogador
			Pipes::updatePipes();
			player->update();

			// desenha o hub
			money.draw();
			coinCount.draw();
			playerScore.draw();

			for (auto obj : gb::pipes) {
				if (player->checkCollision(&obj->coin) && obj->coinVisible) {
					player->coinCount++;
					coinCount.text = std::to_string(player->coinCount);

					obj->coinVisible = false;
				}

				if (player->checkCollision(&obj->pipeBottom) || player->checkCollision(&obj->pipeTop)) {
					death_screen.coinCount_text->text = std::to_string(player->coinCount);
					death_screen.playerScore_text->text = std::to_string(player->score);
					gb::death_screen = true;
				}
			}

		}


		Pipes::drawPipes();
		player->draw();
		scene.drawGround();


		if (gb::onScreen) {
			screen_background.draw();
		}


		if (gb::start_screen) {
			start_screen.update();
			start_screen.draw();
		}
		if (gb::death_screen) {
			death_screen.update();
			death_screen.draw();
		}


		gb::clicked = false;
		gb::action = 0;
		glfwSetCursor(window, gb::cursorState);

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

void mouse_move_callback(GLFWwindow* window, double xpos, double ypos) {
	glfwGetCursorPos(window, &gb::mousePosX, &gb::mousePosY);
}

void mouse_click_callback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		gb::clicked = true;
		gb::action = action;

		if (!gb::started && !gb::onScreen) {
			gb::beforeStart = true;
			gb::start_screen = false;
		}

		if (!gb::paused && !gb::onScreen && !gb::beforeStart)
			((Player*)gb::player)->input(Action::JUMP);
	}
}