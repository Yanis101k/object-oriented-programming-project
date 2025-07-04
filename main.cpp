#include <iostream>
#include <cmath>
#include <string>
using namespace std;
#include <vector>


// Coordinates Class

class Coordinates {
private:
    int x;  // X coordinate (must be positive)
    int y;  // Y coordinate (must be positive)

public:

    Coordinates() : x(0), y(0) {} // a default constructor
    // Constructor with validation to ensure positive coordinates
    Coordinates(int xVal, int yVal) {
        if (xVal < 0 || yVal < 0) {
            cout << "Warning: Coordinates must be positive. Defaulting to (0, 0)." << endl;
            x = 0;
            y = 0;
        } else {
            x = xVal;
            y = yVal;
        }
    }

    // Getter for x
    int getX() const {
        return x;
    }

    // Getter for y
    int getY() const {
        return y;
    }

    // Method to calculate the Euclidean distance to another point
    double distance(const Coordinates& p) const {
        int dx = p.x - x;
        int dy = p.y - y;
        return sqrt(dx * dx + dy * dy);
    }

    // Method to move the point by dx and dy (only if result remains positive)
    void translate(int dx, int dy) {
        if ((x + dx) >= 0 && (y + dy) >= 0) {
            x += dx;
            y += dy;
        } else {
            cout << "Warning: Translation would result in negative coordinates. Operation skipped." << endl;
        }
    }

    // Method to scale the point by a factor (multiply if sign=true, divide if false)
    void scale(int factor, bool sign) {
        if (factor <= 0) {
            cout << "Warning: Scaling factor must be greater than 0. Operation skipped." << endl;
            return;
        }

        if (sign) {
            x *= factor;
            y *= factor;
        } else {
            x /= factor;
            y /= factor;
        }

        
    }

    // Method to return a string representing the coordinates
    string display() const {
        return "X = " + to_string(x) + ", Y = " + to_string(y);
    }
};




// Function to Unit Test Coordinates Class 

void test_coordinate_class() {
    cout << "\n========== Running test_coordinate_class() ==========" << endl;

    int passed = 0;
    int failed = 0;

    // Test 1: Constructor with valid input
    Coordinates p1(10, 20);
    if (p1.getX() == 10 && p1.getY() == 20) {
        cout << "Test 1 passed: Valid constructor" << endl;
        passed++;
    } else {
        cout << "Test 1 FAILED: Valid constructor" << endl;
        failed++;
    }

    // Test 2: Constructor with negative input
    Coordinates p2(-5, -15);
    if (p2.getX() == 0 && p2.getY() == 0) {
        cout << "Test 2 passed: Invalid constructor handled" << endl;
        passed++;
    } else {
        cout << "Test 2 FAILED: Invalid constructor" << endl;
        failed++;
    }

    // Test 3: Distance calculation
    Coordinates p3(13, 24);
    double expectedDistance = sqrt((13 - 10) * (13 - 10) + (24 - 20) * (24 - 20));
    if (abs(p1.distance(p3) - expectedDistance) < 0.001) {
        cout << "Test 3 passed: Distance calculation" << endl;
        passed++;
    } else {
        cout << "Test 3 FAILED: Distance calculation" << endl;
        failed++;
    }

    // Test 4: Valid translate
    p1.translate(5, -3);
    if (p1.getX() == 15 && p1.getY() == 17) {
        cout << "Test 4 passed: Valid translate" << endl;
        passed++;
    } else {
        cout << "Test 4 FAILED: Valid translate" << endl;
        failed++;
    }

    // Test 5: Invalid translate (should skip)
    int prevX = p1.getX(), prevY = p1.getY();
    p1.translate(-100, -100);
    if (p1.getX() == prevX && p1.getY() == prevY) {
        cout << "Test 5 passed: Invalid translate skipped" << endl;
        passed++;
    } else {
        cout << "Test 5 FAILED: Invalid translate not handled" << endl;
        failed++;
    }

    // Test 6: Scale by 2 (multiply)
    p1.scale(2, true);
    if (p1.getX() == prevX * 2 && p1.getY() == prevY * 2) {
        cout << "Test 6 passed: Valid scale *2" << endl;
        passed++;
    } else {
        cout << "Test 6 FAILED: Scale *2" << endl;
        failed++;
    }

    // Test 7: Scale by 2 (divide)
    p1.scale(2, false);
    if (p1.getX() == prevX && p1.getY() == prevY) {
        cout << "Test 7 passed: Valid scale /2" << endl;
        passed++;
    } else {
        cout << "Test 7 FAILED: Scale /2" << endl;
        failed++;
    }

    // Test 8: Scale with factor = 0 (invalid)
    prevX = p1.getX(); prevY = p1.getY();
    p1.scale(0, true);  // should be skipped
    if (p1.getX() == prevX && p1.getY() == prevY) {
        cout << "Test 8 passed: Invalid scale factor 0 skipped" << endl;
        passed++;
    } else {
        cout << "Test 8 FAILED: Scale by 0 not handled" << endl;
        failed++;
    }

    // Test 9: Scale with negative factor (invalid)
    p1.scale(-2, true);  // should be skipped
    if (p1.getX() == prevX && p1.getY() == prevY) {
        cout << "Test 9 passed: Invalid scale factor < 0 skipped" << endl;
        passed++;
    } else {
        cout << "Test 9 FAILED: Scale by negative not handled" << endl;
        failed++;
    }

    // Test 10: Display string check
    string displayStr = p1.display();
    if (displayStr.find("X = " + to_string(p1.getX())) != string::npos &&
        displayStr.find("Y = " + to_string(p1.getY())) != string::npos) {
        cout << "Test 10 passed: Display format" << endl;
        passed++;
    } else {
        cout << "Test 10 FAILED: Display string format incorrect" << endl;
        failed++;
    }

    // Summary
    cout << "========== Test Summary ==========" << endl;
    cout << "Passed: " << passed << ", Failed: " << failed << endl;
    cout << "==================================\n" << endl;
}


