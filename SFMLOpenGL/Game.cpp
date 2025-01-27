#include <Game.h>

static bool flip;

Game::Game() : window(sf::VideoMode(800, 600), "OpenGL Cube Vertex and Fragment Shaders")
{

}

Game::~Game() {}

void Game::run()
{

	initialize();

	sf::Event event;

	while (isRunning) {

#if (DEBUG >= 2)
		DEBUG_MSG("Game running...");
#endif

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		render();
	}
}

/////////////////////////////////////////////////////////

typedef struct
{
	float coordinate[3];
	float color[4];
} Vertex;

Vertex vertex[NUM_VERTICES];

/*Index of Poly / Triangle to Draw */
GLubyte triangles[36] = {
		1,3,0,
		3,2,0,
		5,4,0,
		4,1,0,
		7,6,3,
		6,2,3,
		6,5,2,
		5,0,2,
		5,6,4,
		6,7,4,
		4,7,1,
		1,7,3
};

/////////////////////////////////////////////////////////

/* Variable to hold the VBO identifier and shader data */
GLuint	index, //Index to draw
		vsid, //Vertex Shader ID
		fsid, //Fragment Shader ID
		progID, //Program ID
		vbo = 1, // Vertex Buffer ID
		positionID, //Position ID
		colorID; // Color ID

/////////////////////////////////////////////////////////

void Game::initialize()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, window.getSize().x / window.getSize().y, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_CULL_FACE);

	glTranslatef(0.0f, 0.0f, -8.0f);


	isRunning = true;
	GLint isCompiled = 0;
	GLint isLinked = 0;

	glewInit();

	// Set the coordinates of our vertices
	vertex[0].coordinate[0] = -0.5f;
	vertex[0].coordinate[1] = 0.5f;
	vertex[0].coordinate[2] = 0.5f;

	vertex[1].coordinate[0] = -0.5f;
	vertex[1].coordinate[1] = -0.5f;
	vertex[1].coordinate[2] = 0.5f;

	vertex[2].coordinate[0] = 0.5f;
	vertex[2].coordinate[1] = 0.5f;
	vertex[2].coordinate[2] = 0.5f;

	vertex[3].coordinate[0] = 0.5f;
	vertex[3].coordinate[1] = -0.5f;
	vertex[3].coordinate[2] = 0.5f;

	vertex[4].coordinate[0] = -0.5f;
	vertex[4].coordinate[1] = -0.5f;
	vertex[4].coordinate[2] = -0.5f;

	vertex[5].coordinate[0] = -0.5f;
	vertex[5].coordinate[1] = 0.5f;
	vertex[5].coordinate[2] = -0.5f;

	vertex[6].coordinate[0] = 0.5f;
	vertex[6].coordinate[1] = 0.5f;
	vertex[6].coordinate[2] = -0.5f;

	vertex[7].coordinate[0] = 0.5f;
	vertex[7].coordinate[1] = -0.5f;
	vertex[7].coordinate[2] = -0.5f;


	// Set the colours of our vertices
	vertex[0].color[0] = 1.0f;
	vertex[0].color[1] = 0.0f;
	vertex[0].color[2] = 0.0f;

	vertex[1].color[0] = 1.0f;
	vertex[1].color[1] = 0.0f;
	vertex[1].color[2] = 0.0f;

	vertex[2].color[0] = 1.0f;
	vertex[2].color[1] = 0.0f;
	vertex[2].color[2] = 0.0f;

	vertex[3].color[0] = 0.0f;
	vertex[3].color[1] = 1.0f;
	vertex[3].color[2] = 0.0f;

	vertex[4].color[0] = 0.0f;
	vertex[4].color[1] = 1.0f;
	vertex[4].color[2] = 0.0f;

	vertex[5].color[0] = 0.0f;
	vertex[5].color[1] = 1.0f;
	vertex[5].color[2] = 0.0f;

	vertex[6].color[0] = 0.0f;
	vertex[6].color[1] = 0.0f;
	vertex[6].color[2] = 1.0f;

	vertex[7].color[0] = 0.0f;
	vertex[7].color[1] = 0.0f;
	vertex[7].color[2] = 1.0f;

	/* Create a new VBO using VBO id */
	glGenBuffers(1, &vbo);

	/* Bind the VBO */
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	/* Upload vertex data to GPU */
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * NUM_VERTICES, vertex, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * 36, triangles, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	/* Vertex Shader */
	std::string vs_str;
	loadShader("vert_shader.phil", vs_str);
	const char* vs_src = vs_str.c_str();

	DEBUG_MSG("Setting Up Vertex Shader");

	vsid = glCreateShader(GL_VERTEX_SHADER); //Create Shader and set ID
	glShaderSource(vsid, 1, (const GLchar**)&vs_src, NULL); // Set the shaders source
	glCompileShader(vsid); //Check that the shader compiles

	//Check is Shader Compiled
	glGetShaderiv(vsid, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_TRUE) {
		DEBUG_MSG("Vertex Shader Compiled");
		isCompiled = GL_FALSE;
	}
	else
	{
		DEBUG_MSG("ERROR: Vertex Shader Compilation Error");
	}

	/* Fragment Shader */
	std::string fs_str;
	loadShader("frag_shader.phil", fs_str); //Fragment Shader Src
	const char* fs_src{ fs_str.c_str() };

	DEBUG_MSG("Setting Up Fragment Shader");

	fsid = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fsid, 1, (const GLchar**)&fs_src, NULL);
	glCompileShader(fsid);
	//Check is Shader Compiled
	glGetShaderiv(fsid, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_TRUE) {
		DEBUG_MSG("Fragment Shader Compiled");
		isCompiled = GL_FALSE;
	}
	else
	{
		DEBUG_MSG("ERROR: Fragment Shader Compilation Error");
	}

	DEBUG_MSG("Setting Up and Linking Shader");
	progID = glCreateProgram();	//Create program in GPU
	glAttachShader(progID, vsid); //Attach Vertex Shader to Program
	glAttachShader(progID, fsid); //Attach Fragment Shader to Program
	glLinkProgram(progID);

	//Check is Shader Linked
	glGetProgramiv(progID, GL_LINK_STATUS, &isLinked);

	if (isLinked) {
		DEBUG_MSG("Shader Linked");
	}
	else
	{
		DEBUG_MSG("ERROR: Shader Link Error");
	}

	// Use Progam on GPU
	// https://www.opengl.org/sdk/docs/man/html/glUseProgram.xhtml
	glUseProgram(progID);

	// Find variables in the shader
	// https://www.khronos.org/opengles/sdk/docs/man/xhtml/glGetAttribLocation.xml
	positionID = glGetAttribLocation(progID, "sv_position");
	colorID = glGetAttribLocation(progID, "sv_color");
}

