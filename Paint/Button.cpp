#include "Button.h"

// Default button setup
Button::Button(ButtonRole m_ButtonRole, sf::Vector2f _position, sf::Color _color)
{
	m_ButtonShape.setPosition(_position);
	m_ButtonShape.setSize({ 100, 50 });
	m_ButtonShape.setFillColor({ _color });
	m_ButtonShape.setOutlineThickness(-2.f);
	m_ButtonShape.setOutlineColor(sf::Color(128, 128, 128));
}

Button::~Button()
{
}

// when selected button update the look
void Button::Update()
{
	m_ButtonShape.setOutlineThickness(-8.f);
}

// When button isn't selected, reset
void Button::ResetButton()
{
	m_ButtonShape.setOutlineThickness(-2.f);
}
