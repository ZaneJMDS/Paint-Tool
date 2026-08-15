#include "Canvas.h"
#include <math.h>
#define PI 3.1416

Canvas::Canvas()
{
	m_render_tex = new sf::RenderTexture({ 1024, 800 }); // Render texture config
	sf::RectangleShape NewShape({ 1024, 800 });
	NewShape.setFillColor(sf::Color::White);

	m_render_tex->draw(NewShape);
	m_canvas_shape.setFillColor(sf::Color::White);
	m_canvas_shape.setSize({ 1024, 800 });
	m_canvas_shape.setTexture(&m_render_tex->getTexture());
}

Canvas::~Canvas()
{
}

void Canvas::Update(sf::RenderWindow* _window)
{
	_window->draw(m_canvas_shape);
}

void Canvas::DrawShape(ShapeManager* _manager)
{
	switch (_manager->m_current_tool)
	{
		case tool_rectangle:
		{
			m_render_tex->draw(*_manager->m_rect_ref);
			m_render_tex->display();
			break;
		}

		case tool_circle:
		{
			sf::CircleShape Circle;
			Circle.setRadius(5.f);
			Circle.setFillColor(sf::Color::Red);
			Circle.setPosition(sf::Vector2f(sf::Mouse::getPosition()));

			m_render_tex->draw(Circle);
			m_render_tex->display();

			// Only perform array calculations if there is more than 1 
			if (_manager->m_line_tool_ref.getVertexCount() > 0)
			{
				_manager->m_line_tool_ref[0].position = sf::Vector2f(sf::Mouse::getPosition(*_manager->m_window_ref));
			}


			for (int i = 0; i < 12; i++)
			{
				sf::Vertex NewPoint;
				NewPoint.color = sf::Color::Green;

				sf::Vector2f offset;
				offset.x = 50.f * cosf((30 * i) * (PI / 180));
				offset.y = 50.f * sinf((30 * i) * (PI / 180));
				NewPoint.position = sf::Vector2f(sf::Mouse::getPosition(*_manager->m_window_ref)) + offset;
				_manager->m_line_tool_ref.append(NewPoint);
			}
		}
			break;

		default:
			break;
	}
}
