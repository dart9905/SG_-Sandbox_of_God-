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


int GameOBJ:: collision (float Dx, float Dy, float Dz, map_t& map) {
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
                        _dy = 0;
                    }
                    if (Dz > 0)
                        _z = Z * size - _d;
                    if (Dz < 0)
                        _z = Z * size + size + _d;
                }
    return 0;
}


int GameOBJ:: update (float time, map_t& map) {
    return 0;
}



int GameOBJ:: move (float time, map_t& map) {
    //_dz = -5;
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
    
    return 0;
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
    //========================
    x--;
    if ((x >= 0) && CheckVis (map [x] [y] [z], visibility)) {
        if (visibility)
            map [x] [y] [z]._visibility = VISIBLE;
        else
            if (BesideVisBox(x, y, z, map))
                map [x] [y] [z]._visibility = NOTVISIBLE;
    }
    x += 2;
    if ((x < map._x_size) && CheckVis (map [x] [y] [z], visibility)) {
        if (visibility)
            map [x] [y] [z]._visibility = VISIBLE;
        else
            if (BesideVisBox(x, y, z, map))
                map [x] [y] [z]._visibility = NOTVISIBLE;
    }
    x--;
    //========================
    
    y--;
    if ((y >= 0) && CheckVis (map [x] [y] [z], visibility)) {
        if (visibility)
            map [x] [y] [z]._visibility = VISIBLE;
        else
            if (BesideVisBox(x, y, z, map))
                map [x] [y] [z]._visibility = NOTVISIBLE;
    }
    y += 2;
    if ((y < map._y_size) && CheckVis (map [x] [y] [z], visibility)) {
        if (visibility)
            map [x] [y] [z]._visibility = VISIBLE;
        else
            if (BesideVisBox(x, y, z, map))
                map [x] [y] [z]._visibility = NOTVISIBLE;
    }
    y--;
    //========================
    
    z--;
    if ((z >= 0) && CheckVis (map [x] [y] [z], visibility)) {
        if (visibility)
            map [x] [y] [z]._visibility = VISIBLE;
        else
            if (BesideVisBox(x, y, z, map))
                map [x] [y] [z]._visibility = NOTVISIBLE;
    }
    z += 2;
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


