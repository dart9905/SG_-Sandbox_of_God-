
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


// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"


int map [1000] [1000] [1000];
float angleX, angleY;
#include "helpFile.hpp"


int main(int, char const**)
{
    for (int x = 0; x < 1000; x++)
        for (int y = 0; y < 20; y++)
            for (int z = 0; z < 1000; z++)
            {
                if (y == 0)
                    map [x] [y] [z] = 1;
                /*
                if ((y == 0) || rand() % 100 == 1)
                    map [x] [y] [z] = 1;
                 //*/
            }
    
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
    
    GLuint box [6];
    box [0] = LoadTexture(resourcePath() + "resources/grassBox/top.jpg");
    for (int i = 1; i < 5; i ++) {
        box [i] = LoadTexture(resourcePath() + "resources/grassBox/side.jpg");
    }
    box [5] = LoadTexture(resourcePath() + "resources/grassBox/bottom.jpg");
    
    GLuint skybox [6];
    skybox [0] = LoadTexture(resourcePath() + "resources/skybox/skybox_top.bmp");
    skybox [1] = LoadTexture(resourcePath() + "resources/skybox/skybox_front.bmp");
    skybox [2] = LoadTexture(resourcePath() + "resources/skybox/skybox_back.bmp");
    skybox [3] = LoadTexture(resourcePath() + "resources/skybox/skybox_left.bmp");
    skybox [4] = LoadTexture(resourcePath() + "resources/skybox/skybox_right.bmp");
    skybox [5] = LoadTexture(resourcePath() + "resources/skybox/skybox_bottom.bmp");
    
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glClearDepth(1.f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.f, 1.f, 1.f, 2000.f);
    glEnable(GL_TEXTURE_2D);
    

    float dx = 0, dy = 0, dz = 0;
    
    
    
    sf::Clock clock;
    
    Playr God(10000, 200, 10000);
    
    // -- Mouse --
    sf::Vector2i pixelPos;
    sf::Vector2f Pos;
    
    int xt = 0;
    int yt = 0;
    
    bool mLeft = false;
    bool mRight = false;
    // -----------
    
    
    xt = window.getPosition().x + 400;
    yt = window.getPosition().y + 300;
    
    pixelPos.x = xt;
    pixelPos.y = yt;
    sf::Mouse::setPosition(pixelPos);
    
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
                    mRight = true;
                if (event.key.code == sf::Mouse::Left)
                    mLeft = true;
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
        
        
        ////----------------------
        
        xt = window.getPosition().x + 400;
        yt = window.getPosition().y + 300;
        
        pixelPos = sf::Mouse::getPosition(window);
        //Pos = window.mapPixelToCoords(pixelPos);
        
        
        
        angleX += (xt - pixelPos.x - window.getPosition().x) / 4;
        angleY += (yt - pixelPos.y - window.getPosition().y) / 4;
        
        if (angleY < -89.0)
            angleY = -89.0;
        
        if (angleY > 89.0)
            angleY = 89.0;
        
        pixelPos.x = xt;
        pixelPos.y = yt;
        sf::Mouse::setPosition(pixelPos);
        
        if (mLeft || mRight) {
            float x = God.x;
            float y = God.y + God.h / 2;
            float z = God.z;
            
            int X,Y,Z,oldX,oldY,oldZ;
            int dist = 0;
            
            while (dist < 120) {
                dist++;
                
                
                x += -sin (angleX / 180 * PI);
                X = x / size;
                y +=  tan (angleY / 180 * PI);
                Y = y / size;
                z += -cos (angleX / 180 * PI);
                Z = z / size;
                
                if (check(X, Y, Z)) {
                    if (mLeft) {
                        map [X] [Y] [Z] = 0;
                        break;
                    } else {
                        map [oldX] [oldY] [oldZ] = 1;
                        break;
                    }
                }
                oldX = X;
                oldY = Y;
                oldZ = Z;
                
            }
        }
        mLeft = false;
        mRight = false;
        
        ////----------------------

        
        // Draw the sprite
        window.pushGLStates();
        window.draw(sprite_background);
        window.popGLStates();
        
        
        // Draw the string
        //window.draw(text);
        
        
        
        
        // Apply some transformations
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        
        gluLookAt(God.x, God.y + God.h / 2, God.z, God.x - sin (angleX / 180 * PI),  God.y + God.h / 2 + tan (angleY / 180 * PI),  God.z - cos (angleX / 180 * PI), 0, 1, 0);
        
        
        int R = 30;
        int X = God.x / size;
        int Z = God.z / size;
        
        
        for (int x = X - R; x < X + R; x++)
            for (int y = 0; y <20; y++)
                for (int z = Z - R; z < Z + R; z++)
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
