#include "../exercise.h"

// READ: 虚函数 <https://zh.cppreference.com/w/cpp/language/virtual>

struct A {
    virtual char virtual_name() const {
        return 'A';
    }
    char direct_name() const {
        return 'A';
    }
};
struct B : public A {
    // READ: override <https://zh.cppreference.com/w/cpp/language/override>
    char virtual_name() const override {
        return 'B';
    }
    char direct_name() const {
        return 'B';
    }
};
struct C : public B {
    // READ: final <https://zh.cppreference.com/w/cpp/language/final>
    char virtual_name() const final {
        return 'C';
    }
    char direct_name() const {
        return 'C';
    }
};
struct D : public C {
    char direct_name() const {
        return 'D';
    }
};

int main(int argc, char **argv) {
    constexpr auto MSG = "Replace '?' with its correct name.";

    A a;
    B b;
    C c;
    D d;

    ASSERT(a.virtual_name() == 'A', MSG);  // A's virtual_name is 'A'
    ASSERT(b.virtual_name() == 'B', MSG);  // B overrides virtual_name with 'B'
    ASSERT(c.virtual_name() == 'C', MSG);  // C overrides virtual_name with 'C'
    ASSERT(d.virtual_name() == 'C', MSG);  // d inherits from C, and C's virtual_name is final

    ASSERT(a.direct_name() == 'A', MSG);   // A's direct_name is 'A'
    ASSERT(b.direct_name() == 'B', MSG);   // B's direct_name is 'B'
    ASSERT(c.direct_name() == 'C', MSG);   // C's direct_name is 'C'
    ASSERT(d.direct_name() == 'D', MSG);   // D's direct_name is 'D'

    A &rab = b;
    B &rbc = c;
    C &rcd = d;

    ASSERT(rab.virtual_name() == 'B', MSG); // rab resolves virtual_name to B's implementation
    ASSERT(rbc.virtual_name() == 'C', MSG); // rbc resolves virtual_name to C's implementation
    ASSERT(rcd.virtual_name() == 'C', MSG); // rcd resolves virtual_name to C's implementation

    ASSERT(rab.direct_name() == 'A', MSG);  // rab resolves direct_name based on A (compile-time type)
    ASSERT(rbc.direct_name() == 'B', MSG);  // rbc resolves direct_name based on B (compile-time type)
    ASSERT(rcd.direct_name() == 'C', MSG);  // rcd resolves direct_name based on C (compile-time type)

    A &rac = c;
    B &rbd = d;

    ASSERT(rac.virtual_name() == 'C', MSG); // rac resolves virtual_name to C's implementation
    ASSERT(rbd.virtual_name() == 'C', MSG); // rbd resolves virtual_name to C's implementation

    ASSERT(rac.direct_name() == 'A', MSG);  // rac resolves direct_name based on A (compile-time type)
    ASSERT(rbd.direct_name() == 'B', MSG);  // rbd resolves direct_name based on B (compile-time type)

    A &rad = d;

    ASSERT(rad.virtual_name() == 'C', MSG); // rad resolves virtual_name to C's implementation
    ASSERT(rad.direct_name() == 'A', MSG); 
    return 0;
}

// READ: 扩展阅读-纯虚、抽象 <https://zh.cppreference.com/w/cpp/language/abstract_class>
// READ: 扩展阅读-虚继承 <https://zh.cppreference.com/w/cpp/language/derived_class>
