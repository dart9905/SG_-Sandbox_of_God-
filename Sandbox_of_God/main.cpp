
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
#include <math.h>
#include <time.h>

#define GL_CLAMP_TO_EDGE 0x812F


// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"

const int map_x = 1000;
const int map_y = 1000;
const int map_z = 1000;
int map [map_x] [map_y] [map_z];

float angleX, angleY;

const int window_width = 1500;
const int window_height = 1200;

#include "GameEngine.hpp"

#include "Mouse.hpp"



//      =============================================
//      ==                                         ==
//      ==   ==       ==   =====   ==   ==    ==   ==
//      ==   ===     ===   ==  =   ==   ===   ==   ==
//      ==   == == == ==   =====   ==   == == ==   ==
//      ==   ==  ===  ==   ==  =   ==   ==   ===   ==
//      ==                                         ==
//      =============================================


int main(int, char const**)
{
    float dx = 0, dy = 0, dz = 0;
    
    for (int x = 0; x < 1000; x++)
        for (int y = 0; y < 50; y++)
            for (int z = 0; z < 1000; z++)
            {
                if (y < 1)
                    map [x] [y] [z] = 1;
            }
    
    // Create the main window
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 2;
    settings.minorVersion = 1;
    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Sandbox of God", sf::Style::Default, settings);
    window.setVerticalSyncEnabled(true);

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    
    GLuint box [6];
    GLuint skybox [6];
    MakeTextures (box, skybox);
    
    
    sf::Clock clock;
    
    Playr God(10000, 500, 10000);
    
    mouse_t Mouse (0, 0, false, false, &window);
    
    // Start the game loop
    while (window.isOpen())
    {
        
        // Clear the depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        float time = clock.getElapsedTime().asMilliseconds();
        clock.restart();
        time = time / 50;
        
        if (time  > 3)
            time = 3;
        
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
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.key.code == sf::Mouse::Right)
                    Mouse._Right = true;
                if (event.key.code == sf::Mouse::Left)
                    Mouse._Left = true;
            }
        }
        
        God.keyboard();
        God.update(time);
        
        /*
         
         if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
         dx = -sin (angleX / 180 * PI) * speed;
         dy =  tan (angleY / 180 * PI) * speed;
         dz = -cos (angleX / 180 * PI) * speed;
         x += dx;
         y += dy;
         z += dz;
         }
         if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
         dx =  sin (angleX / 180 * PI) * speed;
         dy = -tan (angleY / 180 * PI) * speed;
         dz =  cos (angleX / 180 * PI) * speed;
         x += dx;
         y += dy;
         z += dz;
         }
         if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
         dx =  sin ((angleX + 90) / 180 * PI) * speed;
         dz =  cos ((angleX + 90) / 180 * PI) * speed;
         x += dx;
         z += dz;
         }
         if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
         dx =  sin ((angleX - 90) / 180 * PI) * speed;
         dz =  cos ((angleX - 90) / 180 * PI) * speed;
         x += dx;
         z += dz;
         }
        */
        
        
        
        Mouse.update(&angleX, &angleY, God);
        
        
        
        
        // Apply some transformations
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        
        gluLookAt(God.x, God.y + God.h / 2, God.z, God.x - sin (angleX / 180 * PI),  God.y + God.h / 2 + tan (angleY / 180 * PI),  God.z - cos (angleX / 180 * PI), 0, 1, 0);
        
        
        int R = 30;
        int Xmin = God.x / size - R;
        int Zmin = God.z / size - R;
        int Xmax = God.x / size + R;
        int Zmax = God.z / size + R;
        
        if (Xmin < 0)
            Xmin = 0;
        if (Zmin < 0)
            Zmin = 0;
        if (Xmax > map_x - 1)
            Xmax = map_x - 1;
        if (Zmax > map_z - 1)
            Zmax = map_z - 1;
        
        for (int x = Xmin; x < Xmax; x++)
            for (int y = 0; y <20; y++)
                for (int z = Zmin; z < Zmax; z++)
                    if (map [x] [y] [z] == 1) {
                        glTranslatef( x * size + size / 2,  y * size + size / 2,  z * size + size / 2);
                        createBox(box, size / 2);
                        glTranslatef(-x * size - size / 2, -y * size - size / 2, -z * size - size / 2);
                    }
        //*/
        /*
        for (int x = 0; x < 60; x++)
            for (int y = 0; y <20; y++)
                for (int z = 0; z < 60; z++)
                    if (map [x] [y] [z] == 1) {
                        glTranslatef( x * size + size / 2,  y * size + size / 2,  z * size + size / 2);
                        createBox(box, size / 2);
                        glTranslatef(-x * size - size / 2, -y * size - size / 2, -z * size - size / 2);
                    }
        //*/
        
        glTranslatef( God.x,  God.y,  God.z);
        createBox(skybox, 1000);
        glTranslatef(-God.x, -God.y, -God.z);
        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}
