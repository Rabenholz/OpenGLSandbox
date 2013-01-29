#pragma once
#include "SFML-Template/GameStateBase.h"
class GameState_MainMenu : public GameStateBase
{
public:
	GameState_MainMenu(const sf::Window& window);
	virtual ~GameState_MainMenu(void);

	virtual void OnAwake(const SFMLStateInfo* lStateInfo);
	virtual void OnUpdate(void);
	virtual void OnRender(sf::RenderTarget& target);
	virtual void OnCleanup(void);
	virtual void OnSuspend(void);
	virtual void OnResume(void);

	//SFMLEvent Overrides
	virtual void OnKeyPressed(sf::Keyboard::Key key, bool alt, bool control, bool shift);
private:
};

