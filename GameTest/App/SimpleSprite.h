//-----------------------------------------------------------------------------
// SimpleSprite.h
// Privides a very simple DSOUND wrapper to load and play wav files.
//-----------------------------------------------------------------------------
#ifndef _SIMPLESPRITE_H_
#define _SIMPLESPRITE_H_

#include "../glut/include/GL/freeglut.h"
#include <map>
#include <vector>
#include <string>

//-----------------------------------------------------------------------------
// CSimpleSprite
//-----------------------------------------------------------------------------
class CSimpleSprite
{
public:
    // fileName: File must be a 32 bit BMP format (A8 R8 G8 B8). The alpha channel can be used to mask out the sprite.
	// nColumns and nRows defines the number of frames in the sprite page. 
    CSimpleSprite(const char *fileName, unsigned int nColumns = 1, unsigned int nRows = 1 );
	// Update, call from your game update function.
    void Update(float dt);
	// Draw, call from your game draw function.
    void Draw();
	
	// Sets and Gets for the various attributes of the sprite.
    void SetPosition(float x, float y) { m_xpos = x; m_ypos = y; }   
    void SetAngle(float a)  { m_angle = a; }
    void SetScale(float s) { m_scale = s; }
    void SetFrame(unsigned int f);
    
	void GetPosition(float &x, float &y) { x = m_xpos; y = m_ypos; }
    float GetWidth()  const { return m_width;  }
    float GetHeight() const { return m_height; }
    float GetAngle()  const { return m_angle;  }
    float GetScale()  const { return m_scale;  }    
	unsigned int GetFrame()  const { return m_frame; }

	// Set the sprite color. r,g,b for color and a= the alpha value (Fade).
	void SetColor(float r, float g, float b, float a = 1.0f) { m_red = r; m_green = g; m_blue = b; m_alpha = a; }

    // Create an animation. 
	// ID, Gives this animation a unique id.
	// speed, Set the movement speed for this sprite.
	// frames, provide a vector of sprite frame indices. Indices into your sprite page.
	void CreateAnimation( unsigned int id, float speed, const std::vector<int> &frames);;
	// Set the current animation to play.
	// Note -1 will stop the animation.
	void SetAnimation(int id);

	//------------------------------------------------------------
	// Advanced:
	//------------------------------------------------------------
	// Directly set the local coordinates of the sprite.
	// Use only if you want non uniform sprites. Skewing or perspective can be achieved using this.
	void SetVertex(unsigned int i, float v) { if(i < 8) m_points[i] = v; }
	float GetVertex(unsigned int i) { if (i >= 8) i = 0; return m_points[i]; }

private:
    void CalculateUVs();
    GLuint m_texture;
    float m_xpos = 0.0F;
    float m_ypos = 0.0F;
    float m_width = 0.0F;
    float m_height = 0.0F;
    unsigned int   m_texWidth = 0;
    unsigned int   m_texHeight = 0;
    float m_angle = 0.0F;
    float m_scale = 1.0F;
    float m_points[8];    
    float m_uvcoords[8];
    unsigned int   m_frame;
    unsigned int   m_nColumns;
    unsigned int   m_nRows;
	float m_red = 1.0f;
	float m_green = 1.0f;
	float m_blue = 1.0f;
	float m_alpha = 1.0f;
    int     m_currentAnim = -1;
    float   m_animTime = 0.0F;

    struct sAnimation
    {
        unsigned int m_id;
        float m_speed;
        std::vector<int> m_frames;
    };
    std::vector<sAnimation> m_animations;

    // Texture management.
    struct sTextureDef
    {
        unsigned int m_width;
        unsigned int m_height;
        GLuint m_textureID;
    };
    bool LoadTexture(const char*);
    static std::map<std::string, sTextureDef > m_textures;
    
};

#endif