#pragma once
#include <SFML/Graphics.hpp>

enum ButtonRole
{
	Button_Rectangle,
	Button_Circle
};

class Button
{
public:
	sf::RectangleShape m_ButtonShape;
	ButtonRole m_ButtonRole;

	Button(ButtonRole m_ButtonRole, sf::Vector2f _position, sf::Color _color);
	~Button();

	void Update();
	void ResetButton();
};

