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
    STONE       = 3,
    WATER       = 4,
    TREE        = 5
};

enum MobTesk_MOB_t {
    STAND       = 5,
    WALKING     = 1,
    RUN         = 2,
    JUMP        = 3,
    HIT         = 4,
    NOTHING     = 0,
    CHASE       = 6
};

enum friendship_status_t {
    FRIEND = 0,
    AGGRESSIVE = 1,
    NEUTRELLY = 2
};

enum visibility_box_t {
    VISIBLE     = 1,
    NOTVISIBLE  = 0
};

enum solid_box_t {
    SOLID       = 0,
    LIQUID      = 1,
    FRIABLE     = 2
};


class box_t {
public:
    box_t (int structure_box = 0, int visibility_box = 0, int solid_box = 0):
    _structure(structure_box),
    _visibility(visibility_box),
    _solid(solid_box)
    {
        _h = 0;
        
    }
    ~box_t () {
        _structure = 0;
        _visibility = 0;
        _solid = 0;
        _h = 0;
    }
    int _structure;
    int _visibility;
    int _solid;
    
    int _box_vis [6] = {0};
    
    double _h;
};


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


class SkinHuman_t {
    int size_pix = 8;
public:
    SkinHuman_t (sf::String name);
    
    SkinBox_t _Head;
    SkinBox_t _Body;
    SkinBox_t _ArmLeft;
    SkinBox_t _ArmRight;
    SkinBox_t _LegsLeft;
    SkinBox_t _LegsRight;
    
    
    GLuint LoadTextureHead (int i, sf::Image& image, sf::Rect <int>& rect_end);
    GLuint LoadTextureBody (int i, sf::Image& image, sf::Rect <int>& rect_end);
    GLuint LoadTextureArmAndLegs (int i, sf::Image& image, sf::Rect <int>& rect_end);
    
    GLuint LoadText ( sf::Image& image, sf::Rect <int>& rect_end, int x, int y);
    
    int SetSize_pix (int size) {
        
        if (size % 2 != 0)
            size--;
        
        if (size < 2)
            size = 2;
        
        size_pix = size;
        return 0;
    }
    int GetSize_pix () {
        return size_pix;
    }
    
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
    GameOBJ (float x0, float y0, float z0, SkinHuman_t* skin0):
    _x (x0),
    _y (y0),
    _z (z0),
    _skin(skin0)
    {
        
        _dx = 0;
        _dy = 0;
        _dz = 0;
        _w = 16;//80 16
        _h = 32;//160 32
        _d = 4;//20 4
        _angleX = 0;
        _angleY = 0;
        _speed = 10;
        _onGround = false;
        _move_time = 0;
        _move_time_check = 10;
        
        
        _health = 50;
    }
    virtual ~GameOBJ () {}
    double _x, _y, _z;                   //coordinates
    double _dx, _dy, _dz;                //move
    double _w, _h, _d;                   //amount
    double _angleX, _angleY;             //turn
    int _move_time;
    int _move_time_check;
    double _onGround;
    double _speed;
    int _jump_speed;
    int _task = 0;
    int _friend_status = 0;
    int _damage = 1;
    
    int _health;
    
    virtual int collision (float Dx, float Dy, float Dz, map_t& map);
    
    virtual int update (float time, map_t& map);
    virtual int draw ();
    virtual int move (float time, map_t& map);
    virtual bool place (int x, int y, int k);
    virtual int attack ();
    virtual bool hitting (int damage);
    
    int setSize (int w, int h, int d) {
        if (_h > 192)
            return 0;
        _w = w;
        _h = h;
        _d = d;
        _jump_speed = sin(_h * 0.005) * 76;
        return  0;
    }
    int setSizeInK (int k) {
        if (_h > 192)
            return 0;
        if (_h * k > 192)
            return 0;
        _w *= k;//_w = _w * k;
        _h *= k;
        _d *= k;
        _jump_speed = Jump_Val (_h);
        return 0;
    }
    int Jump_Val (int h) {
        return sin(_h * 0.004 + 0.52) * 21;
    }
    SkinHuman_t* _skin;
    
    
};


class Mob: public GameOBJ {
public:
    Mob (float x0, float y0, float z0, SkinHuman_t* skin0): GameOBJ (x0, y0, z0, skin0) {
        _jump_speed = Jump_Val (_h);
        _friend_status = AGGRESSIVE;
        _health = 500;
    }
    Mob (float x0, float y0, float z0, SkinHuman_t* skin0, int live): GameOBJ (x0, y0, z0, skin0) {
        _jump_speed = Jump_Val (_h);
        _friend_status = live;
        _health = 500;
    }
    virtual ~Mob () {}
    int update (float time, map_t& map);
    int move (float time, map_t& map);
    int collision (float Dx, float Dy, float Dz, map_t& map);
    int TurnRND ();
    int CollidedWall ();
    
    
    long int _time_work;
    int _angle = 0;
    int _angle_speed = 10;
};


class Avatar: public GameOBJ {
public:
    Avatar (float x0, float y0, float z0, SkinHuman_t* skin0): GameOBJ (x0, y0, z0, skin0) {
        _onGround_two = false;
        _onGround_two_can = false;
        _health = 1000;
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




class Manager_Lord_t: public Manager_t  {
public:
    Manager_Lord_t (int size_): Manager_t(size_) {}
    
    bool place(GameOBJ* ob1, GameOBJ* ob2, int k) {
        if ((ob1->_x - ob2->_x) * (ob1->_x - ob2->_x) + (ob1->_z - ob2->_z) * (ob1->_z - ob2->_z) < k * k) {
            return true;
        }
        return false;
    }
    
    int ANGLE(GameOBJ* ob1, GameOBJ* ob2, int  i) {
        if ((i > 0) && (ob2 -> _friend_status == AGGRESSIVE) && place(ob1, ob2, 10 * size)) {
            double k1 = (ob2 -> _x - ob1 -> _x) / (ob2 -> _z - ob1 -> _z);
            double b1 = ob2 -> _x - ob2 -> _z * k1;
            double angle = atan(k1) / PI * 180;
            if (ob2 -> _z - ob1 -> _z > 0)
                ob2 -> _angleX = angle;
            else
                ob2 -> _angleX = angle + 180;
            ob2 -> _task = CHASE;
        }
        return 0;
    }
    
    int battle (GameOBJ* ob1, GameOBJ* ob2) {
        if (place(ob1, ob2, 3 * size)) {
            //printf("%i\n", 1);
            ob1 -> hitting ( ob2 -> attack());
            ob2 -> hitting ( ob1 -> attack());
        }
        return 0;
    }
    
    
    int updata (float time, map_t& map) {
        for (int i = 0; i < _capasity; i++) {
            if (_data [i]->place (_data [0]->_x,_data [0]->_z, 26 * size)) {
                ANGLE (_data [0], _data [i], i);
                _data [i]->draw();
                _data [i]->move(time, map);
                
                battle (_data [0], _data [i]);
                
                _data [i]->update(time, map);
                
            }
            
        }
        GameOBJ* obj;
        for (int i = 1; i < _capasity; i++) {
            if (_data [i] -> _health < 0) {
                obj = _data [i];
                _data [i] = _data [_capasity - 1];
                _capasity--;
                i--;
                delete obj;
            }
        }
        
    }
    
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

