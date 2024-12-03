#include "GameObject.h"

std::vector<GameObject*> GameObject::objects = std::vector<GameObject*>();

GameObject::GameObject(Shader* shader, Texture* texture, glm::vec2* position, glm::vec2* size, float radius, bool isColored) :
	shader(shader),
	texture(texture),
	position(*position),
	size(*size) {

	this->radius = radius;
	this->isColored = isColored;

	objects.push_back(this);
}

void GameObject::draw() {
	shader->setBool(shader->isColoredLoc, isColored);
	shader->setMat4(shader->modelLoc, model);

	texture->use();
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
void GameObject::update() {

	force += mass * gravity;

	velocity += force * mass * gb::deltaTime;
	position += velocity * gb::deltaTime;


	//fricao do ar
	if (velocity.x > 0) {
		velocity.x += -0.5f;
		if (velocity.x < 0)
			velocity.x = 0;
	}

	if (velocity.x < 0) {
		velocity.x += 0.5f;
		if (velocity.x > 0)
			velocity.x = 0;
	}
	if (velocity.y > 0) {
		velocity.y += -0.5f;
		if (velocity.y < 0)
			velocity.y = 0;
	}

	if (velocity.y < 0) {
		velocity.y += 0.5f;
		if (velocity.y > 0)
			velocity.y = 0;
	}

	// define a velocidade maxima
	if (velocity.x > maxSpeed)
		velocity.x = maxSpeed;

	else if (velocity.x < -maxSpeed)
		velocity.x = -maxSpeed;

	// bordas
	if (position.x > gb::windowX - 100) {
		position.x = gb::windowX - 100;
		velocity.x = -velocity.x;
	}

	if (position.x < 0) {
		position.x = 0;
		velocity.x = -velocity.x;
	}

	if (position.y > gb::windowY - 100) {
		position.y = gb::windowY - 100;
		velocity.y += -velocity.y;
	}

	if (position.y < 0) {
		position.y = 0;
		velocity.y = -velocity.y;
	}

	model = glm::mat4(1.f);
	model = glm::translate(model, glm::vec3(position, 0.f));
	model = glm::scale(model, glm::vec3(size, 0.f));
}

void GameObject::checkCollisionPlayer(Player* obj) {
	hipo = sqrt(powf(obj->position.x - position.x, 2) + powf(obj->position.y - position.y, 2));

	if (hipo <= this->radius || hipo <= obj->radius) {
		glm::vec2 velNorm = glm::normalize(velocity);
		glm::vec2 objVelNorm = glm::normalize(obj->velocity);

		if (velNorm == objVelNorm) {
			std::cout << "E IGUAL\n";
		}
		glm::vec2 tempVelocity = velocity;
		velocity = obj->velocity;
		obj->velocity = tempVelocity;


	}
}


void GameObject::checkCollision(GameObject* obj) {
	hipo = sqrt(powf(obj->position.x - position.x, 2) + powf(obj->position.y - position.y, 2));

	if (hipo <= this->radius || hipo <= obj->radius) {
		glm::vec2 tempforce = velocity;
		velocity = obj->force;
		obj->velocity = tempforce;
	}
}

void GameObject::checkCollisionGlobal(Player* player) {
	for (int i = 0; i < GameObject::objects.size(); i++) {
		for (int j = i + 1; j < GameObject::objects.size(); j++) {
			GameObject::objects[i]->checkCollisionPlayer(player);
			GameObject::objects[i]->checkCollision(GameObject::objects[j]);

		}
	}
}