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
// ==================================================================================
//
//                                     GameOBJ
//
// ==================================================================================


class GameOBJ {
public:
    GameOBJ (float x0, float y0, float z0, GLuint* skin0):
    _x (x0),
    _y (y0),
    _z (z0),
    _skin(skin0)
    {
        
        _dx = 0;
        _dy = 0;
        _dz = 0;
        _w = 80;//80 16
        _h = 160;//160 32
        _d = 20;//20 4
        _angleX = 0;
        _angleY = 0;
        _speed = 17;
        _onGround = false;
        _move_time = 0;
        _move_time_check = 10;
        
        
        _health = 50;
    }
    virtual ~GameOBJ () {}
    float _x, _y, _z;                   //coordinates
    float _dx, _dy, _dz;                //move
    float _w, _h, _d;                   //amount
    float _angleX, _angleY;             //turn
    int _move_time;
    int _move_time_check;
    float _onGround;
    float _speed;
    
    int _health;
    
    virtual int collision (float Dx, float Dy, float Dz, map_t& map);
    
    virtual int update (float time, map_t& map);
    virtual int draw ();
    virtual int move (float time, map_t& map);
    
    GLuint* _skin;
    
    
};


class Mob: public GameOBJ {
public:
    Mob (float x0, float y0, float z0, GLuint* skin0): GameOBJ (x0, y0, z0, skin0) {}
    virtual ~Mob () {}
};


class Avatar: public GameOBJ {
public:
    Avatar (float x0, float y0, float z0, GLuint* skin0): GameOBJ (x0, y0, z0, skin0) {
        _onGround_two = false;
        _onGround_two_can = false;
        
        _w = 16;
        _h = 32;
        _d = 4;
    }
    ~Avatar () {}
    
    bool _onGround_two;
    bool _onGround_two_can;
    
    int update (float time, map_t& map);
    int collision (float Dx, float Dy, float Dz, map_t& map);
    int move (float time, map_t& map);
    int draw ();
};

// ==================================================================================
// ==================================================================================
// ==================================================================================
// ==================================================================================
//
//                                     Manager
//
// ==================================================================================
// ==================================================================================
// ==================================================================================
// ==================================================================================


class Manager_t {
public:
    Manager_t (int size_):
    _size(size_),
    _capasity(0)
    {
        _data = new GameOBJ* [_size];
    }
    
    ~Manager_t () {
        delete [] _data;
    }
    int _resize (size_t new_sz) {
        
        GameOBJ** newdata = new GameOBJ* [new_sz] {nullptr};
        std::copy(&(_data [0]), &(_data[_size]), newdata);
        
        _size = new_sz;
        delete _data;
        
        _data = newdata;
        return 0;
    }
    
    int Add (GameOBJ* NewGameOBJ) {
        if (_capasity == _size) {
            _resize (_size * 2);
        }
        _data [_capasity] = NewGameOBJ;
        _capasity++;
        
    }
    
    
    
    GameOBJ** _data;
    int _size;
    
    int _capasity;
};



class Manager_Delete_t: public Manager_t {
public:
    Manager_Delete_t(int size_): Manager_t(size_) {}
    
    int updata () {
        
        for (; _capasity >= 0; _capasity--) {
            delete _data [_capasity];
        }
    }
};



class Manager_Lord_t: public Manager_t  {
public:
    Manager_Lord_t (int size_, Manager_Delete_t* MDeletre): Manager_t(size_), _Manager_Delete(MDeletre) {}
    
    
    int updata (float time, map_t& map) {
        for (int i = 0; i < _capasity; i++) {
            _data [i]->draw();
            _data [i]->move(time, map);
            if (_data [i]->update(time, map)) {
                _Manager_Delete->Add(_data [i]);
                _data [i] = _data [_capasity];
                i--;
            }
            
        }
    }
    
    Manager_Delete_t* _Manager_Delete;
};



// ==================================================================================
// ==================================================================================
// ==================================================================================
// ==================================================================================
//
//                                     mouse_t
//
// ==================================================================================

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
        w->setMouseCursorVisible(false);
    }
    
    ~mouse_t () {}
    
    int update (Avatar& God, map_t& map);
    
    int angle (Avatar& God);
    
    int tap (Avatar& God, map_t& map);
    
    
    
    
    sf::Vector2u _windowsize;
    
    sf::RenderWindow* _window;
    
    sf::Vector2i _pos;
    
    int _xwindow;
    int _ywindow;
    
    bool _Left;
    bool _Right;
    
};

