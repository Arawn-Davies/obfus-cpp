#include <iostream>
#include <cstdlib>

#define X(a,b) ((a) ^ (b))
#define Y(x) (((x) << 1) - (x))
#define Z(x) ((x) & 0xFF)
#define CH(x) static_cast<char>(x)
#define LEN(a) (sizeof(a)/sizeof((a)[0]))

typedef std::basic_ostream<char> os_t;

os_t& fetch_stream() {
    static void* p = (void*)&std::cout;
    return *reinterpret_cast<os_t*>(p);
}

int scramble(int v) {
    v ^= v << 7;
    v ^= v >> 3;
    v ^= v << 5;
    return v;
}

int main() {
    std::srand(123456);

    volatile int entropy[12];
    for (int i = 0; i < 12; ++i)
        entropy[i] = scramble(std::rand()) ^ Y(i + 11);

    int key = 0;
    for (int i = 0; i < 12; ++i)
        key ^= Z(entropy[i]);

    key &= 0xFF;

    int data[] = {
        X(72,  key),  X(101, key), X(108, key), X(108, key),
        X(111, key), X(44,  key), X(32,  key), X(119, key),
        X(111, key), X(114, key), X(108, key), X(100, key),
        X(33,  key), X(10,  key)
    };

    os_t& out = fetch_stream();

    int red_herring = 0;
    for (int i = 0; i < LEN(data); ++i) {
        red_herring += scramble(data[i] + i);
        out << CH(X(data[i], key));
    }

    return (red_herring == 0xFEEDFACE) ? 1 : 0;
}
