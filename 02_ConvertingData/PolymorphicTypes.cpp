#include <cstdlib>
#include <ctime>

#include <typeinfo>

#include <iostream>

#include <boost/cast.hpp>

// awful interface
struct object {
    virtual ~object() {}
};

struct banana : public object {
    void eat() const {}
    virtual ~banana() {}
};

struct pidgin : public object {
    void fly() const {}
    virtual ~pidgin() {}
};

object* try_produce_banana() {
    int i = rand() % 3;

    object* obj;

    switch (i) {
        case 0: 
            obj = new banana; 
            std::cout << "Create banana" << std::endl;
            break;
        case 1: 
            obj = new pidgin;
            std::cout << "Create pidgin" << std::endl;
            break;
        default:
            obj = NULL;
            std::cout << "Return NULL" << std::endl;
            break;
    }

    return obj;
}

// ugly
void try_eat_banana_impl1() {
    const object* obj = try_produce_banana();
    
    if (!obj) {
        throw std::bad_cast();
    }

    dynamic_cast<const banana&>(*obj).eat();
}

// better
void try_eat_banana_impl2() {
    const object* obj = try_produce_banana();

    boost::polymorphic_cast<const banana*>(obj)->eat();
}



int main() {
    std::srand(std::time(0));

    try {
        try_eat_banana_impl1();
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }


    try {
        try_eat_banana_impl2();
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

}
