#pragma once

#include "Geometry.h"
#include "TGAImage.h"
#include <vector>
#include <string>

class Model
{
public:
    Model(std::string path);

    int NumVerts();
    int NumFaces();

    vec3 Vertex(int index);
    vec3 Vertex(int faceIndex, int numVertex);

private:
    std::vector<vec3> m_Verts;
    std::vector<int> m_FacesVerts;

};