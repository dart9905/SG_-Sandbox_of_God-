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









int MakeTextures (SkinBox_t* arrayBox) {
    arrayBox [GRASS] [0] = LoadTexture(resourcePath() + "resources/minecraft/textures/blocks/grass_n.png");
    for (int i = 1; i < 5; i ++) {
        arrayBox [GRASS] [i] = LoadTexture(resourcePath() + "resources/minecraft/textures/blocks/grass_side.png");
    }
    arrayBox [GRASS] [5] = LoadTexture(resourcePath() + "resources/minecraft/textures/blocks/dirt.png");
    
    for (int i = 0; i < 6; i ++) {
        arrayBox [EARTH] [i] = LoadTexture(resourcePath() + "resources/minecraft/textures/blocks/dirt.png");
    }
    
    
    
    for (int i = 0; i < 6; i ++) {
        arrayBox [STONE] [i] = LoadTexture(resourcePath() + "resources/minecraft/textures/blocks/stone.png");
    }
    
    for (int i = 0; i < 6; i ++) {
        arrayBox [WATER] [i] = LoadTexture(resourcePath() + "resources/minecraft/textures/blocks/water.png");
    }
    
    
    /*
    arrayBox [SKY] [0] = LoadTexture(resourcePath() + "resources/skybox/skybox_top.bmp");
    arrayBox [SKY] [1] = LoadTexture(resourcePath() + "resources/skybox/skybox_front.bmp");
    arrayBox [SKY]  [2] = LoadTexture(resourcePath() + "resources/skybox/skybox_back.bmp");
    arrayBox [SKY]  [3] = LoadTexture(resourcePath() + "resources/skybox/skybox_left.bmp");
    arrayBox [SKY]  [4] = LoadTexture(resourcePath() + "resources/skybox/skybox_right.bmp");
    arrayBox [SKY]  [5] = LoadTexture(resourcePath() + "resources/skybox/skybox_bottom.bmp");
    //*/
    //*
    for (int i = 0; i < 6; i++) {
        arrayBox [SKY]  [i] = LoadTextureSKYBOX(resourcePath() + "resources/skybox/ckybox.png", i);
    }
    
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glClearDepth(1.f);
    glDepthFunc(GL_LESS);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.f, 1.f, 1.f, 2000.f);
    
    glTexEnvi (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    
    
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_BLEND);
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
    image_end.create(image.getSize().x / 4, image.getSize().x / 4);//, sf::Color (0, 0, 0, 255));
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



void createRectangle(SkinBox_t& box,float x_size, float y_size, float z_size)
{
    x_size = x_size / 2;
    y_size = y_size / 2;
    z_size = z_size / 2;
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.8f);
    glBindTexture(GL_TEXTURE_2D, box [0]);
    glBegin(GL_QUADS);
    //top
    glTexCoord2f(0, 0);     glVertex3f(-x_size, y_size, -z_size);
    glTexCoord2f(1, 0);     glVertex3f( x_size, y_size, -z_size);
    glTexCoord2f(1, 1);     glVertex3f( x_size, y_size,  z_size);
    glTexCoord2f(0, 1);     glVertex3f(-x_size, y_size,  z_size);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, box [2]);
    glBegin(GL_QUADS);
    //front/* z+
    glTexCoord2f(0, 0);     glVertex3f(-x_size, -y_size, -z_size);
    glTexCoord2f(1, 0);     glVertex3f( x_size, -y_size, -z_size);
    glTexCoord2f(1, 1);     glVertex3f( x_size,  y_size, -z_size);
    glTexCoord2f(0, 1);     glVertex3f(-x_size,  y_size, -z_size);
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, box [4]);
    glBegin(GL_QUADS);
    //back x-
    glTexCoord2f(0, 0);     glVertex3f( x_size, -y_size, z_size);
    glTexCoord2f(1, 0);     glVertex3f(-x_size, -y_size, z_size);
    glTexCoord2f(1, 1);     glVertex3f(-x_size,  y_size, z_size);
    glTexCoord2f(0, 1);     glVertex3f( x_size,  y_size, z_size);
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, box [1]);
    glBegin(GL_QUADS);
    //left x-
    glTexCoord2f(0, 0);     glVertex3f(-x_size, -y_size,  z_size);
    glTexCoord2f(1, 0);     glVertex3f(-x_size, -y_size, -z_size);
    glTexCoord2f(1, 1);     glVertex3f(-x_size,  y_size, -z_size);
    glTexCoord2f(0, 1);     glVertex3f(-x_size,  y_size,  z_size);
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, box [3]);
    glBegin(GL_QUADS);
    //right x+
    glTexCoord2f(0, 0);     glVertex3f( x_size, -y_size, -z_size);
    glTexCoord2f(1, 0);     glVertex3f( x_size, -y_size,  z_size);
    glTexCoord2f(1, 1);     glVertex3f( x_size,  y_size,  z_size);
    glTexCoord2f(0, 1);     glVertex3f( x_size,  y_size, -z_size);
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, box [5]);
    glBegin(GL_QUADS);
    //bottom
    glTexCoord2f(0, 0);     glVertex3f(-x_size, -y_size,  z_size);
    glTexCoord2f(1, 0);     glVertex3f( x_size, -y_size,  z_size);
    glTexCoord2f(1, 1);     glVertex3f( x_size, -y_size, -z_size);
    glTexCoord2f(0, 1);     glVertex3f(-x_size, -y_size, -z_size);
    glEnd();
    glDisable(GL_ALPHA_TEST);
    
}

