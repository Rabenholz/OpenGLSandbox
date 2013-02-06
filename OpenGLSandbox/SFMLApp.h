#pragma once

#include <GL/glew.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <vector>
#include <map>
#include <memory>

#include "SFML-Template/SFMLEvent.h"
#include "SFML-Template/GameStateBase.h"
#include "SFML-Template/SoundManager.h"
#include "SFML-Template/TextureManager.h"
#include "SFML-Template/FontManager.h"

#include "GameState_MainMenu.h"


class SFMLApp
{
public:
	SFMLApp(void);
	~SFMLApp(void);

	int OnExecute(void);

	bool OnInit(void);
	void OnEvent(sf::Event& Event);
    void OnUpdate(void);
    void OnRender(void);
    void OnCleanup(void);

	void registerState(GameStateBase::ptr gameState, std::string stateID);
	void unregisterState(std::string stateID); //can invalidate active states
	void changeState(std::string stateID, SFMLStateInfo* stateInfo); //replaces the current state
	void pushState(std::string stateID, SFMLStateInfo* stateInfo);
	void popState(void);
	void removeState(std::string stateID);

	GameStateBase* getState(std::string stateID);

	//message handling functions
	void decipherMessage(SFMLStateMessage* message);
	void OnClose(void);
	void OnResize(int width, int height);

private:
	bool m_running;
	sf::Window m_mainWindow;
	std::vector<GameStateBase*> m_states;
	std::map<std::string, GameStateBase::ptr> m_registeredGameStates;

	static GLfloat cubeVertexArray[360];
	static GLushort cubeElementArray[36];
	static GLfloat squareVertexArray[84];
	static GLushort squareElementArray[12];
	GLuint m_vertexBuffer;
	GLuint m_elementBuffer;
	GLuint m_vertexShader1, m_fragmentShader1, m_program1;
	GLint m_position1, m_color1, m_offset1;
	GLfloat m_timerVal;
	GLint m_timer;

	GLfloat m_perspectiveMatrix[16];
};

