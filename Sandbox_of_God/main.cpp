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

const int window_width = 1500;
const int window_height = 1200;

#include "GameEngine.hpp"





//      =============================================
//      ==                                         ==
//      ==   ==       ==   =====   ==   ==    ==   ==
//      ==   ===     ===   ==  =   ==   ===   ==   ==
//      ==   == == == ==   =====   ==   == == ==   ==
//      ==   ==  ===  ==   ==  =   ==   ==   ===   ==
//      ==                                         ==
//      =============================================


box_t map_array_GLOBAL_VARIABLE [512] [512] [512] = {0, 0};

int main(int, char const**)
{
    float dx = 0, dy = 0, dz = 0;
    
    //
    //              LOAD MAP
    //
    
    map_t map (512, 512, 512, &(map_array_GLOBAL_VARIABLE [0] [0] [0]));
    map.Load();
    
    
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
    
    sf::Texture cursor_texture;
    cursor_texture.loadFromFile(resourcePath() + "resources/cursor.png");
    sf::Sprite cursor (cursor_texture);
    cursor.setOrigin(8.0, 8.0);
    cursor.setPosition(window_width / 2, window_height / 2);
    cursor.setScale(3, 3);
    
    
    //
    //              Set the Icon
    //
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    
    SkinBox_t skybox;
    SkinBox_t box_GRASS;
    SkinBox_t box_EARTH;
    SkinBox_t box_STONE;
    SkinBox_t arrayBox [4] = {skybox, box_GRASS, box_EARTH, box_STONE};
    
    MakeTextures (arrayBox);
    SkinHuman_t skin_mob (resourcePath() + "resources/minecraft/textures/entity/steve.png");
    SkinHuman_t skin_mob_tr (resourcePath() + "resources/minecraft/textures/entity/tr.png");
    SkinHuman_t skin_mob_zom (resourcePath() + "resources/minecraft/textures/entity/zombie/husk.png");
    
    sf::Clock clock;
    
    Manager_Delete_t Manager_Delete (2);
    Manager_Lord_t Manager (1, &Manager_Delete);
    Avatar God(map._x_size * size / 2, map._y_size * size, map._z_size * size / 2, &skin_mob);
    Mob Dayn(map._x_size * size / 2, map._y_size * size, map._z_size * size / 2, &skin_mob_zom);
    Dayn.setSizeInK(6);
    
    Manager.Add(&God);
    Manager.Add(&Dayn);
    //*
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
        Manager.Add(new Mob (map._x_size * size / 2 + i * size * 2 - 10 * size, map._y_size * size, map._z_size * size / 2 + j * size * 2  + size * 6, &skin_mob_tr));
    //*/
    mouse_t Mouse (0, 0, false, false, &window);
    
    float angleSky = 0;
    
    
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
        window.setMouseCursorVisible(false);
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
        
    
        
        Mouse.update(God, map);
        
        
        

        // Apply some transformations
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        gluLookAt(God._x - God._d * 1.5 * sin (God._angleX / 180 * PI), God._y + God._h - 5, God._z - God._d * 1.5 * cos (God._angleX / 180 * PI), God._x - sin (God._angleX / 180 * PI) * (1 + God._d * 1.5),  God._y + God._h - 5 + tan (God._angleY / 180 * PI),  God._z - cos (God._angleX / 180 * PI) * (1 + God._d * 1.5), 0, 1, 0);
        
        DrawMAP(God, map, arrayBox);
        // Update the window
        angleSky += 0.01;
        if (angleSky > 359)
            angleSky = 0;
        glTranslatef( God._x,  God._y,  God._z);
        glRotatef(angleSky, 0, 1, 0);
        createBox(arrayBox [SKY], 1500);
        glRotatef(-angleSky, 0, 1, 0);
        glTranslatef(-God._x, -God._y, -God._z);
        
        Manager.updata(time, map);
        Manager_Delete.updata();
        window.pushGLStates();
        window.draw(cursor);
        window.popGLStates();
        window.display();
        
    }
    return EXIT_SUCCESS;
}
