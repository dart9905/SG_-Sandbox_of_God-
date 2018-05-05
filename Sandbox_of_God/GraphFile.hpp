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







int MakeTextures (GLuint** arrayBox) {
    /*
    box_GRASS [0] = LoadTexture(resourcePath() + "resources/textures/blocks/mycelium_top.png");//"resources/grassBox/top.jpg");
    for (int i = 1; i < 5; i ++) {
        box_GRASS [i] = LoadTexture(resourcePath() + "resources/textures/blocks/mycelium_side.png");//"resources/grassBox/side.jpg");
    }
    box_GRASS [5] = LoadTexture(resourcePath() + "resources/grassBox/bottom.jpg");
    */
    for (int i = 0; i < 6; i ++) {
        arrayBox [GRASS] [i] = LoadTexture(resourcePath() + "resources/textures/blocks/end_stone.png");
    }
    
    for (int i = 0; i < 6; i ++) {
        arrayBox [EARTH] [i] = LoadTexture(resourcePath() + "resources/textures/blocks/end_stone.png");//"resources/grassBox/bottom.jpg");
    }
    
    
    
    for (int i = 0; i < 6; i ++) {
        arrayBox [STONE] [i] = LoadTexture(resourcePath() + "resources/textures/blocks/enchanting_table_bottom.png");//"resources/grassBox/Stone_Block.png");
    }
    for (int i = 0; i < 6; i ++) {
        arrayBox [4] [i] = LoadTexture(resourcePath() + "resources/textures/blocks/quartz_block_chiseled.png");//"resources/grassBox/Stone_Block.png");
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
     arrayBox [SKY] [0] = LoadTexture(resourcePath() + "resources/skybox4/skybox_front.bmp");
     arrayBox [SKY] [1] = LoadTexture(resourcePath() + "resources/skybox4/skybox_top.jpg");
     arrayBox [SKY] [2] = LoadTexture(resourcePath() + "resources/skybox4/skybox_bottom.jpg");
     arrayBox [SKY] [3] = LoadTexture(resourcePath() + "resources/skybox4/skybox_right.jpg");
     arrayBox [SKY] [4] = LoadTexture(resourcePath() + "resources/skybox4/skybox_left.jpg");
     arrayBox [SKY] [5] = LoadTexture(resourcePath() + "resources/skybox4/skybox_back.jpg");
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
    glTranslatef( _x,  _y + 4,  _z);
    createRectangle (_skin, _w, 24, _d * 2);
    {
        //head
        glTranslatef( 0, 20, 0);
        createBox (_skin, 16);
        glTranslatef( 0, -20, 0);
    }
    {
        //legs right
        glTranslatef( -4,  -24, 0);
        createRectangle (_skin, _w / 2 , 24, _d * 2);
        glTranslatef( +4, +24, 0);
    }
    {
        //legs left
        glTranslatef( +4,  -24, 0);
        createRectangle (_skin, _w / 2 , 24, _d * 2);
        glTranslatef( -4, +24, 0);
    }
    {
        //arm right
        glTranslatef( -12, 0, 0);
        createRectangle (_skin, _w / 2 , 24, _d * 2);
        glTranslatef( +12, 0, 0);
    }
    {
        //arm left
        glTranslatef( +12, 0, 0);
        createRectangle (_skin, _w / 2 , 24, _d * 2);
        glTranslatef( -12, 0, 0);
    }
    glTranslatef( -_x,  -_y - 4,  -_z);
    return 0;
}


int Avatar::draw () {
    
    //body
    glTranslatef( _x,  _y + 4,  _z);
    glRotatef(+angleX, 0, 1, 0);
    createRectangle (_skin, _w, 24, _d * 2);
    {
        //legs right
        glTranslatef( -4,  -24, 0);
        createRectangle (_skin, _w / 2 , 24, _d * 2);
        glTranslatef( +4, +24, 0);
    }
    {
        //legs left
        glTranslatef( +4,  -24, 0);
        createRectangle (_skin, _w / 2 , 24, _d * 2);
        glTranslatef( -4, +24, 0);
    }
    {
        //arm right
        glTranslatef( -12, 0, 0);
        createRectangle (_skin, _w / 2 , 24, _d * 2);
        glTranslatef( +12, 0, 0);
    }
    {
        //arm left
        glTranslatef( +12, 0, 0);
        createRectangle (_skin, _w / 2 , 24, _d * 2);
        glTranslatef( -12, 0, 0);
    }
    glRotatef(-angleX, 0, 1, 0);
    glTranslatef( -_x,  -_y - 4,  -_z);
    
    
    return 0;
}



#endif HELPFILE_H