//
// Abstract Shape Class
// 
class Shape {
protected:
    Coordinates position; // Position of the shape (e.g., top-left or center)
    int sides;            // Number of sides of the shape

public:
    // Constructor: sets number of sides and initial position
    // Constructor: validates number of sides 
    Shape(int noOfSides, Coordinates coord)
        : position(0, 0), sides(0)  // default safe values
    {
        if (noOfSides < 0) {
            cout << "Warning: Shape sides cannot be negative. Defaulting to 0." << endl;
        } else {
            sides = noOfSides;
        }
            position = coord;
        
    }

    // Getter for coordinates
    Coordinates getCoordinates() const {
        return position;
    }

    // Getter for number of sides
    int getSides() const {
        return sides;
    }

    // Setter for position 
    void setCoordinates(Coordinates newCoord) {
      
            position = newCoord;
       
    }

    // Translate shape: only perform if resulting position stays non-negative
    virtual void translate(int dx, int dy) {
            position.translate(dx, dy);
    }

    // Scale shape: only perform if factor is strictly greater than 0
    virtual void scale(int factor, bool sign) {

        position.scale(factor, sign); // This only scales the position
    }

    // Pure virtual method to compute area (must be overridden)
    virtual double getArea() const = 0;

    // Pure virtual method to compute perimeter (must be overridden)
    virtual double getPerimeter() const = 0;

    // Virtual method to return general shape info (can be overridden)
    virtual string display() const {
        return "Shape with " + to_string(sides) + " sides at " + position.display();
    }

    // Virtual destructor
    virtual ~Shape() {}
};
/*
// ==============================
// Test function for Shape class
// ==============================
void test_shape_class() {
    cout << "\n========== Running test_shape_class() ==========" << endl;

    int passed = 0, failed = 0;

    // Test 1: Valid constructor
    Shape s1(4, Coordinates(10, 20));
    if (s1.getSides() == 4 && s1.getCoordinates().getX() == 10) {
        cout << "Test 1 passed: Valid constructor" << endl;
        passed++;
    } else {
        cout << "Test 1 FAILED: Valid constructor" << endl;
        failed++;
    }

    // Test 2: Constructor with invalid sides and negative coordinates
    Shape s2(-5, Coordinates(-1, -2)); // Should default to 0 sides and (0,0)
    if (s2.getSides() == 0 && s2.getCoordinates().getX() == 0 && s2.getCoordinates().getY() == 0) {
        cout << "Test 2 passed: Invalid constructor handled" << endl;
        passed++;
    } else {
        cout << "Test 2 FAILED: Invalid constructor" << endl;
        failed++;
    }

    // Test 3: Translate with valid shift
    s1.translate(5, 5);
    if (s1.getCoordinates().getX() == 15 && s1.getCoordinates().getY() == 25) {
        cout << "Test 3 passed: Valid translate" << endl;
        passed++;
    } else {
        cout << "Test 3 FAILED: Valid translate" << endl;
        failed++;
    }

    // Test 4: Translate with invalid shift
    int prevX = s1.getCoordinates().getX();
    int prevY = s1.getCoordinates().getY();
    s1.translate(-100, -100); // Should skip
    if (s1.getCoordinates().getX() == prevX && s1.getCoordinates().getY() == prevY) {
        cout << "Test 4 passed: Invalid translate skipped" << endl;
        passed++;
    } else {
        cout << "Test 4 FAILED: Invalid translate" << endl;
        failed++;
    }

    // Test 5: Scale with invalid factor
    s1.scale(0, true); // Should skip
    if (s1.getCoordinates().getX() == prevX && s1.getCoordinates().getY() == prevY) {
        cout << "Test 5 passed: Invalid scale factor skipped" << endl;
        passed++;
    } else {
        cout << "Test 5 FAILED: Invalid scale not skipped" << endl;
        failed++;
    }

    // Test 6: Valid scale
    s1.scale(2, true);
    if (s1.getCoordinates().getX() == prevX * 2 && s1.getCoordinates().getY() == prevY * 2) {
        cout << "Test 6 passed: Valid scale *2" << endl;
        passed++;
    } else {
        cout << "Test 6 FAILED: Valid scale *2" << endl;
        failed++;
    }

    // Summary
    cout << "========== Test Summary ==========" << endl;
    cout << "Passed: " << passed << ", Failed: " << failed << endl;
    cout << "==================================\n" << endl;
} */

