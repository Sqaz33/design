#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

struct IObserver {
    virtual void update(int newState) = 0;
};

struct ISubject {
    void attach(std::shared_ptr<IObserver> observer) {
        observers_.push_back(observer);
    }

    void detach(std::shared_ptr<IObserver> observer) {
        std::erase_if(
            observers_,
            [=] (auto obs) {
                return obs.lock() == observer;
            }
        );
    }

    virtual void notify(int state) {
        for (auto it = observers_.begin(), itEnd = observers_.end(); it != itEnd; ) {
            if (auto obs = it->lock()) {
                obs->update(state);
                ++it;
            } else {
                observers_.erase(it);
            }
        }
    }
    virtual ~ISubject() {}
private:
    std::vector<std::weak_ptr<IObserver>> observers_;
};

struct ConcreteSubject : ISubject {
    void setState(int x) {
        state_ = x;
        notify(state_);
    }
private:
    int state_ = 0;
};

struct ConcreteObserver : IObserver {
    void update(int newState) override {
        state_ = newState;
        std::cout << "State now: " << newState << '\n';
    }
private:
    int state_ = 0;
};

int main() {
    ConcreteSubject subject;
    auto obs1 = std::make_shared<ConcreteObserver>();
    auto obs2 = std::make_shared<ConcreteObserver>();
    subject.attach(obs1);
    subject.attach(obs2);
    subject.setState(1);
    subject.setState(2);
    subject.setState(3);
    subject.setState(4);
}