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
    
    int update (float* angleX, float* angleY, const Playr& God) {
        angle (angleX, angleY);
        tap (angleX, angleY, God);
        return 0;
    }
    
    int angle (float* angleX, float* angleY) {
        _xwindow = _window->getPosition().x + _windowsize.x / 2;
        _ywindow = _window->getPosition().y + _windowsize.y / 2;
        
        _pos = sf::Mouse::getPosition(*_window);
        
        *angleX += (_xwindow - _pos.x - _window->getPosition().x) / 4;
        *angleY += (_ywindow - _pos.y - _window->getPosition().y) / 4;
        
        if (*angleY < -89.0)
            *angleY = -89.0;
        
        if (*angleY > 89.0)
            *angleY = 89.0;
        
        _pos.x = _xwindow;
        _pos.y = _ywindow;
        sf::Mouse::setPosition(_pos);
        return 0;
    }
    
    int tap (float* angleX, float* angleY, const Playr& God) {
        if (_Left || _Right) {
            float x = God.x;
            float y = God.y + God.h / 2;
            float z = God.z;
            
            int X = 0, Y = 0, Z = 0;
            int oldX = 0, oldY = 0, oldZ = 0;
            int dist = 0;
            
            while (dist < 120) {
                dist++;
                
                
                x += -sin (*angleX / 180 * PI);
                X = x / size;
                y +=  tan (*angleY / 180 * PI);
                Y = y / size;
                z += -cos (*angleX / 180 * PI);
                Z = z / size;
                
                if (check(X, Y, Z)) {
                    if (_Left) {
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
        _Left = false;
        _Right = false;
    }
    
    sf::Vector2u _windowsize;
    
    sf::RenderWindow* _window;
    
    sf::Vector2i _pos;
    
    int _xwindow;
    int _ywindow;
    
    bool _Left;
    bool _Right;
    
};
