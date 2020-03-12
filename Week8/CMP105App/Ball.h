#pragma once
#include "Framework/GameObject.h"
#include "Framework/Vector.h"
#include <iostream>
class Ball : public GameObject
{
private:
	sf::RenderWindow* window_;
	float speed_;
	float acceleration_;
	sf::Vector2f direction_;
	sf::Vector2f target_;
	std::string name_;

public:
	// Constructor
	Ball();

	// Destructor
	~Ball();

	// Functions
	std::string getName();
	void setName(std::string name);
	void setTarget(sf::Vector2f target);
	void setWindow(sf::RenderWindow* hwnd);
	void update(float dt) override;
	void handleInput(float dt) override;
	void moveToTarget(float dt);
	void checkBouncing();
	void collisionResponse(GameObject* collider) override;
};
