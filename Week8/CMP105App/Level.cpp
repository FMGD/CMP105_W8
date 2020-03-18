#include "Level.h"

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	// initialise game objects
	ball_texture_.loadFromFile("gfx/Beach_Ball.png");

	ball_1_bounding_circle_.setInput(in);
	ball_1_bounding_circle_.setWindow(hwnd);
	ball_1_bounding_circle_.setTexture(&ball_texture_);
	ball_1_bounding_circle_.setSize(sf::Vector2f(32 * 4, 32 * 4));
	ball_1_bounding_circle_.setPosition(100, 300);
	ball_1_bounding_circle_.setName("Ball1 bounding circle");

	ball_2_bounding_circle_.setInput(in);
	ball_2_bounding_circle_.setWindow(hwnd);
	ball_2_bounding_circle_.setTexture(&ball_texture_);
	ball_2_bounding_circle_.setSize(sf::Vector2f(32 * 4, 32 * 4));
	ball_2_bounding_circle_.setPosition(700, 300);
	ball_2_bounding_circle_.setName("Ball2 bounding circle");

	ball_1_AABB_.setInput(in);
	ball_1_AABB_.setWindow(hwnd);
	ball_1_AABB_.setCollisionBox(sf::FloatRect(0, 0, 32 * 4, 32 * 4));
	ball_1_AABB_.setTexture(&ball_texture_);
	ball_1_AABB_.setSize(sf::Vector2f(32 * 4, 32 * 4));
	ball_1_AABB_.setPosition(100, 500);
	ball_1_AABB_.setName("Ball1 AABB");
	ball_1_AABB_.setOutlineColor(sf::Color::Red); // For collision box
	ball_1_AABB_.setOutlineThickness(2.f);

	ball_2_AABB_.setInput(in);
	ball_2_AABB_.setWindow(hwnd);
	ball_2_AABB_.setCollisionBox(sf::FloatRect(0, 0, 32 * 4, 32 * 4));
	ball_2_AABB_.setTexture(&ball_texture_);
	ball_2_AABB_.setSize(sf::Vector2f(32 * 4, 32 * 4));
	ball_2_AABB_.setPosition(700, 500);
	ball_2_AABB_.setName("Ball2 AABB");
	ball_2_AABB_.setOutlineColor(sf::Color::Red); // For collision box
	ball_2_AABB_.setOutlineThickness(2.f);

	pong_.setInput(in);
	pong_.setWindow(hwnd);
	pong_.setCollisionBox(sf::FloatRect(0, 0, 32 * 4, 32 * 4));
	pong_.setTexture(&ball_texture_);
	pong_.setSize(sf::Vector2f(32 * 4, 32 * 4));
	pong_.setPosition(window->getSize().x/2 - right_paddle_.getSize().x/2, window->getSize().y / 2 - right_paddle_.getSize().y / 2);
	pong_.setName("Pong");
	pong_.setOutlineColor(sf::Color::Red); // For collision box
	pong_.setOutlineThickness(2.f);

	left_paddle_.setInput(in);
	left_paddle_.setWindow(hwnd);
	left_paddle_.setCollisionBox(sf::FloatRect(0, 0, 32 * 2, 32 * 8));
	left_paddle_.setSize(sf::Vector2f(32 * 2, 32 * 8));
	left_paddle_.setPositionX(0);
	left_paddle_.setPosition(0, window->getSize().y/2 - left_paddle_.getSize().y/2);
	left_paddle_.setFillColor(sf::Color::Blue);
	left_paddle_.setName("Left paddle");

	right_paddle_.setInput(in);
	right_paddle_.setWindow(hwnd);
	right_paddle_.setCollisionBox(sf::FloatRect(0, 0, 32 * 2, 32 * 8));
	right_paddle_.setSize(sf::Vector2f(32 * 2, 32 * 8));
	right_paddle_.setPositionX(1);
	right_paddle_.setPosition(window->getSize().x - right_paddle_.getSize().x, window->getSize().y / 2 - right_paddle_.getSize().y / 2);
	right_paddle_.setFillColor(sf::Color::Green);
	right_paddle_.setName("Right paddle");

	// Set init Target
	ball_2_bounding_circle_.setTarget(ball_1_bounding_circle_.getPosition());
	ball_1_bounding_circle_.setTarget(ball_2_bounding_circle_.getPosition());

	ball_2_AABB_.setTarget(ball_1_AABB_.getPosition());
	ball_1_AABB_.setTarget(ball_2_AABB_.getPosition());

}

Level::~Level()
{

}

// handle user input
void Level::handleInput(float dt)
{
	left_paddle_.handleInput(dt);
	right_paddle_.handleInput(dt);
}

// Update game objects
void Level::update(float dt)
{
	// Update Objects
	ball_1_bounding_circle_.update(dt);
	ball_2_bounding_circle_.update(dt);

	ball_1_AABB_.update(dt);
	ball_2_AABB_.update(dt);

	pong_.update(dt);
	left_paddle_.update(dt);
	right_paddle_.update(dt);


	// Check for collision
	if (Collision::checkBoundingCircle(&ball_1_bounding_circle_, &ball_2_bounding_circle_))
	{
		// Resolve collision
		ball_1_bounding_circle_.collisionResponse(&ball_2_bounding_circle_);
		ball_2_bounding_circle_.collisionResponse(&ball_1_bounding_circle_);
	}

	if (Collision::checkBoundingBox(&ball_1_AABB_, &ball_2_AABB_))
	{
		// Resolve collision
		ball_1_AABB_.collisionResponse(&ball_2_AABB_);
		ball_2_AABB_.collisionResponse(&ball_1_AABB_);
	}

	// Pong
	if (Collision::checkBoundingBox(&pong_, &left_paddle_))
	{
		// Resolve collision
		pong_.collisionResponse(&left_paddle_);
	}
	else if (Collision::checkBoundingBox(&pong_, &right_paddle_))
	{
		// Resolve collision
		pong_.collisionResponse(&right_paddle_);
	}


}

// Render level
void Level::render()
{
	beginDraw();
	window->draw(ball_1_bounding_circle_);
	window->draw(ball_2_bounding_circle_);

	window->draw(ball_1_AABB_);
	window->draw(ball_2_AABB_);

	window->draw(pong_);
	window->draw(left_paddle_);
	window->draw(right_paddle_);

	endDraw();
}

// Begins rendering to the back buffer. Background colour set to light blue.
void Level::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}