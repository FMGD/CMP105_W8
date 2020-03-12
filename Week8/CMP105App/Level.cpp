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

	ball_2_AABB_.setInput(in);
	ball_2_AABB_.setWindow(hwnd);
	ball_2_AABB_.setCollisionBox(sf::FloatRect(0, 0, 32 * 4, 32 * 4));
	ball_2_AABB_.setTexture(&ball_texture_);
	ball_2_AABB_.setSize(sf::Vector2f(32 * 4, 32 * 4));
	ball_2_AABB_.setPosition(700, 500);
	ball_2_AABB_.setName("Ball2 AABB");


	ball_2_bounding_circle_.setTarget(ball_1_bounding_circle_.getPosition());
	ball_1_bounding_circle_.setTarget(ball_2_bounding_circle_.getPosition());

	ball_2_AABB_.setTarget(ball_1_AABB_.getPosition());
	ball_1_AABB_.setTarget(ball_2_AABB_.getPosition());

	boll_1_AABB_collision_box_.setSize(sf::Vector2f(ball_1_AABB_.getCollisionBox().width, ball_1_AABB_.getCollisionBox().height));
	boll_1_AABB_collision_box_.setPosition(ball_1_AABB_.getPosition());
	boll_1_AABB_collision_box_.setOutlineColor(sf::Color::Red);
	boll_1_AABB_collision_box_.setFillColor(sf::Color::Transparent);
	boll_1_AABB_collision_box_.setOutlineThickness(2.f);

	boll_2_AABB_collision_box_.setSize(sf::Vector2f(ball_2_AABB_.getCollisionBox().width, ball_2_AABB_.getCollisionBox().height));
	boll_2_AABB_collision_box_.setPosition(ball_2_AABB_.getPosition());
	boll_2_AABB_collision_box_.setOutlineColor(sf::Color::Red);
	boll_2_AABB_collision_box_.setFillColor(sf::Color::Transparent);
	boll_2_AABB_collision_box_.setOutlineThickness(2.f);

}

Level::~Level()
{

}

// handle user input
void Level::handleInput(float dt)
{

}

// Update game objects
void Level::update(float dt)
{
	// Update Objects
	ball_1_bounding_circle_.update(dt);
	ball_2_bounding_circle_.update(dt);

	ball_1_AABB_.update(dt);
	ball_2_AABB_.update(dt);

	boll_1_AABB_collision_box_.setPosition(ball_1_AABB_.getPosition());
	boll_2_AABB_collision_box_.setPosition(ball_2_AABB_.getPosition());

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


}

// Render level
void Level::render()
{
	beginDraw();
	window->draw(ball_1_bounding_circle_);
	window->draw(ball_2_bounding_circle_);

	window->draw(ball_1_AABB_);
	window->draw(boll_1_AABB_collision_box_);
	window->draw(ball_2_AABB_);
	window->draw(boll_2_AABB_collision_box_);

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