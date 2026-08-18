#include <SFML/Graphics.hpp>
#include "Button.h"
#include "FileInterface.h"
#include "Canvas.h"
#include "ShapeManager.h"

int main()
{
    // Window Setup
    sf::RenderWindow window(sf::VideoMode({ 1024, 900 }), "Paint (Alpha)"); // Window Config
    sf::RenderWindow tool_window(sf::VideoMode({ 400, 200 }), "Colour Picker"); // Colour Window Config
    window.setFramerateLimit(60);
    tool_window.setFramerateLimit(60);

    // Classes
    Canvas g_CanvasManager;
    ShapeManager g_ShapeManager;
    g_ShapeManager.m_window_ref = &window;
    FileInterface g_FileInterface;

    // Circle setup
    sf::CircleShape Circle(g_CanvasManager.GetThickness());
    sf::CircleShape Circle2(g_CanvasManager.GetThickness());
    sf::CircleShape Circle3(g_CanvasManager.GetThickness());
    Circle3.setFillColor(sf::Color(0, 0, 0, 0));
    Circle3.setOutlineThickness(2.f);
    Circle3.setOutlineColor(sf::Color(128, 128, 128));

    // Rectangle setup
    sf::RectangleShape Rectangle({ 50.f, 50.f });

    // Set up circle and rectangle tools
    g_ShapeManager.SetTools(&Circle, &Rectangle, &Circle2);

    // Button Setup
    std::vector<Button> buttons;
    std::vector<Button> color_buttons;

    // Text and font set up
    sf::Font Font1("Arial.ttf");
    const int text_size = 16;
    
    sf::Text SaveText(Font1, "Save", text_size);
    sf::Text LoadText(Font1, "Load", text_size);
    sf::Text ResetCanvas(Font1, "Reset", text_size);
    sf::Text CircleText(Font1, "Draw (1)", text_size);
    sf::Text SquareText(Font1, "Boxes (2)", text_size);
    sf::Text EllipseText(Font1, "Ellipses (3)", text_size);
    sf::Text LineText(Font1, "Lines (4)", text_size);
    
    const int button_count = 7;
    sf::Text text_array[button_count] = { SaveText, LoadText, ResetCanvas, CircleText, SquareText, EllipseText, LineText };

    // Create menu buttons
    for (int i = 0; i < button_count; i++)
    {
        // Makes button with role, location, and colour 
        Button NewButton((ButtonRole)i, { 100.f * i, 800.f }, sf::Color::Black);
        text_array[i].setPosition({ 100.f * i + 10.f, 810.f });
        buttons.push_back(NewButton);
    }

    // Color setup
    const int color_count = 8;
    sf::Color color_array[color_count] = {sf::Color::Black, sf::Color::Red, sf::Color(255, 165, 0), sf::Color::Yellow, sf::Color::Green, sf::Color::Cyan, sf::Color::Blue, sf::Color::Magenta};
    sf::Color current_color = color_array[0];

    // Create colour buttons
    float row = 0.f;
    float collumn = 0.f;
    for (int i = 0; i < color_count; i++)
    {
        // Makes button with role, location, and colour 
        if (i == 4) { row = 50.f; collumn = 400.f; }
        Button NewButton((ButtonRole)i, { 100.f * i - collumn, row }, color_array[i]);
        color_buttons.push_back(NewButton);
    }

    // Variables for making shapes
    bool is_drawing = false;
    sf::Vector2i last_mouse_pos = sf::Mouse::getPosition(window);

    // Only grab input while the main window is open 
    while (window.isOpen())
    {
        // Create thickness text
        std::string OutlineThickText = "";
        sf::Text ThicknessText(Font1, OutlineThickText + "Thickness: " + std::to_string(g_CanvasManager.GetThickness()), 24);
        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window); // Draw to this location
        Circle3.setPosition(sf::Vector2f(mouse_pos.x - Circle3.getRadius(), mouse_pos.y - Circle3.getRadius()));

        // If an event happened in Main window
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

            // Change shape size from scroll wheel
            if (auto* mouse = event->getIf<sf::Event::MouseWheelScrolled>())
            {
                // Check the size isn't too small
                if (g_CanvasManager.GetThickness() > 0.f)
                {
                    // Scroll down decreases size
                    if ((mouse->delta) < 0) 
                    { 
                        g_CanvasManager.SetThickness(g_CanvasManager.GetThickness() - 2.f);
                        Circle3.setRadius(Circle3.getRadius() - 2.f);
                    } 
                }

                // Check the size isn't too large
                if (g_CanvasManager.GetThickness() < 50.f)
                {
                    // Scroll up increases size
                    if ((mouse->delta) > 0) 
                    { 
                        g_CanvasManager.SetThickness(g_CanvasManager.GetThickness() + 2.f); 
                        Circle3.setRadius(Circle3.getRadius() + 2.f);
                    } 
                }
            }

            // Left mb pressed
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                // Draw in canvas if the mouse is in range
                if (g_ShapeManager.GetTool() == tool_circle)
                {
                    g_CanvasManager.DrawShape(&g_ShapeManager, &window, last_mouse_pos, current_color); // Pass in shape being drawn, window to get mouse location, and colour of shape
                }

                // Button Menu
                for (int i = 0; i < button_count; i++)
                {
                    // Did user click on a button
                    if (buttons[i].m_ButtonShape.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
                    {
                        buttons[i].Update();

                        // Save file by clicking the button
                        if (i == 0)
                        {
                            g_FileInterface.SaveFile(g_CanvasManager.GetCanvas());
                        }

                        // Open file by clicking the button
                        if (i == 1)
                        {
                            g_FileInterface.LoadFile(g_CanvasManager.GetCanvas());
                        }

                        // Reset canvas to white
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
                            g_ShapeManager.SwapTool(tool_elipse);
                        }

                        // Lines
                        if (i == 6)
                        {
                            g_ShapeManager.SwapTool(tool_line);
                        }
                    }
                }
            }

            // Right MB pressed
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
            {
                // Draw in canvas
                g_CanvasManager.DrawShape(&g_ShapeManager, &window, last_mouse_pos, sf::Color::White); // Pass in shape being drawn, window to get mouse location, and colour of shape
            }

            // Grab mouse position when first held
            if (const auto* keyPressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                last_mouse_pos = sf::Mouse::getPosition(window);
            }

            // Left MB released
            if (const auto* keyPressed = event->getIf<sf::Event::MouseButtonReleased>())
            {
                // As long as its not the default draw circle
                if (g_ShapeManager.GetTool() != tool_circle)
                {
                    g_CanvasManager.DrawShape(&g_ShapeManager, &window, last_mouse_pos, current_color); // Pass in shape being drawn, window to get mouse location, and colour of shape
                }
            }

            // Save file with (ctrl + s)
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl)) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)))
            {
                g_FileInterface.SaveFile(g_CanvasManager.GetCanvas());
            }

            // Open file with (ctrl + o)
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl)) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::O)))
            {
                g_FileInterface.LoadFile(g_CanvasManager.GetCanvas());
            }

            // Reset canvas to white with (ctrl + r)
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl)) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)))
            {
                g_CanvasManager.ResetCanvas();
            }

            // Tool selectors
            // Draw
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))
            {
                g_ShapeManager.SwapTool(tool_circle);
                OutlineThickText = "";
            }

            // Boxes
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))
            {
                g_ShapeManager.SwapTool(tool_rectangle);
                OutlineThickText = "Outline ";
            }

            // Elipses
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3))
            {
                g_ShapeManager.SwapTool(tool_elipse);
                OutlineThickText = "Outline ";
            }

            // Lines
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4))
            {
                g_ShapeManager.SwapTool(tool_line);
                OutlineThickText = "";
            }
        }

        // If an event happened in Tool window
        while (const std::optional event = tool_window.pollEvent())
        {
            // Catch the resize events
            if (const auto* resized = event->getIf<sf::Event::Resized>())
            {
                // update the view to the new size of the window
                sf::FloatRect visibleArea({ 0.f, 0.f }, sf::Vector2f(resized->size));
                tool_window.setView(sf::View(visibleArea));
            }

            // Left mb pressed
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                // Color Button Menu
                for (int i = 0; i < color_count; i++)
                {
                    if (color_buttons[i].m_ButtonShape.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(tool_window))))
                    {
                        current_color = color_array[i];
                        color_buttons[i].Update();
                    }
                }
            }
        }

        // Window updates
        g_ShapeManager.Update(&window); // Update before clear
        window.clear();
        g_CanvasManager.Update(&window); // Update after clear
        
        // Draw menu buttons
        for (int i = 0; i < button_count; i++)
        {
            window.draw(buttons[i].m_ButtonShape);
            window.draw(text_array[i]);
        }

        // Draw thickness
        ThicknessText.setPosition({ 110.f * button_count, 810.f });
        window.draw(ThicknessText);
        if (g_ShapeManager.GetTool() == tool_circle) 
        { 
            // Check Mouse is on the canvas
            if (mouse_pos.x < 1024 && mouse_pos.x > 0 && mouse_pos.y < 800 && mouse_pos.y > 0) { window.draw(Circle3); } // Preview circle
        } 

        for (int i = 0; i < color_count; i++) 
        {
            // if (current_color == color_array[i]) { current_color; }
        }

        window.display();

        // Tool window updates
        tool_window.clear();

        // Draw color buttons
        for (int i = 0; i < color_count; i++) { tool_window.draw(color_buttons[i].m_ButtonShape); }

        // Tool window updates
        tool_window.display();
    }
    return 0;
}