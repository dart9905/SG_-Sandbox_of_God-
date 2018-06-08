// ==================================================================================
// ==================================================================================
// ==================================================================================
//
//                                     MAP_T
//
// ==================================================================================
// ==================================================================================
// ==================================================================================




class map_t {
    // ==============================================================================
    // ==============================================================================
    // ==============================================================================
    
    class cell {
    public:
        cell () {
            x = 0;
            y = 0;
            z = 0;
        }
        cell (int xx, int yy, int zz) {
            x = xx;
            y = yy;
            z = zz;
        }
        ~cell () {
            x = 0;
            y = 0;
            z = 0;
        }
        int x;
        int y;
        int z;
    };
    
    class map_t_z {
    public:
        map_t_z () {
            _data = nullptr;
        }
        
        ~map_t_z () {
            _data = nullptr;
        }
        
        
        int set (box_t* map_array = nullptr) {
            _data = map_array;
            return 0;
        }
        
        
        box_t& operator [] (long int i) {
            _data += i;
            return *_data;
        }
        //int& operator [] (int i);
        
        box_t* _data;
    };
    // =============================================================================
    // =============================================================================
    // =============================================================================
    class map_t_yz {
    public:
        map_t_yz ()
        {
            _data = nullptr;
        }
        
        ~map_t_yz () {
            _data = nullptr;
        }
        
        int set (box_t* map_array = nullptr) {
            _data = map_array;
            return 0;
        }
        
        int set_z (long int z) {
            _z_size = z;
            return 0;
        }
        
        map_t_z& operator [] (long int i) {
            _map_z.set (_data + i * _z_size);
            return _map_z;
        }
        
        
        //map_t_z& operator [] (int i);
        
        box_t* _data;
        map_t_z _map_z;
        long int _z_size;
        
    };
    // =============================================================================
    // =============================================================================
    // =============================================================================
    
    map_t_yz _map_yz;
    int _R_rand = 0;
    int  _R2_rand = 1;
    int _k_rand = 30;
    int _h_grass = 10;
    int _AverageHeight;
public:
    map_t (long int map_x = 10, long int map_y = 10, long int map_z = 10,  box_t* map_array = nullptr):
    _x_size (map_x),
    _y_size (map_y),
    _z_size (map_z),
    _data (map_array)
    {
        _map_yz.set_z(_z_size);
    };
    
    ~map_t () {
        _data = nullptr;
    };
    
    map_t_yz& operator [] (long int i) {
        _data_copy = _data + i * _y_size * _z_size;
        _map_yz.set (_data_copy);
        return _map_yz;
    }
    
    int Load ();
    int Load_F ();
    int RecCell1 (cell cell, int h);
    int RecCell2 (cell cell, int h);
    bool VisibilityCheck (int x_main, int y_main, int z_main);
    
    box_t* _data;
    box_t* _data_copy;
    long int _x_size;
    long int _y_size;
    long int _z_size;
    
};


//*
int map_t::Load () {
    _R_rand = _y_size / 3;
    /*
    cell cell1 (0,              rand() % _R_rand,     0);
    cell cell2 (_x_size - 1,    rand() % _R_rand,     0);
    cell cell3 (0,              rand() % _R_rand,     _z_size - 1);
    cell cell4 (_x_size - 1,    rand() % _R_rand,     _z_size - 1);
    
    _AverageHeight = (cell1.y + cell2.y + cell3.y + cell4.y) / 4;
    //*/
    
    (*this) [0]             [0] [0]._h              = rand() % _R_rand;
    (*this) [_x_size - 1]   [0] [0]._h              = rand() % _R_rand;
    (*this) [0]             [0] [_z_size - 1]._h    = rand() % _R_rand;
    (*this) [_x_size - 1]   [0] [_z_size - 1]._h    = rand() % _R_rand;
    
    cell cell;
    
    
    for (int i = _x_size; i > 2; i = i / 2) {
        _R_rand = (_y_size * _k_rand / 100 * (i) / _x_size) + 1;
        for (int x0 = i / 2 - 1; x0 < _x_size; x0 += i) {
            for (int z0 = i / 2 - 1; z0 < _z_size; z0 += i) {
                cell.x = x0;
                cell.z = z0;
                RecCell1 (cell, i);
            }
        }
        for (int x0 = i / 2 - 1; x0 < _x_size; x0 += i) {
            for (int z0 = i / 2 - 1; z0 < _z_size; z0 += i) {
                cell.x = x0;
                cell.z = z0;
                RecCell2 (cell, i);
            }
        }
    }
    /*
    FILE* file = fopen("/Users/macbook/Desktop/text.txt", "w");
    for (int i = 0; i < _x_size; i++) {
        for (int j = 0, h = (*this) [i] [0] [j]._h; j < _z_size; j++, h = (*this) [i] [0] [j]._h) {
            fprintf(file, "%i  ", h);
        }
        fprintf(file, "\n");
    }
    fclose(file);
    //*/
    int max_h = 0;
    
    for (int i = 0; i < _x_size; i++) {
        for (int j = 0; j < _z_size; j++) {
            if ((*this) [i] [0] [j]._h == -1) {
                printf("[%i 0 %i] = %lg", i, j, (*this) [i] [0] [j]._h);
                assert((*this) [i] [0] [j]._h == -1);
            }
            if (max_h < (*this) [i] [0] [j]._h)
                max_h = (*this) [i] [0] [j]._h;
        }
    }
    int k = 0;
    for (int i = 0; i < _x_size; i++) {
        for (int j = 0; j < _z_size; j++) {
            (*this) [i] [0] [j]._h = ((*this) [i] [0] [j]._h / max_h) * ((*this) [i] [0] [j]._h / max_h) * ((*this) [i] [0] [j]._h / max_h)* ((*this) [i] [0] [j]._h / max_h);
            (*this) [i] [0] [j]._h = (*this) [i] [0] [j]._h * _y_size / 3 + _y_size / 3;
            k = (*this) [i] [0] [j]._h;
        }
    }
    Load_F ();
    /*
    FILE* file = fopen("/Users/macbook/Desktop/text.txt", "w");
    for (int i = 0; i < _x_size; i++) {
        for (int j = 0, h = (*this) [i] [0] [j]._h; j < _z_size; j++, h = (*this) [i] [0] [j]._h) {
            fprintf(file, "%i  ", h);
        }
        fprintf(file, "\n");
    }
    fclose(file);
    //*/
    return 0;
}


