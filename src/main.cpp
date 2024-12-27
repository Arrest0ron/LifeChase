#include <SFML/Graphics.hpp>
#include "vmath.hpp"

int main() {
    VM::Matrix NewMatrix = VM::Matrix::randomatrix(4);
    std::cout << (NewMatrix) << NewMatrix* NewMatrix.inverse();
    return 0;
}
