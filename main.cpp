#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <tuple>
#include <vector>

struct Point {
    int x;
    int y;
};

using Route = std::vector<Point>;
constexpr Point depot{0, 0};

int distance(Point a, Point b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

bool by_coordinates(Point a, Point b) {
    return std::tie(a.x, a.y) < std::tie(b.x, b.y);
}

Route nearest_first(Route remaining) {
    Route route;
    Point current = depot;

    while (!remaining.empty()) {
        auto nearest = std::min_element(
            remaining.begin(), remaining.end(), [current](Point a, Point b) {
                return std::make_tuple(distance(current, a), a.x, a.y)
                     < std::make_tuple(distance(current, b), b.x, b.y);
            });
        current = *nearest;
        route.push_back(current);
        remaining.erase(nearest);
    }
    return route;
}

void print_route(const char* name, const Route& route) {
    std::cout << name << ": (0, 0)";
    Point current = depot;
    int length = 0;

    for (Point next : route) {
        int leg = distance(current, next);
        std::cout << " --" << leg << "--> (" << next.x << ", " << next.y << ')';
        length += leg;
        current = next;
    }

    int back = distance(current, depot);
    std::cout << " --" << back << "--> (0, 0) | total: " << length + back << '\n';
}

int main() {
    const Route addresses{{4, 1}, {0, 5}, {1, 2}};
    Route sorted = addresses;
    std::sort(sorted.begin(), sorted.end(), by_coordinates);

    print_route("Input order", addresses);
    print_route("Nearest first", nearest_first(addresses));
    print_route("Sorted by X, then Y", sorted);
}
