#include "ShapeManager.h"

ShapeManager::ShapeManager()
{
	m_current_tool = tool_circle; // Starting tool
	sf::Vertex a;
	a.color = sf::Color::Green; 
	a.position = sf::Vector2f(0, 0);
	m_line_tool_ref.append(a);
	m_line_tool_ref.setPrimitiveType(sf::PrimitiveType::TriangleFan);
}

ShapeManager::~ShapeManager()
{
}

// Set shapes for circle and rectangle tools
void ShapeManager::SetTools(sf::CircleShape* _circle_ref, sf::RectangleShape* _rect_ref, sf::CircleShape* _elipse_ref)
{
	m_circle_ref = _circle_ref;
	m_rect_ref = _rect_ref;
	m_elipse_ref = _elipse_ref;
}

void ShapeManager::Update(sf::RenderWindow* _window)
{
	sf::Vector2f mouse_pos = (sf::Vector2f)sf::Mouse::getPosition(*_window);

	switch (m_current_tool)
	{
	case tool_rectangle:
		m_rect_ref->setPosition(mouse_pos);
		break;

	case tool_circle:
		m_circle_ref->setPosition(mouse_pos);
		break;

	case tool_elipse:
		m_elipse_ref->setPosition(mouse_pos);
		break;

	case tool_line:
		break;

	case tool_colour:
		break;

	default:
		break;
	}
}
