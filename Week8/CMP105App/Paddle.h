#pragma once
#include "Framework/GameObject.h"
class Paddle :	public GameObject
{
private:
	sf::RenderWindow* window_;
	float speed_;
	float acceleration_;
	sf::Vector2f direction_;
	sf::Vector2f target_;
	std::string name_;
	int player_code_;

public:
	// Constructor
	Paddle();

	// Destructor
	~Paddle();

	// Functions
	std::string getName();
	void setName(std::string name);
	void setWindow(sf::RenderWindow* hwnd);
	void update(float dt) override;
	void handleInput(float dt) override;
	void setPositionX(int position_code);
	bool canMove();
};

