#include <iostream>
#include <unistd.h>

int main() {
    for(int i = 0; i < 2; i++) {
        fork();
        std::cout << "-"; //It will get 6
        //printf("-"); //It will get 8
    }

    fflush(stdout);
    return 0;
}