void createRectangle(SkinBox_t& box,float x_size, float y_size, float z_size, int* box_vis)
{
    x_size = x_size / 2;
    y_size = y_size / 2;
    z_size = z_size / 2;
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.8f);
    if (box_vis [0] == 1) {
        glBindTexture(GL_TEXTURE_2D, box [0]);
        glBegin(GL_QUADS);
        //top
        glTexCoord2f(0, 0);     glVertex3f(-x_size, y_size, -z_size);
        glTexCoord2f(1, 0);     glVertex3f( x_size, y_size, -z_size);
        glTexCoord2f(1, 1);     glVertex3f( x_size, y_size,  z_size);
        glTexCoord2f(0, 1);     glVertex3f(-x_size, y_size,  z_size);
        glEnd();
    }
    
    if (box_vis [1] == 1) {
        glBindTexture(GL_TEXTURE_2D, box [2]);
        glBegin(GL_QUADS);
        //front/* z+
        glTexCoord2f(0, 0);     glVertex3f(-x_size, -y_size, -z_size);
        glTexCoord2f(1, 0);     glVertex3f( x_size, -y_size, -z_size);
        glTexCoord2f(1, 1);     glVertex3f( x_size,  y_size, -z_size);
        glTexCoord2f(0, 1);     glVertex3f(-x_size,  y_size, -z_size);
        glEnd();
    }
    
    
    if (box_vis [3] == 1) {
        glBindTexture(GL_TEXTURE_2D, box [4]);
        glBegin(GL_QUADS);
        //back x-
        glTexCoord2f(0, 0);     glVertex3f( x_size, -y_size, z_size);
        glTexCoord2f(1, 0);     glVertex3f(-x_size, -y_size, z_size);
        glTexCoord2f(1, 1);     glVertex3f(-x_size,  y_size, z_size);
        glTexCoord2f(0, 1);     glVertex3f( x_size,  y_size, z_size);
        glEnd();
    }
    
    if (box_vis [2] == 1) {
        glBindTexture(GL_TEXTURE_2D, box [1]);
        glBegin(GL_QUADS);
        //left x-
        glTexCoord2f(0, 0);     glVertex3f(-x_size, -y_size,  z_size);
        glTexCoord2f(1, 0);     glVertex3f(-x_size, -y_size, -z_size);
        glTexCoord2f(1, 1);     glVertex3f(-x_size,  y_size, -z_size);
        glTexCoord2f(0, 1);     glVertex3f(-x_size,  y_size,  z_size);
        glEnd();
    }
    
    if (box_vis [4] == 1) {
        glBindTexture(GL_TEXTURE_2D, box [3]);
        glBegin(GL_QUADS);
        //right x+
        glTexCoord2f(0, 0);     glVertex3f( x_size, -y_size, -z_size);
        glTexCoord2f(1, 0);     glVertex3f( x_size, -y_size,  z_size);
        glTexCoord2f(1, 1);     glVertex3f( x_size,  y_size,  z_size);
        glTexCoord2f(0, 1);     glVertex3f( x_size,  y_size, -z_size);
        glEnd();
    }
    if (box_vis [5] == 1) {
        glBindTexture(GL_TEXTURE_2D, box [5]);
        glBegin(GL_QUADS);
        //bottom
        glTexCoord2f(0, 0);     glVertex3f(-x_size, -y_size,  z_size);
        glTexCoord2f(1, 0);     glVertex3f( x_size, -y_size,  z_size);
        glTexCoord2f(1, 1);     glVertex3f( x_size, -y_size, -z_size);
        glTexCoord2f(0, 1);     glVertex3f(-x_size, -y_size, -z_size);
        glEnd();
    }
    glDisable(GL_ALPHA_TEST);
    
}



