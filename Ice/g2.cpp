#include "stdafx.h"

//#include <map>

#include "AceProgram.hpp"
#include "AceColRect.hpp"

#include "g2.h"

extern AceProgram* ProgCol;
extern AceColRect* RectCol;

using namespace g2::Internal;

//std::map<GLuint, int*> dimByTid;

void g2::ortho(int width, int height) {
    WinOrtho = glm::ortho(0.f, (float)width, 0.f, (float)height);
}

void g2::viewport(int width, int height) {
    glViewport(0, 0, width, height);
}

void g2::clear() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void g2::rgb(unsigned char _red, unsigned char _green, unsigned char _blue) {
    red = _red / 255.f;
    green = _green / 255.f;
    blue = _blue / 255.f;

    if (beginType == 1) {
        quadRed[quadIndex] = red;
        quadGreen[quadIndex] = green;
        quadBlue[quadIndex] = blue;

        ++quadIndex;
    }
}

void g2::rect(int left, int bottom, int width, int height) {
    if (beginType == 1) {
        quadLeft = left;
        quadBottom = bottom;
        quadWidth = width;
        quadHeight = height;
    }
    else {
        RectCol->draw(ProgCol, left, bottom, width, height, &WinOrtho, red, green, blue);
    }
}

void g2::beginQuad() {
    beginType = 1;
    quadIndex = 0;
}

void g2::end() {
    if (beginType == 1) {
        RectCol->draw(ProgCol, quadLeft, quadBottom, quadWidth, quadHeight, &WinOrtho, quadRed, quadGreen, quadBlue);
    }

    beginType = 0;
}

//void g2::uninit() {
    //clear dimByTid
//}

GLuint g2::createTexture() {
    GLuint tid;

    glGenTextures(1, &tid);

    return tid;
}

void g2::freeTexture(GLuint tid) {
    glDeleteTextures(1, &tid);
}

void g2::beginTexture(GLuint tid) {
    beginType = 2;

    textureId = tid;

    glBindTexture(GL_TEXTURE_2D, tid);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

int textureWidth, textureHeight;

void g2::size(int width, int height) {
    textureWidth = width;
    textureHeight = height;
}

namespace g2 {
    namespace Internal {
        float red;
        float green;
        float blue;

        glm::mat4 WinOrtho;

        // 0: none, 1: quad, 2: texture
        int beginType;

        // texture
        GLuint textureId;

        // quad
        int quadIndex;
    
        float quadRed[4];
        float quadGreen[4];
        float quadBlue[4];

        float quadLeft;
        float quadBottom;
        float quadWidth;
        float quadHeight;
    }
}

