#ifndef HELPFILE_H
#define HELPFILE_H

#define GL_CLAMP_TO_EDGE 0x812F

const float PI =3.141592653; 
float size = 20.f;

bool check(int x, int y, int z);


class Playr {
public:
    
    float x, y, z;
    float dx, dy, dz;
    float w, h, d;
    bool onGround;
    float speed;
    
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
        speed = 5;
        onGround = false;
    }
    
    
    
    void collision (float Dx, float Dy, float Dz) {
        for (int X = (x - w) / size; X < (x + w)/ size; X++)
            for (int Y = (y - h) / size; Y < (y + h)/ size; Y++)
                for (int Z = (z - d) / size; Z < (z + d)/ size; Z++)
                    if (check(X, Y, Z)) {
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
            y += dy;
            z += dz;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            dx =  sin (angleX / 180 * PI) * speed;
            dz =  cos (angleX / 180 * PI) * speed;
            x += dx;
            y += dy;
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
    
    
    
    void update (float time) {
        if (!onGround)
            dy -= 1.5 * time;
        onGround = false;
        
        x += dx * time;
        collision(dx, 0, 0);
        
        y += dy * time;
        collision(0, dy, 0);
        
        z += dz * time;
        collision(0, 0, dz);
        
        dz = 0;
        dx = 0;
    }
};





GLuint LoadTexture(sf::String name)
{
	    sf::Image image;
        if (!image.loadFromFile(name))
            return EXIT_FAILURE;

		image.flipVertically(); 

		GLuint texture=0;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
    
    //
    //          The lower function is the union of these two.
    //
    /*
     glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
     image.getSize().x,
     image.getSize().y,
     0, GL_RGBA, GL_UNSIGNED_BYTE,
     image.getPixelsPtr());
     */
    
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


bool check(int x, int y, int z)
{
   if ((x<0) || (x>=1000) || 
	   (y<0) || (y>=1000) || 
	   (z<0) || (z>=1000)) return false;
  
   return map[x][y][z];
}



#endif HELPFILE_H
