// Module: geometry / source file: geometry.cpp
// The implementation file for the module geometry:
// contains the definitions for the functions that can
// be used for area and circumference calculations
// with squares and circles.

const double PI = 3.141593;

double square_perimeter(double side) {
    return 4 * side;
}

double square_area(double side) {
    return side * side;
}

double circle_perimeter(double radius) {
    return 2 * PI * radius;
}

double circle_area(double radius) {
    return PI * radius * radius;
}
