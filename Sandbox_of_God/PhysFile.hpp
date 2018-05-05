
bool check(int x, int y, int z, map_t& map);



int Playr:: collision (float Dx, float Dy, float Dz, map_t& map) {
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
                        onGround_two = false;
                        dy = 0;
                    }
                    if (Dz > 0)
                        z = Z * size - d;
                    if (Dz < 0)
                        z = Z * size + size + d;
                }
    return 0;
}


int mob:: collision (float Dx, float Dy, float Dz, map_t& map) {
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
    return 0;
}



int Playr:: update (float time, map_t& map) {
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
    return 0;
}


int mob:: update (float time, map_t& map) {
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
    return 0;
}



int Playr:: keyboard () {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        if ((onGround_two) && (!onGround) && (onGround_two_can)) {
            onGround_two = false;
            dy = 25;
        }
        if ((!onGround_two) && (onGround)) {
            onGround = false;
            onGround_two_can = false;
            onGround_two = true;
            dy = 16;
            speed_angle = -2;
        }
    } else
        onGround_two_can = true;
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        dx = -sin (angleX / 180 * PI) * speed;
        dz = -cos (angleX / 180 * PI) * speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        dx =  sin (angleX / 180 * PI) * speed;
        dz =  cos (angleX / 180 * PI) * speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        dx =  sin ((angleX + 90) / 180 * PI) * speed;
        dz =  cos ((angleX + 90) / 180 * PI) * speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        dx =  sin ((angleX - 90) / 180 * PI) * speed;
        dz =  cos ((angleX - 90) / 180 * PI) * speed;
    }
    
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


