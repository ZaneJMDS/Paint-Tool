#include "Button.h"

// Default button setup
Button::Button(ButtonRole m_ButtonRole, sf::Vector2f _position, sf::Color _color)
{
	m_ButtonShape.setPosition(_position);
	m_ButtonShape.setSize({ 100, 50 });
	m_ButtonShape.setFillColor({ _color });
}

Button::~Button()
{
}

// when click button update
void Button::Update()
{
	switch (m_ButtonRole)
	{
	case Button_Rectangle:
		break;
	case Button_Circle:
		break;
	default:
		break;
	}
}
