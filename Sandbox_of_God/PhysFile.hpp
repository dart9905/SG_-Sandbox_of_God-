// ==================================================================================
// ==================================================================================
// ==================================================================================
//
//                                     Phys
//
// ==================================================================================
// ==================================================================================
// ==================================================================================
bool check(int x, int y, int z, map_t& map);

int GameOBJ::collision(float Dx, float Dy, float Dz, map_t &map) {
    return 0;
}

int GameOBJ::attack () {
    return _damage;
}

bool GameOBJ::hitting(int damage) {
    _health = _health - damage;
    if (_health < 0)
        return false;
    return true;
}

int Mob::CollidedWall() {
    if (_dy == 0 && _onGround) {
        _dy = _jump_speed;
        _onGround = false;
        _y += _dy;
    }
    if (_dy < 0 && !_onGround) {
        _task = NOTHING;
        TurnRND();
    }
}

int Mob:: collision (float Dx, float Dy, float Dz, map_t& map) {
    for (int X = (_x - _w) / size; X < (_x + _w)/ size; X++)
        for (int Y = (_y - _h) / size; Y < (_y + _h)/ size; Y++)
            for (int Z = (_z - _d) / size; Z < (_z + _d)/ size; Z++)
                if (check(X, Y, Z, map)) {
                    if (Dx > 0) {
                        _x = X * size - _w;
                        CollidedWall();
                    }
                    if (Dx < 0) {
                        _x = X * size + size + _w;
                        CollidedWall();
                    }
                    if (Dy > 0) {
                        _y = Y * size - _h;
                    }
                    if (Dy < 0) {
                        _y = Y * size + size + _h;
                        _onGround = true;
                        _dy = 0;
                    }
                    if (Dz > 0) {
                        _z = Z * size - _d;
                        CollidedWall();
                    }
                    if (Dz < 0) {
                        _z = Z * size + size + _d;
                        CollidedWall();
                    }
                }
    return 0;
}



int GameOBJ:: update (float time, map_t& map) {
    return _health;
}

int Mob:: TurnRND () {
    if (_angle == 0) {
        _angle = rand () % 3000;
        if (_angle > 40)
            _angle = 0;
        else
            _angle = (_angle - 20);
    }
    return 0;
}

int Mob:: update (float time, map_t& map) {
    //_task = STAND;
    //_angleX = 90;
    switch (_task) {
        case STAND:
            _time_work--;
            if (_time_work == 0)
                _task = NOTHING;
            TurnRND ();
            break;
            
        case WALKING:
            _time_work--;
            if (_time_work == 0)
                _task = NOTHING;
            break;
            
        case RUN:
            _time_work--;
            if (_time_work == 0)
                _task = NOTHING;
            break;
            
        case JUMP:
            _task = NOTHING;
            break;
            
        case HIT:
            _task = NOTHING;
            break;
            
        case CHASE:
            _angle = 0;
            _time_work = 0;
            _task = NOTHING;
            break;
            
        case NOTHING:
            _time_work = 0;
            _task = rand() % 100;
            if ((_task < 20) && (_time_work == 0)) {
                _task = STAND;
                _time_work = rand() % 500 + 200;
            }
            if ((_task >= 20) && (_task < 80) && (_time_work == 0)) {
                _task = WALKING;
                _time_work = rand() % 500+ 200;
            }
            if ((_task >= 80) && (_task <= 100) && (_time_work == 0)) {
                _task = RUN;
                _time_work = rand() % 100 + 100;
            }
            break;
            
        default:
            _task = NOTHING;
            break;
     
    }
    
    //*/
    return _health;
}

bool GameOBJ:: place(int x, int z, int k) {
    if ((_x - x) * (_x - x) + (_z - z) * (_z - z) < k * k) {
        return true;
    }
    return false;
}

int GameOBJ:: move(float time, map_t &map) {
    return 0;
}

