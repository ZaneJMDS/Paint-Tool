#include <SFML/Graphics.hpp>
#include "Button.h"
#include "FileInterface.h"
#include "Canvas.h"
#include "ShapeManager.h"

int main()
{
    // Window Setup
    sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "Paint (Alpha)"); // Window Config
    sf::RenderWindow tool_window(sf::VideoMode({ 400, 400 }), "Colour Picker (Alpha)"); // Colour Window Config
    window.setFramerateLimit(60);
    
    // TEMP RENDER TEXTURE FOR TESTING
    sf::RenderTexture texture({ 1920, 1080 });

    // Classes
    Canvas g_CanvasManager;
    ShapeManager g_ShapeManager;
    g_ShapeManager.m_window_ref = &window;
    FileInterface g_FileInterface;

    // Circle setup
    sf::CircleShape Circle(50.f); // Starting Circle

    // Rectangle setup
    sf::RectangleShape Rectangle({ 50.f, 50.f });

    // Set up circle and rectangle tools
    g_ShapeManager.SetTools(&Circle, &Rectangle);

    // Button Setup
    const int button_count = 7;
    std::vector<Button> buttons;

    // Text and font set up
    sf::Font Font1("Arial.ttf");
    sf::Text SaveText(Font1, "Save", 24);
    sf::Text LoadText(Font1, "Load", 24);
    sf::Text ResetCanvas(Font1, "Reset Canvas", 24);
    sf::Text CircleText(Font1, "Draw", 24);
    sf::Text SquareText(Font1, "Boxes", 24);
    sf::Text EllipseText(Font1, "Ellipses", 24);
    sf::Text LineText(Font1, "Lines", 24);
    sf::Text text_array[button_count] = { SaveText, LoadText, ResetCanvas, CircleText, SquareText, EllipseText, LineText };

    // Create menu buttons
    for (int i = 0; i < button_count; i++)
    {
        // Makes button with role, location, and colour 
        Button NewButton((ButtonRole)i, { 100.f * i, 800.f }, sf::Color::Green);
        text_array[i].setPosition({ 100.f * i, 800.f });
        buttons.push_back(NewButton);
    }

    // Only grab input while the window is open 
    while (window.isOpen())
    {
        sf::Text ThicknessText(Font1, "Thickness: " + std::to_string(g_CanvasManager.GetThickness()), 24);

        // If an event happened
        while (const std::optional event = window.pollEvent())
        {
            // Need to tell windows to close
            if (event->is<sf::Event::Closed>()) { window.close(); }

            // Catch the resize events
            if (const auto* resized = event->getIf<sf::Event::Resized>())
            {
                // update the view to the new size of the window
                sf::FloatRect visibleArea({ 0.f, 0.f }, sf::Vector2f(resized->size));
                window.setView(sf::View(visibleArea));
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
                if (g_CanvasManager.GetThickness() > 5.f)
                {
                    if ((mouse->delta) < 0) { g_CanvasManager.SetThickness(g_CanvasManager.GetThickness() - 5.f); } // Scroll down decreases size
                }

                // Check the size isn't too large
                if (g_CanvasManager.GetThickness() < 100.f)
                {
                    if ((mouse->delta) > 0) { g_CanvasManager.SetThickness(g_CanvasManager.GetThickness() + 5.f); } // Scroll up increases size
                }
            }

            // Left mb pressed
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                // Draw in canvas
                g_CanvasManager.DrawShape(&g_ShapeManager, &window, sf::Color::Red); // Pass in window to get mouse location

                // Button Menu
                for (int i = 0; i < button_count; i++)
                {
                    if (buttons[i].m_ButtonShape.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
                    {
                        // Save file by clicking the button
                        if (i == 0)
                        {
                            g_FileInterface.SaveFile(&texture);
                        }

                        // Open file by clicking the button
                        if (i == 1)
                        {
                            g_FileInterface.LoadFile(&texture);
                        }

                        if (i == 2)
                        {
                            g_CanvasManager.ResetCanvas();
                        }
                        
                        // Draw
                        if (i == 3)
                        {
                            g_ShapeManager.SwapTool(tool_circle);
                        }

                        // Boxes
                        if (i == 4)
                        {
                            g_ShapeManager.SwapTool(tool_rectangle);
                        }

                        // Elipses
                        if (i == 5)
                        {
                            g_ShapeManager.SwapTool(tool_circle);
                        }

                        // Lines
                        if (i == 6)
                        {
                            g_ShapeManager.SwapTool(tool_rectangle);
                        }
                    }
                }
            }

            // Save file with (ctrl + s)
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl)) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)))
            {
                g_FileInterface.SaveFile(&texture);
            }

            // Open file with (ctrl + o)
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl)) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::O)))
            {
                g_FileInterface.LoadFile(&texture);
            }

            // Tool selectors
            // Draw
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))
            {
                g_ShapeManager.SwapTool(tool_circle);
            }

            // Boxes
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))
            {
                g_ShapeManager.SwapTool(tool_rectangle);
            }

            // Elipses
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))
            {
                g_ShapeManager.SwapTool(tool_circle);
            }

            // Lines
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4))
            {
                g_ShapeManager.SwapTool(tool_line);
            }
        }

        // Window updates
        g_ShapeManager.Update(&window); // Update before clear
        window.clear();
        g_CanvasManager.Update(&window); // Update after clear
        
        // Draw buttons
        for (int i = 0; i < button_count; i++)
        {
            window.draw(buttons[i].m_ButtonShape);
            window.draw(text_array[i]);
        }
        
        ThicknessText.setPosition({ 100.f * button_count, 800.f });
        window.draw(ThicknessText);

        window.display();

        // Tool window updates
        tool_window.clear();
        tool_window.display();
    }

    return 0;
}