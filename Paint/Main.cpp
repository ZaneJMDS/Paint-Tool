#include <SFML/Graphics.hpp>
#include "Button.h"
#include "FileInterface.h"
#include "Canvas.h"
#include "ShapeManager.h"

int main()
{
    // Setup
    sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "Paint (Alpha)"); // Window Config
    sf::RenderWindow tool_window(sf::VideoMode({ 400, 400 }), "Tool Window (Alpha)"); // Tool Window Config
    
    // Classes
    Canvas g_CanvasManager;
    ShapeManager g_ShapeManager;
    g_ShapeManager.m_window_ref = &window;
    FileInterface g_FileInterface;

    // Circle setup
    sf::CircleShape Circle(50.f); // Starting Circle
    Circle.setFillColor(sf::Color::Green); // Starting colour
    Circle.setPosition({ -100, -100 }); // Hide starting circle

    // Rectangle setup
    sf::RectangleShape Rectangle({ 50.f, 50.f });
    Rectangle.setFillColor(sf::Color::Yellow);
    Rectangle.setPosition({ 100, 100 });

    g_ShapeManager.SetTools(&Circle, &Rectangle);

    sf::Color color_array[2] = { sf::Color::Red, sf::Color::Blue };

    // Buttons
    int button_count = 2;
    std::vector<Button> buttons;

    // Create 2 menu buttons
    for (int i = 0; i < button_count; i++)
    {
        // Makes button with role, location, and colour 
        Button NewButton((ButtonRole)i, { 200.f * i, 0.f }, color_array[i]);
        buttons.push_back(NewButton);
    }

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) { window.close(); }

            // Catch the resize events
            if (const auto* resized = event->getIf<sf::Event::Resized>())
            {
                // update the view to the new size of the window
                sf::FloatRect visibleArea({ 0.f, 0.f }, sf::Vector2f(resized->size));
                window.setView(sf::View(visibleArea));
            }

            // If user has clicked in the window
            if (const auto* MouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                // If user clicked the left MB
                if (MouseButtonPressed->button == sf::Mouse::Button::Left)
                {
                    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
                }
            }

            // Mouse button released
            if (const auto* MouseButtonReleased = event->getIf<sf::Event::MouseButtonReleased>()) 
            {
                // If user released the left MB
                if (MouseButtonReleased->button == sf::Mouse::Button::Left)
                {
                    // Only perform array calculations if there is more than 1 
                    if(g_ShapeManager.m_line_tool_ref.getVertexCount() > 0)
                    {
                        g_ShapeManager.m_line_tool_ref[0].position = sf::Vector2f(sf::Mouse::getPosition(window));
                    }
                }
            }

            // Change shape size from scroll wheel
            if (auto* mouse = event->getIf<sf::Event::MouseWheelScrolled>())
            {
                // Check the size isn't too small
                if (Circle.getRadius() > 5)
                {
                    if ((mouse->delta) < 0) { Circle.setRadius(Circle.getRadius() - 5.f); } // Scroll down decreases size
                }

                // Check the size isn't too large
                if (Circle.getRadius() < 100)
                {
                    if ((mouse->delta) > 0) { Circle.setRadius(Circle.getRadius() + 5.f); } // Scroll up increases size
                }
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                g_CanvasManager.DrawShape(&g_ShapeManager);
            }
        }

        // Draw buttons
        for (int i = 0; i < button_count; i++)
        {
            window.draw(buttons[i].m_ButtonShape);
        }

        // Window updates
        // g_ShapeManager.Update(&window); BREAKPOINT ERROR
        window.clear();
        g_CanvasManager.Update(&window);
        window.draw(Circle);
        window.display();

        // Tool window updates
        tool_window.clear();
        tool_window.draw(Rectangle);
        tool_window.display();
    }
}