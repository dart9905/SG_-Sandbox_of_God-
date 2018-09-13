// ==================================================================================
// ==================================================================================
// ==================================================================================
//
//                                     Mouse
//
// ==================================================================================
// ==================================================================================
// ==================================================================================
int mouse_t:: update (Avatar& God, map_t& map) {
    angle (God);
    tap (God, map);
    return 0;
}

int mouse_t:: angle (Avatar& God) {
    _xwindow = _window->getPosition().x + _windowsize.x / 2;
    _ywindow = _window->getPosition().y + _windowsize.y / 2;
    
    _pos = sf::Mouse::getPosition(*_window);
    
    God._angleX += (_xwindow - _pos.x - _window->getPosition().x) / 4;
    God._angleY += (_ywindow - _pos.y - _window->getPosition().y) / 4;
    
    if (God._angleY < -89.0)
        God._angleY = -89.0;
    
    if (God._angleY > 89.0)
        God._angleY = 89.0;
    _pos.x = _xwindow;
    _pos.y = _ywindow;
    sf::Mouse::setPosition(_pos);
    return 0;
}


int mouse_t:: tap (Avatar& God, map_t& map) {
    if (_Left || _Right) {
        float Godx = God._x;
        float Gody = God._y + God._h / 2;
        float Godz = God._z;
        
        int X = 0, Y = 0, Z = 0;
        int oldX = 0, oldY = 0, oldZ = 0;
        int dist = 0;
        
        while (dist < 120) {
            dist++;
            
            
            Godx += -sin (God._angleX / 180 * PI);
            X = Godx / size;
            Gody +=  tan (God._angleY / 180 * PI);
            Y = Gody / size;
            Godz += -cos (God._angleX / 180 * PI);
            Z = Godz / size;
            
            
            
            if (check(X, Y, Z, map)) {
                
                if (_Left) {
                    map [X] [Y] [Z]._structure = SKY;
                    map [X] [Y] [Z]._visibility = NOTVISIBLE;
                    PathVisBox (X, Y, Z, map, true);
                    break;
                } else {
                    map [oldX] [oldY] [oldZ]._structure = TREE;
                    map [oldX] [oldY] [oldZ]._visibility = VISIBLE;
                    PathVisBox (oldX, oldY, oldZ, map, false);
                    break;
                }
            }
            oldX = X;
            oldY = Y;
            oldZ = Z;
            
        }
    }
    _Left = false;
    _Right = false;
}



