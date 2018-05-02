// ==================================================================================
// ==================================================================================
// ==================================================================================
//
//                                     Class
//
// ==================================================================================
// ==================================================================================
// ==================================================================================


enum structure_box_t {
    SKY         = 0,
    GRASS       = 1,
    EARTH       = 2,
    STONE       = 3
};

enum visibility_box_t {
    VISIBLE     = 1,
    NOTVISIBLE  = 0
};


class box_t {
public:
    box_t (int structure_box = 0, int visibility_box = 0):
    _structure(structure_box),
    _visibility(visibility_box)
    {}
    ~box_t () {
        _structure = 0;
        _visibility = 0;
    }
    int _structure;
    int _visibility;
};


// ==================================================================================
//
//                                     MAP_T
//
// ==================================================================================
#include "Map.hpp"
// ==================================================================================
// ==================================================================================
// ==================================================================================



class Playr {
public:
    Playr (float x0, float y0, float z0):
    x (x0),
    y (y0),
    z (z0)
    {
        dx = 0;
        dy = 0;
        dz = 0;
        w = 5;
        h = 20;
        d = 5;
        speed = 5;
        onGround = false;
    }
    
    float x, y, z;
    float dx, dy, dz;
    float w, h, d;
    bool onGround;
    float speed;
    
    int collision (float Dx, float Dy, float Dz, map_t& map);
    
    int keyboard ();
    
    int update (float time, map_t& map);
};



class mouse_t {
public:
    
    mouse_t (int x, int y, bool l, bool r, sf::RenderWindow* w):
    _xwindow (x),
    _ywindow (y),
    _Left (l),
    _Right (r),
    _window (w) {
        _windowsize = w->getSize();
        _xwindow = _window->getPosition().x + 400;
        _ywindow = _window->getPosition().y + 300;
        _pos.x = _xwindow;
        _pos.y = _ywindow;
        sf::Mouse::setPosition(_pos);
    }
    
    ~mouse_t () {}
    
    int update (float* angleX, float* angleY, const Playr& God, map_t& map);
    
    int angle (float* angleX, float* angleY);
    
    int tap (float* angleX, float* angleY, const Playr& God, map_t& map);
    
    
    
    
    sf::Vector2u _windowsize;
    
    sf::RenderWindow* _window;
    
    sf::Vector2i _pos;
    
    int _xwindow;
    int _ywindow;
    
    bool _Left;
    bool _Right;
    
};

