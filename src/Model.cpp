#include "Model.h"
#include <sstream>
#include <fstream>
#include <iostream>

Model::Model(std::string path)
{
    std::ifstream in;
    in.open(path, std::ifstream::in);

    if (in.fail()) return;

    std::string line;

    while (!in.eof())
    {
        std::getline(in, line);
        std::istringstream iss (line.c_str());

        char trash;

        if (!line.compare(0, 2, "v "))
        {
            iss >> trash;
            
            vec3 v = { 0.0f, 0.0f, 0.0f };

            for (int i : { 0, 1, 2 }) iss >> v[i];

            m_Verts.push_back(v);
        } else if (!line.compare(0, 2, "f "))
        {
            int f = 0;
            int t = 0;
            int n = 0;
            int count = 0;

            iss >> trash;

            while (iss >> f >> trash >> t >> trash >> n)
            {
                m_FacesVerts.push_back(--f);
                count++;
            }

            if (count != 3)
            {
                std::cerr << "The obj file is supposed to be triangulated" << std::endl;
                return;
            }
        }
    }
}

int Model::NumVerts()
{
    return m_Verts.size();
}

int Model::NumFaces()
{
    return m_FacesVerts.size() / 3;
}

vec3 Model::Vertex(int index)
{
    return m_Verts[index];
}

vec3 Model::Vertex(int faceIndex, int numVertex)
{
    return m_Verts[m_FacesVerts[faceIndex * 3 + numVertex]];
}