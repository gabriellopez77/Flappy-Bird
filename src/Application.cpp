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
#include "ui/Main_screen.h"
#include "ui/DressingRoom.h"
#include "ui/Hud_screen.h"
#include "ui/Pause_screen.h"
#include "ui/Start_screen.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_click_callback(GLFWwindow* window, int button, int action, int mods);
void mouse_move_callback(GLFWwindow* window, double xpos, double ypos);
void inputs();

int main() {
	glfwInit();
	glfwInitHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwInitHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwInitHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Flappy Bird - v0.0.6", NULL, NULL);
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwSetWindowPos(window, mode->width / 2 - SCREEN_WIDTH /2, mode->height / 2 - SCREEN_HEIGHT /2);
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

	GameObject screen_background(292, 206, 16, 16);
	screen_background.size = glm::ivec2(SCREEN_WIDTH, SCREEN_HEIGHT);
	screen_background.alpha = 0.5f;

	Player player = Player(2, 487, 20,20);
	gb::player = &player;
	player.size = glm::ivec2(PLAYER_SIZE);
	player.position = PLAYER_START_POSITION;
	player.collSize = glm::vec2(50, 45);

	Scenery scene;
	
	Main_screen main_screen;
	Start_screen start_screen;
	Pause pause_screen;
	Hud hud;
	DressingRoom dressingRoom_screen;
	Death_screen death_screen;

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

		// keyboard input
		inputs();


		if (gb::currentStatus != (char)stats::Started) {
			player.update();
		}

		if (gb::currentScreen != (char)ui::Death_screen && gb::currentScreen != (char)ui::Pause_screen)
			scene.update();

		if (gb::currentStatus == (char)stats::Starting) {
			player.position.x += 300.f * gb::deltaTime;
				screen_background.alpha -= 0.03f;
			if (player.position.x > (SCREEN_WIDTH / 2) - 150) {
				player.position.x = (SCREEN_WIDTH / 2) -150;
				player.velocity.y = 0.f;
				screen_background.alpha = 0.5f;
				gb::currentStatus = (char)stats::Started;
				gb::currentScreen = (int)ui::Hud_screen;

				hud.score_text.text = '0';
				hud.coinCount_text.text = '0';
				gb::genPipesDelay = 0.f;
			}
		}
		scene.drawBackground();

		if (gb::currentStatus == (char)stats::Started && !gb::paused) {
			// geração dos pipes
			gb::genPipesDelay += gb::deltaTime;
			if (gb::genPipesDelay >= PIPES_GEN_DELAY) {
				gb::pipes.push_back(new Pipes());
				gb::genPipesDelay = 0.f;
			}

			player.scoreDelay += gb::deltaTime;
			if (player.scoreDelay >= 2.f) {
				player.scoreDelay = 0.f;
				player.score++;
				hud.score_text.text = std::to_string(player.score);
				hud.score_text.position.x = (SCREEN_WIDTH / 2) - (24 * hud.score_text.text.size());
			}

			// atualiza os pipes e o jogador
			Pipes::updatePipes();
			player.update();

			for (auto obj : gb::pipes) {
				if (player.checkCollision(&obj->coin) && !obj->coinCollected) {
					player.matchCoinCount++;
					hud.coinCount_text.text = std::to_string(player.matchCoinCount);
					obj->coinCollected = true;
				}

				if (player.checkCollision(&obj->pipeBottom) || player.checkCollision(&obj->pipeTop)) {
					death_screen.coinCount_text.text = std::to_string(player.matchCoinCount);
					death_screen.playerScore_text.text = std::to_string(player.score);
					gb::currentScreen = (int)ui::Death_screen;
				}
			}

		}


		Pipes::drawPipes();
		player.draw();
		scene.drawGround();


		gb::onScreen = gb::currentScreen != (int)ui::Hud_screen;
		gb::paused = gb::currentScreen != (int)ui::Hud_screen;

		if (gb::onScreen) {
			screen_background.draw();
		}
		gb::gui[gb::currentScreen]->update();
		gb::gui[gb::currentScreen]->draw();

		gb::clicked = false;
		glfwSetCursor(window, gb::cursorState);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

bool pressed = false;
void inputs() {
	if (glfwGetKey(gb::window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		if (!pressed) {
			if (gb::currentScreen == (int)ui::Pause_screen)
				gb::currentScreen = (int)ui::Hud_screen;
			else if (gb::currentScreen == (int)ui::Hud_screen)
				gb::currentScreen = (int)ui::Pause_screen;

			pressed = true;
		}
	}
	else pressed = false;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int heigth) {
	glViewport(0.f, 0.f, static_cast<int>(width), static_cast<int>(heigth));
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

		if (!gb::paused && !gb::onScreen && gb::currentStatus == (char)stats::Started)
			((Player*)gb::player)->input(Action::JUMP);
	}
}