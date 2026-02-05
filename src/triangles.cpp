
#include <ctime>
#include <iostream>
#include <vector>

#include "../include/octo_tree.hpp"
#include "../include/triangles.hpp"

double get_coordinate() {
    double coord = std::numeric_limits<double>::quiet_NaN();
    std::cin >> coord;
    if (!std::cin.good())
        throw std::invalid_argument("Incorrect coordinate");
    return coord;
}

int main() {
    try {
        size_t size = 0;
        std::cin >> size;
        if (!std::cin.good()) {
            std::cout << "Error: incorrect size" << std::endl;
            return 1;
        }

#ifndef NDEBUG
        auto start_time = std::clock();
#endif
        std::vector<triangles::Triangle<double>> triangles{};
        triangles.reserve(size);

        double coord_range = 0;
        const size_t tr_coord_amount = 9;
        for (unsigned i = 0; i < size; i++) {
            std::array<double, tr_coord_amount> coordinates{};
            for (size_t i = 0; i < tr_coord_amount; ++i) {
                double coord = get_coordinate();
                double abs = std::abs(coord);
                if (abs > coord_range)
                    coord_range = abs;
                coordinates[i] = coord;
            }
            triangles::Triangle<double> triangle{coordinates[0], coordinates[1], coordinates[2],
                                                 coordinates[3], coordinates[4], coordinates[5],
                                                 coordinates[6], coordinates[7], coordinates[8]};
            triangles.push_back(triangle);
        }

        coord_range = std::ceil(coord_range);
        triangles::OctoTree<double> tree{coord_range};
        for (auto &triangle : triangles) {
            tree.add_triangle(std::move(triangle));
        }
        std::set<size_t> intersections = tree.intersections();
        for (auto sec : intersections)
            std::cout << sec << "\n";

#ifndef NDEBUG
        auto duration = std::clock() - start_time;
        std::cout << "runtime: " << duration << " us" << std::endl;
#endif
        return 0;
    } catch (const std::invalid_argument &e) {
        std::cout << "Invalid argument: " << e.what() << std::endl;
        return 1;
    } catch (const std::out_of_range &e) {
        std::cout << "Triangle is out of tree range: " << e.what() << std::endl;
        return 1;
    } catch (const std::exception &e) {
        std::cout << "Error: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cout << "Unknown error" << std::endl;
        return 1;
    }
}