// ==============================
// Rectangle Class
// ==============================
class Rectangle : public Shape {
private:
    double width;   // Width of the rectangle (must be positive)
    double length;  // Length of the rectangle (must be positive)

public:
    // Constructor with validation
    Rectangle(Coordinates position, double width, double length)
        : Shape(4, position) // 4 sides passed to Shape constructor
    {
        if (width <= 0 || length <= 0) {
            cout << "Warning: Width and length must be positive. Defaulting to 1." << endl;
            this->width = 1;
            this->length = 1;
        } else {
            this->width = width;
            this->length = length;
        }
    }

    // Override getArea()
    double getArea() const override {
        return width * length;
    }

    // Override getPerimeter()
    double getPerimeter() const override {
        return 2 * (width + length);
    }

    // Override scale(): update dimensions as well as position
    void scale(int factor, bool sign) override {
        if (factor <= 0) {
            cout << "Warning: Scaling factor must be greater than 0. Operation skipped." << endl;
            return;
        }

        // Scale position from base class
        Shape::scale(factor, sign);

        // Scale dimensions
        if (sign) {
            width *= factor;
            length *= factor;
        } else {
            width /= factor;
            length /= factor;
        }

    }

    // Override display()
    string display() const override {
        return "Rectangle at " + position.display() +
               ", Width = " + to_string(width) +
               ", Length = " + to_string(length) +
               ", Area = " + to_string(getArea()) +
               ", Perimeter = " + to_string(getPerimeter());
    }
};


// ==============================
// Test function for Rectangle class
// ==============================
void test_rectangle_class() {
    cout << "\n========== Running test_rectangle_class() ==========" << endl;

    int passed = 0, failed = 0;

    // Test 1: Valid constructor
    Rectangle r1(Coordinates(10, 20), 5, 10);
    if (r1.getCoordinates().getX() == 10 && r1.getCoordinates().getY() == 20 &&
        r1.getArea() == 50 && r1.getPerimeter() == 30) {
        cout << "Test 1 passed: Valid constructor and methods" << endl;
        passed++;
    } else {
        cout << "Test 1 FAILED: Constructor or methods" << endl;
        failed++;
    }

    // Test 2: Invalid constructor (negative width/length)
    Rectangle r2(Coordinates(5, 5), -2, -4);
    if (r2.getArea() == 1 && r2.getPerimeter() == 4) {
        cout << "Test 2 passed: Invalid dimensions defaulted to 1" << endl;
        passed++;
    } else {
        cout << "Test 2 FAILED: Invalid constructor handling" << endl;
        failed++;
    }

    // Test 3: Translate (valid)
    r1.translate(10, 5);
    if (r1.getCoordinates().getX() == 20 && r1.getCoordinates().getY() == 25) {
        cout << "Test 3 passed: Valid translation" << endl;
        passed++;
    } else {
        cout << "Test 3 FAILED: Translation" << endl;
        failed++;
    }

    // Test 4: Translate (invalid)
    Coordinates before = r1.getCoordinates();
    r1.translate(-100, -100); // Should be skipped
    if (r1.getCoordinates().getX() == before.getX() &&
        r1.getCoordinates().getY() == before.getY()) {
        cout << "Test 4 passed: Invalid translation skipped" << endl;
        passed++;
    } else {
        cout << "Test 4 FAILED: Invalid translation" << endl;
        failed++;
    }

    // Test 5: Scale with factor = 0 (should skip)
    before = r1.getCoordinates();
    r1.scale(0, true); // Should do nothing
    if (r1.getCoordinates().getX() == before.getX()) {
        cout << "Test 5 passed: Invalid scale factor skipped" << endl;
        passed++;
    } else {
        cout << "Test 5 FAILED: Scale by 0 not handled" << endl;
        failed++;
    }

    // Test 6: Scale with valid factor (multiply)
    r1.scale(2, true); // Should double dimensions
        // We use fabs( a -b) < 0.001 instead of a == b to compare doubles,
        // because floating-point values can have small precision errors.
        // This condition checks if the numbers are "close enough" to be considered equal.

    if ( fabs(r1.getArea() - 200.0) < 0.001 &&  fabs(r1.getPerimeter() - 60.00 ) < 0.001 ) {
        cout << "Test 6 passed: Scale *2" << endl;
        passed++;
    } else {
        cout << "Test 6 FAILED: Scale *2" << endl;
        failed++;
    }

    // Test 7: Scale with valid factor (divide)
        // We use fabs( a -b) < 0.001 instead of a == b to compare doubles,
        // because floating-point values can have small precision errors.
        // This condition checks if the numbers are "close enough" to be considered equal.
    r1.scale(2, false); // Should bring dimensions back to original
    if ( fabs(r1.getArea() - 50 ) < 0.001  && fabs(r1.getPerimeter() - 30) < 0.001 ) {
        cout << "Test 7 passed: Scale /2" << endl;
        passed++;
    } else {
        cout << "Test 7 FAILED: Scale /2" << endl;
        failed++;
    }

    // Test 8: Display contains keywords
    string output = r1.display();
    if (output.find("Rectangle") != string::npos &&
        output.find("Width") != string::npos &&
        output.find("Area") != string::npos) {
        cout << "Test 8 passed: Display formatting" << endl;
        passed++;
    } else {
        cout << "Test 8 FAILED: Display output" << endl;
        failed++;
    }

    // Summary
    cout << "========== Test Summary ==========" << endl;
    cout << "Passed: " << passed << ", Failed: " << failed << endl;
    cout << "==================================\n" << endl;
}