void createBox(SkinBox_t& box,float _size)
{
    createRectangle(box, _size, _size, _size);
}

void createBox(SkinBox_t& box,float _size, int* box_vis)
{
    createRectangle(box, _size, _size, _size, box_vis);
}



int DrawMAP (Avatar& God, map_t& map, SkinBox_t* arrayBox) {
    int R = 25;
    
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
                            createBox (arrayBox [GRASS], size, map [x] [y] [z]._box_vis);
                            break;
                            
                        case EARTH:
                            createBox(arrayBox [EARTH], size, map [x] [y] [z]._box_vis);
                            break;
                            
                        case STONE:
                            createBox(arrayBox [STONE], size, map [x] [y] [z]._box_vis);
                            break;
                        case WATER:
                            //glColor4f(1.0f,1.0f,1.0f,0.85f);
                            glAlphaFunc (GL_GREATER, 0.5f);
                            glEnable (GL_ALPHA_TEST);
                            createBox(arrayBox [WATER], size);
                            
                            glColor4f(1.0f,1.0f,1.0f,1.0f);
                            break;
                        default:
                            break;
                    }
                    glTranslatef(-x * size - size / 2, -y * size - size / 2, -z * size - size / 2);
                }
    return 0;
}

int MobDrawHeadMan (SkinBox_t& skin, int w, int h, int d, int angle) {
    //head
    glTranslatef( 0, h * 20 / 32, 0);
    createBox (skin, h * 16 / 32);
    glTranslatef( 0, -h * 20 / 32, 0);
    return 0;
}

int MobDrawLegsRightMan (SkinBox_t& skin, int w, int h, int d, int angle) {
    //legs right
    glTranslatef( -w * 4 / 16,  -h * 12 / 32, 0);
    glRotatef(+angle, 1, 0, 0);
    glTranslatef( 0,  -h * 12 / 32, 0);
    
    createRectangle (skin, w / 2 , h * 24 / 32, d * 2);
    
    glTranslatef( 0, +h * 12 / 32, 0);
    glRotatef(-angle, 1, 0, 0);
    glTranslatef( +w * 4 / 16, +h * 12 / 32, 0);
    return 0;
}

int MobDrawLegsLeftMan (SkinBox_t& skin, int w, int h, int d, int angle) {
    //legs left
    glTranslatef( +w * 4 / 16,  -h * 12 / 32, 0);
    glRotatef(-angle, 1, 0, 0);
    glTranslatef( 0,  -h * 12 / 32, 0);
    
    createRectangle (skin, w / 2 , h * 24 / 32, d * 2);
    
    glTranslatef( -w * 4 / 16, +h * 12 / 32, 0);
    glRotatef(+angle, 1, 0, 0);
    glTranslatef( 0, +h * 12 / 32, 0);
    return 0;
}

int MobDrawArmRightMan (SkinBox_t& skin, int w, int h, int d, int angle) {
    //arm right
    glTranslatef( -w * 12 / 16, h * 12 / 32, 0);
    glRotatef(-angle, 1, 0, 0);
    glTranslatef( 0, -h * 12 / 32, 0);
    createRectangle (skin, w / 2 , h * 24 / 32, d * 2);
    glTranslatef( 0, h * 12 / 32, 0);
    glRotatef(angle, 1, 0, 0);
    glTranslatef( +w * 12 / 16, -h * 12 / 32, 0);
    return 0;
}

int MobDrawArmLeftMan (SkinBox_t& skin, int w, int h, int d, int angle) {
    //arm left
    glTranslatef( +w * 12 / 16, h * 12 / 32, 0);
    glRotatef(+angle, 1, 0, 0);
    glTranslatef( 0, -h * 12 / 32, 0);
    createRectangle (skin, w / 2 , h * 24 / 32, d * 2);
    glTranslatef( 0, h * 12 / 32, 0);
    glRotatef(-angle, 1, 0, 0);
    glTranslatef( -w * 12 / 16, -h * 12 / 32, 0);
    return 0;
}

