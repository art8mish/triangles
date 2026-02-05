

#include <array>
#include <cassert>
#include <concepts>
#include <iterator>
#include <limits>
#include <list>
#include <optional>
#include <set>
#include <stdexcept>

#include "point.hpp"
#include "triangles.hpp"

namespace triangles {
template <std::floating_point T> class OctoTree final {

    struct Octant;
    std::list<Octant> nodes_{};
    using Node = typename std::list<Octant>::iterator;
    Node root_;

    using Triangles = typename std::list<Triangle<T>>;
    Triangles triangles_{};

    struct Octant final {
        static const size_t CHILDS_NUM = 8;
        const T MIN_SIDE = 1;
        const size_t MAX_SIZE = 8;

        Point<T> min_; // left down corner
        Point<T> max_; // right up corner
        Point<T> mid_; // center
        T eps_{epsilon<T>()};

        using Childs = typename std::array<Node, CHILDS_NUM>;
        std::optional<Childs> childs_;
        std::vector<typename Triangles::const_iterator> triangles_{};

        void validate() const {
            if ((max_.x - min_.x < MIN_SIDE - eps_) || (max_.y - min_.y < MIN_SIDE - eps_) ||
                (max_.z - min_.z < MIN_SIDE - eps_))
                throw std::logic_error("Node initialization points is not valid");
        }

        Point<T> mid() const {
            return Point<T>{min_.x + (max_.x - min_.x) / 2, min_.y + (max_.y - min_.y) / 2,
                            min_.z + (max_.z - min_.z) / 2};
        }

        Octant(const Point<T> &min, const Point<T> &max) : min_{min}, max_{max} {
            validate();
            mid_ = mid();
        }
        Octant(const std::pair<Point<T>, Point<T>> &octant) : Octant(octant.first, octant.second) {}
        Octant(const Triangle<T> &tr) : Octant(Point<T>{
            std::min(tr.p1().x, tr.p2().x, tr.p3().x),
            std::min(tr.p1().y, tr.p2().y, tr.p3().y),
            std::min(tr.p1().z, tr.p2().z, tr.p3().z)
        }, Point<T>{
            std::max(tr.p1().x, tr.p2().x, tr.p3().x),
            std::max(tr.p1().y, tr.p2().y, tr.p3().y),
            std::max(tr.p1().z, tr.p2().z, tr.p3().z)
        }) {}

        const Childs &childs() const {
            return *childs_;
        }

        const Triangles &triangles() const {
            return triangles_;
        }

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

        Octant OctantI() const {
            return Octant{mid_, max_};
        }

        Octant OctantII() const {
            return Octant{Point<T>{mid_.x, min_.y, mid_.z}, Point<T>{max_.x, mid_.y, max_.z}};
        }

        Octant OctantIII() const {
            return Octant{Point<T>{mid_.x, min_.y, min_.z}, Point<T>{max_.x, mid_.y, mid_.z}};
        }

        Octant OctantIV() const {
            return Octant{Point<T>{mid_.x, mid_.y, min_.z}, Point<T>{max_.x, max_.y, mid_.z}};
        }

        Octant OctantV() const {
            return Octant{Point<T>{min_.x, mid_.y, mid_.z}, Point<T>{mid_.x, max_.y, max_.z}};
        }

        Octant OctantVI() const {
            return Octant{Point<T>{min_.x, min_.y, mid_.z}, Point<T>{mid_.x, mid_.y, max_.z}};
        }

        Octant OctantVII() const {
            return Octant{min_, mid_};
        }

        Octant OctantVIII() const {
            return Octant{Point<T>{min_.x, mid_.y, min_.z}, Point<T>{mid_.x, max_.y, mid_.z}};
        }

        bool intersects_octant(const Octant<T> &other) const {
            return Triangle<T>.segments_intersect(min_.x, max_.x, other.min_.x, other.max_.x) &&
                Triangle<T>.segments_intersect(min_.y, max_.y, other.min_.y, other.max_.y) &&
                Triangle<T>.segments_intersect(min_.y, max_.y, other.min_.y, other.max_.y)
        }

        bool contains(const Point<T> &p) const {
            return ((p.x > min_.x - eps_) && (p.x < max_.x + eps_)) &&
                   ((p.y > min_.y - eps_) && (p.y < max_.y + eps_)) &&
                   ((p.z > min_.z - eps_) && (p.z < max_.z + eps_));
        }

        bool contains_triangle_point(const Triangle<T> &tr) const {
            return contains(tr.p1()) || contains(tr.p2()) || contains(tr.p3());
        }

        bool contains(const Triangle<T> &tr) const {
            if (contains_triangle_point(tr))
                return true;

            const Octant<T> &aabb {tr};
            if (intersects_octant(aabb))
                return true;

            const Plane<T> tr_plane = tr.get_plane();
            T dist = tr_plane.signed_distance(mid_);
            const Vector<T> &n = tr_plane.normal();
            Vector<T> abs_n{std::abs(n.x()), std::abs(n.y()), std::abs(n.z())};
            Vector<T> half_side {mid_, max_};
            T max_dist = abs_n.edot(half_side);

            return max_dists - dist > -eps_;
        }

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

        bool is_divided() const {
            return childs_.has_value();
        }

        bool stop_condition() const {
            return (size() == MAX_SIZE) && (side_size() / 2. > MIN_SIDE + eps_);
        }

        void add_triangle(Triangles::const_iterator triangle_it) {
            triangles_.push_back(triangle_it);
        }

        void clear_triangles() {
            triangles_.clear();
        }

        std::string to_string() const {
            std::string dump = "Octant(x=[" + std::to_string(min_.x) + ": " +
                               std::to_string(max_.x) + "], y=[" + std::to_string(min_.y) + ": " +
                               std::to_string(max_.y) + "], z=[" + std::to_string(min_.z) + ": " +
                               std::to_string(max_.z) + "], " + "mid=" + mid_.to_string() + ")\n";
            if (!is_divided() && triangles_.size() != 0) {
                dump += "Triangles:\n";
                auto begin = triangles_.begin();
                for (auto tr_it : triangles_)
                    dump += tr_it->to_string() + "\n";
            }
            return dump;
        }
    };

    void divide_node(Node node) {
        assert(!node->is_divided());
        std::array<Octant, Octant::CHILDS_NUM> child_octants{
            node->OctantI(), node->OctantII(), node->OctantIII(), node->OctantIV(),
            node->OctantV(), node->OctantVI(), node->OctantVII(), node->OctantVIII()
        };

        typename Octant::Childs childs{};
        for (size_t i = 0; i < child_octants.size(); ++i) {
            childs[i] = nodes_.insert(nodes_.end(), std::move(child_octants[i]));
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

    void add_triangle_(Triangles::const_iterator tr_it, Node node) {
        assert(node->contains(*tr_it));

        if (!node->is_divided() && node->stop_condition())
            divide_node(node);

        if (node->is_divided()) {
            for (auto child : node->childs()) {
                if (child->contains(*tr_it))
                    add_triangle_(tr_it, child);
            }
        } else
            node->add_triangle(tr_it);
    }

    void dump_node(Node node) const {
        std::cout << "Octant(min=" << node->min_.to_string() << ", max=[" << node->max_.to_string()
                  << ", mid=" << node->mid_.to_string() << ")\n";
        if (node->is_divided()) {
            std::cout << "Childs:\n";
            for (auto child : node->childs()) {
                dump_node(child);
            }
        } else if (node->triangles_.size() > 0) {
            std::cout << "Triangles:\n";
            auto begin = triangles_.begin();
            for (auto tr_it : node->triangles_)
                std::cout << std::distance(begin, tr_it) << ": " << tr_it->to_string() << "\n";
        }
        std::cout << "\n";
    }

    void check_contains(const Triangle<T> &triangle) const {
        if (!root_->contains(triangle))
            throw std::out_of_range("OctoTree can't insert triangle out of root bounds");
    }

public:
    OctoTree(const Point<T> &min, const Point<T> &max) {
        nodes_.push_back(Octant{min, max});
        root_ = nodes_.begin();
    }
    OctoTree(T range) : OctoTree(Point<T>{-range, -range, -range}, Point<T>{range, range, range}) {}

    void add_triangle(const Triangle<T> &triangle) {
        check_contains(triangle);
        auto tr_it = triangles_.insert(triangles_.end(), triangle);
        add_triangle_(tr_it, root_);
    }

    void add_triangle(const Triangle<T> &&triangle) {
        check_contains(triangle);
        auto tr_it = triangles_.insert(triangles_.end(), std::move(triangle));
        add_triangle_(tr_it, root_);
    }

    std::set<size_t> intersections() const {
        std::set<size_t> intersections{};
        // intersections.reserve(triangles_.size());

        auto first_tr = triangles_.begin();
        for (auto node = nodes_.begin(), nend = nodes_.end(); node != nend; ++node) {
            if (node->is_divided())
                continue;

            std::vector<typename Triangles::const_iterator> triangles = node->triangles_;
            auto tr_end = triangles.end();

            for (auto i = triangles.begin(); i != tr_end; ++i) {
                typename Triangles::const_iterator triangle_i = *i;
                bool found = false;
                for (auto j = i + 1; j != tr_end; ++j) {
                    typename Triangles::const_iterator triangle_j = *j;
                    if (triangle_i->intersects(*triangle_j)) {
                        auto jndex = std::distance(first_tr, triangle_j);
                        assert(jndex >= 0);
                        intersections.insert(static_cast<size_t>(jndex));
                        found = true;
                    }
                }
                if (found) {
                    auto index = std::distance(first_tr, triangle_i);
                    assert(index >= 0);
                    intersections.insert(static_cast<size_t>(index));
                }
            }
        }
        return intersections;
    }

    void dump() const {
        std::cout << "OctoTree dump:\n";
        dump_node(root_);
    }
};
} // namespace triangles
