#include "olcConsoleGameEngine.h"
using namespace std;

struct vec3d {
    float x, y, z;
};

struct triangle {
    vec3d p[3]; //grouping 3 vertices
};

struct mesh {
    vector<triangle> tris;
};

struct mat4x4 {
    float m[4][4] = { 0 }; //Row & Col
};

class olcEngine3D : public olcConsoleGameEngine {
public:
    olcEngine3D() {
        m_sAppName = L"3D Demo"; //unicode is enabled
    }

private:
    mesh meshCube;
    mat4x4 matProj;

    void MultiplyMatrixVector(vec3d &i, vec3d &o, mat4x4 &m) { //i is for input, o is for output, m is for matrix
        o.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + m.m[3][0];
        o.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + m.m[3][1];
        o.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + m.m[3][2];
        float w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + m.m[3][3];

        if (w != 0) {
            o.x /= w;
            o.y /= w;
            o.z /= w;
        }
    }

public:
    bool OnUserCreate() override {

        meshCube.tris = {
            //South
            {0.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,   1.0f, 1.0f, 0.0f},
            {0.0f, 0.0f, 0.0f,  1.0f, 1.0f, 0.0f,   1.0f, 0.0f, 0.0f},

            //East
            {1.0f, 0.0f, 0.0f,  1.0f, 1.0f, 0.0f,   1.0f, 1.0f, 1.0f},
            {1.0f, 0.0f, 0.0f,  1.0f, 1.0f, 1.0f,   1.0f, 0.0f, 1.0f},

            //North
            {1.0f, 0.0f, 1.0f,  1.0f, 1.0f, 1.0f,   0.0f, 1.0f, 1.0f},
            {1.0f, 0.0f, 1.0f,  0.0f, 1.0f, 1.0f,   0.0f, 0.0f, 1.0f},

            //West
            {0.0f, 0.0f, 1.0f,  0.0f, 1.0f, 1.0f,   0.0f, 1.0f, 0.0f},
            {0.0f, 0.0f, 1.0f,  0.0f, 1.0f, 0.0f,   0.0f, 0.0f, 0.0f},

            //Top
            {0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 1.0f,   1.0f, 1.0f, 0.0f},
            {0.0f, 1.0f, 0.0f,  1.0f, 1.0f, 1.0f,   1.0f, 1.0f, 0.0f},

            //Bottom
            {1.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 0.0f},
            {1.0f, 0.0f, 1.0f,  0.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f},
        };

        //Matrix
        float fNear = 0.1f; //zNear
        float fFar = 1000.0f; //zFar
        float fFov = 90.0f;
        float fAspectRatio = (float)ScreenHeight() / (float)ScreenWidth(); // aspectRatio = height/width
        float fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * 3.14159f); // 180*pi is to convert to radians

        matProj.m[0][0] = fAspectRatio * fFovRad;
        matProj.m[1][1] = fFovRad;
        matProj.m[2][2] = fFar / (fFar - fNear);
        matProj.m[3][2] = (-fFar * fNear) / (fFar - fNear);
        matProj.m[2][3] = 1.0f;
        matProj.m[3][3] = 0.0f;


        return true; //continue running
    }

    bool OnUserUpdate(float fElapsedTime) override {

        Fill(0, 0, ScreenWidth(), ScreenHeight(), PIXEL_SOLID, FG_BLACK);

        for (auto tri : meshCube.tris) {
            triangle triProjected;
            MultiplyMatrixVector(tri.p[0], triProjected.p[0], matProj);
            MultiplyMatrixVector(tri.p[1], triProjected.p[1], matProj);
            MultiplyMatrixVector(tri.p[2], triProjected.p[2], matProj);

            DrawTriangle(triProjected.p[0].x, triProjected.p[0].y,
                triProjected.p[1].x, triProjected.p[1].y,
                triProjected.p[2].x, triProjected.p[2].y,
                PIXEL_SOLID, FG_WHITE);
        }


        return true;
    }
};

int main()
{
    olcEngine3D demo;
    if (demo.ConstructConsole(256, 240, 4, 4)) {
        demo.Start();
    }
}