int GameOBJ::draw () {
    
    
    //body
    glTranslatef( _x,  _y + _h * 4 / 32,  _z);
    createRectangle (_skin->_Body, _w,  _h * 24 / 32, _d * 2);
    
    MobDrawHeadMan (_skin->_Head, _w, _h, _d, _move_time);
    MobDrawLegsRightMan (_skin->_LegsRight, _w, _h, _d, _move_time);
    MobDrawLegsLeftMan (_skin->_LegsLeft, _w, _h, _d, _move_time);
    MobDrawArmRightMan (_skin->_ArmRight, _w, _h, _d, _move_time);
    MobDrawArmLeftMan (_skin->_ArmLeft, _w, _h, _d, _move_time);
    
    glRotatef(-_angleX, 0, 1, 0);
    glTranslatef( -_x,  -_y - _h * 4 / 32,  -_z);
    return 0;
}


int Avatar::draw () {
    //body
    glTranslatef( _x,  _y + 4,  _z);
    glRotatef(+_angleX, 0, 1, 0);
    createRectangle (_skin->_Body, _w, 24, _d * 2);
    MobDrawLegsRightMan (_skin->_LegsRight, _w, _h, _d, _move_time);
    MobDrawLegsLeftMan (_skin->_LegsLeft, _w, _h, _d, _move_time);
    MobDrawArmRightMan (_skin->_ArmRight, _w, _h, _d, _move_time);
    MobDrawArmLeftMan (_skin->_ArmLeft, _w, _h, _d, _move_time);
    
    glRotatef(-_angleX, 0, 1, 0);
    glTranslatef( -_x,  -_y - 4,  -_z);
    
    
    return 0;
}

SkinHuman_t::SkinHuman_t (sf::String name) {
    sf::Image image;
    if (!image.loadFromFile(name))
        return EXIT_FAILURE;
    if (image.getSize().x != 8 * 8 && image.getSize().y != 8 * 8) {
        if (image.getSize().x > image.getSize().y) {
            SetSize_pix(image.getSize().y / 8);
        } else
            SetSize_pix(image.getSize().x / 8);
    }
    //Head
    sf::Rect<int> rect_Head (0, 0, 4 * size_pix, size_pix * 2);
    for (int i = 0; i < 6; i++)
        _Head [i] = LoadTextureHead (i, image, rect_Head);
    
    //_Body
    sf::Rect<int> rect_Body (size_pix * 2, size_pix * 2, size_pix * 5, size_pix * 4);
    for (int i = 0; i < 6; i++)
        _Body [i] = LoadTextureBody (i, image, rect_Body);
    
    //_ArmLeft
    sf::Rect<int> rect_ArmLeft (size_pix * 5, size_pix * 2, 7 * size_pix, size_pix * 4);
    for (int i = 0; i < 6; i++)
        _ArmLeft [i] = LoadTextureArmAndLegs (i, image, rect_ArmLeft);
    
    //_ArmRight
    sf::Rect<int> rect_ArmRight (size_pix * 4, size_pix * 6, 6 * size_pix, size_pix * 8);
    for (int i = 0; i < 6; i++)
        _ArmRight [i] = LoadTextureArmAndLegs (i, image, rect_ArmLeft);
    
    //_LegsLeft
    sf::Rect<int> rect_LegsLeft (0, size_pix * 2, 2 * size_pix, size_pix * 4);
    for (int i = 0; i < 6; i++)
        _LegsLeft [i] = LoadTextureArmAndLegs (i, image, rect_LegsLeft);
    
    //_LegsRight
    sf::Rect<int> rect_LegsRight (size_pix * 2, size_pix * 6, 4 * size_pix, size_pix * 8);
    for (int i = 0; i < 6; i++)
        _LegsRight [i] = LoadTextureArmAndLegs (i, image, rect_LegsLeft);
    
    
    
    
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glClearDepth(1.f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.f, 1.f, 1.f, 2000.f);
    glEnable(GL_TEXTURE_2D);
}

