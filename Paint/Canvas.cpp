#include "Canvas.h"
#include <math.h>
#define PI 3.1416

// The area where the user is allowed to draw their image
Canvas::Canvas()
{
	m_render_tex = new sf::RenderTexture({ 1024, 800 }); // Render texture config
	sf::RectangleShape NewShape({ 1024, 800 }); // Canvas size
	NewShape.setFillColor(sf::Color::White); // Set starting background to white

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

// Draw current selected shape to the screen
void Canvas::DrawShape(ShapeManager* _manager, sf::RenderWindow* _window, sf::Color _color)
{
	sf::Vector2i mouse_pos = sf::Mouse::getPosition(*_window); // Draw to this location

	switch (_manager->m_current_tool)
	{
		// Draw rectangle
		case tool_rectangle:
		{
			// Default rectangle parameters
			sf::RectangleShape Rectangle;
			Rectangle.setSize({ 20.f, 20.f });
			Rectangle.setFillColor(sf::Color::Red);
			Rectangle.setPosition(sf::Vector2f(mouse_pos));

			// Draw to screen
			m_render_tex->draw(Rectangle);
			m_render_tex->display();
		}
		
			break;

		// Draw circle
		case tool_circle:
		{
			// Default circle parameters
			sf::CircleShape Circle;
			Circle.setRadius(5.f);
			Circle.setFillColor(sf::Color::Red);
			Circle.setPosition(sf::Vector2f(mouse_pos));

			// Draw to screen
			m_render_tex->draw(Circle);
			m_render_tex->display();

			// Only perform array calculations if there is more than 1 element
			if (_manager->m_line_tool_ref.getVertexCount() > 0)
			{
				_manager->m_line_tool_ref[0].position = sf::Vector2f(mouse_pos);
			}

			for (int i = 0; i < 12; i++)
			{
				sf::Vertex NewPoint;
				NewPoint.color = sf::Color::Green;

				sf::Vector2f offset;
				offset.x = 25.f * cosf((30 * i) * (PI / 180));
				offset.y = 25.f * sinf((30 * i) * (PI / 180));
				NewPoint.position = sf::Vector2f(sf::Mouse::getPosition(*_manager->m_window_ref)) + offset;
				_manager->m_line_tool_ref.append(NewPoint);
			}
		}
			
			break;
		
		// If no tool has been selected, do nothing
		default:
			break;
	}
}
