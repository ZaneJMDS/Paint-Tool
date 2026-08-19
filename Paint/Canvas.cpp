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
	delete m_render_tex;
}

void Canvas::Update(sf::RenderWindow* _window)
{
	_window->draw(m_canvas_shape);
}

// Draw current selected shape to the screen
void Canvas::DrawShape(ShapeManager* _manager, sf::RenderWindow* _window, sf::Vector2i _last_mouse_pos, sf::Color _color)
{
	// Check Mouse is on the canvas
	sf::Vector2i mouse_pos = sf::Mouse::getPosition(*_window); // Draw to this location
	if (mouse_pos.x < 1024 && mouse_pos.x > 0 && mouse_pos.y < 800 && mouse_pos.y > 0)
	{
		switch (_manager->m_current_tool)
		{
			// Draw rectangle
		case tool_rectangle:
		{
			// Create box shape
			sf::RectangleShape Rectangle;
			Rectangle.setSize(sf::Vector2f(mouse_pos - _last_mouse_pos));
			Rectangle.setFillColor(_color);
			Rectangle.setPosition(sf::Vector2f(_last_mouse_pos));
			Rectangle.setOutlineThickness(-thickness);

			// Draw to screen
			m_render_tex->draw(Rectangle);
			m_render_tex->display();
		}

		break;

		// Draw circle
		case tool_circle:
		{
			// Center the circle closer to the mouse
			mouse_pos.x -= thickness;
			mouse_pos.y -= thickness;

			// Create draw shape
			sf::CircleShape Circle;
			Circle.setRadius(thickness);
			Circle.setFillColor(_color);
			Circle.setPosition(sf::Vector2f(mouse_pos));

			// Draw to screen
			m_render_tex->draw(Circle);
			m_render_tex->display();
		}

		break;

		case tool_elipse:
		{
			// Create elipse shape
			sf::CircleShape Elipse;
			Elipse.setFillColor(_color);
			Elipse.setPosition(sf::Vector2f(_last_mouse_pos));
			Elipse.setRadius(5); // Have to set radius
			Elipse.setScale(sf::Vector2f(mouse_pos / 10 - _last_mouse_pos / 10));
			Elipse.setOutlineThickness(-thickness / 50.f);

			// Draw to screen
			m_render_tex->draw(Elipse);
			m_render_tex->display();
		}

		break;

		case tool_line:
		{
			// Find the distance
			float a = mouse_pos.x - _last_mouse_pos.x; // Horizontal
			float b = mouse_pos.y - _last_mouse_pos.y; // Vertical
			float distance = std::sqrt((a * a + b * b)); // Hypoteneus

			// Create line shape
			sf::RectangleShape Line;
			Line.setSize(sf::Vector2f({ distance, 0 }));
			Line.setOutlineThickness(thickness / 2.f);
			Line.setOutlineColor(_color); // OutlineColor centers the line to the mouse
			Line.setPosition(sf::Vector2f(_last_mouse_pos));

			// Calculate the angle
			float angle = ((std::atan2(b, a)) * 180) / PI; // Tan^-1 (a / b) Convert to degrees
			Line.setRotation(sf::degrees(angle));

			// Draw to screen
			m_render_tex->draw(Line);
			m_render_tex->display();
		}

		break;

		// If no tool has been selected, do nothing
		default:
			break;
		}
	}
}

// Set the canvas back to white
void Canvas::ResetCanvas()
{
	// Do the same as in the constructor but with the same render texture
	sf::RectangleShape NewShape({ 1024, 800 }); // Canvas size
	NewShape.setFillColor(sf::Color::White); // Set starting background to white

	m_render_tex->draw(NewShape);
}
