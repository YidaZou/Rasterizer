//
//  drawing.h
//  A1
//
//  Created by Yida Zou on 1/26/23.
//

#ifndef drawing_h
#define drawing_h

//draw bounding boxes
void drawBox(Triangle& t, float (&color)[3], std::shared_ptr<Image>& image){
    //bounds of triangle
    int xMin = std::min({t.a.x,t.b.x,t.c.x});
    int xMax = std::max({t.a.x,t.b.x,t.c.x});
    int yMin = std::min({t.a.y,t.b.y,t.c.y});
    int yMax = std::max({t.a.y,t.b.y,t.c.y});
    
    //drawing
    for(int y = yMin; y <= yMax; ++y) {
        for(int x = xMin; x <= xMax; ++x) {
            image->setPixel(x, y, color[0], color[1], color[2]);
        }
    }
}

//draw triangles
void drawTriangle(Triangle& t, float (&color)[3], std::shared_ptr<Image>& image){
    //bounds of triangle
    int xMin = std::min({t.a.x,t.b.x,t.c.x});
    int xMax = std::max({t.a.x,t.b.x,t.c.x});
    int yMin = std::min({t.a.y,t.b.y,t.c.y});
    int yMax = std::max({t.a.y,t.b.y,t.c.y});
    
    //drawing
    Vertex v;
    for(int y = yMin; y <= yMax; ++y) {
        for(int x = xMin; x <= xMax; ++x) {
            v.x = x; v.y = y;
            //std::cout<<"p: " <<v.x << " " << v.y << std::endl;
            if(isInside(t.a, t.b, t.c, v)){
                image->setPixel(x, y, color[0], color[1], color[2]);
            }
        }
    }
}

//draw per-vertex colored triangles
void drawPerVertexTriangle(Triangle& t, std::shared_ptr<Image>& image){
    //bounds of triangle
    int xMin = std::min({t.a.x,t.b.x,t.c.x});
    int xMax = std::max({t.a.x,t.b.x,t.c.x});
    int yMin = std::min({t.a.y,t.b.y,t.c.y});
    int yMax = std::max({t.a.y,t.b.y,t.c.y});
    
    //drawing
    Vertex v;
    for(int y = yMin; y <= yMax; ++y) {
        for(int x = xMin; x <= xMax; ++x) {
            v.x = x; v.y = y;
            if(isInside(t.a, t.b, t.c, v)){
                vector<unsigned char> color = colorWeight(t.a, t.b, t.c, v);    //color interpolation
                image->setPixel(x, y, color[0], color[1], color[2]);
            }
        }
    }
}

#endif /* drawing_h */