/////////////////////////////////////////////////////////

void Game::loadShader(std::string const& t_fileSrc, std::string& t_dest)
try
{
	// Open our file
	std::ifstream inputStream{ t_fileSrc };

	// If error opening file, throw exception
	if (!inputStream.is_open())
	{
		std::string msg{ "ERROR while opening shader file: " + t_fileSrc };
		throw std::exception(msg.c_str());
	}

	// Clear out the destination string
	t_dest.clear();

	std::string line;

	// Read each line of file into our shader string
	while (std::getline(inputStream, line))
	{
		t_dest += std::string(line + "\n");
	}

	// Close our file
	inputStream.close();
}
catch (const std::exception& e)
{
	std::cout << e.what();
}

/////////////////////////////////////////////////////////

void Game::update()
{
	// Decrease y-rotation
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		for (int i = 0; i < NUM_VERTICES; i++)
		{
			gpp::Vector3 tri;
			tri.x = vertex[i].coordinate[0];
			tri.y = vertex[i].coordinate[1];
			tri.z = vertex[i].coordinate[2];

			tri = gpp::Matrix3::rotationY(-0.001f) * tri;

			vertex[i].coordinate[0] = tri.x;
			vertex[i].coordinate[1] = tri.y;
			vertex[i].coordinate[2] = tri.z;
		}
	}

	// Increase y-rotation
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		for (int i = 0; i < NUM_VERTICES; i++)
		{
			gpp::Vector3 tri;
			tri.x = vertex[i].coordinate[0];
			tri.y = vertex[i].coordinate[1];
			tri.z = vertex[i].coordinate[2];

			tri = gpp::Matrix3::rotationY(0.001f) * tri;

			vertex[i].coordinate[0] = tri.x;
			vertex[i].coordinate[1] = tri.y;
			vertex[i].coordinate[2] = tri.z;
		}
	}

	// Decrease x-rotation
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		for (int i = 0; i < NUM_VERTICES; i++)
		{
			gpp::Vector3 tri;
			tri.x = vertex[i].coordinate[0];
			tri.y = vertex[i].coordinate[1];
			tri.z = vertex[i].coordinate[2];

			tri = gpp::Matrix3::rotationX(-0.001f) * tri;

			vertex[i].coordinate[0] = tri.x;
			vertex[i].coordinate[1] = tri.y;
			vertex[i].coordinate[2] = tri.z;
		}
}

	// Increase x-rotation
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		for (int i = 0; i < NUM_VERTICES; i++)
		{
			gpp::Vector3 tri;
			tri.x = vertex[i].coordinate[0];
			tri.y = vertex[i].coordinate[1];
			tri.z = vertex[i].coordinate[2];

			tri = gpp::Matrix3::rotationX(0.001f) * tri;

			vertex[i].coordinate[0] = tri.x;
			vertex[i].coordinate[1] = tri.y;
			vertex[i].coordinate[2] = tri.z;
		}
	}

	// Increase z-rotation
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		for (int i = 0; i < NUM_VERTICES; i++)
		{
			gpp::Vector3 tri;
			tri.x = vertex[i].coordinate[0];
			tri.y = vertex[i].coordinate[1];
			tri.z = vertex[i].coordinate[2];

			tri = gpp::Matrix3::rotationZ(0.001f) * tri;

			vertex[i].coordinate[0] = tri.x;
			vertex[i].coordinate[1] = tri.y;
			vertex[i].coordinate[2] = tri.z;
		}
	}

	// Decrease z-rotation
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		for (int i = 0; i < NUM_VERTICES; i++)
		{
			gpp::Vector3 tri;
			tri.x = vertex[i].coordinate[0];
			tri.y = vertex[i].coordinate[1];
			tri.z = vertex[i].coordinate[2];

			tri = gpp::Matrix3::rotationZ(-0.001f) * tri;

			vertex[i].coordinate[0] = tri.x;
			vertex[i].coordinate[1] = tri.y;
			vertex[i].coordinate[2] = tri.z;
		}
	}

	// Translate up
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		glTranslatef(0.0f, 0.001f, 0.0f);
	}

	// Translate down
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		glTranslatef(0.0f, -0.001f, 0.0f);
	}

	// Translate left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		glTranslatef(-0.001f, 0.0f, 0.0f);
	}

	// Translate right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		glTranslatef(0.001f, 0.0f, 0.0f);
	}

	// Scale down
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		for (int i = 0; i < NUM_VERTICES; i++)
		{
			gpp::Vector3 tri;
			tri.x = vertex[i].coordinate[0];
			tri.y = vertex[i].coordinate[1];
			tri.z = vertex[i].coordinate[2];

			tri = gpp::Matrix3::scale(0.9999f) * tri;

			vertex[i].coordinate[0] = tri.x;
			vertex[i].coordinate[1] = tri.y;
			vertex[i].coordinate[2] = tri.z;
		}
	}

	// Scale up
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		for (int i = 0; i < NUM_VERTICES; i++)
		{
			gpp::Vector3 tri;
			tri.x = vertex[i].coordinate[0];
			tri.y = vertex[i].coordinate[1];
			tri.z = vertex[i].coordinate[2];

			tri = gpp::Matrix3::scale(1.0001f) * tri;

			vertex[i].coordinate[0] = tri.x;
			vertex[i].coordinate[1] = tri.y;
			vertex[i].coordinate[2] = tri.z;
		}
	}

