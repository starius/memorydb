
#include <stdio.h>
#define DBGPRINTF(fmt, ...)  printf(fmt, __VA_ARGS__)

#include <cstddef>
#include <cassert>
#include <iostream>
#include <vector>

template<typename T>
class Model;

class AbstractReference {
    virtual void foo() = 0;
};

template<typename T, int d>
class Foo : T {
public:
    int ref;
};

template<typename T>
class Model {
public:
    int ref;
    int ref1() {
        return ((T*)this)->q;
    }
};

template<typename T>
class Reference : AbstractReference {
public:
    //~ Model<T>* host() { return (Model<T>*)((char*)this - offsetof(Model<T>, ref)); }
    //~ Model<T>* host() { return (T*)((char*)this - offset); }
    //~ Model<T>* host() { return (T*)((char*)this - offsetof(T, r)); }
    Model<T>* host() {
        return (T*)((char*)this - offset);
    }

    void foo() {}

private:
    static int offset;
};

class User : public Model<User> {
public:
    Reference<User> r;
    int q;
    int a;
    //~ Reference<User, offsetof(User, q)> r;

private:
    static int i;
};

template<typename T> int Reference<T>::offset = offsetof(T, r);

int User::i = 100;

class A1 {
private:
    int i;
};
class A2 : A1 {
private:
    A1 f;
    A2* e;
};

int f(int a) {
    return 1;
}
int f(int* a) {
    return 2;
}

class Df {
    std::vector<int> a;
    std::vector<int> b;
    //~ std::vector<int> c;
};

enum Bar {
    b, c
};

int main() {
    int r = 34;
    double d;
    d = double(r);
    r = int(d);
    int* pr = &r;
    assert(f(r) == 1);
    assert(f(pr) == 2);
    //~ for (int i=0; i<9999999; i++)
    //~ {
    //~ new Df;
    //~ }
    //~
    //~ char w;
    //~ std::cin >> w;
    User user;
    assert(user.r.host() == &user);
    std::cout << ((int)(user.r.host())) % 32 << std::endl;
    std::cout << (int)(&user) << std::endl;
    std::cout << sizeof(A2) << std::endl;
    Foo<User, b> q;
    int* q1;
    q1 = NULL;
    //~ DBGPRINTF("qwe%s", "123");
}

