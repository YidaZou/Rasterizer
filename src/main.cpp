#include <iostream>
#include <string>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include "Image.h"
#include "triangle.h"
#include "boundingBox.h"
#include "drawing.h"

// This allows you to skip the `std::` in front of C++ standard library
// functions. You can also say `using std::cout` to be more selective.
// You should never do this in a header file.
using namespace std;

double RANDOM_COLORS[7][3] = {
	{0.0000,    0.4470,    0.7410},
	{0.8500,    0.3250,    0.0980},
	{0.9290,    0.6940,    0.1250},
	{0.4940,    0.1840,    0.5560},
	{0.4660,    0.6740,    0.1880},
	{0.3010,    0.7450,    0.9330},
	{0.6350,    0.0780,    0.1840},
};

int main(int argc, char **argv)
{
	if(argc < 5) {
		cout << "Usage: ./A1 meshfile imgfile width height tasknumber" << endl;
		return 0;
	}
	string meshName(argv[1]);
    string imgName(argv[2]);
    int width = atoi(argv[3]);
    int height = atoi(argv[4]);
    int taskNum = atoi(argv[5]);
    // Create the image. We're using a `shared_ptr`, a C++11 feature.
    auto image = make_shared<Image>(width, height);

	// Load geometry
	vector<float> posBuf; // list of vertex positions
	vector<float> norBuf; // list of vertex normals
	vector<float> texBuf; // list of vertex texture coords
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	string errStr;
	bool rc = tinyobj::LoadObj(&attrib, &shapes, &materials, &errStr, meshName.c_str());
	if(!rc) {
		cerr << errStr << endl;
	} else {
		// Some OBJ files have different indices for vertex positions, normals,
		// and texture coordinates. For example, a cube corner vertex may have
		// three different normals. Here, we are going to duplicate all such
		// vertices.
		// Loop over shapes
		for(size_t s = 0; s < shapes.size(); s++) {
			// Loop over faces (polygons)
			size_t index_offset = 0;
			for(size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
				size_t fv = shapes[s].mesh.num_face_vertices[f];
				// Loop over vertices in the face.
				for(size_t v = 0; v < fv; v++) {
					// access to vertex
					tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
					posBuf.push_back(attrib.vertices[3*idx.vertex_index+0]);
					posBuf.push_back(attrib.vertices[3*idx.vertex_index+1]);
					posBuf.push_back(attrib.vertices[3*idx.vertex_index+2]);
					if(!attrib.normals.empty()) {
						norBuf.push_back(attrib.normals[3*idx.normal_index+0]);
						norBuf.push_back(attrib.normals[3*idx.normal_index+1]);
						norBuf.push_back(attrib.normals[3*idx.normal_index+2]);
					}
					if(!attrib.texcoords.empty()) {
						texBuf.push_back(attrib.texcoords[2*idx.texcoord_index+0]);
						texBuf.push_back(attrib.texcoords[2*idx.texcoord_index+1]);
					}
				}
				index_offset += fv;
				// per-face material (IGNORE)
				shapes[s].mesh.material_ids[f];
			}
		}
	}
	cout << "Number of vertices: " << posBuf.size()/3 << endl;
    
    //organize posBuf
    vector<Vertex> vertices = toVertices(posBuf);
    vector<Triangle> triangles = toTriangles(vertices);
    
    //calculate bounds of whole image
    vector<float> bounds = findBounds(vertices);
    
    //scale and translate
    scaleTranslate(width, height, bounds, triangles);
    
    switch (taskNum) {
        //Task 1: Drawing Bounding Boxes
        case 1:
        {
            float color[3];
            for(int i=0; i<triangles.size(); i++){
                color[0] = RANDOM_COLORS[i%7][0]*255;   //r
                color[1] = RANDOM_COLORS[i%7][1]*255;   //g
                color[2] = RANDOM_COLORS[i%7][2]*255;   //b
                drawBox(triangles[i], color, image);
            }
            
        }
            break;
        //Task 2: Drawing Triangles
        case 2:
        {
            float color[3];
            for(int i=0; i<triangles.size(); i++){
                color[0] = RANDOM_COLORS[i%7][0]*255;   //r
                color[1] = RANDOM_COLORS[i%7][1]*255;   //g
                color[2] = RANDOM_COLORS[i%7][2]*255;   //b
                drawTriangle(triangles[i], color, image);
            }
        }
            break;
        //Task 3: interpolating Per-Vertex Colors
        case 3:
        {
            for(int i=0; i<triangles.size(); i++){
                //assign colors to vertices of triangle
                //a
                triangles[i].a.r = RANDOM_COLORS[i%7][0]*255;   //r
                triangles[i].a.g = RANDOM_COLORS[i%7][1]*255;   //g
                triangles[i].a.b = RANDOM_COLORS[i%7][2]*255;   //b
                //b
                triangles[i].b.r = RANDOM_COLORS[(i+1)%7][0]*255;   //r
                triangles[i].b.g = RANDOM_COLORS[(i+1)%7][1]*255;   //g
                triangles[i].b.b = RANDOM_COLORS[(i+1)%7][2]*255;   //b
                //c
                triangles[i].c.r = RANDOM_COLORS[(i+2)%7][0]*255;   //r
                triangles[i].c.g = RANDOM_COLORS[(i+2)%7][1]*255;   //g
                triangles[i].c.b = RANDOM_COLORS[(i+2)%7][2]*255;   //b
                
                drawPerVertexTriangle(triangles[i], image);
            }
        }
            break;
        //Task 4: Vertical Color
        case 4:
        {
            float color[3] = {255,0,0};
            for(int i=0; i<triangles.size(); i++){
                
                drawTriangle(triangles[i], color, image);
            }
        }
            break;
        
        default:
        {
            cout << "Task Not Found" << endl;
        }
            break;
    }
    image->writeToFile(imgName);
	return 0;
}
