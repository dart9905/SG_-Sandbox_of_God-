
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


int map_array_GLOBAL_VARIABLE [1024] [612] [1024] = {0};


int main(int, char const**)
{
    float dx = 0, dy = 0, dz = 0;
    
    //
    //              LOAD MAP
    //
    
    map_t map (1024, 612, 1024, &(map_array_GLOBAL_VARIABLE [0] [0] [0]));
    
    for (int x = 0; x < 1024; x++)
        for (int y = 0; y < 612; y++)
            for (int z = 0; z < 1024; z++)
            {
                
                if (y < 1)
                    map [x] [y] [z] = 1;
            }
    
    
    //
    //              Create the main window
    //
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 2;
    settings.minorVersion = 1;
    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Sandbox of God", sf::Style::Default, settings);
    window.setVerticalSyncEnabled(true);
    
    
    //
    //              Set the Icon
    //
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    
    GLuint box [6];
    GLuint skybox [6];
    MakeTextures (box, skybox);
    
    
    sf::Clock clock;
    
    Playr God(map._x * 10, 500, map._z * 10);
    
    mouse_t Mouse (0, 0, false, false, &window);
    
    
    int R = 20;
    int Xmin_place = 0, Zmin_place = 0, Xmax_place = 0, Zmax_place = 0;
    
    
    //
    //              Start the game loop
    //
    while (window.isOpen())
    {
        
        // Clear the depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        float time = clock.getElapsedTime().asMilliseconds();
        clock.restart();
        time = time / 50;
        
        if (time  > 3)
            time = 3;
        
        
        //
        //                  Process events
        //
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
        God.update(time, map);
        
        
        
        Mouse.update(&angleX, &angleY, God, map);
        
        
        
        
        // Apply some transformations
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        
        gluLookAt(God.x, God.y + God.h / 2, God.z, God.x - sin (angleX / 180 * PI),  God.y + God.h / 2 + tan (angleY / 180 * PI),  God.z - cos (angleX / 180 * PI), 0, 1, 0);
        
        
        R = 20;
        Xmin_place = God.x / size - R;
        Zmin_place = God.z / size - R;
        Xmax_place = God.x / size + R;
        Zmax_place = God.z / size + R;
        
        if (Xmin_place < 0)
            Xmin_place = 0;
        if (Zmin_place < 0)
            Zmin_place = 0;
        if (Xmax_place > map._x - 1)
            Xmax_place = map._x - 1;
        if (Zmax_place > map._z - 1)
            Zmax_place = map._z - 1;
        
        for (int x = Xmin_place; x < Xmax_place; x++)
            for (int y = 0; y <map._y; y++)
                for (int z = Zmin_place; z < Zmax_place; z++)
                    if (map [x] [y] [z] == 1) {
                        glTranslatef( x * size + size / 2,  y * size + size / 2,  z * size + size / 2);
                        createBox(box, size / 2);
                        glTranslatef(-x * size - size / 2, -y * size - size / 2, -z * size - size / 2);
                    }
        
        glTranslatef( God.x,  God.y,  God.z);
        createBox(skybox, 1000);
        glTranslatef(-God.x, -God.y, -God.z);
        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}
