struct Square
{
    int side_length;
};

struct Rectangle
{
    int side_length_a;
    int side_length_b;
};

struct Triangle
{
    int side_length_a;
    int side_length_b;
    int the_angle_between_a_b;
};

struct Circle
{
    int radius;
};


const int N_FIGURES = 4;
enum Figure
{
    SQUARE,
    RECTANGLE,
    TRIANGLE,
    CIRCLE,
};