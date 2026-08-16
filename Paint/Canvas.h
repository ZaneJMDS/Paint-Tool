#pragma once
#include "ShapeManager.h"

class Canvas
{
public:
	sf::RenderTexture* m_render_tex;
	sf::RectangleShape m_canvas_shape;
	float thickness = 10.f;

	Canvas();
	~Canvas();
	void Update(sf::RenderWindow* _window);
	void DrawShape(ShapeManager* _manager, sf::RenderWindow* _window, sf::Color _color);
	void ResetCanvas();
	int GetThickness() { return thickness; }
	void SetThickness(float _thickness) { thickness = _thickness; }
};

