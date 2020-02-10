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

	const double DEG_TO_RAD{ 3.14159265 / 180.0f };

	float m_r, m_g, m_b;

	float r_theta{ 240.0f };
	float g_theta{ 120.0f };
	float b_theta{ 0.0f };

	float rotationAngle = 0.0f;
};

const int NUM_VERTICES{ 8 };

#endif