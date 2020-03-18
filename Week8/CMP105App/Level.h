#pragma once

#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include "Framework/Collision.h"
#include "Ball.h"
#include "Paddle.h"
#include <string>
#include <iostream>


class Level{
public:
	Level(sf::RenderWindow* hwnd, Input* in);
	~Level();

	void handleInput(float dt);
	void update(float dt);
	void render();

private:
	// Default functions for rendering to the screen.
	void beginDraw();
	void endDraw();

	// Default variables for level class.
	sf::RenderWindow* window;
	Input* input;

	// Game Objects
	Ball ball_1_bounding_circle_;
	Ball ball_2_bounding_circle_;

	Ball ball_1_AABB_;
	Ball ball_2_AABB_;
	sf::Texture ball_texture_;

	Ball pong_;
	Paddle left_paddle_;
	Paddle right_paddle_;

};