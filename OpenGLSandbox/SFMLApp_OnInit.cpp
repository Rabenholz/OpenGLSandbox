#include "stdafx.h"
#include "SFMLApp.h"
#include <sstream>
#include <fstream>

bool SFMLApp::OnInit(void)
{
	m_mainWindow.create(sf::VideoMode(800, 600, 32), "OpenGL Sandbox");

	GLenum glewerr = glewInit();
	if(glewerr != GLEW_OK)
	{
		printf("Glew init failed\n");
	}
	glClearDepth(1.f);
	glClearColor(0.f, 0.f, 0.f, 0.f);

	//init buffer objects
	m_vertexBuffer = 0;
	glGenBuffers(1, &m_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertexArray), cubeVertexArray, GL_STATIC_DRAW);
	
	m_elementBuffer = 0;
	glGenBuffers(1, &m_elementBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeElementArray), cubeElementArray, GL_STATIC_DRAW);

	//load and compile shaders
	{
		//load text file
		std::vector<char> charBuffer;
	 std::ifstream file("shader1.glslv", std::ios_base::binary);
        if (file)
        {
            file.seekg(0, std::ios_base::end);
            std::streamsize size = file.tellg();
            if (size > 0)
            {
                file.seekg(0, std::ios_base::beg);
                charBuffer.resize(static_cast<std::size_t>(size));
                file.read(&charBuffer[0], size);
            }
            charBuffer.push_back('\0');
        }
        else
        {
            printf("Failed to load file\n");
        }
	GLint length;
    GLchar *source = &charBuffer[0];
    GLint shader_ok;

	m_vertexShader1 = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(m_vertexShader1, 1, (const GLchar**)&source, &length);

    glCompileShader(m_vertexShader1);
	glGetShaderiv(m_vertexShader1, GL_COMPILE_STATUS, &shader_ok);
		if (!shader_ok) 
		{
			printf("Failed to compile vertex shader\n");
			GLint maxLength = 0;
			glGetShaderiv(m_vertexShader1, GL_INFO_LOG_LENGTH, &maxLength);
 
			//The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(m_vertexShader1, maxLength, &maxLength, &infoLog[0]);
			printf("Log: %s\n",&infoLog[0]);
			glDeleteShader(m_vertexShader1);
		}
	}
	//load and compile fragshader
	{
		//load text file
		std::vector<char> charBuffer;
	 std::ifstream file("shader1.glslf", std::ios_base::binary);
        if (file)
        {
            file.seekg(0, std::ios_base::end);
            std::streamsize size = file.tellg();
            if (size > 0)
            {
                file.seekg(0, std::ios_base::beg);
                charBuffer.resize(static_cast<std::size_t>(size));
                file.read(&charBuffer[0], size);
            }
            charBuffer.push_back('\0');
        }
        else
        {
            printf("Failed to load file\n");
        }
	GLint length;
    GLchar *source = &charBuffer[0];
    GLint shader_ok;

	m_fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(m_fragmentShader1, 1, (const GLchar**)&source, &length);

    glCompileShader(m_fragmentShader1);
	glGetShaderiv(m_fragmentShader1, GL_COMPILE_STATUS, &shader_ok);
		if (!shader_ok) 
		{
			printf("Failed to compile fragment shader\n");
			//show_info_log(shader, glGetShaderiv, glGetShaderInfoLog);
			glDeleteShader(m_fragmentShader1);
		}
	}
	//link shaders into program
	{
		GLint program_ok;

		m_program1 = glCreateProgram();
		glAttachShader(m_program1, m_vertexShader1);
		glAttachShader(m_program1, m_fragmentShader1);
		glLinkProgram(m_program1);
		glGetProgramiv(m_program1, GL_LINK_STATUS, &program_ok);
		if (!program_ok) 
		{
			printf("Failed to link shader program:\n");
			//show_info_log(program, glGetProgramiv, glGetProgramInfoLog);
			glDeleteProgram(m_program1);
		}

		glDetachShader(m_program1, m_vertexShader1);
		glDetachShader(m_program1, m_fragmentShader1);
	}
	m_position1 = 0;
	m_color1 = 0;
	//get shader variable locations
	m_position1 = glGetAttribLocation(m_program1, "position");
	m_color1 = glGetAttribLocation(m_program1, "vexColor");

	m_timer = 0;
	m_timerVal = 0.0f;
	m_timer = glGetUniformLocation(m_program1, "timer");

	std::unique_ptr<GameState_MainMenu> mainMenuGameState(new GameState_MainMenu(m_mainWindow));
	registerState(std::move(mainMenuGameState), "MainMenu");
	changeState("MainMenu", nullptr);

	return true;
}