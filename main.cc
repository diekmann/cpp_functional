// g++ -Wall -Wextra -std=c++11 main.cc  && ./a.out; echo $?
// Outputs 3


typedef struct {} Unit;
constexpr Unit unit = Unit{};


// data Nat = Zero | Succ Nat
struct Zero {
    typedef Zero Nat;
};

template<typename T>
struct Succ {
    typedef Succ<typename T::Nat> Nat;
};


// typeclass for types which can be converted to an int
template<typename T>
struct toInt {};


template<>
struct toInt<Zero> {
    static const int value = 0;
};

template<typename T>
struct toInt<Succ<T>> {
    static const int value = 1 + toInt<T>::value;
};


// Example (also the return value of main)
constexpr int three_int = toInt<Succ<Succ<Succ<Zero>>>>::value;



// Proving: isEven
template<typename T>
struct isEven {};

// Zero is even
template<>
struct isEven<Zero>{
    static constexpr Unit qed = unit;
};

// If T is even, then Succ<Succ<T>> is even
template<typename T>
struct isEven<Succ<Succ<T>>> {
    static constexpr Unit qed = isEven<T>::qed;
};

// Check proof by forcing evaluation to qed
constexpr Unit even_zero  = isEven<Zero>::qed;
//constexpr Unit even_one   = isEven<Succ<Zero>>::qed;
constexpr Unit even_two   = isEven<Succ<Succ<Zero>>>::qed;
//constexpr Unit even_three = isEven<Succ<Succ<Succ<Zero>>>>::qed;
constexpr Unit even_four  = isEven<Succ<Succ<Succ<Succ<Zero>>>>>::qed;



extern int puts(const char *s);

int main() {
    return three_int;
}
