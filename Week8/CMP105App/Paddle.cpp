#include "Paddle.h"

// Constructor
Paddle::Paddle()
{
	velocity.y = 200.0f;
}

// Destructor
Paddle::~Paddle()
{

}

// Functions
void Paddle::update(float dt)
{
}


// Funtions 
void Paddle::handleInput(float dt)
{
	if (canMove())
	{
		if (player_code_ == 0)
		{
			if (input->isKeyDown(sf::Keyboard::W)) // up
			{
				move(0 * dt, -velocity.y * dt);
			}
			else if (input->isKeyDown(sf::Keyboard::S) ) //down
			{
				move(0 * dt, velocity.y * dt);
			}
		}
		else if (player_code_ == 1)
		{
			if (input->isKeyDown(sf::Keyboard::Up)) // up
			{
				move(0 * dt, -velocity.y * dt);
			}
			else if (input->isKeyDown(sf::Keyboard::Down)) //down
			{
				move(0 * dt, velocity.y * dt);
			}
		}

	}

}

void Paddle::setWindow(sf::RenderWindow* hwnd)
{
	window_ = hwnd;
}


void Paddle::setName(std::string name)
{
	name_ = name;
}

std::string Paddle::getName()
{
	return name_;
}

void Paddle::setPositionX(int player_code)
{
	player_code_ = player_code;
	switch (player_code_)
	{
	case 0: //Left window
		this->setPosition(0, this->getPosition().y);
		break;
	case 1: //Right window
		this->setPosition(window_->getSize().x - this->getSize().x, this->getPosition().y);
		break;
	default:
		break;
	}
}

bool Paddle::canMove()
{
	//Limits right and bottom where the object can be visible
	sf::Vector2u game_limits(window_->getSize().x - this->getSize().x, window_->getSize().y - this->getSize().y);

	if (getPosition().y > game_limits.y) // Collision ground
	{
		setPosition(getPosition().x, game_limits.y);
		return false;
	}
	else if (getPosition().y < 0) // Collision top
	{
		setPosition(getPosition().x, 0);
		return false;
	}
	else
	{
		return true;
	}
}


