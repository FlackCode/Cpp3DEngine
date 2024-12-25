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

class olcEngine3D : public olcConsoleGameEngine {
public:
    olcEngine3D() {
        m_sAppName = L"3D Demo"; //unicode is enabled
    }

private:
    mesh meshCube;

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

        return true; //continue running
    }

    bool OnUserUpdate(float fElapsedTime) override {
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
