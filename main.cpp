#include <iostream>
#include <cmath>
#include <string>
using namespace std;

// ==============================
// Coordinates Class
// ==============================
class Coordinates {
private:
    int x;  // X coordinate (must be positive)
    int y;  // Y coordinate (must be positive)

public:
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


// Main Function (Testing Coordinates)

int main() {
    
    test_coordinate_class() ; 
    return 0 ;

}