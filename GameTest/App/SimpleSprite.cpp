///////////////////////////////////////////////////////////////////////////////
// Filename: SimpleSprite.cpp
// Privides a very simple DSOUND wrapper to load and play wav files.
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
#include "../stdafx.h"
//-----------------------------------------------------------------------------
#include <windows.h>
#include <stdio.h>
#include <assert.h>
//-----------------------------------------------------------------------------

#include "app.h"
#include "AppSettings.h"
#include "TextureLoader.h"
#include "SimpleSprite.h"

#include "../glut/include/GL/freeglut_ext.h"

std::map<std::string, CSimpleSprite::sTextureDef > CSimpleSprite::m_textures;

//-----------------------------------------------------------------------------
CSimpleSprite::CSimpleSprite(const char *fileName, unsigned int nColumns, unsigned int nRows, int frame, float scale)
	: m_nColumns(nColumns)
	, m_nRows(nRows)
    , m_frame(frame)
    , m_scale(scale)
{
	if (LoadTexture(fileName))
	{
		CalculateUVs();
		m_points[0] = -(m_width / 2.0f);
		m_points[1] = -(m_height / 2.0f);
		m_points[2] = m_width / 2.0f;
		m_points[3] = -(m_height / 2.0f);
		m_points[4] = m_width / 2.0f;
		m_points[5] = m_height / 2.0f;
		m_points[6] = -(m_width / 2.0f);
		m_points[7] = m_height / 2.0f;
	}
}

void CSimpleSprite::Update(float dt)
{
    if (m_currentAnim >= 0)
    {
        sAnimation& anim = m_animations[m_currentAnim];
        m_animTime += dt/1000.0f;
        float duration = anim.m_speed * anim.m_frames.size();
        if (m_animTime > duration)
        {
            m_animTime = m_animTime - duration;
        }

        int frame = (int)( m_animTime / anim.m_speed );
        m_frame = frame;
		frame %= anim.m_frames.size();
        SetFrame(anim.m_frames[frame]);        

        // Stop playing the animation
        if (anim.m_frames[frame] == anim.m_frames[anim.m_frames.size() - 1] && !anim.m_loop)
        {
            m_currentAnim = -1;
            return;
        }
    }
}

void CSimpleSprite::CalculateUVs()
{
    float u = 1.0f / m_nColumns;
    float v = 1.0f / m_nRows;
    int row = m_frame / m_nColumns;
    int column = m_frame % m_nColumns;

    m_width = m_texWidth * u;
    m_height = m_texHeight * v;
    m_uvcoords[0] = u * column;
    m_uvcoords[1] = v * (float)(row+1);

    m_uvcoords[2] = u * (float)(column+1);
    m_uvcoords[3] = v * (float)(row + 1);

    m_uvcoords[4] = u * (float)(column + 1);
    m_uvcoords[5] = v * row;

    m_uvcoords[6] = u * column;
    m_uvcoords[7] = v * row;
}

void CSimpleSprite::Draw()
{            
#if APP_USE_VIRTUAL_RES
    float scalex = m_scale / APP_VIRTUAL_WIDTH;
    float scaley = m_scale / APP_VIRTUAL_HEIGHT;
#else
    float scalex = m_scale;
    float scaley = m_scale;
#endif
    float x = m_xpos;
    float y = m_ypos;
#if APP_USE_VIRTUAL_RES
    APP_VIRTUAL_TO_NATIVE_COORDS(x, y);
#endif
    
    glPushMatrix();
    glTranslatef(x, y, 0.0f);   
    glScalef(scalex, scaley, 1.f);    
    glRotatef(m_angle * 180 / PI, 0.0f, 0.0f, 1.0f);     
	glColor4f(m_red, m_green, m_blue, m_alpha);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    glBegin(GL_QUADS);

    std::vector<unsigned int> uvIDs = {
        0, 1,   // top left
        2, 3,   // top right
        4, 5,   // bot right
        6, 7    // bot left
    };

    if (m_verticalFlip)
    {
        uvIDs = {
            2, 3,   // top right
            0, 1,   // top left
            6, 7,   // bot left
            4, 5    // bot right
        };
    }
    
    for (unsigned int i = 0; i < 8; i += 2)
    {
        glTexCoord2f(m_uvcoords[i], m_uvcoords[i + 1]);
        glVertex2f(m_points[uvIDs[i]], m_points[uvIDs[i + 1]]);
    }
    glEnd();
    glPopMatrix();
    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
}

void CSimpleSprite::SetFrame(unsigned int f)
{
    m_frame = f;
    if (m_frame > m_nRows*m_nColumns)
    {
        m_frame = 0;
    }
    CalculateUVs();
}

void CSimpleSprite::SetAnimation(int id)
{
    for (int i = 0; i < m_animations.size(); i++)
    {
        if (m_animations[i].m_id == id)
        {
            m_currentAnim = i;
            return;
        }
    }
	m_currentAnim = -1;
}

void CSimpleSprite::CreateAnimation(unsigned int id, float speed, const std::vector<int> &frames, bool loop)
{
	sAnimation anim;
	anim.m_id = id;
	anim.m_speed = speed;
	anim.m_frames = frames;
    anim.m_loop = loop;
	m_animations.push_back(anim);
}

bool CSimpleSprite::LoadTexture(const char * filename)
{
    if (m_textures.find(filename) != m_textures.end())
    {        
        sTextureDef &texDef = m_textures[filename];
        m_texture = texDef.m_textureID;
        m_texWidth = texDef.m_width;
        m_texHeight = texDef.m_height;
		return true;
    }
    
    unsigned char *imageData = loadBMPRaw(filename, m_texWidth, m_texHeight, true);

    GLuint texture = 0;
	if (imageData)
	{
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_texWidth, m_texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

		free(imageData);
		sTextureDef textureDef = { m_texWidth, m_texHeight, texture };
		m_textures[filename] = textureDef;
		m_texture = texture;
		return true;
	}
	return false;
}