int Mob:: move (float time, map_t& map) {
    //*
    if (_angle > 0) {
        _angle--;
        _angleX += _angle_speed;
    }
    if (_angle < 0) {
        _angle++;
        _angleX -= _angle_speed;
    }
    
    switch (_task) {
        case WALKING:
            _dx = -sin (_angleX / 180 * PI) * _speed;
            _dz = -cos (_angleX / 180 * PI) * _speed;
            
            break;
            
        case RUN:
            _dx = -sin (_angleX / 180 * PI) * _speed * 1.2;
            _dz = -cos (_angleX / 180 * PI) * _speed * 1.2;
            break;
            
        case CHASE:
            _dx = -sin (_angleX / 180 * PI) * _speed * 1.2;
            _dz = -cos (_angleX / 180 * PI) * _speed * 1.2;
            break;
            
        case STAND:
            _dx = 0;
            _dz = 0;
            break;
        default:
            break;
    }
    
    if (_dz || _dx) {
        _move_time += _move_time_check;
        if (_move_time > 50)
            _move_time_check = - 20 * _speed / _h;
        
        if (_move_time < -50)
            _move_time_check = 20 * _speed / _h;
        
    } else {
        _move_time = 0;
        _move_time_check = 20 * _speed / _h;
    }
    
    if (!_onGround)
        _dy -= 1.5 * time;
    _onGround = false;
    
    _x += _dx * time;
    collision(_dx, 0, 0, map);
    
    _y += _dy * time;
    collision(0, _dy, 0, map);
    
    _z += _dz * time;
    collision(0, 0, _dz, map);
    
    
    _dz = 0;
    _dx = 0;
    //*/
    return 0;
}



int Avatar:: collision (float Dx, float Dy, float Dz, map_t& map) {
    for (int X = (_x - _w) / size; X < (_x + _w)/ size; X++)
        for (int Y = (_y - _h) / size; Y < (_y + _h)/ size; Y++)
            for (int Z = (_z - _d) / size; Z < (_z + _d)/ size; Z++)
                if (check(X, Y, Z, map)) {
                    if (Dx > 0)
                        _x = X * size - _w;
                    if (Dx < 0)
                        _x = X * size + size + _w;
                    if (Dy > 0)
                        _y = Y * size - _h;
                    if (Dy < 0) {
                        _y = Y * size + size + _h;
                        _onGround = true;
                        _onGround_two = false;
                        _dy = 0;
                        
                        _speed = 17;
                    }
                    if (Dz > 0)
                        _z = Z * size - _d;
                    if (Dz < 0)
                        _z = Z * size + size + _d;
                }
    return 0;
}



int Avatar:: update (float time, map_t& map) {
    
    return _health;
}



int Avatar:: move (float time, map_t& map) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        if ((_onGround_two) && (!_onGround) && (_onGround_two_can)) {
            _onGround_two = false;
            _dy = 25;
            _speed = 50;
        }
        if ((!_onGround_two) && (_onGround)) {
            _onGround = false;
            _onGround_two_can = false;
            _onGround_two = true;
            _dy = 16;
        }
    } else
        _onGround_two_can = true;
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        _dx = -sin (_angleX / 180 * PI) * _speed;
        _dz = -cos (_angleX / 180 * PI) * _speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        _dx =  sin (_angleX / 180 * PI) * _speed;
        _dz =  cos (_angleX / 180 * PI) * _speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        _dx =  sin ((_angleX + 90) / 180 * PI) * _speed;
        _dz =  cos ((_angleX + 90) / 180 * PI) * _speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        _dx =  sin ((_angleX - 90) / 180 * PI) * _speed;
        _dz =  cos ((_angleX - 90) / 180 * PI) * _speed;
    }
    if (_dz || _dx) {
        _move_time += _move_time_check;
        if (_move_time > 50)
            _move_time_check = - 20 * _speed / _h;
        
        if (_move_time < -50)
            _move_time_check = 20 * _speed / _h;
        
    } else {
        _move_time = 0;
        _move_time_check = 20 * _speed / _h;
    }
    
    if (!_onGround) {
        _dy -= 1.5 * time;
    }
    _onGround = false;
    
    _x += _dx * time;
    collision(_dx, 0, 0, map);
    
    _y += _dy * time;
    collision(0, _dy, 0, map);
    
    _z += _dz * time;
    collision(0, 0, _dz, map);
    
    
    
    
    _dz = 0;
    _dx = 0;
    return 0;
    
}



bool check(int x, int y, int z, map_t& map)
{
    if ((x < 0) || (x >= map._x_size) ||
        (y < 0) || (y >= map._y_size) ||
        (z < 0) || (z >= map._z_size)) return false;
    
    return map [x] [y] [z]._structure;
}


