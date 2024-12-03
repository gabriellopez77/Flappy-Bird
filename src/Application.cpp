#include "../Dependencies/glad/glad.h"
#include "../Dependencies/glfw/glfw3.h"


#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "Shader.h"
#include "Texture.h"
#include "Player.h"
#include "GameObject.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

const float vertices[] = {
//  positions    texture coords
	0.0f, 1.0f,	 0.0f, 1.0f,
	1.0f, 0.0f,	 1.0f, 0.0f,
	0.0f, 0.0f,	 0.0f, 0.0f,

	0.0f, 1.0f,  0.0f, 1.0f,
	1.0f, 1.0f,  1.0f, 1.0f,
	1.0f, 0.0f,  1.0f, 0.0f
};

const unsigned int indices[] = {
	0, 1, 3, 1, 2, 3
};

Shader shader;

double mousePosX;
double mousePosY;

int main() {

	glfwInit();
	glfwInitHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwInitHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwInitHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(gb::windowX, gb::windowY, "2D game", NULL, NULL);

	// cria o contexto atual
	glfwMakeContextCurrent(window);

	// ativa o V-SYNC
	glfwSwapInterval(1);

	// carrega o glad
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);


	unsigned int VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);


	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	shader = Shader("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");
	shader.use();

	framebuffer_size_callback(window, gb::windowX, gb::windowY);

	Texture texture1 = Texture("assets/textures/gojo.jpeg", GL_RGB);
	Texture texture2 = Texture("assets/textures/cobblestone.png", GL_RGBA);
	Texture texture3 = Texture("assets/textures/face.png", GL_RGBA);


	Player player = Player(&shader, 95.f);
	player.textureID = texture3.ID;

	glm::vec2 cubePosition = { 450, 250 };
	glm::vec2 cubeSize = { 100, 100 };
	GameObject* cube = new GameObject(&shader, &texture3, &cubePosition, &cubeSize, 90.f, false);
	glm::mat4 ground;

	glClearColor(0.2f, 0.3f, 0.3f, 1.f);
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);


		float currentFrame = static_cast<float>(glfwGetTime());
		gb::deltaTime = currentFrame - gb::lastFrame;
		gb::lastFrame = currentFrame;

		player.input(window);


		if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
			glm::vec2 cubePosition = { mousePosX, mousePosY };
			glm::vec2 cubeSize = { 100, 100 };
			GameObject* cube = new GameObject(&shader, &texture3, &cubePosition, &cubeSize, 90.f, false);
		}

		GameObject::checkCollisionGlobal(&player);
		cube->checkCollisionPlayer(&player);
		//std::cout << "velocity" << player.velocity.y << '\n';
		std::cout << "position " << player.position.y << '\n';

		player.update();
		player.draw();
		
		cube->update();
		cube->draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int heigth) {
	glViewport(0.f, 0.f, width, heigth);
	gb::windowX = width;
	gb::windowY = heigth;

	glm::mat4 projection = glm::ortho(0.0f, (float)gb::windowX, (float)gb::windowY, 0.f, -1.0f, 1.f);
	shader.setMat4(shader.projectionLoc, projection);
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
	glfwGetCursorPos(window, &mousePosX, &mousePosY);
}