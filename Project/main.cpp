#include <iostream>

int main() {

    // Image
    const int image_width = 256;
    const int image_height = 256;

    // Render
    std::cout << "P3\n"<< image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; --j) {
        std::cerr<< " \rScanLines remaining: "<< j << ' '<< std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto r = double(i) / (image_width-1);
            auto g = double(j) / (image_height-1);
            auto b = 0.25;

            int ir = 255;
            int ig = static_cast<int>(255 * r);
            int ib = static_cast<int>(255 * r);

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }

    std::cerr<<" \n Done. \n";
}