// =================================================================================
// =================================================================================
// =================================================================================
//
//                          BREAK AND BILD BOX: MOUSE
//
// =================================================================================
// =================================================================================
// =================================================================================



bool CheckVis (const box_t& arg, bool visibility) {
    return ((((arg._visibility == NOTVISIBLE) && visibility) || ((arg._visibility == VISIBLE) && !visibility)) && (arg._structure != SKY));
}



bool BesideVisBox (int x0, int y0, int z0, map_t& map) {
    int Xmin_place = x0 - 1, Ymin_place = y0 - 1, Zmin_place = z0 - 1;
    int Xmax_place = x0 + 1, Ymax_place = y0 + 1, Zmax_place = z0 + 1;
    if (Xmin_place < 0)
        Xmin_place = 0;
    if (Zmin_place < 0)
        Zmin_place = 0;
    if (Xmax_place > map._x_size - 1)
        Xmax_place = map._x_size - 1;
    if (Zmax_place > map._z_size - 1)
        Zmax_place = map._z_size - 1;
    
    if (map [Xmin_place] [y0] [z0]._structure == SKY)
        return false;
    if (map [Xmax_place] [y0] [z0]._structure == SKY)
        return false;
    if (map [x0] [Ymin_place] [z0]._structure == SKY)
        return false;
    if (map [x0] [Ymax_place] [z0]._structure == SKY)
        return false;
    if (map [x0] [y0] [Zmin_place]._structure == SKY)
        return false;
    if (map [x0] [y0] [Zmax_place]._structure == SKY)
        return false;
    return true;
    
}



bool PathVisBox(int x0, int y0, int z0, map_t& map, bool visibility)
{
    int x = x0, y = y0, z = z0;
    map.VisibilityCheckPro(x, y, z);
    //========================
    x--;
    map.VisibilityCheckPro(x, y, z);
    if ((x >= 0) && CheckVis (map [x] [y] [z], visibility)) {
        if (visibility)
            map [x] [y] [z]._visibility = VISIBLE;
        else
            if (BesideVisBox(x, y, z, map))
                map [x] [y] [z]._visibility = NOTVISIBLE;
    }
    x += 2;
    map.VisibilityCheckPro(x, y, z);
    if ((x < map._x_size) && CheckVis (map [x] [y] [z], visibility)) {
        if (visibility)
            map [x] [y] [z]._visibility = VISIBLE;
        else
            if (BesideVisBox(x, y, z, map))
                map [x] [y] [z]._visibility = NOTVISIBLE;
    }
    x--;
    map.VisibilityCheckPro(x, y, z);
    //========================
    
    y--;
    map.VisibilityCheckPro(x, y, z);
    if ((y >= 0) && CheckVis (map [x] [y] [z], visibility)) {
        if (visibility)
            map [x] [y] [z]._visibility = VISIBLE;
        else
            if (BesideVisBox(x, y, z, map))
                map [x] [y] [z]._visibility = NOTVISIBLE;
    }
    y += 2;
    map.VisibilityCheckPro(x, y, z);
    if ((y < map._y_size) && CheckVis (map [x] [y] [z], visibility)) {
        if (visibility)
            map [x] [y] [z]._visibility = VISIBLE;
        else
            if (BesideVisBox(x, y, z, map))
                map [x] [y] [z]._visibility = NOTVISIBLE;
    }
    y--;
    map.VisibilityCheckPro(x, y, z);
    //========================
    
    z--;
    map.VisibilityCheckPro(x, y, z);
    if ((z >= 0) && CheckVis (map [x] [y] [z], visibility)) {
        if (visibility)
            map [x] [y] [z]._visibility = VISIBLE;
        else
            if (BesideVisBox(x, y, z, map))
                map [x] [y] [z]._visibility = NOTVISIBLE;
    }
    z += 2;
    map.VisibilityCheckPro(x, y, z);
    if ((z < map._z_size) && CheckVis (map [x] [y] [z], visibility)) {
        if (visibility)
            map [x] [y] [z]._visibility = VISIBLE;
        else
            if (BesideVisBox(x, y, z, map))
                map [x] [y] [z]._visibility = NOTVISIBLE;
    }
    //========================
    
    
    
    return false;
}


