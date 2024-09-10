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
        Solitaire s1(ENGLISH);
        Solitaire s2(DIAMOND);

        bool t1 = s1.m_numMarbles == NUMENGLISHMARBLES && s1.m_numRows == ENGLISHSIZE && s1.m_numColumns == ENGLISHSIZE && s1.m_board != nullptr;
        bool t2 = s2.m_numMarbles == NUMDIAMONDMARBLES && s2.m_numRows == DIAMONDSIZE && s2.m_numColumns == DIAMONDSIZE && s2.m_board != nullptr;

        if(t1 && t2) {
            return true;
        } else {
            return false;
        }
    }
    // 3. Test whether newBoard(...) works correctly for an error case (e.g., re-initializing an empty object)
    bool testNewBoardErrorCase() {
        Solitaire s1(NONE);
        Solitaire s2(FRENCH);

        if(!s1.newBoard() && !s2.newBoard()) {
            return true;
        } else {
            return false;
        }
    }
    // 4. Test whether newBoard(...) works correctly for a normal case (valid re-initialization)
    bool testNewBoardNormalCase() {
        Solitaire s1(DIAMOND);

        // Play a few valid moves to change up the board
        s1.play(pair<int,int>(6,4), pair<int,int>(4,4));
        s1.play(pair<int,int>(5,2), pair<int,int>(5,4));

        int before_marbles = s1.m_numMarbles;
        string before_board_state =  s1.board_to_string();
        int** before_move_address = s1.m_board;

        s1.newBoard();

        int after_marbles = s1.m_numMarbles;
        string after_board_state =  s1.board_to_string();
        int** after_move_address = s1.m_board;

        // If the re-initialization worked, the same memory location must've been
        // kept but the shape must've been reset.
        if(before_move_address == after_move_address && before_marbles != after_marbles && before_board_state != after_board_state) {
            return true;
        } else {
            return false;
        }
    }
    // 5. Test whether changeBoard(...) works correctly when called on the same board shape
    bool testChangeBoardSameShape() {
        // If it works correctly then the memory address of
        // the board should be the same but the board state will be different.
        Solitaire s1(ENGLISH);
        s1.play(pair(1,3), pair(3,3));
        s1.play(pair(2,1), pair(2,3));

        int **before_addy = s1.m_board;
        int before_marble = s1.m_numMarbles;
        string before_state = s1.board_to_string();

        s1.changeBoard(ENGLISH);

        int **after_addy = s1.m_board;
        int after_marble = s1.m_numMarbles;
        string after_state = s1.board_to_string();

        if(before_addy == after_addy &&
            before_marble != after_marble &&
            before_state != after_state
        ) {
            return true;
        } else {
            return false;
        }
    }
    // 6. Test whether changeBoard(...) works correctly when called on a different board shape
    bool testChangeBoardDifferentShape() {
        // If it works correctly then the memory address of
        // the board should be different fr, also everything else should be different too!
        Solitaire s1(ENGLISH);

        // in this case we don't need to make moves to alter
        // the board state since changing up the board
        // will do that for us fr

        int **before_addy = s1.m_board;
        int before_marble = s1.m_numMarbles;
        string before_state = s1.board_to_string();

        s1.changeBoard(DIAMOND);

        int **after_addy = s1.m_board;
        int after_marble = s1.m_numMarbles;
        string after_state = s1.board_to_string();

        if(before_addy != after_addy &&
           before_marble != after_marble &&
           before_state != after_state
                ) {
            return true;
        } else {
            return false;
        }
    }
    // 7. Test whether play(...) works correctly for a correct move (normal case)
    bool testPlayNormalMove() {
        Solitaire s1(ENGLISH);

        // All valid moves
        if(
        s1.play(pair(5, 3), pair(3, 3)) &&
        s1.play(pair(4, 1), pair(4, 3)) &&
        s1.play(pair(2, 2), pair(4, 2)) &&
        s1.play(pair(3, 3), pair(5, 3))
        ) {
            return true;
        } else {
            return false;
        }
    }
    // 8. Test whether play(...) works correctly for a wrong move (error case)
    bool testPlayErrorMove() {
        Solitaire s1(DIAMOND);

        // All invalid moves
        if(
            !s1.play(pair(0, 0), pair(-1, -1)) &&
            !s1.play(pair(0, 4), pair(1, 4)) &&
            !s1.play(pair(4, 4), pair(1032, -9233)) &&
            !s1.play(pair(5, 2), pair(5, 4))
        ) {
            return true;
        } else {
            return false;
        }
    }
    // 9. Test the copy constructor for an error case (copying an empty object)
    bool testCopyConstructorErrorCase() {
        Solitaire s1(NONE);
        Solitaire s2(s1);

        // Object is empty
        if( s2.m_numMarbles == 0 && s2.m_numRows == 0 && s2.m_numColumns == 0 && s2.m_board == nullptr ) {
            return true;
        } else {
            return false;
        }
    }
    // 10. Test the copy constructor for a normal case (copying a valid object)
    bool testCopyConstructorNormalCase() {
        Solitaire s1(ENGLISH);

        s1.play(pair(5, 3), pair(3, 3));
        s1.play(pair(4, 1), pair(4, 3));
        s1.play(pair(2, 2), pair(4, 2));
        s1.play(pair(3, 3), pair(5, 3));

        Solitaire s2(s1);

        int original_marbles = s1.m_numMarbles;
        string original_board_state =  s1.board_to_string();
        int** original_move_address = s1.m_board;

        int copy_marbles = s2.m_numMarbles;
        string copy_board_state =  s2.board_to_string();
        int** copy_move_address = s2.m_board;

        // It should be different memory address but everything
        // else should be the same fr
        if(original_move_address != copy_move_address && original_marbles == copy_marbles && original_board_state == copy_board_state) {
            return true;
        } else {
            return false;
        }
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

    TEST("Constructor Error Case", testConstructorErrorCase);
    TEST("Constructor Normal Case", testConstructorNormalCase);
    TEST("New Board Error Case", testNewBoardErrorCase);
    TEST("New Board Normal Case", testNewBoardNormalCase)
    TEST("Change Board Same Shape", testChangeBoardSameShape);
    TEST("Change Board Different Shape", testChangeBoardDifferentShape)
    TEST("Play Normal Move", testPlayNormalMove);
    TEST("Play Error Move", testPlayErrorMove);
    TEST("Copy Constructor Error Case", testCopyConstructorErrorCase);
    TEST("Copy Constructor Normal Case", testCopyConstructorNormalCase);
}