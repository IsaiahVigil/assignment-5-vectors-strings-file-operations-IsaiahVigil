#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include "pixel.h"

// Function prototypes
void avg_colors(const std::vector<Pixel> &pixel_list);
void flip_vert(std::vector<Pixel> &pixel_list);

int main() {
    // Step 1: Create the vector to store pixels
    std::vector<Pixel> pixel_list;

    // Step 2: Open the input file
    std::ifstream infile("pixels.dat");
    if (!infile.is_open()) {
        std::cerr << "Could not open input\n";
        return 1;
    }

    // Read and Parse
    std::string line;
    while (std::getline(infile, line)) {
        std::stringstream ss(line);
        std::string temp;
        Pixel pixel;

        std::getline(ss, temp, ',');
        pixel.x = std::stoi(temp);
        std::getline(ss, temp, ',');
        pixel.y = std::stoi(temp);
        std::getline(ss, temp, ',');
        pixel.r = std::stof(temp);
        std::getline(ss, temp, ',');
        pixel.g = std::stof(temp);
        std::getline(ss, temp, ',');
        pixel.b = std::stof(temp);

        // Add pixel list
        pixel_list.push_back(pixel);
    }
    infile.close();

    avg_colors(pixel_list);
    flip_vert(pixel_list); 

    std::ofstream outfile("flipped.dat");
    if (!outfile.is_open()) {
        std::cerr << "Could not open output\n";
        return 1;
    }

    //Output
    outfile << std::fixed << std::setprecision(9);
    for (const auto &pixel : pixel_list) {
        outfile << pixel.x << "," << pixel.y << "," << pixel.r << "," << pixel.g << "," << pixel.b << "\n";
    }
    outfile.close();

    std::cout << "Flipped img written to flipped.dat\n";
    return 0;
}

//Calc avg colors
void avg_colors(const std::vector<Pixel> &pixel_list) {
    float r_sum = 0, g_sum = 0, b_sum = 0;
    for (const auto &pixel : pixel_list) {
        r_sum += pixel.r;
        g_sum += pixel.g;
        b_sum += pixel.b;
    }

    int count = pixel_list.size();
    std::cout << "Average R: " << (r_sum / count) << "\n";
    std::cout << "Average G: " << (g_sum / count) << "\n";
    std::cout << "Average B: " << (b_sum / count) << "\n";
}

//Flip pixels vertically
void flip_vert(std::vector<Pixel> &pixel_list) {
    int y_max = 256; 
    for (auto &pixel : pixel_list) {
        pixel.y = y_max - 1 - pixel.y;
    }
}