// Square Class

class Square : public Shape {
private:
    double side; // Side length of the square (must be positive)

public:

    // Constructor with input validation
    Square(Coordinates position, double sideLength)
        : Shape(4, position) // A square has 4 sides
    {
        if (sideLength <= 0) {
            cout << "Warning: Side must be positive. Defaulting to 1.0." << endl;
            side = 1.0;
        } else {
            side = sideLength;
        }
    }

    // Override getArea()
    double getArea() const override {
        return side * side;
    }

    // Override getPerimeter()
    double getPerimeter() const override {
        return 4 * side;
    }

    // Override scale() with validation
    void scale(int factor, bool sign) override {
        if (factor <= 0) {
            cout << "Warning: Scaling factor must be greater than 0. Operation skipped." << endl;
            return;
        }

        // Scale position using base class method
        Shape::scale(factor, sign);

        // Scale side length
        if (sign) {
            side *= factor;
        } else {
            side /= factor;
        }

        // Ensure side remains valid
        if (side <= 0) {
            cout << "Warning: Scaling resulted in invalid side length. Resetting to 1.0." << endl;
            side = 1.0;
        }
    }

    // Override display()
    string display() const override {
        return "Square at " + position.display() +
               ", Side = " + to_string(side) +
               ", Area = " + to_string(getArea()) +
               ", Perimeter = " + to_string(getPerimeter());
    }
};


// ==============================
// Test function for Square class
// ==============================
void test_square_class() {
    cout << "\n========== Running test_square_class() ==========" << endl;

    int passed = 0, failed = 0;

    // Test 1: Valid constructor
    Square s1(Coordinates(10, 20), 4.0);
    if (s1.getCoordinates().getX() == 10 && s1.getCoordinates().getY() == 20 &&
        abs(s1.getArea() - 16.0) < 0.001 && abs(s1.getPerimeter() - 16.0) < 0.001) {
        cout << "Test 1 passed: Valid constructor and calculations" << endl;
        passed++;
    } else {
        cout << "Test 1 FAILED: Constructor or calculations" << endl;
        failed++;
    }

    // Test 2: Invalid constructor (negative side)
    Square s2(Coordinates(5, 5), -2.0);  // Should default to 1.0
    if (s2.getArea() == 1 && s2.getPerimeter() == 4 ) {
        cout << "Test 2 passed: Invalid constructor handled" << endl;
        passed++;
    } else {
        cout << "Test 2 FAILED: Invalid constructor" << endl;
        failed++;
    }

    // Test 3: Valid translate
    s1.translate(5, 5);
    if (s1.getCoordinates().getX() == 15 && s1.getCoordinates().getY() == 25) {
        cout << "Test 3 passed: Valid translate" << endl;
        passed++;
    } else {
        cout << "Test 3 FAILED: Translate" << endl;
        failed++;
    }

    // Test 4: Invalid translate (should skip)
    Coordinates before = s1.getCoordinates();
    s1.translate(-100, -100);
    if (s1.getCoordinates().getX() == before.getX() &&
        s1.getCoordinates().getY() == before.getY()) {
        cout << "Test 4 passed: Invalid translate skipped" << endl;
        passed++;
    } else {
        cout << "Test 4 FAILED: Translate check" << endl;
        failed++;
    }

    // Test 5: Scale with invalid factor (zero)
    s1.scale(0, true); // Should skip

        // We use fabs( a -b) < 0.001 instead of a == b to compare doubles,
        // because floating-point values can have small precision errors.
        // This condition checks if the numbers are "close enough" to be considered equal.
    if (fabs(s1.getArea() - 16.0) < 0.001 && fabs( s1.getPerimeter() - 16.0 ) < 0.001 ) {
        cout << "Test 5 passed: Invalid scale factor skipped" << endl;
        passed++;
    } else {
        cout << "Test 5 FAILED: Scale by 0 not handled" << endl;
        failed++;
    }

    // Test 6: Valid scale (multiply)
    s1.scale(2, true); // side becomes 8

        // We use fabs( a -b) < 0.001 instead of a == b to compare doubles,
        // because floating-point values can have small precision errors.
        // This condition checks if the numbers are "close enough" to be considered equal.
    if (fabs(s1.getArea() - 64.0) < 0.001 && fabs(s1.getPerimeter() - 32.0) < 0.001) {
        cout << "Test 6 passed: Scale *2" << endl;
        passed++;
    } else {
        cout << "Test 6 FAILED: Scale *2" << endl;
        failed++;
    }




    // Test 7: Valid scale (divide)
    s1.scale(2, false); // side becomes 4 again

        // We use fabs( a -b) < 0.001 instead of a == b to compare doubles,
        // because floating-point values can have small precision errors.
        // This condition checks if the numbers are "close enough" to be considered equal.
    if (fabs(s1.getArea() - 16.0) < 0.001 && fabs(s1.getPerimeter() - 16.0) < 0.001) {
        cout << "Test 7 passed: Scale /2" << endl;
        passed++;
    } else {
        cout << "Test 7 FAILED: Scale /2" << endl;
        failed++;
    }

    // Test 8: Display string contains key info
    string output = s1.display();
    if (output.find("Square") != string::npos &&
        output.find("Side") != string::npos &&
        output.find("Area") != string::npos) {
        cout << "Test 8 passed: Display formatting" << endl;
        passed++;
    } else {
        cout << "Test 8 FAILED: Display check" << endl;
        failed++;
    }

    // Summary
    cout << "========== Test Summary ==========" << endl;
    cout << "Passed: " << passed << ", Failed: " << failed << endl;
    cout << "==================================\n" << endl;
}

