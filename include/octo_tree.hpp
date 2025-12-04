

#include <array>
#include <list>
#include <concepts>

#include <point.hpp>
#include <triangles.hpp>

namespace triangles {


template <std::floating_point T> 
class TrianglesOctoTree {
    const T MIN_SIDE = 1;
    const size_t MAX_CHILDS = 8;

    size_t size_ {0};
    std::list<NodeImpl> nodes_{};
    using Node = typename std::list<NodeImpl>::iterator;
    
    Node root_;
    
    class NodeImpl {
        const T MIN_SIZE = 1;
        const size_t MAX_SIZE = 10;

        Point<T> min_; // left down corner
        Point<T> max_; // right up corner
        Point<T> mid_; // center
        
        Node parent_;
        std::optional<std::array<Node, MAX_SIZE>> childs_ = std::nullopt;
        std::list<Triangle<T>> triangles_ {};

        bool divided_flg {false};

        void check_validity() const {
            if ((max_.x - min_.x > MIN_SIDE) && (max_.y - min_.y > MIN_SIDE) && (max_.z - min_.z > MIN_SIDE))
                return;
            throw std::logic_error("Node initialization points is not valid");
        }

        void divide_space() {
            if (divided_flg)
                return;
            
            childs_.emplace();
            childs_[0] = NodeImpl{min_, mid_};
            childs_[1] = NodeImpl{min_, mid_};
            childs_[2] = NodeImpl{min_, mid_};
            childs_[3] = NodeImpl{min_, mid_};
            childs_[4] = NodeImpl{min_, mid_};
            childs_[5] = NodeImpl{min_, mid_};
            childs_[6] = NodeImpl{min_, mid_};
            childs_[7] = NodeImpl{min_, mid_};

            for (size_t i = 0; i < childs_->size(); ++i) {
                (*childs_)[i] = NodeImpl{};
            }


            divided_flg = true;
        }

        Point<T> calc_mid() const {
            return Point<T>{
                (max_.x - min_.x) / 2, 
                (max_.y - min_.y) / 2, 
                (max_.z - min_.z) / 2
            }
        }
       
    public:
        NodeImpl() = delete;
        NodeImpl(const Point<T> &min, const Point<T> &max, Node parent)
            : min_{min}, max_{max}, mid_{calc_mid()}, parent_(parent) {
            check_validity();
        }

        size_t size() const {
            return triangles_.size();
        }

        void add_triangle(const Triangle<T> &triangle) {
            if (size() == MAX_SIZE) {
                divide_space();

            }
        }        
    };
     
    
public:
    OctoTree(const Point<T> &min, const Point<T> &max) {
        nodes_.push_back(NodeImpl{min, max});
        root_ = nodes_.begin();
    }

    void add_triangle(const Triangle<T> &triangle) {
        root_.add_triangle(triangle);
    }

};
} // namespace triangles
