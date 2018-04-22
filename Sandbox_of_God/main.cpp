
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//

//#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <GLUT/GLUT.h>
#include <iostream>


// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"

#include "helpFile.hpp"


float angleX, angleY;
float speed = 1.0;


int main(int, char const**)
{
    /*
    sf::Window window1(sf::VideoMode(800, 600), "OpenGL");
    sf::ContextSettings settings1 = window1.getSettings();
    
    std::cout << "depth bits:" << settings1.depthBits << std::endl;
    std::cout << "stencil bits:" << settings1.stencilBits << std::endl;
    std::cout << "antialiasing level:" << settings1.antialiasingLevel << std::endl;
    std::cout << "version:" << settings1.majorVersion << "." << settings1.minorVersion << std::endl;
     */
    // Create the main window
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 2;
    settings.minorVersion = 1;
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML OpenGL", sf::Style::Default, settings);
    window.setVerticalSyncEnabled(true);
    //sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Load a sprite to display
    sf::Texture texture_background;
    if (!texture_background.loadFromFile(resourcePath() + "cute_image.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite sprite_background(texture_background);
    
    GLuint box [7];
    
    for (int i = 0; i < 6; i ++) {
        box [i] = LoadTexture(resourcePath() + "resources/grassBox/bottom.jpg");
    }
    
    /*
    box[0] = LoadTexture(resourcePath() + "resources/box_test/1.jpg");
    box[1] = LoadTexture(resourcePath() + "resources/box_test/2.jpg");
    box[2] = LoadTexture(resourcePath() + "resources/box_test/3.jpg");
    box[3] = LoadTexture(resourcePath() + "resources/box_test/4.jpg");
    box[4] = LoadTexture(resourcePath() + "resources/box_test/5.jpg");
    box[5] = LoadTexture(resourcePath() + "resources/box_test/6.jpg");
    */
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glClearDepth(1.f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.f, 1.f, 1.f, 500.f);
    glEnable(GL_TEXTURE_2D);
    

    // Start the game loop
    
    sf::Clock clock;
    
    while (window.isOpen())
    {
        
        // Clear the depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
        
        
        ////----------------------
        
        ////----------------------
        
        
        float time = clock.getElapsedTime().asSeconds() * 100 * 0.3;
        float size = 20.f;

        
        // Draw the sprite
        window.pushGLStates();
        window.draw(sprite_background);
        window.popGLStates();
        
        
        // Draw the string
        //window.draw(text);
        
        
        
        
        // Apply some transformations
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0, 0, -100);
        glRotatef(time, 1, 0, 0);
        
        
        for (int x = 0; x < 1; x++) {
            for (int y = 0; y < 1; y++) {
                glTranslatef( x * size * 2,  y * size * 2, 0);
                createBox(box, size);
                glTranslatef(-x * size * 2, -y * size * 2, 0);
            }
        }

        // Update the window
        window.display();
    }
    
    //glDeleteTextures(1, &texture);
    return EXIT_SUCCESS;
}
