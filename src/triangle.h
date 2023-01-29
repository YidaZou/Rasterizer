//
//  triangle.h
//  A1
//
//  Created by Yida Zou on 1/26/23.
//

#ifndef triangle_h
#define triangle_h

#include <stdio.h>
#include <cmath>
#include <vector>

using std::vector;

struct Vertex {
    float x, y, z;
    int r,g,b;
};

struct Triangle{
    Vertex a, b, c;
};

//area of triangle formed by v1, v2, and v3
float triangleArea(Vertex& v1, Vertex& v2, Vertex& v3){
   return abs((v1.x*(v2.y-v3.y) + v2.x*(v3.y-v1.y)+ v3.x*(v1.y-v2.y))/2.0);
}

//check whether v is inside triangle
bool isInside(Vertex& v1, Vertex& v2, Vertex& v3, Vertex& v){
   float area = triangleArea(v1, v2, v3);  //area of triangle ABC
   float area1 = triangleArea(v, v2, v3);  //area of vBC
   float area2 = triangleArea(v1, v, v3);  //area of AvC
   float area3 = triangleArea(v1, v2, v);  //area of ABv

   return (abs(area - (area1 + area2 + area3)) < 0.01);  //is inside if areas add up
}

vector<unsigned char> colorWeight(Vertex& v1, Vertex& v2, Vertex& v3, Vertex& v){
    //weights of the 3 triangle vertexes
    float w1 = 1/(sqrt(pow(v1.x-v.x,2) + pow(v1.y-v.y,2)));
    float w2 = 1/(sqrt(pow(v2.x-v.x,2) + pow(v2.y-v.y,2)));
    float w3 = 1/(sqrt(pow(v3.x-v.x,2) + pow(v3.y-v.y,2)));
    
    //colored weights of vertex
    unsigned char r = (w1*v1.r + w2*v2.r + w3*v3.r)/(w1+w2+w3);
    unsigned char g = (w1*v1.g + w2*v2.g + w3*v3.g)/(w1+w2+w3);
    unsigned char b = (w1*v1.b + w2*v2.b + w3*v3.b)/(w1+w2+w3);
    
    return {r,g,b};
}

vector<Vertex> toVertices(vector<float>& posBuf){
    vector<Vertex> vertices;
    for(int i=0; i<posBuf.size()-2; i+=3){
        Vertex v;
        v.x = posBuf[i];
        v.y = posBuf[i+1];
        v.z = posBuf[i+2];
        vertices.push_back(v);
    }
    return vertices;
}

vector<Triangle> toTriangles(vector<Vertex>& vertices){
    vector<Triangle> triangles;
    for(int i=0; i<vertices.size()-2; i+=3){
        Triangle t;
        t.a = vertices[i];
        t.b = vertices[i+1];
        t.c = vertices[i+2];
        triangles.push_back(t);
        //std::cout << i << ": " << t.a.x << t.b.x << t.c.x << std::endl;
    }
    return triangles;
}

#endif /* triangle_h */