GLuint SkinHuman_t::LoadText ( sf::Image& image, sf::Rect <int>& rect_end, int x, int y) {
    
    
    sf::Image image_end;
    image_end.create(x, y);//, sf::Color (0, 0, 0, 255));
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


GLuint SkinHuman_t::LoadTextureHead (int i, sf::Image& image, sf::Rect <int>& rect_end) {
    
    sf::Image image_end;
    image_end.create(4 * size_pix, size_pix * 2);// sf::Color (0, 0, 0, 255);
    image_end.copy(image, 0, 0, rect_end, true);
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
    switch (i) {
        case 0:
            x1 = size_pix; y1 = 0; x2 = size_pix * 2; y2 = size_pix;
            break;
        case 5:
            x1 = size_pix * 2; y1 = 0; x2 = size_pix * 3; y2 = size_pix;
            break;
        case 1:
            x1 = 0; y1 = size_pix; x2 = size_pix; y2 = size_pix * 2;
            break;
        case 2:
            x1 = size_pix; y1 = size_pix; x2 = 2 * size_pix; y2 = 2 * size_pix;
            break;
        case 3:
            x1 = size_pix * 2; y1 = size_pix; x2 = 3 * size_pix; y2 = 2 * size_pix;
            break;
        case 4:
            x1 = 3 * size_pix; y1 = size_pix; x2 = size_pix * 4; y2 = size_pix * 2;
            break;
            
        default:
            break;
    }
    sf::Rect<int> rect_end1 (x1, y1, x2, y2);
    
    return LoadText(image_end, rect_end1, x2 - x1, y2 - y1);
}

GLuint SkinHuman_t::LoadTextureBody (int i, sf::Image& image, sf::Rect <int>& rect_end) {
    
    sf::Image image_end;
    image_end.create(3 * size_pix, size_pix * 2);// sf::Color (0, 0, 0, 255);
    image_end.copy(image, 0, 0, rect_end, true);
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
    switch (i) {
        case 0:
            x1 = size_pix / 2; y1 = 0; x2 = (size_pix * 3) / 2; y2 = size_pix / 2;
            break;
        case 5:
            x1 = (size_pix * 3) / 2; y1 = 0; x2 = (size_pix * 5) / 2; y2 = size_pix / 2;
            break;
        case 1:
            x1 = 0; y1 = size_pix / 2; x2 = size_pix / 2; y2 = size_pix * 2;
            break;
        case 2:
            x1 = size_pix / 2; y1 = size_pix / 2; x2 = (size_pix * 3) / 2; y2 = size_pix * 2;
            break;
        case 3:
            x1 = (size_pix * 3) / 2; y1 = size_pix / 2; x2 = size_pix * 2; y2 = size_pix * 2;
            break;
        case 4:
            x1 = size_pix * 2; y1 = size_pix / 2; x2 = (size_pix * 5) / 2; y2 = size_pix * 2;
            break;
            
        default:
            break;
    }
    sf::Rect<int> rect_end1 (x1, y1, x2, y2);
    
    return LoadText(image_end, rect_end1, x2 - x1, y2 - y1);
}



GLuint SkinHuman_t::LoadTextureArmAndLegs (int i, sf::Image& image, sf::Rect <int>& rect_end) {
    
    sf::Image image_end;
    image_end.create(2 * size_pix, size_pix * 2);// sf::Color (0, 0, 0, 255);
    image_end.copy(image, 0, 0, rect_end, true);
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
    switch (i) {
        case 0:
            x1 = size_pix / 2; y1 = 0; x2 = size_pix; y2 = size_pix / 2;
            break;
        case 5:
            x1 = size_pix; y1 = 0; x2 = (size_pix * 3) / 2; y2 = size_pix / 2;
            break;
        case 1:
            x1 = 0; y1 = size_pix / 2; x2 = size_pix / 2; y2 = size_pix * 2;
            break;
        case 2:
            x1 = size_pix / 2; y1 = size_pix / 2; x2 = size_pix; y2 = size_pix * 2;
            break;
        case 3:
            x1 = size_pix; y1 = size_pix / 2; x2 = (size_pix * 3) / 2; y2 = size_pix * 2;
            break;
        case 4:
            x1 = (size_pix * 3) / 2; y1 = size_pix / 2; x2 = size_pix * 2; y2 = size_pix * 2;
            break;
            
        default:
            break;
    }
    sf::Rect<int> rect_end1 (x1, y1, x2, y2);
    
    return LoadText(image_end, rect_end1, x2 - x1, y2 - y1);
}





#endif HELPFILE_H
