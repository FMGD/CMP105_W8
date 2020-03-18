#include "Ball.h"

// Constructor
Ball::Ball()
{
	speed_ = 500.0f;
	acceleration_ = 500.0f;
	is_target_ = false;
	velocity = sf::Vector2f(500.0f, 0);

}

// Destructor
Ball::~Ball()
{

}

// Functions
void Ball::update(float dt)
{
	if (is_target_)
		Ball::moveToTarget(dt);
	else
		Ball::move(dt);
	Ball::checkBouncing();
}


// Funtions 
void Ball::handleInput(float dt)
{

}

void Ball::setWindow(sf::RenderWindow* hwnd)
{
	window_ = hwnd;
}

void Ball::setTarget(sf::Vector2f target)
{
	is_target_ = true;
	target_ = target;
}

void Ball::setName(std::string name)
{
	name_ = name;
}

std::string Ball::getName()
{
	return name_;
}

void Ball::moveToTarget(float dt)
{
	//Calculate direction
	direction_ = target_ - getPosition();
	direction_ = Vector::normalise(direction_);

	// Object with acceleration
	velocity += (direction_ * acceleration_) * dt; // v = u + a*t (accelerate towards the point)
	sf::Vector2f displacement = velocity * dt + 0.5f * (direction_ * acceleration_) * dt * dt; // s = ut + 1/2*a*t^2

	//Move
	setPosition(getPosition() + displacement);
}

void Ball::move(float dt)
{

	//velocity = ( speed_); // v = u  (fixed speed)
	sf::Vector2f displacement = velocity * dt; // s = v*t

	//Move
	setPosition(getPosition() + displacement);

}

void Ball::checkBouncing()
{
	//Limits right and bottom where the object can be visible
	sf::Vector2u game_limits(window_->getSize().x - this->getSize().x, window_->getSize().y - this->getSize().y);

	if (name_ != "Pong")
	{
		if (getPosition().x > game_limits.x) // Collision right
		{
			setPosition(game_limits.x, getPosition().y);
			velocity.x = -velocity.x;
			std::cout << "Bouncing right\n";
		}
		else if (getPosition().x < 0) // Collision left
		{
			setPosition(0, getPosition().y);
			velocity.x = -velocity.x;
			std::cout << "Bouncing left\n";
		}
	}
	else
	{
		if (getPosition().x > game_limits.x) // Collision right
		{
			setPosition(window_->getSize().x/2 - this->getSize().x/2, window_->getSize().y / 2 - this->getSize().y / 2);
			std::cout << "Point To player left\n";
		}
		else if (getPosition().x < 0) // Collision left
		{
			setPosition(window_->getSize().x/2 - this->getSize().x/2, window_->getSize().y / 2 - this->getSize().y / 2);
			std::cout << "Point To player right\n";
		}
	}


	if (getPosition().y > game_limits.y) // Collision ground
	{
		setPosition(getPosition().x, game_limits.y);
		velocity.y = -velocity.y;
		std::cout << "Bouncing bottom\n";
	}
	else if (getPosition().y < 0) // Collision top
	{
		setPosition(getPosition().x, 0);
		velocity.y = -velocity.y;
		std::cout << "Bouncing top\n";
	}
}

void Ball::collisionResponse(GameObject* collider)
{
	velocity.x = -velocity.x;
	std::cout << "Collision Response Success: " <<  getName() << std::endl;
}