// ==============================
// Circle Class
// ==============================
class Circle : public Shape {
private:
    double radius;  // Radius of the circle (must be positive)

public:
    // Constructor with input validation
    Circle(Coordinates position, double r)
        : Shape(0, position)  // Circles are defined with 0 sides
    {
        if (r <= 0) {
            cout << "Warning: Radius must be positive. Defaulting to 1.0." << endl;
            radius = 1.0;
        } else {
            radius = r;
        }
    }

    // Override getArea()
    double getArea() const override {
        return M_PI * radius * radius;  // M_PI is a standard constant for π from <cmath>
    }

    // Override getPerimeter()
    double getPerimeter() const override {
        return 2 * M_PI * radius;
    }

    // Override scale(): multiply or divide the radius and scale position
    void scale(int factor, bool sign) override {
        if (factor <= 0) {
            cout << "Warning: Scaling factor must be greater than 0. Operation skipped." << endl;
            return;
        }

        // Scale center position (from Shape)
        Shape::scale(factor, sign);

        // Scale radius
        if (sign) {
            radius *= factor;
        } else {
            radius /= factor;
        }

        // Ensure radius remains valid
        if (radius <= 0) {
            cout << "Warning: Radius became non-positive after scaling. Resetting to 1.0." << endl;
            radius = 1.0;
        }
    }

    // Override display()
    string display() const override {
        return "Circle at " + position.display() +
               ", Radius = " + to_string(radius) +
               ", Area = " + to_string(getArea()) +
               ", Perimeter = " + to_string(getPerimeter());
    }
};