int map_t::RecCell1 (cell cell, int h) {
    
    int a1 = (*this) [cell.x - (h - 2) / 2]     [0]     [cell.z - (h - 2) / 2]._h;
    int a2 = (*this) [cell.x + h / 2]           [0]     [cell.z - (h - 2) / 2]._h;
    int a3 = (*this) [cell.x - (h - 2) / 2]     [0]     [cell.z + h / 2]._h;
    int a4 = (*this) [cell.x + h / 2]           [0]     [cell.z + h / 2]._h;
    int y = (a1 + a2 + a3 + a4) / 4 + rand() % _R_rand * _R2_rand;
    
    (*this) [cell.x]        [0] [cell.z]._h         = y;
    (*this) [cell.x + 1]    [0] [cell.z]._h         = y;
    (*this) [cell.x]        [0] [cell.z + 1]._h     = y;
    (*this) [cell.x + 1]    [0] [cell.z + 1]._h     = y;
    
    return 0;
}


int map_t::RecCell2 (cell cell, int h) {
    
    int y = 0;
    int a1 = 0, a2 = 0, a3 = 0, a4 = 0;
    
    {
        a1 = (*this) [cell.x - (h - 2) / 2]     [0]     [cell.z - (h - 2) / 2]._h;
        a2 = (*this) [cell.x + h / 2]           [0]     [cell.z - (h - 2) / 2]._h;
        a3 = (*this) [cell.x]                   [0]     [cell.z]._h;
        
        
        class cell cell1 (cell.x, 0, cell.z - (h - 2) / 2);
        if (cell1.z == 0) {
            y = (a1 + a2 + a3) / 3 + rand() % _R_rand * _R2_rand;
        } else {
            a4 = (*this) [cell.x] [0] [cell.z - h]._h;
            y = (a1 + a2 + a3 + a4) / 4 + rand() % _R_rand * _R2_rand;
        }
        
        (*this) [cell1.x]        [0] [cell1.z]._h         = y;
        (*this) [cell1.x + 1]    [0] [cell1.z]._h         = y;
    }
    
    {
        a1 = (*this) [cell.x - (h - 2) / 2]     [0]     [cell.z + h / 2]._h;
        a2 = (*this) [cell.x + h / 2]           [0]     [cell.z + h / 2]._h;
        a3 = (*this) [cell.x]                   [0]     [cell.z]._h;
        
        
        class cell cell1 (cell.x, 0, cell.z + h / 2);
        if (cell1.z == _z_size - 1) {
            y = (a1 + a2 + a3) / 3 + rand() % _R_rand * _R2_rand;
        } else {
            a4 = (*this) [cell.x] [0] [cell.z + h]._h;
            y = (a1 + a2 + a3 + a4) / 4 + rand() % _R_rand * _R2_rand;
        }
        
        (*this) [cell1.x]        [0] [cell1.z]._h         = y;
        (*this) [cell1.x + 1]    [0] [cell1.z]._h         = y;
    }
    
    {
        a1 = (*this) [cell.x - (h - 2) / 2]     [0]     [cell.z - (h - 2) / 2]._h;
        a2 = (*this) [cell.x - (h - 2) / 2]     [0]     [cell.z + h / 2]._h;
        a3 = (*this) [cell.x]                   [0]     [cell.z]._h;
        
        
        class cell cell1 (cell.x - (h - 2) / 2, 0, cell.z);
        if (cell1.x == 0) {
            y = (a1 + a2 + a3) / 3 + rand() % _R_rand * _R2_rand;
        } else {
            a4 = (*this) [cell.x - h] [0] [cell.z]._h;
            y = (a1 + a2 + a3 + a4) / 4 + rand() % _R_rand * _R2_rand;
        }
        
        (*this) [cell1.x]        [0] [cell1.z]._h         = y;
        (*this) [cell1.x]        [0] [cell1.z + 1]._h     = y;
    }
    
    {
        a1 = (*this) [cell.x + h / 2]     [0]     [cell.z - (h - 2) / 2]._h;
        a2 = (*this) [cell.x + h / 2]     [0]     [cell.z + h / 2]._h;
        a3 = (*this) [cell.x]             [0]     [cell.z]._h;
        
        
        class cell cell1 (cell.x + h / 2, 0, cell.z);
        if (cell1.x == _x_size - 1) {
            y = (a1 + a2 + a3) / 3 + rand() % _R_rand * _R2_rand;
        } else {
            a4 = (*this) [cell.x + h] [0] [cell.z]._h;
            y = (a1 + a2 + a3 + a4) / 4 + rand() % _R_rand * _R2_rand;
        }
        
        (*this) [cell1.x]        [0] [cell1.z]._h         = y;
        (*this) [cell1.x]        [0] [cell1.z + 1]._h     = y;
    }
    
    return 0;
}



