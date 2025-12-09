

#include <array>
#include <list>
#include <concepts>
#include <cassert>

#include <point.hpp>
#include <triangles.hpp>

namespace triangles {
template <std::floating_point T> 
class TrianglesOctoTree {

    struct Octant;
    std::list<Octant> nodes_{};
    using Node = typename std::list<Octant>::iterator;
    Node root_;

    struct TriangleWrapper final {
        Triangle<T> triangle_;
        std::vector<Node> nodes_ {};

        TriangleWrapper() = delete;
        TriangleWrapper(const Triangle<T> &triangle): triangle_{triangle} {};

        const Triangle<T> &triangle() const {
           return triangle_;
        }
        
        void add_node(Node node) {
            nodes_.push_back(node);
        }

        void clear() {
            nodes_.clear();
        }
    }
    using Triangles = typename std::list<Triangle>;
    Triangles triangles_ {};
    
    struct Octant {
        const size_t CHILDS_NUM = 8;
        const T MIN_SIDE = 1;
        const size_t MAX_SIZE = 10;

        Point<T> min_; // left down corner
        Point<T> max_; // right up corner
        Point<T> mid_; // center
        T eps_{epsilon<T>()};
        
        Node parent_;

        using Childs = typename std::array<Node, CHILDS_NUM>
        std::optional<Childs> childs_;
        std::vector<Triangles::iterator> triangles_ {};

        void check_validity() const {
            if ((max_.x - min_.x > MIN_SIDE) && (max_.y - min_.y > MIN_SIDE) && (max_.z - min_.z > MIN_SIDE))
                return;
            throw std::logic_error("Node initialization points is not valid");
        }
        
        Point<T> mid() const {
            return Point<T>{
                (max_.x - min_.x) / 2, 
                (max_.y - min_.y) / 2, 
                (max_.z - min_.z) / 2
            }
        }

        // void divide(std::array<Node, CHILDS_NUM> &node_arr) {
        //     if (is_divided())
        //         return;
        //     childs_.emplace(node_arr);
        // }   

        Octant() = delete;
        Octant(const Point<T> &min, const Point<T> &max, Node parent)
            : min_{min}, max_{max}, mid_{mid()}, parent_(parent) {
            check_validity();
        }
        Octant(const std::pair<Point<T>, Point<T>> &octant, Node parent)
            : Octant(octant.first, octant.second, parent) {}

        // notation Octant{N} means Octant from table 
        // ('+' -> greater than mid, '-' -> lower than mid)
        //  N   | x y z
        //------|-------
        // I    | + + +
        // II   | + − +
        // III  | + − −
        // IV   | + + −
        // V    | − + +
        // VI   | − − +
        // VII  | − − −
        // VIII | − + −


        Octant OctantI(Node parent) const {
            return Octant {mid_, max_, parent};
        }

        Octant OctantII(Node parent) const {
            return Octant {
                Point<T>{mid_.x, min_.y, mid_.z},
                Point<T>{max_.x, mid_.y, max_.z},
                parent
            };
        }

        Octant OctantIII(Node parent) const {
            return Octant {
                Point<T>{mid_.x, min_.y, min_.z},
                Point<T>{max_.x, mid_.y, mid_.z},
                parent
            };
        }

        Octant OctantIV(Node parent) const {
            return Octant {
                Point<T>{mid_.x, mid_.y, min_.z},
                Point<T>{max_.x, max_.y, mid_.z},
                parent
            };
        }

        Octant OctantV(Node parent) const {
            return Octant {
                Point<T>{min_.x, mid_.y, mid_.z},
                Point<T>{mid_.x, max_.y, max_.z},
                parent
            };
        }

        Octant OctantVI(Node parent) const {
            return Octant {
                Point<T>{min_.x, min_.y, mid_.z},
                Point<T>{mid_.x, mid_.y, max_.z},
                parent
            };
        }

        Octant OctantVII(Node parent) const {
            return Octant {min_, mid_, parent};
        }

        Octant OctantVIII(Node parent) const {
            return Octant {
                Point<T>{min_.x, mid_.y, min_.z},
                Point<T>{mid_.x, max_.y, mid_.z},
                parent
            };
        }

        bool contains(const Point<T> &p) {
            return ((p.x > min_.x - eps_) && (p.x < max_.x + eps_))
                && ((p.y > min_.y - eps_) && (p.y < max_.y + eps_))
                && ((p.z > min_.z - eps_) && (p.z < max_.z + eps_));
        }

