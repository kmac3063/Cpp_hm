#pragma once

class PrimeNumberGenerator {
 private:
    int numb;
    static bool isPrime(const int& n) {
        for (size_t i = 2; i * i <= n; i++)
            if (n % i == 0) return false;
        return n >= 2;
    }

 public:
    explicit PrimeNumberGenerator(const int& start) {
        numb = start - 1;
            if (numb < 1)
        numb = 1;
    }

    int GetNextPrime() {
        numb++;
        while (!isPrime(numb))
            numb++;
        return numb;
    }
};
