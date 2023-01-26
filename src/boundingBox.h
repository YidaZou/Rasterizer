//
//  boundingBox.h
//  A1
//
//  Created by Yida Zou on 1/26/23.
//

#ifndef boundingBox_h
#define boundingBox_h
#include <vector>
#include <algorithm>
#include "Image.h"

vector<float> findBounds(vector<Vertex> vertices){
    float xMin = vertices[0].x;
    float xMax = vertices[0].x;
    float yMin = vertices[0].y;
    float yMax = vertices[0].y;
    for(auto v : vertices){
        if(v.x < xMin){
            xMin = v.x;
        }
        if(v.x > xMax){
            xMax = v.x;
        }
        if(v.y < yMin){
            yMin = v.y;
        }
        if(v.y > yMax){
            yMax = v.y;
        }
    }
    return {xMin,xMax,yMin,yMax};
}

void drawBox(Triangle t, vector<float> color, std::shared_ptr<Image> image){
    int xMin = std::min({t.a.x,t.b.x,t.c.x});
    int xMax = std::max({t.a.x,t.b.x,t.c.x});
    int yMin = std::min({t.a.y,t.b.y,t.c.y});
    int yMax = std::max({t.a.y,t.b.y,t.c.y});
    for(int y = yMin; y <= yMax; ++y) {
        for(int x = xMin; x <= xMax; ++x) {
            image->setPixel(x, y, color[0], color[1], color[2]);
        }
    }
}

#endif /* boundingBox_h */
