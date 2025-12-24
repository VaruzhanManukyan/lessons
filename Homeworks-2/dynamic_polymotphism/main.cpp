#include <iostream>

class Animal {
public:
    struct VTable {
        void (*speak)(void*);
        void (*move)(void*);
    };
    static VTable vtable;
    VTable* vptr;

    Animal() { vptr = &vtable; }
    void speak() { vptr->speak(this); }
    void move() { vptr->move(this); }

    static void speak_impl(void* self) { std::cout << "Animal speaks\n"; }
    static void move_impl(void* self) { std::cout << "Animal moves\n"; }
};

Animal::VTable Animal::vtable = {
    Animal::speak_impl,
    Animal::move_impl
};

class Dog : public Animal {
public:
    static Animal::VTable vtable;
    Dog() : Animal() { vptr = &vtable; }

    static void speak_impl(void* self) { std::cout << "Dog says: Woof!\n"; }
    static void move_impl(void* self) { std::cout << "Dog runs\n"; }
};

Animal::VTable Dog::vtable = {
    Dog::speak_impl,
    Dog::move_impl
};

void act(Animal* a) { a->speak(); a->move(); }

int main() {
    Animal a;
    Dog d;

    a.speak();
    a.move();

    d.speak();
    d.move();

    act(&a);
    act(&d);

    return 0;
}
