#ifndef SHAPES_H
#define SHAPES_H

//Shapes contains some static numbers representing the different
//shapes, a musicchip can have.
class Shapes{
public:

    static const int TRIANGLE = 3;
    static const int PENTAGON = 5;
    static const int SQUARE = 4;
    static const int HEXAGON = 6;
    //Circle useses the number 12, but in imageprocessor instead of
    //== it useses >=, so a circle is a shape with 12 or more contours
    static const int CIRCLE = 12;
};
#endif // SHAPES_H

