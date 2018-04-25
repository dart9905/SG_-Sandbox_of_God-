
bool check(int x, int y, int z, map_t& map);

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
        speed = 2;
        onGround = false;
    }
    
    float x, y, z;
    float dx, dy, dz;
    float w, h, d;
    bool onGround;
    float speed;
    
    
    
    
    
    void collision (float Dx, float Dy, float Dz, map_t& map) {
        for (int X = (x - w) / size; X < (x + w)/ size; X++)
            for (int Y = (y - h) / size; Y < (y + h)/ size; Y++)
                for (int Z = (z - d) / size; Z < (z + d)/ size; Z++)
                    if (check(X, Y, Z, map)) {
                        if (Dx > 0)
                            x = X * size - w;
                        if (Dx < 0)
                            x = X * size + size + w;
                        if (Dy > 0)
                            y = Y * size - h;
                        if (Dy < 0) {
                            y = Y * size + size + h;
                            onGround = true;
                            dy = 0;
                        }
                        if (Dz > 0)
                            z = Z * size - d;
                        if (Dz < 0)
                            z = Z * size + size + d;
                    }
    }
    
    
    
    void keyboard () {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            if (onGround) {
                onGround = false;
                dy = 12;
            }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            dx = -sin (angleX / 180 * PI) * speed;
            dz = -cos (angleX / 180 * PI) * speed;
            x += dx;
            //y += dy;
            z += dz;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            dx =  sin (angleX / 180 * PI) * speed;
            dz =  cos (angleX / 180 * PI) * speed;
            x += dx;
            //y += dy;
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
        
    }
    
    
    
    void update (float time, map_t& map) {
        if (!onGround)
            dy -= 1.5 * time;
        onGround = false;
        
        x += dx * time;
        collision(dx, 0, 0, map);
        
        y += dy * time;
        collision(0, dy, 0, map);
        
        z += dz * time;
        collision(0, 0, dz, map);
        
        dz = 0;
        dx = 0;
    }
};


bool check(int x, int y, int z, map_t& map)
{
    if ((x < 0) || (x >= map._x) ||
        (y < 0) || (y >= map._y) ||
        (z < 0) || (z >= map._z)) return false;
    
    return map [x] [y] [z];
}



