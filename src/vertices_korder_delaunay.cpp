#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

#include "dimensional_traits_3.h"
#include "rhomboid_tiling.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef DimensionalTraits_3<K> Dt3;

template<class Dt>
std::vector<typename Dt::Point> read_points(std::istream &stream) {
    std::vector<typename Dt::Point> points;
    for (std::string s; std::getline(stream, s);) {
        if (s.empty() || s[0] == '#')
            continue;
        std::stringstream ss(s);
        std::vector<double> p;
        double v;
        while (!ss.eof()) {
            ss >> v;
            if (ss.fail()) break;
            p.push_back(v);
        }
        if (p.size() == Dt::dimension) {
            points.push_back(Dt::make_point(p));
        } else if (!p.empty()) {
            return std::vector<typename Dt::Point>();
        }
    }
    return points;
}

int main(int argc, char** argv) {
    if (argc != 4) {
        std::cerr << "Usage: VerticesKOrderDelaunay input.xyz k output.txt" << std::endl;
        return 1;
    }
    std::ifstream infile(argv[1]);
    if (!infile) {
        std::cerr << "input file not found" << std::endl;
        return 1;
    }
    int k = std::atoi(argv[2]);
    if (k <= 0) {
        std::cerr << "invalid k" << std::endl;
        return 1;
    }
    std::ofstream outfile(argv[3]);
    if (!outfile) {
        std::cerr << "output file not found" << std::endl;
        return 1;
    }
    auto points = read_points<Dt3>(infile);
    if (points.empty()) {
        std::cerr << "invalid input format" << std::endl;
        return 1;
    }
    if (k > static_cast<int>(points.size())) {
        k = points.size();
    }
    RhomboidTiling<Dt3> rt(points, k);
    auto vertices = rt.get_vertices(k);
    for (const auto& v : vertices) {
        for (std::size_t i = 0; i < v.size(); ++i) {
            if (i) outfile << ' ';
            outfile << v[i];
        }
        outfile << '\n';
    }
    return 0;
}
