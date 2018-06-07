
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
const float size = 32.f;
const float PI = 3.141592653;



class SkinBox_t {
    GLuint _error;
public:
    
    GLuint _top;
    GLuint _bottom;
    GLuint _left;
    GLuint _back;
    GLuint _right;
    GLuint _front;
    
    
    GLuint& operator [] (int i) {
        switch (i) {
            case 0:
                return _top;
                break;
            case 1:
                return _bottom;
                break;
            case 2:
                return _left;
                break;
            case 3:
                return _front;
                break;
            case 4:
                return _right;
                break;
            case 5:
                return _back;
                break;
            default:
                return _error;
                break;
        }
    }
};


GLuint LoadTexture(sf::String name);
void createRectangle(SkinBox_t& box,float x_size, float y_size, float z_size);
void createBox(SkinBox_t& box,float _size);




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
    
    
    //
    //              Create the main window
    //
    sf::ContextSettings settings;
    settings.depthBits = 32;
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
    
    
    SkinBox_t box_WATER;
    for (int i = 0; i < 6; i ++) {
        box_WATER [i] = LoadTexture(resourcePath() + "water.png");
    }
    
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glClearDepth(1.f);
    glDepthFunc(GL_LESS);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.f, 1.f, 1.f, 2000.f);
    
    glTexEnvi (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    
    
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_BLEND);
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    
    // -- Mouse --
    sf::Vector2i pixelPos;
    sf::Vector2f Pos;
    
    float angleX = 0.0, angleY = 0.0;
    int xt = 0;
    int yt = 0;
    int x= 0, y = 0, z = 0;
    
    pixelPos.x = xt;
    pixelPos.y = yt;
    
    sf::Mouse::setPosition(pixelPos);
    
    sf::Clock clock;
    //
    //              Start the game loop
    //
    while (window.isOpen())
    {
        
        // Clear the depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        float time = clock.getElapsedTime().asMilliseconds() / 20;
        //clock.restart();
        //time = time / 50;
        
        //if (time  > 3)
          //  time = 3;
        
        
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
        }
        
        ////-----------------------
        
        pixelPos = sf::Mouse::getPosition(window);
        
        angleX += (window_width / 2 - pixelPos.x) / 4;
        angleY += (window_height / 2 - pixelPos.y) / 4;
        
        
        pixelPos.x = window.getPosition().x + window_width / 2;
        pixelPos.y = window.getPosition().y + window_height / 2;
        sf::Mouse::setPosition(pixelPos);
        
        ////-----------------------
        
        
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        glAlphaFunc (GL_GREATER, 0.5f);
        glEnable (GL_ALPHA_TEST);
        
        glTranslatef(0,0,  -100);
        glRotated(-angleY, 1, 0, 0);
        glRotated(angleX, 0, 1, 0);
        
        
        createBox(box_WATER, size);
        
        
        glRotated(-angleX, 0, 1, 0);
        glRotated(angleY, 1, 0, 0);
        glTranslatef(0,0,  100);
        
        
        
        window.display();
        
    }
    return EXIT_SUCCESS;
}








GLuint LoadTexture(sf::String name)
{
    sf::Image image;
    if (!image.loadFromFile(name))
        return EXIT_FAILURE;
    
    image.flipVertically();
    
    GLuint texture=0;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, image.getSize().x, image.getSize().y, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    return texture;
}




void createBox(SkinBox_t& box,float _size)
{
    createRectangle(box, _size, _size, _size);
}




void createRectangle(SkinBox_t& box,float x_size, float y_size, float z_size)
{
    x_size = x_size / 2;
    y_size = y_size / 2;
    z_size = z_size / 2;
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.8f);
    glBindTexture(GL_TEXTURE_2D, box [0]);
    glBegin(GL_QUADS);
    //top
    glTexCoord2f(0, 0);     glVertex3f(-x_size, y_size, -z_size);
    glTexCoord2f(1, 0);     glVertex3f( x_size, y_size, -z_size);
    glTexCoord2f(1, 1);     glVertex3f( x_size, y_size,  z_size);
    glTexCoord2f(0, 1);     glVertex3f(-x_size, y_size,  z_size);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, box [2]);
    glBegin(GL_QUADS);
    //front
    glTexCoord2f(0, 0);     glVertex3f(-x_size, -y_size, -z_size);
    glTexCoord2f(1, 0);     glVertex3f( x_size, -y_size, -z_size);
    glTexCoord2f(1, 1);     glVertex3f( x_size,  y_size, -z_size);
    glTexCoord2f(0, 1);     glVertex3f(-x_size,  y_size, -z_size);
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, box [4]);
    glBegin(GL_QUADS);
    //back
    glTexCoord2f(0, 0);     glVertex3f( x_size, -y_size, z_size);
    glTexCoord2f(1, 0);     glVertex3f(-x_size, -y_size, z_size);
    glTexCoord2f(1, 1);     glVertex3f(-x_size,  y_size, z_size);
    glTexCoord2f(0, 1);     glVertex3f( x_size,  y_size, z_size);
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, box [1]);
    glBegin(GL_QUADS);
    //left
    glTexCoord2f(0, 0);     glVertex3f(-x_size, -y_size,  z_size);
    glTexCoord2f(1, 0);     glVertex3f(-x_size, -y_size, -z_size);
    glTexCoord2f(1, 1);     glVertex3f(-x_size,  y_size, -z_size);
    glTexCoord2f(0, 1);     glVertex3f(-x_size,  y_size,  z_size);
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, box [3]);
    glBegin(GL_QUADS);
    //right
    glTexCoord2f(0, 0);     glVertex3f( x_size, -y_size, -z_size);
    glTexCoord2f(1, 0);     glVertex3f( x_size, -y_size,  z_size);
    glTexCoord2f(1, 1);     glVertex3f( x_size,  y_size,  z_size);
    glTexCoord2f(0, 1);     glVertex3f( x_size,  y_size, -z_size);
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, box [5]);
    glBegin(GL_QUADS);
    //bottom
    glTexCoord2f(0, 0);     glVertex3f(-x_size, -y_size,  z_size);
    glTexCoord2f(1, 0);     glVertex3f( x_size, -y_size,  z_size);
    glTexCoord2f(1, 1);     glVertex3f( x_size, -y_size, -z_size);
    glTexCoord2f(0, 1);     glVertex3f(-x_size, -y_size, -z_size);
    glEnd();
    glDisable(GL_ALPHA_TEST);
    
}