#if (DEBUG >= 2)
	DEBUG_MSG("Update up...");
#endif

}

/////////////////////////////////////////////////////////

void Game::render()
{

#if (DEBUG >= 2)
	DEBUG_MSG("Drawing...");
#endif

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);

	/*	As the data positions will be updated by the this program on the
		CPU bind the updated data to the GPU for drawing	*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * NUM_VERTICES, vertex, GL_STATIC_DRAW);

	/*	Draw Triangle from VBO	(set where to start from as VBO can contain
		model components that 'are' and 'are not' to be drawn )	*/

	// Set pointers for each parameter
	// https://www.opengl.org/sdk/docs/man4/html/glVertexAttribPointer.xhtml
	glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (float*)NULL+3);

	//Enable Arrays
	glEnableVertexAttribArray(positionID);
	glEnableVertexAttribArray(colorID);

	glUseProgram(progID); // Where program is your shader program
	GLint uniform = glGetUniformLocation(progID, "rainbow");
	glUniform3f(uniform, m_r, m_g, m_b);


	// Generate sin wave
	float sin_r{ sinf(r_theta * DEG_TO_RAD) };
	float sin_g{ sinf(g_theta * DEG_TO_RAD) };
	float sin_b{ sinf(b_theta * DEG_TO_RAD) };

	(r_theta < 360.0f) ? r_theta += 0.1f : r_theta = 0.0f;
	(g_theta < 360.0f) ? g_theta += 0.1f : g_theta = 0.0f;
	(b_theta < 360.0f) ? b_theta += 0.1f : b_theta = 0.0f;

	std::cout << m_r << std::endl;

	// Normalise to the range 0 - 1
	m_r = (1 + sin_r) / 2.0f;
	m_g = (1 + sin_g) / 2.0f;
	m_b = (1 + sin_b) / 2.0f;

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, (char*)NULL + 0);

	glUseProgram(0);

	window.display();

}

/////////////////////////////////////////////////////////

void Game::unload()
{
#if (DEBUG >= 2)
	DEBUG_MSG("Cleaning up...");
#endif
	glDeleteProgram(progID);
	glDeleteBuffers(1, &vbo);
}