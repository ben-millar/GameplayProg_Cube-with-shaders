#ifndef GAME_H
#define GAME_H

#include <Debug.h>

#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <GL/wglew.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include <Vector3.h>
#include <Matrix3.h>

class Game
{
public:
	Game();
	~Game();
	void run();
private:
	sf::Window window;
	bool isRunning = false;
	void initialize();
	void loadShader(std::string const& t_fileSrc, std::string& t_dest);
	void update();
	void render();
	void unload();

	sf::Clock clock;
	sf::Time elapsed;

	float rotationAngle = 0.0f;
};

const int NUM_VERTICES{ 8 };

#endif