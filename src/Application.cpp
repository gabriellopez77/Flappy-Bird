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

	// impede o redimensionamento da janela
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Flappy Bird - v0.0.8", NULL, NULL);

	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	// centraliza a janela no centro da tela
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

	GameObject screen_background(292, 206, 1, 1);
	screen_background.size = glm::ivec2(SCREEN_WIDTH, SCREEN_HEIGHT);
	screen_background.alpha = BACKGROUND_ALPHA;

	GameObject white_blink(292, 224, 1, 1);
	white_blink.size = glm::ivec2(SCREEN_WIDTH, SCREEN_HEIGHT);
	white_blink.alpha = 0.f;

	Player player = Player(2, 487, 20,20);
	gb::player = &player;
	player.size = glm::ivec2(PLAYER_SIZE);
	player.position = PLAYER_START_POSITION;
	player.collision->size = glm::vec2(50, 45);
	player.collision->position.x = player.position.x + 3.f;

	Scenery scene;
	
	Main_screen main_screen;
	Start_screen start_screen;
	Pause pause_screen;
	Hud hud_screen;
	DressingRoom dressingRoom_screen;
	Death_screen death_screen;

	glClearColor(0.f, 0.f, 0.f, 0.f);
	framebuffer_size_callback(window, SCREEN_WIDTH, SCREEN_HEIGHT);

	float deathTime = 0.f;
	bool piscar = true;
	std::cout << std::boolalpha;
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		// define o ponteiro do mouse
		gb::cursorState = glfwCreateStandardCursor(GLFW_CENTER_CURSOR);

		// delta time
		float currentFrame = static_cast<float>(glfwGetTime());
		gb::deltaTime = currentFrame - gb::lastFrame;
		gb::lastFrame = currentFrame;


		inputs();

		// atualiza se o jogo nao estiver pausado
		if (gb::currentScreen != ui::Pause_screen) {
			player.update();
			scene.update();
		}


		if (gb::currentStatus == status::Dead && gb::currentScreen != ui::Death_screen) {
			deathTime += gb::deltaTime;

			if (white_blink.alpha >= 0.99f)
				piscar = false;
			float elevado = pow(white_blink.alpha, 2);

			if (piscar)
				white_blink.alpha = gb::lerp(white_blink.alpha, 1.f, gb::deltaTime * 30.f);
			else
				white_blink.alpha = gb::lerp(white_blink.alpha, 0.f, gb::deltaTime * 40.f);


			if (deathTime >= 1.f) {
				deathTime = 0.f;
				piscar = true;
				gb::changeCurrentInterface(ui::Death_screen);
			}	
		}

		scene.drawBackground();

		if (gb::currentStatus == status::Started && !gb::paused && gb::currentStatus != status::Dead) {
			// geração dos pipes
			gb::genPipesDelay += gb::deltaTime;
			if (gb::genPipesDelay >= PIPES_GEN_DELAY) {
				gb::pipes.push_back(new Pipes());
				gb::genPipesDelay = 0.f;
			}

			// atualiza os pipes
			Pipes::updatePipes();

		}
		
		// desenha os objetos
		Pipes::drawPipes();
		player.draw();
		scene.drawGround();


		gb::onScreen = gb::currentScreen != ui::Hud_screen;
		gb::paused = gb::currentScreen != ui::Hud_screen;

		
		if (gb::onScreen)
			screen_background.draw();

		if (gb::currentStatus == status::Dead)
			white_blink.draw();

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
			if (gb::currentScreen == ui::Pause_screen)
				gb::currentScreen = ui::Hud_screen;
			else if (gb::currentScreen == ui::Hud_screen)
				gb::currentScreen = ui::Pause_screen;

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
	glUniformMatrix4fv(GameObject::shader->projectionLoc, 1, GL_FALSE, &projection[0][0]);
}

void mouse_move_callback(GLFWwindow* window, double xpos, double ypos) {
	glfwGetCursorPos(window, &gb::mousePosX, &gb::mousePosY);
}

void mouse_click_callback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		gb::clicked = true;

		if (gb::currentStatus == status::Starting) {
			((Player*)gb::player)->groundCollided = false;
			((Player*)gb::player)->input(action::JUMP);
			gb::currentStatus = status::Started;
			gb::changeCurrentInterface(ui::Hud_screen);

			gb::genPipesDelay = 0.f;
		}

		if (!gb::paused && !gb::onScreen && gb::currentStatus == status::Started)
			((Player*)gb::player)->input(action::JUMP);
	}
}