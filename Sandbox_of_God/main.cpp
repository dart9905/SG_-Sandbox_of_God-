
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

#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glu32.lib") // +++++
#pragma comment (lib, "glut32.lib") 


// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"

int main(int, char const**)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

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
    
    GLuint texture = 0;
    {
        sf::Image image;
        image.loadFromFile(resourcePath() + "icon.png");
        
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                     image.getSize().x,
                     image.getSize().y,
                     0, GL_RGBA, GL_UNSIGNED_BYTE,
                     image.getPixelsPtr());
        //gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, image.getSize().x, image.getSize().y, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    }
    
    
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glClearDepth(1.f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.f, 1.f, 1.f, 500.f);
    glEnable(GL_TEXTURE_2D);
    /*
    //
    //              ТЕКСТ
    //
    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    sf::Text text("Hello SFML", font, 50);
    text.setFillColor(sf::Color::Black);
    */
    
    
    //
    //              МУЗЫКА
    //
    /*
    // Load a music to play
    sf::Music music;
    if (!music.openFromFile(resourcePath() + "nice_music.ogg")) {
        return EXIT_FAILURE;
    }

    // Play the music
    music.play();
    */

    // Start the game loop
    while (window.isOpen())
    {
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

        // Clear screen
        window.clear();

        // Draw the sprite
        window.draw(sprite_background);

        // Draw the string
        //window.draw(text);

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
