#include "solitaire.h"
#include <vector>
#include <functional>
#include <string>
using namespace std;

const string green_escape_code = "\x1b[32;1m";
const string red_escape_code = "\x1b[31;1m";
const string reset_escape_code = "\x1b[0m";

class Tester {
public:
    // 1. Test whether the constructor works correctly for an error case (unsupported shape like French board)
    bool testConstructorErrorCase() {
        // Create two objects with invalid parameters
        Solitaire s1(FRENCH);
        Solitaire s2(NONE);

        // Check that they're empty, their values are zero
        bool t1 = s1.m_numMarbles == 0 && s1.m_numRows == 0 && s1.m_numColumns == 0 && s1.m_board == nullptr;
        bool t2 = s2.m_numMarbles == 0 && s2.m_numRows == 0 && s2.m_numColumns == 0 && s2.m_board == nullptr;

        if(t1 && t2) {
            return true;
        } else {
            return false;
        }
    }

    // 2. Test whether the constructor works correctly for a normal case (supported shape like English board)
    bool testConstructorNormalCase() {
        // Implementation goes here
        return false;
    }

    // 3. Test whether newBoard(...) works correctly for an error case (e.g., re-initializing an empty object)
    bool testNewBoardErrorCase() {
        // Implementation goes here
        return false;
    }

    // 4. Test whether newBoard(...) works correctly for a normal case (valid re-initialization)
    bool testNewBoardNormalCase() {
        // Implementation goes here
        return false;
    }

    // 5. Test whether changeBoard(...) works correctly when called on the same board shape
    bool testChangeBoardSameShape() {
        // Implementation goes here
        return false;
    }

    // 6. Test whether changeBoard(...) works correctly when called on a different board shape
    bool testChangeBoardDifferentShape() {
        // Implementation goes here
        return false;
    }

    // 7. Test whether play(...) works correctly for a correct move (normal case)
    bool testPlayNormalMove() {
        // Implementation goes here
        return false;
    }

    // 8. Test whether play(...) works correctly for a wrong move (error case)
    bool testPlayErrorMove() {
        // Implementation goes here
        return false;
    }

    // 9. Test the copy constructor for an error case (copying an empty object)
    bool testCopyConstructorErrorCase() {
        // Implementation goes here
        return false;
    }

    // 10. Test the copy constructor for a normal case (copying a valid object)
    bool testCopyConstructorNormalCase() {
        // Implementation goes here
        return false;
    }

    // 11. Test whether the object remains unchanged when trying to re-initialize an empty object
    bool testNewBoardDoesNotModifyEmptyObject() {
        // Implementation goes here
        return false;
    }

    // 12. Test whether newBoard(...) returns false when called on an empty object
    bool testNewBoardReturnsFalseOnEmptyObject() {
        // Implementation goes here
        return false;
    }
};

void run_test(string name, function<bool()> func) {
    if (func()) {
        cout << green_escape_code << "[ PASSED ]" << reset_escape_code << "\t" << name << endl;
    } else {
        cout << red_escape_code << "[ FAILED ]" << reset_escape_code << "\t" << name << endl;
    }
}

#define TEST(name, func) run_test(name, [&t]()  { return t.func(); } );

int main() {
    Tester t;
    TEST("testConstructorErrorCase", testConstructorErrorCase);

}