        bool contains(const Triangle<T> &tr) {
            return contains(tr.p1()) || contains(tr.p2()) || contains(tr.p3());
        }

        // unsigned get_octant(const Point<T> &p) {

        //     if (p.x == mid_.x) {

        //     }

        //     if (point.x < mid_.x) {

        //     }
        // }

        size_t size() const {
            return triangles_.size();
        }

        T side_size() const {
            return max_.x - min_.x;
        }

        void divide(Childs &&childs) {
            if (is_divided())
                return;
            childs_.emplace(std::move(childs));
        }

        // void divide(Node begin, Node end) {
        //     if (is_divided())
        //         return;
        //     childs_.emplace(std::copy(begin, end, childs_.begin()));
        // }

        bool is_divided() const {
            return childs_.has_value();
        }

        bool stop_condition() const {
            return (size() == MAX_SIZE) || (side_size() < MIN_SIDE - eps_);
        }

        void add_triangle(Triangles::iterator triangle_it) {
            triangles_.push_back(triangle_it);
        } 

        void clear_triangles() {
            triangles_.clear();
        }

        std::string to_string() const {
            std::string dump = "Octant(x=[" + std::to_string(std::round(min_.x * 100)) + ": " + std::to_string(std::round(max_.x * 100))
                + "], y=[" + std::to_string(std::round(min_.y * 100)) + ": " + std::to_string(std::round(max_.y * 100))
                + "], z=[" + std::to_string(std::round(min_.z * 100)) + ": " + std::to_string(std::round(max_.z * 100)) + ")"
            if (!is_divided()) {
                dump += " has triangles:\n"
                for (auto &tr_it : triangles_ )
                    dump += (*tr_it).to_string() + " ";
            }
            return dump;
        }
    
    };

    void divide_node(Node node) {
        assert(!node->is_divided());

        std::array<Octant, Octant::CHILDS_NUM> child_octants{
            node->OctantI(node),
            node->OctantII(node),
            node->OctantIII(node),
            node->OctantIV(node),
            node->OctantV(node),
            node->OctantVI(node),
            node->OctantVII(node),
            node->OctantVIII(node)
        }
        Octant::Childs childs {};
        for (size_t i = 0; i < child_octants.size(); ++i) {
            nodes_.push_back(std::move(child_octants[i]));
            childs[i] = nodes_.back();
        }

        for (const auto tr_it : node->triangles_) {
            for (const auto oct_it : childs) {
                if (oct_it->contains(*tr_it))
                    oct_it->add_triangle(tr_it);
            }
        }
        node->clear_triangles();
        node->divide(std::move(childs));
    }

    void add_triangle_(Triangles::iterator &tr_it, Node node) {
        assert(node->contains(*tr_it));

        if (!node->is_divided() && node->stop_condition()) {
            divide_node(node);
            for (const auto &child : node->childs_) {
                if (child->contains(*tr_it))
                    add_triangle_(tr_it, child);
            }
        }

        else
            node->add_triangle(tr_it);
    }

    void dump_(Node node) const {
        std::cout << node.to_string() + "\n";
        if (node->is_divided()) {
            for (const auto &child : node->childs_) {
                dump_(child);
            }
        }
    }

public:
    OctoTree(const Point<T> &min, const Point<T> &max) {
        nodes_.push_back(Octant{min, max, nodes_.end()});
        root_ = nodes_.begin();
    }

    void add_triangle(const Triangle<T> &triangle) {
        triangles_.push_back(TriangleWrapper{triangle});
        add_triangle_(triangles_.back(), root_);
    }

    std::unordered_set<size_t> intersections() const {
        std::unordered_set<size_t> intersections {};
        intersections.reserve(triangles_.size());
        for (const auto node=nodes_.begin(), end=nodes_.end(); node != end; ++node) {
            if (node->is_divided())
                continue;
            
            std::vector<Triangles::iterator> triangles = node->triangles_;
            const size_t n = triangles.size();
            for (size_t i = 0; i < n; ++i) {
                bool found = false;
                for (size_t j = i + 1; j < n; ++j) {
                    if (triangles[i]->intersection(*triangles[j])) {
                        intersections.insert(j);
                        found = true;
                    }
                }
                if (found) {
                    intersections.insert(i);
                }
            }
        }
        return int_trs;
    }

    void dump() const {
        std::cout << "OctoTree dump:\n";
        dump_(root_);
    }
};
} // namespace triangles
