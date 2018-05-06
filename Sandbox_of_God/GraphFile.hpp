// ==================================================================================
// ==================================================================================
// ==================================================================================
//
//                                     Graph
//
// ==================================================================================
// ==================================================================================
// ==================================================================================



#ifndef HELPFILE_H
#define HELPFILE_H



GLuint LoadTexture(sf::String name);
GLuint LoadTextureSKYBOX(sf::String name, int i);







int MakeTextures (GLuint** arrayBox) {
    for (int i = 0; i < 6; i ++) {
        arrayBox [GRASS] [i] = LoadTexture(resourcePath() + "resources/textures/blocks/end_stone.png");
    }
    
    for (int i = 0; i < 6; i ++) {
        arrayBox [EARTH] [i] = LoadTexture(resourcePath() + "resources/textures/blocks/end_stone.png");
    }
    
    
    
    for (int i = 0; i < 6; i ++) {
        arrayBox [STONE] [i] = LoadTexture(resourcePath() + "resources/textures/blocks/enchanting_table_bottom.png");
    }
    for (int i = 0; i < 6; i ++) {
        arrayBox [4] [i] = LoadTexture(resourcePath() + "resources/textures/blocks/quartz_block_chiseled.png");
    }
    
    
    /*
    arrayBox [SKY] [0] = LoadTexture(resourcePath() + "resources/skybox/skybox_top.bmp");
    arrayBox [SKY] [1] = LoadTexture(resourcePath() + "resources/skybox/skybox_front.bmp");
    skybox [2] = LoadTexture(resourcePath() + "resources/skybox/skybox_back.bmp");
    skybox [3] = LoadTexture(resourcePath() + "resources/skybox/skybox_left.bmp");
    skybox [4] = LoadTexture(resourcePath() + "resources/skybox/skybox_right.bmp");
    skybox [5] = LoadTexture(resourcePath() + "resources/skybox/skybox_bottom.bmp");
    //*/
    /*
    for (int i = 0; i < 6; i++) {
        arrayBox [SKY]  [i] = LoadTextureSKYBOX(resourcePath() + "resources/skybox2/map.jpg", i);
    }
    //*/
    //*
    arrayBox [SKY]  [0] = LoadTexture(resourcePath() + "resources/skybox2/skybox_top.png");
    arrayBox [SKY]  [1] = LoadTexture(resourcePath() + "resources/skybox2/skybox_right.png");
    arrayBox [SKY]  [2] = LoadTexture(resourcePath() + "resources/skybox2/skybox_back.png");
    arrayBox [SKY]  [3] = LoadTexture(resourcePath() + "resources/skybox2/skybox_left.png");
    arrayBox [SKY]  [4] = LoadTexture(resourcePath() + "resources/skybox2/skybox_front.png");
    arrayBox [SKY]  [5] = LoadTexture(resourcePath() + "resources/skybox2/skybox_bottom.png");
    //*/
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glClearDepth(1.f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.f, 1.f, 1.f, 2000.f);
    glEnable(GL_TEXTURE_2D);

}



GLuint LoadTextureSKYBOX(sf::String name, int i)
{
    sf::Image image;
    if (!image.loadFromFile(name))
        return EXIT_FAILURE;
    
    int x1 = 0, y1 = 0, x2 = image.getSize().x / 4, y2 = x2;
    if (i == 0) {
        x1 = x2;
        y1 = 0;
    }
    
    if (i == 5) {
        x1 = x2;
        y1 = x2 * 2;
    }
    
    if ((i > 0) && (i < 5)) {
        x1 = (i - 1) * x2;
        y1 = x2;
    }
    x2 += x1;
    y2 += y1;
    sf::Rect<int> rect_end (x1, y1, x2, y2);
    //*/
    sf::Image image_end;
    image_end.copy(image, 0, 0, rect_end, true);
    
    image_end.flipVertically();
    
    GLuint texture=0;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, image_end.getSize().x, image_end.getSize().y, GL_RGBA, GL_UNSIGNED_BYTE, image_end.getPixelsPtr());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    return texture;
}



GLuint LoadTexture(sf::String name)
{
	    sf::Image image;
        if (!image.loadFromFile(name))
            return EXIT_FAILURE;

		image.flipVertically();

		GLuint texture=0;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
    
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, image.getSize().x, image.getSize().y, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);  

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        
		return texture;
}



