#include "stdafx.h"
#include "SFMLApp.h"
#include <sstream>


bool SFMLApp::OnInit(void)
{
	m_mainWindow.create(sf::VideoMode(800, 600, 32), "Insurgency");

	std::unique_ptr<GameState_MainMenu> mainMenuGameState(new GameState_MainMenu(m_mainWindow));
	registerState(std::move(mainMenuGameState), "MainMenu");
	changeState("MainMenu", nullptr);

	return true;
}