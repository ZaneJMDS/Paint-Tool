#pragma once
#include "ShapeManager.h"

class Canvas
{
public:
	sf::RenderTexture* m_render_tex;
	sf::RectangleShape m_canvas_shape;

	Canvas();
	~Canvas();
	void Update(sf::RenderWindow* _window);
	void DrawShape(ShapeManager* _manager, sf::RenderWindow* _window, sf::Color _color);
};