void createRectangle(GLuint box[],float x_size, float y_size, float z_size)
{
    x_size = x_size / 2;
    y_size = y_size / 2;
    z_size = z_size / 2;
    
    glBindTexture(GL_TEXTURE_2D, box[0]);
    glBegin(GL_QUADS);
    //top
    glTexCoord2f(0, 0);     glVertex3f(-x_size, y_size, -z_size);
    glTexCoord2f(1, 0);     glVertex3f( x_size, y_size, -z_size);
    glTexCoord2f(1, 1);     glVertex3f( x_size, y_size,  z_size);
    glTexCoord2f(0, 1);     glVertex3f(-x_size, y_size,  z_size);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, box[1]);
    glBegin(GL_QUADS);
    //front
    glTexCoord2f(0, 0);     glVertex3f(-x_size, -y_size, -z_size);
    glTexCoord2f(1, 0);     glVertex3f( x_size, -y_size, -z_size);
    glTexCoord2f(1, 1);     glVertex3f( x_size,  y_size, -z_size);
    glTexCoord2f(0, 1);     glVertex3f(-x_size,  y_size, -z_size);
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, box[2]);
    glBegin(GL_QUADS);
    //back
    glTexCoord2f(0, 0);     glVertex3f( x_size, -y_size, z_size);
    glTexCoord2f(1, 0);     glVertex3f(-x_size, -y_size, z_size);
    glTexCoord2f(1, 1);     glVertex3f(-x_size,  y_size, z_size);
    glTexCoord2f(0, 1);     glVertex3f( x_size,  y_size, z_size);
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, box[3]);
    glBegin(GL_QUADS);
    //left
    glTexCoord2f(0, 0);     glVertex3f(-x_size, -y_size,  z_size);
    glTexCoord2f(1, 0);     glVertex3f(-x_size, -y_size, -z_size);
    glTexCoord2f(1, 1);     glVertex3f(-x_size,  y_size, -z_size);
    glTexCoord2f(0, 1);     glVertex3f(-x_size,  y_size,  z_size);
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, box[4]);
    glBegin(GL_QUADS);
    //right
    glTexCoord2f(0, 0);     glVertex3f( x_size, -y_size, -z_size);
    glTexCoord2f(1, 0);     glVertex3f( x_size, -y_size,  z_size);
    glTexCoord2f(1, 1);     glVertex3f( x_size,  y_size,  z_size);
    glTexCoord2f(0, 1);     glVertex3f( x_size,  y_size, -z_size);
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, box[5]);
    glBegin(GL_QUADS);
    //bottom
    glTexCoord2f(0, 0);     glVertex3f(-x_size, -y_size,  z_size);
    glTexCoord2f(1, 0);     glVertex3f( x_size, -y_size,  z_size);
    glTexCoord2f(1, 1);     glVertex3f( x_size, -y_size, -z_size);
    glTexCoord2f(0, 1);     glVertex3f(-x_size, -y_size, -z_size);
    glEnd();
    
}



void createBox(GLuint box[],float _size)
{
    createRectangle(box, _size, _size, _size);
}



int DrawMAP (Avatar& God, map_t& map, GLuint** arrayBox) {
    int R = 20;
    
    int Xmin_place = God._x / size - R;
    int Zmin_place = God._z / size - R;
    int Xmax_place = God._x / size + R;
    int Zmax_place = God._z / size + R;
    
    if (Xmin_place < 0)
        Xmin_place = 0;
    if (Zmin_place < 0)
        Zmin_place = 0;
    if (Xmax_place > map._x_size)
        Xmax_place = map._x_size;
    if (Zmax_place > map._z_size)
        Zmax_place = map._z_size;
    
    for (int x = Xmin_place; x < Xmax_place; x++)
        for (int y = 0; y <map._y_size; y++)
            for (int z = Zmin_place; z < Zmax_place; z++)
                if (map [x] [y] [z]._visibility == VISIBLE) {
                    glTranslatef( x * size + size / 2,  y * size + size / 2,  z * size + size / 2);
                    switch (map [x] [y] [z]._structure) {
                        case SKY:
                            break;
                            
                        case GRASS:
                            createBox (arrayBox [GRASS], size);
                            break;
                            
                        case EARTH:
                            createBox(arrayBox [EARTH], size);
                            break;
                            
                        case STONE:
                            createBox(arrayBox [STONE], size);
                            break;
                            
                        default:
                            break;
                    }
                    glTranslatef(-x * size - size / 2, -y * size - size / 2, -z * size - size / 2);
                }
    return 0;
}