// ==============================
// Test function for Circle class
// ==============================
void test_circle_class() {
    cout << "\n========== Running test_circle_class() ==========" << endl;

    int passed = 0, failed = 0;

    // Test 1: Valid constructor
    Circle c1(Coordinates(10, 10), 5.0);
    if (c1.getCoordinates().getX() == 10 && c1.getCoordinates().getY() == 10 &&
        fabs(c1.getArea() - (M_PI * 25.0)) < 0.001 &&
        fabs(c1.getPerimeter() - (2 * M_PI * 5.0)) < 0.001) {
        cout << "Test 1 passed: Valid constructor and calculations" << endl;
        passed++;
    } else {
        cout << "Test 1 FAILED: Constructor or calculations" << endl;
        failed++;
    }

    // Test 2: Invalid constructor (negative radius)
    Circle c2(Coordinates(5, 5), -3.0);  // Should default to radius = 1.0
    if (fabs(c2.getArea() - (M_PI)) < 0.001 &&
        fabs(c2.getPerimeter() - (2 * M_PI)) < 0.001) {
        cout << "Test 2 passed: Invalid radius handled" << endl;
        passed++;
    } else {
        cout << "Test 2 FAILED: Invalid radius" << endl;
        failed++;
    }

    // Test 3: Valid translate
    c1.translate(5, 5);
    if (c1.getCoordinates().getX() == 15 && c1.getCoordinates().getY() == 15) {
        cout << "Test 3 passed: Valid translate" << endl;
        passed++;
    } else {
        cout << "Test 3 FAILED: Translate" << endl;
        failed++;
    }

    // Test 4: Invalid translate
    Coordinates before = c1.getCoordinates();
    c1.translate(-100, -100); // Should skip
    if (c1.getCoordinates().getX() == before.getX() &&
        c1.getCoordinates().getY() == before.getY()) {
        cout << "Test 4 passed: Invalid translate skipped" << endl;
        passed++;
    } else {
        cout << "Test 4 FAILED: Invalid translate" << endl;
        failed++;
    }

    // Test 5: Scale with valid factor (multiply)
    c1.scale(2, true);  // Radius = 10
    if (fabs(c1.getArea() - (M_PI * 100.0)) < 0.001 &&
        fabs(c1.getPerimeter() - (2 * M_PI * 10.0)) < 0.001) {
        cout << "Test 5 passed: Scale *2" << endl;
        passed++;
    } else {
        cout << "Test 5 FAILED: Scale *2" << endl;
        failed++;
    }

    // Test 6: Scale with valid factor (divide)
    c1.scale(2, false);  // Radius = 5 again
    if (fabs(c1.getArea() - (M_PI * 25.0)) < 0.001 &&
        fabs(c1.getPerimeter() - (2 * M_PI * 5.0)) < 0.001) {
        cout << "Test 6 passed: Scale /2" << endl;
        passed++;
    } else {
        cout << "Test 6 FAILED: Scale /2" << endl;
        failed++;
    }

    // Test 7: Invalid scale (factor = 0)
    before = c1.getCoordinates();
    c1.scale(0, true);
    if (c1.getCoordinates().getX() == before.getX() &&
        fabs(c1.getArea() - (M_PI * 25.0)) < 0.001 &&
        fabs(c1.getPerimeter() - (2 * M_PI * 5.0)) < 0.001 ) {
        cout << "Test 7 passed: Invalid scale skipped" << endl;
        passed++;
    } else {
        cout << "Test 7 FAILED: Invalid scale" << endl;
        failed++;
    }

    // Test 8: Display content check
    string output = c1.display();
    if (output.find("Circle") != string::npos &&
        output.find("Radius") != string::npos &&
        output.find("Area") != string::npos) {
        cout << "Test 8 passed: Display formatting" << endl;
        passed++;
    } else {
        cout << "Test 8 FAILED: Display check" << endl;
        failed++;
    }

    // Summary
    cout << "========== Test Summary ==========" << endl;
    cout << "Passed: " << passed << ", Failed: " << failed << endl;
    cout << "==================================\n" << endl;
}

// Triangle class 
class Triangle : public Shape {
private :
// Coordinates of the three Points that correspond to the three vertices of the triangle
        Coordinates position1 , position2  , position3 ; 
        
public:
  // class Constructor
  Triangle( Coordinates position1 , Coordinates position2 , Coordinates position3 )
          : Shape( 3 , position1 ) // triangle defined with three sides and the base class will store the first position of it three
   {
    this->position1 = position1 ; this->position2 = position2 ; this->position3 = position3 ;
   }  

   // Override getPerimeter()
   double getPerimeter() const override {

    // calculates the three sides of the triangles and return thier sum  
    double side1 = position1.distance( position2 ) ; 
    double side2 = position1.distance ( position3 ) ; 
    double side3 = position2.distance( position3 ) ; 

    return side1 + side2 + side3 ; 

   }
   
   // Override getArea()
   double getArea() const override {
    
    /* 
    calculate the are of triangle using this formula : 

    𝑎𝑟𝑒𝑎 = √𝑠(𝑠 − 𝑎)(𝑠 − 𝑏)(𝑠 − 𝑐)

    where a , b , c are three sides of our triangle 

    and s is semiperimeter = ( a + b + c ) / 2 

    */

    // calculates the three sides of the triangles
    double side1 = position1.distance( position2 ) ; 
    double side2 = position1.distance ( position3 ) ; 
    double side3 = position2.distance( position3 ) ; 

    double s =  ( side1 + side2 + side3 ) / 2.0 ;  // semiperimeter  calculation 

    return sqrt( s * ( s - side1 ) * ( s - side2 ) * ( s - side3 )) ; 

   }

   // override translate() 
   void translate( int dx , int dy ) override {

    // translate all the three positions 
    position1.translate( dx , dy ) ;
    position2.translate( dx , dy ) ; 
    position3.translate( dx , dy ) ; 

   }

   // override scale()

   void scale( int factor , bool sign ) override {

   
        position1.scale( factor  , sign ) ;
        position2.scale( factor, sign ) ;
        position3.scale( factor, sign ) ;

   }

   // Override display()
   string display() const override {
    return "Triangle At " + position1.display() + " | "+ position2.display() + " | " + position3.display() +
    ", Area = " + to_string(getArea()) +
    ", Perimeter = " + to_string(getPerimeter());
    
   }
   
   
} ;


// ShapeList Class

