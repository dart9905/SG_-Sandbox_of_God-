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
        
        
        box_t& operator [] (int i) {
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
        
        int set_z (int z) {
            _z_size = z;
            return 0;
        }
        
        map_t_z& operator [] (int i) {
            _map_z.set (_data + i * _z_size);
            return _map_z;
        }
        
        
        //map_t_z& operator [] (int i);
        
        box_t* _data;
        map_t_z _map_z;
        int _z_size;
        
    };
    // =============================================================================
    // =============================================================================
    // =============================================================================
    
    map_t_yz _map_yz;
    
public:
    map_t (int map_x = 10, int map_y = 10, int map_z = 10,  box_t* map_array = nullptr):
    _x_size (map_x),
    _y_size (map_y),
    _z_size (map_z),
    _data (map_array)
    {
        _R_rand = 0;
        _map_yz.set_z(_z_size);
    };
    
    ~map_t () {
        _data = nullptr;
    };
    
    map_t_yz& operator [] (int i) {
        _map_yz.set (_data + i * _y_size * _z_size);
        return _map_yz;
    }
    
    int Load ();
    
    box_t* _data;
    int _x_size;
    int _y_size;
    int _z_size;
    int _R_rand;
};


//*
int map_t::Load () {
    _R_rand = RAND_MAX / _y_size;
    (*this) [0]         [_y_size / 4 + rand() / _R_rand] [0]._structure        = STONE;
    (*this) [_x_size]   [_y_size / 4 + rand() / _R_rand] [0]._structure        = STONE;
    (*this) [0]         [_y_size / 4 + rand() / _R_rand] [_z_size]._structure  = STONE;
    (*this) [_x_size]   [_y_size / 4 + rand() / _R_rand] [_z_size]._structure  = STONE;
    
    
    
    return 0;
}
 //*/
/*
int map_t::Load () {
    
    
    for (int x = 0; x < _x_size; x++)
        for (int y = 0; y < _y_size; y++)
            for (int z = 0; z < _z_size; z++)
            {
                (*this)  [x] [y] [z]._solid = SOLID;
                if (y < _y_size / 2 - _y_size / 100 * 5) {
                    (*this) [x] [y] [z]._visibility = NOTVISIBLE;
                    if (rand() % 100 <= 10) {
                        (*this)  [x] [y] [z]._structure = EARTH;
                    } else
                        (*this)  [x] [y] [z]._structure = STONE;
                }
                
                if ((y >= _y_size / 2 - _y_size / 100 * 5) && (y < _y_size / 2)) {
                    (*this)  [x] [y] [z]._visibility = NOTVISIBLE;
                    
                    if (rand() % 100 <= 10) {
                        (*this)  [x] [y] [z]._structure = STONE;
                    } else
                        (*this)  [x] [y] [z]._structure = EARTH;
                }
                
                if (y == _y_size / 2) {
                    (*this)  [x] [y] [z]._visibility = VISIBLE;
                    if (rand() % 100 <= 10) {
                        (*this)  [x] [y] [z]._structure = STONE;
                    } else
                        (*this)  [x] [y] [z]._structure = GRASS;
                }
            }
    return 0;
}
//*/
// =================================================================================
// =================================================================================
// =================================================================================
