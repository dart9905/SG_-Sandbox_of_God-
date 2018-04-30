#ifndef HELPFILE_H
#define HELPFILE_H



GLuint LoadTexture(sf::String name);



int MakeTextures (GLuint box_terra [], GLuint box [], GLuint skybox []) {
    box [0] = LoadTexture(resourcePath() + "resources/grassBox/top.jpg");
    for (int i = 1; i < 5; i ++) {
        box [i] = LoadTexture(resourcePath() + "resources/grassBox/side.jpg");
    }
    box [5] = LoadTexture(resourcePath() + "resources/grassBox/bottom.jpg");
    
    for (int i = 0; i < 6; i ++) {
        box_terra [i] = LoadTexture(resourcePath() + "resources/grassBox/bottom.jpg");
    }
    
    
    /*
    skybox [0] = LoadTexture(resourcePath() + "resources/skybox/skybox_top.bmp");
    skybox [1] = LoadTexture(resourcePath() + "resources/skybox/skybox_front.bmp");
    skybox [2] = LoadTexture(resourcePath() + "resources/skybox/skybox_back.bmp");
    skybox [3] = LoadTexture(resourcePath() + "resources/skybox/skybox_left.bmp");
    skybox [4] = LoadTexture(resourcePath() + "resources/skybox/skybox_right.bmp");
    skybox [5] = LoadTexture(resourcePath() + "resources/skybox/skybox_bottom.bmp");
    */
    skybox [0] = LoadTexture(resourcePath() + "resources/skybox4/skybox_front.bmp");
    skybox [1] = LoadTexture(resourcePath() + "resources/skybox4/skybox_top.jpg");
    skybox [2] = LoadTexture(resourcePath() + "resources/skybox4/skybox_bottom.jpg");
    skybox [3] = LoadTexture(resourcePath() + "resources/skybox4/skybox_right.jpg");
    skybox [4] = LoadTexture(resourcePath() + "resources/skybox4/skybox_left.jpg");
    skybox [5] = LoadTexture(resourcePath() + "resources/skybox4/skybox_back.jpg");
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

		return texture;
}


void createBox(GLuint box[],float size)
{
    
    
        glBindTexture(GL_TEXTURE_2D, box[0]);
        glBegin(GL_QUADS);
            //top
            glTexCoord2f(0, 0);     glVertex3f(-size, size, -size);
            glTexCoord2f(1, 0);     glVertex3f( size, size, -size);
            glTexCoord2f(1, 1);     glVertex3f( size, size,  size);
            glTexCoord2f(0, 1);     glVertex3f(-size, size,  size);
        glEnd();
	    glBindTexture(GL_TEXTURE_2D, box[1]);
	    glBegin(GL_QUADS);
		    //front
            glTexCoord2f(0, 0);     glVertex3f(-size, -size, -size);
            glTexCoord2f(1, 0);     glVertex3f( size, -size, -size);
            glTexCoord2f(1, 1);     glVertex3f( size,  size, -size);
            glTexCoord2f(0, 1);     glVertex3f(-size,  size, -size);
        glEnd();
		
	    glBindTexture(GL_TEXTURE_2D, box[2]);
	    glBegin(GL_QUADS);
			//back
            glTexCoord2f(0, 0);     glVertex3f( size, -size, size);
            glTexCoord2f(1, 0);     glVertex3f(-size, -size, size);
            glTexCoord2f(1, 1);     glVertex3f(-size,  size, size);
            glTexCoord2f(0, 1);     glVertex3f( size,  size, size);
        glEnd();
    
		glBindTexture(GL_TEXTURE_2D, box[3]);
	    glBegin(GL_QUADS);
			//left
            glTexCoord2f(0, 0);     glVertex3f(-size, -size,  size);
            glTexCoord2f(1, 0);     glVertex3f(-size, -size, -size);
            glTexCoord2f(1, 1);     glVertex3f(-size,  size, -size);
            glTexCoord2f(0, 1);     glVertex3f(-size,  size,  size);
        glEnd();
    
		glBindTexture(GL_TEXTURE_2D, box[4]);
	    glBegin(GL_QUADS);
			//right
            glTexCoord2f(0, 0);     glVertex3f( size, -size, -size);
            glTexCoord2f(1, 0);     glVertex3f( size, -size,  size);
            glTexCoord2f(1, 1);     glVertex3f( size,  size,  size);
            glTexCoord2f(0, 1);     glVertex3f( size,  size, -size);
        glEnd();

		glBindTexture(GL_TEXTURE_2D, box[5]);
	    glBegin(GL_QUADS);
			//bottom
            glTexCoord2f(0, 0);     glVertex3f(-size, -size,  size);
            glTexCoord2f(1, 0);     glVertex3f( size, -size,  size);
            glTexCoord2f(1, 1);     glVertex3f( size, -size, -size);
            glTexCoord2f(0, 1);     glVertex3f(-size, -size, -size);
        glEnd();
        
}



#endif HELPFILE_H
