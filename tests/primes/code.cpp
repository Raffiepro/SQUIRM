#include <bits/stdc++.h>
#include <stdio.h>

int main(){
    // Mostra el nombre 10000 primer
    int n = 2000;
    int i = 2;
    int t = 0;
    while (t < n) {
        int divisible = 0;
        for (int j = 2; j < i; j = j + 1) {
            if (i % j == 0) {
                divisible = 1;
                break;
            }
        }
        i = i + 1;
        if (divisible == 0) {
            t = t + 1;
        }
    }

    std::cout << i - 1 << std::endl;

}