class ShapeList {
private:
    vector<Shape*> listofShapes;  // Stores a list of shapes using polymorphism

public:
    // Add a shape to the list
    void addShape(Shape* s) {
        if (s != nullptr) {
            listofShapes.push_back(s);
        }
    }

    // Translate all shapes in the list by (dx, dy)
    void translateShapes(int dx, int dy) {
        for (Shape* s : listofShapes) {
            if (s != nullptr) {
                s->translate(dx, dy);
            }
        }
    }

    // Return the shape at a specific position (index starts at 0)
    Shape* getShape(int pos) {
        if (pos >= 0 && pos < static_cast<int>(listofShapes.size())) {
            return listofShapes[pos];
        }
        cout << "Warning: Invalid position in getShape(). Returning nullptr." << endl;
        return nullptr;
    }

    // Remove the shape at a specific position and return it (caller is responsible for deletion)
    Shape* removeShape(int pos) {
        if (pos >= 0 && pos < static_cast<int>(listofShapes.size())) {
            Shape* removed = listofShapes[pos];
            listofShapes.erase(listofShapes.begin() + pos);
            return removed;
        }
        cout << "Warning: Invalid position in removeShape()." << endl;
        return nullptr;
    }

    // Return the area of the shape at a given position
    double area(int pos) {
        Shape* s = getShape(pos);
        if (s != nullptr) {
            return s->getArea();
        }
        return -1.0;
    }

    // Return the perimeter of the shape at a given position
    double perimeter(int pos) {
        Shape* s = getShape(pos);
        if (s != nullptr) {
            return s->getPerimeter();
        }
        return -1.0;
    }

    // Scale all shapes in the list
    void scale(int factor, bool sign) {
        for (Shape* s : listofShapes) {
            if (s != nullptr) {
                s->scale(factor, sign);
            }
        }
    }

    // Display information about all shapes
    string display() {
        string result = "--- Shape List ---\n\n";
        for (size_t i = 0; i < listofShapes.size(); ++i) {
            result += "Shape " + to_string(i + 1) + ": " + listofShapes[i]->display() + "\n\n";
        }
        return result;
    }

    // Destructor: delete all dynamically allocated shapes
    ~ShapeList() {
        for (Shape* s : listofShapes) {
            delete s;
        }
        listofShapes.clear();
    }
};


// ShapeManagement Class

class ShapeManagement {
private:
    ShapeList shapes;  // Composition: ShapeManagement "has-a" ShapeList

public:
    // Display menu options
    void displayMenu() {
        cout << "\n\n Shape Management Menu " << endl;
        cout << "1. Add a shape" << endl;
        cout << "2. Remove a shape" << endl;
        cout << "3. Display all shapes" << endl;
        cout << "4. Translate all shapes" << endl;
        cout << "5. Scale all shapes" << endl;
        cout << "6. Get area of a shape by position" << endl;
        cout << "7. Get perimeter of a shape by position" << endl;
        cout << "0. Exit\n\n" << endl;
    }

    // Add a shape (user selects type and provides input)
    void addShape() {
        int type;
        cout << "Select shape type: 1-Rectangle, 2-Circle, 3-Square, 4-Triangle: ";
        cin >> type;

        if (type == 1) {
            int x, y;
            double width, length;
            cout << "Enter x y coordinates: ";
            cin >> x >> y;
            cout << "Enter width and length: ";
            cin >> width >> length;
            shapes.addShape(new Rectangle(Coordinates(x, y), width, length));
        }
        else if (type == 2) {
            int x, y;
            double radius;
            cout << "Enter x y coordinates: ";
            cin >> x >> y;
            cout << "Enter radius: ";
            cin >> radius;
            shapes.addShape(new Circle(Coordinates(x, y), radius));
        }
        else if (type == 3) {
            int x, y;
            double side;
            cout << "Enter x y coordinates: ";
            cin >> x >> y;
            cout << "Enter side length: ";
            cin >> side;
            shapes.addShape(new Square(Coordinates(x, y), side));
        }
        else if (type == 4) {
            int x1, y1, x2, y2, x3, y3;
            cout << "Enter coordinates of point 1: ";
            cin >> x1 >> y1;
            cout << "Enter coordinates of point 2: ";
            cin >> x2 >> y2;
            cout << "Enter coordinates of point 3: ";
            cin >> x3 >> y3;
            shapes.addShape(new Triangle(
                Coordinates(x1, y1),
                Coordinates(x2, y2),
                Coordinates(x3, y3)
            ));
        } else {
            cout << "Invalid shape type selected." << endl;
        }
    }

    // Remove a shape at a given position
    void removeShape() {
        int pos;
        cout << "Enter shape position to remove (starting from 0): ";
        cin >> pos;
        Shape* removed = shapes.removeShape(pos);
        if (removed != nullptr) {
            cout << "Shape removed: " << removed->display() << endl;
            delete removed;  // Important: free memory
        }
    }