int GameOBJ::draw () {
    
    
    //body
    glTranslatef( _x,  _y + _h * 4 / 32,  _z);
    createRectangle (_skin, _w, _h * 24 / 32, _d * 2);
    
    {
        //head
        glTranslatef( 0, _h * 20 / 32, 0);
        createBox (_skin, _h * 16 / 32);
        glTranslatef( 0, -_h * 20 / 32, 0);
    }
    {
        //legs right
        glTranslatef( -_w * 4 / 16,  -_h * 12 / 32, 0);
        glRotatef(+_move_time, 1, 0, 0);
        glTranslatef( 0,  -_h * 12 / 32, 0);
        
        createRectangle (_skin, _w / 2 , _h * 24 / 32, _d * 2);
        
        glTranslatef( 0, +_h * 12 / 32, 0);
        glRotatef(-_move_time, 1, 0, 0);
        glTranslatef( +_w * 4 / 16, +_h * 12 / 32, 0);
    }
    {
        //legs left
        glTranslatef( +_w * 4 / 16,  -_h * 12 / 32, 0);
        glRotatef(-_move_time, 1, 0, 0);
        glTranslatef( 0,  -_h * 12 / 32, 0);
        
        createRectangle (_skin, _w / 2 , _h * 24 / 32, _d * 2);
        
        glTranslatef( -_w * 4 / 16, +_h * 12 / 32, 0);
        glRotatef(+_move_time, 1, 0, 0);
        glTranslatef( 0, +_h * 12 / 32, 0);
    }
    {
        //arm right
        glTranslatef( -_w * 12 / 16, _h * 12 / 32, 0);
        glRotatef(-_move_time, 1, 0, 0);
        glTranslatef( 0, -_h * 12 / 32, 0);
        createRectangle (_skin, _w / 2 , _h * 24 / 32, _d * 2);
        glTranslatef( 0, _h * 12 / 32, 0);
        glRotatef(_move_time, 1, 0, 0);
        glTranslatef( +_w * 12 / 16, -_h * 12 / 32, 0);
    }
    {
        //arm left
        glTranslatef( +_w * 12 / 16, _h * 12 / 32, 0);
        glRotatef(+_move_time, 1, 0, 0);
        glTranslatef( 0, -_h * 12 / 32, 0);
        createRectangle (_skin, _w / 2 , _h * 24 / 32, _d * 2);
        glTranslatef( 0, _h * 12 / 32, 0);
        glRotatef(-_move_time, 1, 0, 0);
        glTranslatef( -_w * 12 / 16, -_h * 12 / 32, 0);
    }
    glRotatef(-_angleX, 0, 1, 0);
    glTranslatef( -_x,  -_y - _h * 4 / 32,  -_z);
    return 0;
}


int Avatar::draw () {
    //body
    glTranslatef( _x,  _y + 4,  _z);
    glRotatef(+_angleX, 0, 1, 0);
    createRectangle (_skin, _w, 24, _d * 2);
    {
        //legs right
        glTranslatef( -4,  -12, 0);
        glRotatef(+_move_time, 1, 0, 0);
        glTranslatef( 0,  -12, 0);
        
        createRectangle (_skin, _w / 2 , 24, _d * 2);
        
        glTranslatef( 0, +12, 0);
        glRotatef(-_move_time, 1, 0, 0);
        glTranslatef( +4, +12, 0);
    }
    {
        //legs left
        glTranslatef( +4,  -12, 0);
        glRotatef(-_move_time, 1, 0, 0);
        glTranslatef( 0,  -12, 0);
        
        createRectangle (_skin, _w / 2 , 24, _d * 2);
        
        glTranslatef( -4, +12, 0);
        glRotatef(+_move_time, 1, 0, 0);
        glTranslatef( 0, +12, 0);
    }
    {
        //arm right
        glTranslatef( -12, 12, 0);
        glRotatef(-_move_time, 1, 0, 0);
        glTranslatef( 0, -12, 0);
        createRectangle (_skin, _w / 2 , 24, _d * 2);
        glTranslatef( 0, 12, 0);
        glRotatef(_move_time, 1, 0, 0);
        glTranslatef( +12, -12, 0);
    }
    {
        //arm left
        glTranslatef( +12, 12, 0);
        glRotatef(+_move_time, 1, 0, 0);
        glTranslatef( 0, -12, 0);
        createRectangle (_skin, _w / 2 , 24, _d * 2);
        glTranslatef( 0, 12, 0);
        glRotatef(-_move_time, 1, 0, 0);
        glTranslatef( -12, -12, 0);
    }
    glRotatef(-_angleX, 0, 1, 0);
    glTranslatef( -_x,  -_y - 4,  -_z);
    
    
    return 0;
}



#endif HELPFILE_H
