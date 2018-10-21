#include <Stdio.h>
#include <iostream>
#include <fstream>
#include <glm/vec3.hpp>
#include "Ray.h"
#include "Sphere.h"
#include "HitableList.h"
#include "float.h"
#include "Utilities.h"
#include "Camera.h"

using namespace std;

glm::vec3 COLOR(Ray& ray, Hitable *scene) {
	HitObjectRecord record;
	if (scene->CheckObjectHit(ray, 0.0f, FLT_MAX, record)) {
		return (0.5f * glm::vec3(record.normal.x + 1.0f, record.normal.y + 1.0f, record.normal.z + 1.0f));
	}
	else {
		// set value between 0.0 - 1.0
		float t = 0.5f * (ray.direction.y + 1.0f);
		// linear blend between white and kind of blue
		return (1.0f - t) * glm::vec3(1.0f, 1.0f, 1.0f) + t * glm::vec3(0.5f, 0.7f, 1.0f);
	}
}

void Render(int minX, int maxX, int minY, int maxY, int numberOfSamplesPerPixel, int imageWidth, int imageHeight, Camera &camera, Hitable* scene, std::vector<glm::vec3> &colorBuffer) {
	for (int y = maxY; y >= minY; y--) {
		for (int x = minX; x < maxX; x++) {
			glm::vec3 color(0.0f, 0.0f, 0.0f);

			// This loop is for AA
			for (int sample = 0; sample < numberOfSamplesPerPixel; sample++) {
				// Generate the Ray
				float u = float(x + GetRandom()) / float(imageWidth);
				float v = float(y + GetRandom()) / float(imageHeight);
				Ray ray = camera.GenerateRay(u, v);
				// Generate the Color
				color += COLOR(ray, scene);
			}

			// Averaging the color from the samples
			color /= numberOfSamplesPerPixel;

			// fill the file with the pixel RGB data
			int ir = int(255.99* color[0]);
			int ig = int(255.99* color[1]);
			int ib = int(255.99* color[2]);
			int index = x + y * imageWidth;
			colorBuffer[index] = color;
		}
	}
}

void main() {
	// Image Dimensions
	int imageWidth = 800;
	int imageHeight = 400;
	// Final Color Buffer
	std::vector<glm::vec3> colorBuffer(imageWidth*imageHeight);

	// For Anti Aliasing
	int numberOfSamplesPerPixel = 100;
	
	// Create a camera
	Camera camera;

	// Create a list of hitable objects in the scene
	std::vector<Hitable*> listOfObjectsInScene;
	Sphere* sphere1 = new Sphere(0.5f, glm::vec3(0.0f, 0.0f, -1.0f));
	Sphere* sphere2 = new Sphere(100.0f, glm::vec3(0.0f, -100.5f, -1.0f));
	listOfObjectsInScene.push_back(sphere1);
	listOfObjectsInScene.push_back(sphere2);
	Hitable* scene = new HitableList(listOfObjectsInScene);

	// This function renders the tile of an image and fills the buffer
	int minX, maxX, minY, maxY;
	minX = 0;
	maxX = imageWidth;
	minY = 0;
	maxY = (imageHeight - 1);
	Render(minX, maxX, minY, maxY, numberOfSamplesPerPixel, imageWidth, imageHeight, camera, scene, colorBuffer);

	// Writing the .PPM renderd image file
	ofstream myFile;
	string filePath = R"(C:\Users\Rudraksha\Documents\Projects\RayTracer\Image.ppm)";
	myFile.open(filePath, ios::out | ios::trunc);
	if (!myFile) {
		std::cout << "Could not open file" << endl;
	}
	myFile << "P3\n";
	myFile << imageWidth << " " << imageHeight << "\n";
	myFile << "255\n";
	for (int index = ((imageWidth * imageHeight) - 1); index >= 0 ; index--) {
		myFile << colorBuffer[index].x << " " << colorBuffer[index].y << " " << colorBuffer[index].z << "\n";
	}
	myFile.close();
}