int map_t::Load_F () {
    int max = -1;
    
    for (int x = 0; x < _x_size; x++)
        for (int y = 0; y < _y_size; y++)
            for (int z = 0; z < _z_size; z++)
            {
                (*this)  [x] [y] [z]._solid = SOLID;
                max = (*this)  [x] [0] [z]._h;
                if (y < max) {
                    if (rand() % 100 <= 10) {
                        (*this)  [x] [y] [z]._structure = EARTH;
                    } else
                        (*this)  [x] [y] [z]._structure = STONE;
                }
                
                if ((y >= max) && (y < max + _h_grass)) {
                    
                    if (rand() % 100 <= 10) {
                        (*this)  [x] [y] [z]._structure = STONE;
                    } else
                        (*this)  [x] [y] [z]._structure = EARTH;
                }
                
                if (y == max + _h_grass) {
                    //*
                    if (rand() % 100 <= 10) {
                        (*this)  [x] [y] [z]._structure = STONE;
                    } else
                        (*this)  [x] [y] [z]._structure = GRASS;
                }
            }
    /*
    FILE* file = fopen("/Users/macbook/Desktop/text2.txt", "w");
    for (int i = 0; i < _x_size; i++) {
        for (int j = 0, h = (*this) [i] [0] [j]._h; j < _z_size; j++, h = (*this) [i] [0] [j]._h) {
            fprintf(file, "%i  ", h);
        }
        fprintf(file, "\n");
    }
    fclose(file);
    file = fopen("/Users/macbook/Desktop/text1.txt", "w");
    for (int y = 0; y < _y_size; y++) {
        fprintf(file, "# %i\n", y);
        for (int x = 0; x < _x_size; x++) {
            for (int z = 0; z < _z_size; z++) {
            fprintf(file, "%i  ", (*this)  [x] [y] [z]._structure);
            }
            fprintf(file, "\n");
        }
        fprintf(file, "\n\n");
    }
    fclose(file);
    //*/
    for (int x = 0; x < _x_size; x++)
        for (int y = 0; y < _y_size; y++)
            for (int z = 0; z < _z_size; z++)
            {
                max = (*this)  [x] [0] [z]._h;
                if (y <= max + 10) {
                    if (VisibilityCheck(x,y,z))
                        (*this)  [x] [y] [z]._visibility = VISIBLE;
                    else
                        (*this) [x] [y] [z]._visibility = NOTVISIBLE;
                }
            }
    
    return 0;
}



bool map_t::VisibilityCheck (int x_main, int y_main, int z_main) {
    int x = x_main;
    int y = y_main;
    int z = z_main;
    
    x--;
    if ((x > 0) && ((*this)  [x] [y] [z]._structure == SKY)) {
        return true;
    }
    x += 2;
    if ((x < _x_size) && ((*this)  [x] [y] [z]._structure == SKY)) {
        return true;
    }
    x--;
    y--;
    if ((y > 1) && ((*this)  [x] [y] [z]._structure == SKY)) {
        return true;
    }
    y += 2;
    if ((x < _y_size) && ((*this)  [x] [y] [z]._structure == SKY)) {
        return true;
    }
    y--;
    z--;
    if ((z > 0) && ((*this)  [x] [y] [z]._structure == SKY)) {
        return true;
    }
    z += 2;
    if ((z < _z_size) && ((*this)  [x] [y] [z]._structure == SKY)) {
        return true;
    }
    z--;
    
    
}

//*/
// =================================================================================
// =================================================================================
// =================================================================================
