#include <iostream>
#include <cassert>
#include <cstring>

#include "string.hpp"

int main() {
    std::cout << "Running String tests...\n";

    {
        String s;
        assert(s.is_small());
        assert(s.empty());
        assert(s.size() == 0);
        assert(s.capacity() >= s.size());
        std::cout << "Test0 (default) passed\n";
    }

    {
        const char *t = "hello";
        String s(t);
        assert(s.is_small());
        assert(!s.empty());
        assert(s.size() == std::strlen(t));
        assert(s.capacity() >= s.size());
        std::cout << "Test1 (small ctor) passed\n";
    }

    {
        const std::size_t small_cap = 23;
        std::string exactly(small_cap, 'a');
        std::string above  (small_cap + 1, 'b');

        String s_exactly(exactly.c_str());
        String s_above  (above.c_str());

        assert(s_exactly.is_small());
        assert(s_exactly.size() == exactly.size());
        assert(s_above.is_small() == false);
        assert(s_above.size() == above.size());
        std::cout << "Test2 (borderline sizes) passed\n";
    }

    {
        const char *t = "this is a quite long string that should be big";
        String orig(t);
        assert(!orig.is_small());
        std::size_t orig_size = orig.size();

        String copy(orig);
        assert(copy.size() == orig_size);
        assert(copy.is_small() == orig.is_small());
        std::cout << "Test3 (copy ctor) passed\n";
    }

    {
        String a("short");
        String b("This is definitely longer than small capacity");
        a = b;
        assert(a.size() == b.size());
        assert(a.is_small() == b.is_small());
        String small("ok");
        b = small;
        assert(b.size() == small.size());
        assert(b.is_small() == small.is_small());
        std::cout << "Test4 (copy assign) passed\n";
    }

    {
        String s1("move-source-string");
        std::size_t s1_size = s1.size();
        String moved = std::move(s1);
        assert(moved.size() == s1_size);
        assert(s1.is_small());
        assert(s1.empty());
        std::cout << "Test5 (move ctor) passed\n";
    }

    {
        String s2("another-move-source");
        std::size_t s2_size = s2.size();
        String target("tmp");
        target = std::move(s2);
        assert(target.size() == s2_size);
        assert(s2.is_small());
        assert(s2.empty());
        std::cout << "Test6 (move assign) passed\n";
    }

    {
        String a("self-assign-test-very-long-string-to-force-big");
        bool was_small = a.is_small();
        std::size_t old_size = a.size();
        a = a;
        assert(a.size() == old_size);
        assert(a.is_small() == was_small);
        std::cout << "Test7 (self-assignment) passed\n";
    }

    {
        String s("");
        assert(s.empty());
        assert(s.size() == 0);
        assert(s.is_small());
        std::cout << "Test8 (empty string) passed\n";
    }

    std::cout << "All requested checks passed (no content-level checks performed).\n";
    std::cout << "If you want tests that verify string contents (strcmp) or reference-count behavior,\n";
    std::cout << "add a public c_str() and/or a use_count() accessor in your class and I will provide extra tests.\n";

    return 0;
}
