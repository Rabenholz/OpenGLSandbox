#include "StdAfx.h"
#include "GameState_MainMenu.h"


GameState_MainMenu::GameState_MainMenu(const sf::Window& window)
	:GameStateBase(window)
{
}


GameState_MainMenu::~GameState_MainMenu(void)
{
}

void GameState_MainMenu::OnAwake(const SFMLStateInfo* lStateInfo)
{
}
void GameState_MainMenu::OnUpdate(void)
{
	GameStateBase::updateGUIElements();
}
void GameState_MainMenu::OnRender(sf::RenderTarget& target)
{
	GameStateBase::drawDisplayList(target);
}
void GameState_MainMenu::OnCleanup(void)
{
	GameStateBase::Cleanup();
}
void GameState_MainMenu::OnSuspend(void)
{
}
void GameState_MainMenu::OnResume(void)
{
}

void GameState_MainMenu::OnKeyPressed(sf::Keyboard::Key key, bool alt, bool control, bool shift)
{
	//switch(key)
	//{
	//}
}