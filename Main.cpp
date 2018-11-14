#include <Stdio.h>
#include <iostream>
#include <fstream>
#include <glm/vec3.hpp>
#include "thread"
#include "Ray.h"
#include "Sphere.h"
#include "float.h"
#include "Utilities.h"
#include "Camera.h"

using namespace std;

glm::vec3 GetRayColor(Ray& ray, Hitable *scene, int depth) {
	HitObjectRecord *record = new HitObjectRecord();
	/*if (scene->CheckObjectHit(ray, EPSILON, FLT_MAX, record)) {
		Ray rayScattered;
		glm::vec3 attenuation(0.0f, 0.0f, 0.0f);
		if (depth < 50 && record->material->Scatter(ray, record, attenuation, rayScattered)) {
			return attenuation * GetRayColor(rayScattered, scene, depth + 1);
		}
		else {
			return glm::vec3(0.0f, 0.0f, 0.0f);
		}
	}
	*/
	if (scene->CheckObjectHit(ray, EPSILON, FLT_MAX, record)) {
		return 0.5f * glm::vec3(record->normal.x + 1.0f, record->normal.y + 1.0f, record->normal.z + 1.0f);
	} else {
		// set value between 0.0 - 1.0
		float t = 0.5f * (ray.direction.y + 1.0f);
		// linear blend between white and kind of blue
		return (1.0f - t) * glm::vec3(1.0f, 1.0f, 1.0f) + t * glm::vec3(0.5f, 0.7f, 1.0f);
	}

	delete record;
}

void Render(int minX, int maxX, int minY, int maxY, int numberOfSamplesPerPixel, int tileWidth, int tileHeight, int imageWidth, int imageHeight, Camera &camera, Hitable* scene, std::vector<glm::vec3*> &colorBuffer) {
	// X-axis goes from min to max
	// Y-axis goes form max to min
	for (int y = maxY; y > minY; y--) {
		for (int x = minX; x < maxX; x++) {
			glm::vec3 color(0.0f, 0.0f, 0.0f);

			// This loop is for AA
			int depth = 0;
			for (int sample = 0; sample < numberOfSamplesPerPixel; sample++) {
				// Generate the Ray
				float u = float(x + Utilities::GetRandom()) / float(imageWidth);
				float v = float(y + Utilities::GetRandom()) / float(imageHeight);
				Ray ray = camera.GenerateRay(u, v);
				// Generate the Color
				color += GetRayColor(ray, scene, depth);
			}

			// Averaging the color from the samples
			color /= numberOfSamplesPerPixel;
			color = Utilities::Gamma2(color);

			// fill the file with the pixel RGB data
			color[0] = int(255.99* color[0]);
			color[1] = int(255.99* color[1]);
			color[2] = int(255.99* color[2]);
			int index = x + (imageHeight - y) * imageWidth;
			colorBuffer[index]->x = color.x;
			colorBuffer[index]->y = color.y;
			colorBuffer[index]->z = color.z;
		}
	}
}

void main() {
	// Image Dimensions
	int imageWidth = 600;
	int imageHeight = 300;
	int colorBufferDimension = imageWidth*imageHeight;
	// Final Color Buffer
	std::vector<glm::vec3*> colorBuffer(colorBufferDimension);

	// Fill in the color buffer
	for (int i = 0; i < colorBufferDimension; i++) {
		colorBuffer[i] = new glm::vec3(0.0f, 0.0f, 0.0f);
	}

	// For multi-threading
	thread threads[NumberOfThreads];

	// For Anti Aliasing
	int numberOfSamplesPerPixel = 100;
	
	// Create a camera
	Camera camera;

	// Create a list of hitable objects in the scene
	std::vector<Hitable*> *listOfObjectsInScene = new std::vector<Hitable*>();
	Sphere* sphere1 = new Sphere(0.5f, glm::vec3(0.0f, 0.0f, -1.0f));
	Sphere* sphere2 = new Sphere(100.0f, glm::vec3(0.0f, -100.5f, -1.0f));
	listOfObjectsInScene->push_back(sphere1);
	listOfObjectsInScene->push_back(sphere2);
	Hitable* scene = new HitableList(listOfObjectsInScene);

	// The entire tiling architecture is for multithreading the renderer
	// Tile bounds
	int minX, maxX, minY, maxY;
	// Dividing the image into 3 x 2 tiles.
	int rows = 2;
	int colums = 3;
	int tileWidth = imageWidth / colums;
	int tileHeight = imageHeight / rows;
	int threadIndex = 0;
	for (int yTileDim = 0; yTileDim < rows; yTileDim++) {
		for (int xTileDim = 0; xTileDim < colums; xTileDim++) {
			// This part renders one tile at a time of the whole image and fills the color buffer
			minX = xTileDim * tileWidth;
			maxX = ((xTileDim + 1) * tileWidth);
			minY = ((1 - yTileDim) * tileHeight);
			maxY = ((rows - yTileDim) * (tileHeight));
			threads[threadIndex] = thread(Render, minX, maxX, minY, maxY, numberOfSamplesPerPixel, tileWidth, tileHeight, imageWidth, imageHeight, camera, scene, colorBuffer);
			threadIndex += 1;
		}
	}

	// Sync Threads
	for (int i = 0; i < NumberOfThreads; i++) {
		threads[i].join();
	}

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
	for (int index = 0; index < (imageWidth * imageHeight); index++) {
		myFile << colorBuffer[index]->x << " " << colorBuffer[index]->y << " " << colorBuffer[index]->z << "\n";
	}
	myFile.close();
}