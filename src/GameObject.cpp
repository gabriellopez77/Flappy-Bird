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
	position += force * gb::deltaTime;


	// fricao do ar
	//if (force.x > 0) {
	//	force.x += -0.5f;
	//	if (force.x < 0)
	//		force.x = 0;
	//}

	//if (force.x < 0) {
	//	force.x += 0.5f;
	//	if (force.x > 0)
	//		force.x = 0;
	//}
	//if (force.y > 0) {
	//	force.y += -0.5f;
	//	if (force.y < 0)
	//		force.y = 0;
	//}

	//if (force.y < 0) {
	//	force.y += 0.5f;
	//	if (force.y > 0)
	//		force.y = 0;
	//}

	// define a velocidade maxima
	if (force.x > maxSpeed)
		force.x = maxSpeed;

	else if (force.x < -maxSpeed)
		force.x = -maxSpeed;

	// bordas
	if (position.x > gb::windowX - 100) {
		position.x = gb::windowX - 100;
		force.x = -force.x;
	}

	else if (position.x < 0) {
		position.x = 0;
		force.x = -force.x;
	}

	if (position.y > gb::windowY - 100) {
		position.y = gb::windowY - 100;
		force.y = -force.y;
	}

	else if (position.y < 0) {
		position.y = 0;
		force.y = -force.y;
	}

	model = glm::mat4(1.f);
	model = glm::translate(model, glm::vec3(position, 0.f));
	model = glm::scale(model, glm::vec3(size, 0.f));
}

void GameObject::checkCollisionPlayer(Player* obj) {
	hipo = sqrt(powf(obj->position.x - position.x, 2) + powf(obj->position.y - position.y, 2));

	if (hipo <= this->radius || hipo <= obj->radius) {
		glm::vec2 tempforce = force;
		force = obj->force;
		obj->force = tempforce;
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