#include <iostream>
#include <cassert>

#include <boost/move/move.hpp>
#include <boost/container/vector.hpp>

class descriptor_owner1 {
    void * descriptor_;

public:
    descriptor_owner1()
        : descriptor_(NULL)
    {}

    explicit descriptor_owner1(const char* param)
        : descriptor_(strdup(param))
    {}

    descriptor_owner1(descriptor_owner1&& param)
        : descriptor_(param.descriptor_) {
        param.descriptor_ = NULL;
    }

    descriptor_owner1& operator=(descriptor_owner1&& param) {
        clear();
        std::swap(descriptor_, param.descriptor_);
        return *this;
    }

    void clear() {
        free(descriptor_);
        descriptor_ = NULL;
    }

    bool empty() const {
        return !descriptor_;
    }

    ~descriptor_owner1() {
        clear();
    }
};


class descriptor_owner_movable {
    void * descriptor_;
    BOOST_MOVABLE_BUT_NOT_COPYABLE(descriptor_owner_movable)

public:
    descriptor_owner_movable()
	: descriptor_(NULL)
    {}

    explicit descriptor_owner_movable(const char* param)
        : descriptor_(strdup(param))
    {}

    descriptor_owner_movable(BOOST_RV_REF(descriptor_owner_movable) param)
        : descriptor_(param.descriptor_) {
        param.descriptor_ = NULL;
    }

    descriptor_owner_movable& operator=(BOOST_RV_REF(descriptor_owner_movable) param) {
        clear();
        std::swap(descriptor_, param.descriptor_);
        return *this;
    }

    // ...

    void clear() {
        free(descriptor_);
        descriptor_ = NULL;
    }

    bool empty() const {
        return !descriptor_;
    }

    ~descriptor_owner_movable() {
        clear();
    }

};



descriptor_owner1 construct_descriptor2() {
    return descriptor_owner1("Construct using string");
}


descriptor_owner_movable construct_descriptor3() {
    return descriptor_owner_movable("Construct using string");
}



int main() {
    std::cout << "C++11\n";
    descriptor_owner1 desc;
    desc = construct_descriptor2();
    assert(!desc.empty());

    std::cout << "Boost\n";
    descriptor_owner_movable desc_movable;
    desc_movable = construct_descriptor3();
    assert(!desc_movable.empty());


    // boost containers
    descriptor_owner_movable movable;
    movable = construct_descriptor3();
    boost::container::vector<descriptor_owner_movable> vec;
    vec.resize(10);
    vec.push_back(construct_descriptor3());
    vec.back() = boost::move(vec.front());

    return 0;
}

