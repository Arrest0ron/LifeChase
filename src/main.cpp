#include <SFML/Graphics.hpp>
#include "vmath.hpp"

int main() {
    VM::Matrix NewMatrix = VM::Matrix::identity(5)*3;
    std::cout << (NewMatrix).determinant();
    return 0;
}
