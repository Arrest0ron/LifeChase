#include <SFML/Graphics.hpp>
#include "vmath.hpp"

int main() {
    VM::Matrix NewMatrix = VM::Matrix::identity(5) *5;
    VM::Matrix NewMatrix2 = 8*VM::Matrix::identity(5);
    std::cout <<  NewMatrix*NewMatrix2;
    return 0;
}
