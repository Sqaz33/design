#ifndef SLIDING_TOP_STACK_HPP
#define SLIDING_TOP_STACK_HPP

#include <vector>

namespace sliding_top_stack {

template <typename T>
class SlidingTopStack {
public:
    auto size() { return stack_.size(); }
    
    void pop() { stack_.erase(stack_.begin() + (top_--)); }

    T& top() { return stack_[top_]; }

    bool onRealTop() { return top_ == stack_.size() - 1; }

    auto topPos() { return top_; }
    // UB: if top < 0 or >= stack_.size(). Vot i dumay golovoy.
    T& toLeft() { return stack_[top_--]; }

    T& toRight() { return stack_[top_++]; }

    void push(T& v) {
        ++top_;
        eraseAfterTop_();
        stack_.push_back(v);
    } 

    void push(T&& v) {
        ++top_;
        eraseAfterTop_();
        stack_.push_back(std::move(v));
    }

    auto data() { return stack_; }

private:
    std::vector<T> stack_;
    int top_ = -1;

private:
    void eraseAfterTop_() {
        stack_.erase(
            stack_.begin() + top_,
            stack_.end()
        );
    }
};


} // namespace sliding_top_stack


#endif // SLIDING_TOP_STACK_HPP