    // Display all shapes
    void displayShapes() {
        cout << shapes.display();
    }
     
        // Get area of a shape at a given position
    void getAreaOfShape() {
        int pos;
        cout << "Enter shape position to calculate area (starting from 0): ";
        cin >> pos;
        double result = shapes.area(pos);
        if (result >= 0) {
            cout << "Area of shape at position " << pos << " = " << result << endl;
        } else {
            cout << "Invalid position. Cannot compute area." << endl;
        }
    }

    // Get perimeter of a shape at a given position
    void getPerimeterOfShape() {
        int pos;
        cout << "Enter shape position to calculate perimeter (starting from 0): ";
        cin >> pos;
        double result = shapes.perimeter(pos);
        if (result >= 0) {
            cout << "Perimeter of shape at position " << pos << " = " << result << endl;
        } else {
            cout << "Invalid position. Cannot compute perimeter." << endl;
        }
    }
    // Translate all shapes
    void translateShapes() {
        int dx, dy;
        cout << "Enter dx and dy to translate all shapes: ";
        cin >> dx >> dy;
        shapes.translateShapes(dx, dy);
    }

    // Scale all shapes
    void scaleShapes() {
        int factor;
        bool sign;
        cout << "Enter scale factor: ";
        cin >> factor;
        cout << "Enter scale type (1 for multiply, 0 for divide): ";
        cin >> sign;
        shapes.scale(factor, sign);
    }

            // Direct add method for testing (bypasses menu)
        void addShapeDirectly(Shape* shape) {
            shapes.addShape(shape);
        }

        // Provide access to ShapeList for testing
        ShapeList& getShapeList() {
            return shapes;
        }
};

// ==============================
// Test function for ATI Test Plan
// ==============================
void test_ATI_functional_scenario() {
    cout << "\n========== Running ATI Functional Test Scenario ==========" << endl;

    ShapeManagement manager;

    // Helper access to ShapeList
    ShapeList& shapeList = manager.getShapeList();

    // Step 1: Add Triangle
    Triangle* t = new Triangle(Coordinates(50, 50), Coordinates(20, 70), Coordinates(70, 70));
    manager.addShapeDirectly(t);

    // Step 2: Add Rectangle
    Rectangle* r = new Rectangle(Coordinates(100, 20), 10, 15);
    manager.addShapeDirectly(r);

    // Step 3: Add Circle
    Circle* c = new Circle(Coordinates(80, 100), 25);
    manager.addShapeDirectly(c);

    // Step 4: Add Square
    Square* s = new Square(Coordinates(90, 40), 20);
    manager.addShapeDirectly(s);

    // Step 5: Add 3 more shapes
    manager.addShapeDirectly(new Rectangle(Coordinates(10, 10), 5, 6));
    manager.addShapeDirectly(new Triangle(Coordinates(0, 0), Coordinates(30, 0), Coordinates(15, 25)));
    manager.addShapeDirectly(new Square(Coordinates(5, 5), 10));

    // Step 6: Area and perimeter of second shape (index 1)
    cout << "Area of shape 2: " << shapeList.area(1) << endl;
    cout << "Perimeter of shape 2: " << shapeList.perimeter(1) << endl;

    // Step 7: Display all shapes
    cout << shapeList.display();

    // Step 8: Remove third shape (index 2)
    Shape* removed = shapeList.removeShape(2);
    if (removed) {
        cout << "Removed shape: " << removed->display() << endl;
        delete removed;
    }

    // Step 9: Translate all shapes by (10, 15)
    shapeList.translateShapes(10, 15);

    // Step 10: Display all shapes after translation
    cout << "\n--- After Translation ---\n";
    cout << shapeList.display();

    // Step 11: Scale all shapes by factor 2 (multiply)
    shapeList.scale(2, true);

    // Step 12: Display all shapes after scaling
    cout << "\n--- After Scaling ---\n";
    cout << shapeList.display();

    // Step 13: Error handling - invalid index
    Shape* sErr = shapeList.removeShape(20);
    if (!sErr) cout << "Handled invalid remove correctly.\n";

    double aErr = shapeList.area(100);
    if (aErr < 0) cout << "Handled invalid area correctly.\n";

    cout << "========== ATI Test Completed ==========" << endl;
}

// Main Function

int main() {
     //test_ATI_functional_scenario() ; 
    
    ShapeManagement manager;  // Create shape manager
    int choice;

    do {
        // Display menu options
        manager.displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        // Handle user choice
        switch (choice) {
            case 1:
                manager.addShape();
                break;
            case 2:
                manager.removeShape();
                break;
            case 3:
                manager.displayShapes();
                break;
            case 4:
                manager.translateShapes();
                break;
            case 5:
                manager.scaleShapes();
                break;
            case 6:
                manager.getAreaOfShape();
                break;
            case 7:
                manager.getPerimeterOfShape();
                break;
            case 0:
                cout << "Exiting program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != 0);  // Keep running until user selects Exit */

    return 0;
}
