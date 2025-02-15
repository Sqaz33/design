#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

namespace {

bool isWord(const std::string& str) {
    return std::all_of(
        str.begin(),
        str.end(),
        [] (char c) { return std::isalpha(c); }
    );
}

bool isNumber(const std::string& str) {
    return std::all_of(
        str.begin(),
        str.end(),
        [] (char c) { return std::isdigit(c); }
    );
}

} // namespace

class SentenceProduct {
public:
    void pushWord(std::string word) {
        ss << word << ' ';
    }

    auto getSentence() const {
        auto sentence = ss.str();
        sentence.back() = '.';
        return sentence;
    }

private:
    std::stringstream ss;
};

class ExpressionProduct {
public:
    void pushNumber(int x) {
        nums_.push_back(x);
    }

    int compute() const {
        int res = 0;
        auto plus = [&res] (int v) mutable { res += v; };
        std::for_each(nums_.begin(), nums_.end(), plus);
        return res;
    }

private:
    std::vector<int> nums_;
};

class Builder {
public:
    virtual void buildPart(std::string data) = 0;
    virtual ~Builder() {}
};

class Director {
public:
    Director(std::shared_ptr<Builder> builder) :
        builder_(builder)
    {}

    void readIput(std::istream& in) {
        std::istream_iterator<std::string> it(in), end; 
        for (; it != end; ++it) {
            builder_->buildPart(*it);
        }
    }

private:
    std::shared_ptr<Builder> builder_;
};

class SentenceBuilder : public Builder {
public:
    void buildPart(std::string data) override {
        if (!isWord(data)) return;
        if (!product_) {
            product_ = std::make_unique<SentenceProduct>();
        }
        product_->pushWord(data);
    }

    auto getSentenceProduct() {
        return std::move(product_);
    }

private:
    std::unique_ptr<SentenceProduct> product_;
};

class ExpressionBuilder : public Builder {
public:
    void buildPart(std::string data) override {
        if (!isNumber(data)) return;
        if (!product_) {
            product_ = std::make_unique<ExpressionProduct>();
        }
        product_->pushNumber(std::stoi(data));
    }

    auto getExpressionProduct() {
        return std::move(product_);
    }

private:
    std::unique_ptr<ExpressionProduct> product_;
};

// ctrl + D
int main() {
#ifdef SENTENCE
    auto builder = std::make_shared<SentenceBuilder>();
#else 
    auto builder = std::make_shared<ExpressionBuilder>();
#endif
    Director director(builder);
    director.readIput(std::cin);
#ifdef SENTENCE
    auto product = builder->getSentenceProduct();
    std::cout << product->getSentence() << '\n';
#else 
    auto product = builder->getExpressionProduct();
    std::cout << product->compute() << '\n';
#endif
}

