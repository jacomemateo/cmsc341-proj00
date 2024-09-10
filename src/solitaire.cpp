// UMBC - CMSC 341 - Fall 2024 - Proj0
#include "solitaire.h"

const pair<int, int> empty_spaces_english[4] = {
        make_pair(0, 0),
        make_pair(0, 1),
        make_pair(1, 0),
        make_pair(1, 1),
};

const pair<int, int> empty_spaces_diamond[10] = {
        make_pair(0, 0),
        make_pair(0, 1),
        make_pair(0, 2),
        make_pair(0, 3),
        make_pair(1, 0),
        make_pair(1, 1),
        make_pair(1, 2),
        make_pair(2, 0),
        make_pair(2, 1),
        make_pair(3, 0),
};

// Default constructor
Solitaire::Solitaire() : m_numRows(0), m_numColumns(0), m_board(nullptr), m_shape(NONE), m_numMarbles(0) {}

// Initializes all member variables and it allocates required memory if necessary.
Solitaire::Solitaire(BOARDSHAPE shape) : m_board(nullptr) {
    init(shape);
}

Solitaire::Solitaire(const Solitaire & rhs) {
    m_numRows = rhs.m_numRows;
    m_numColumns = rhs.m_numColumns;
    m_shape = rhs.m_shape;
    m_numMarbles = rhs.m_numMarbles;


    if(rhs.m_board == nullptr) {
        m_board = nullptr;
    }
    else {
        m_board = new int* [m_numRows];

        for(int i=0; i<m_numRows; i++) {
            m_board[i] = new int[m_numColumns];
            for(int j=0; j<m_numColumns; j++) {
                m_board[i][j] = rhs.m_board[i][j];
            }
        }
    }
}

Solitaire::~Solitaire(){
    clear();
}

void Solitaire::clear() {
    // We have to add this check in case the
    // user provided a non-supported shape so that
    // we don't try to deallocate a non-existent address
    if(m_board != nullptr) {
        for (int i = 0; i < m_numRows; i++) {
            delete[] m_board[i];
        }

        delete[] m_board;
        m_board = nullptr;
    }

    // Reset the rest of the variables fr
    m_numRows = 0;
    m_numColumns = 0;
    m_shape = NONE;
    m_numMarbles = 0;
}

bool Solitaire::play(pair<int,int> origin, pair<int,int> destination){
    // Bound checking for the 2d array
    if(
        origin.first < 0 || origin.first > m_numColumns ||
        origin.second < 0 || origin.second > m_numRows ||
        destination.first < 0 || destination.first > m_numColumns ||
        destination.second < 0 || destination.second > m_numColumns
    ) {
        return false;
    }

    bool invalid_conditions[4];

    // Destination is empty
    invalid_conditions[0] = m_board[destination.first][destination.second] != HOLE;

     // Destination is orthogonal
    invalid_conditions[1] = !(origin.second - destination.second == 0 || origin.first - destination.first == 0);

     // Destination is exactly 2 moves away
    pair<int, int> direction = make_pair(abs(destination.first - origin.first), abs(destination.second - origin.second));
    invalid_conditions[2] = !(direction.first == 2 || direction.second == 2);

    // Check that middle point is a marble
    pair<int, int> middle_point = make_pair( (origin.first+destination.first)/2, (origin.second+destination.second)/2);
    invalid_conditions[3] = m_board[middle_point.first][middle_point.second] != MARBLE;

    for(bool condition : invalid_conditions) {
        if(condition) {
            return false;
        }
    }

    // Switch thingies
    m_board[origin.first][origin.second] = HOLE;
    m_board[middle_point.first][middle_point.second] = HOLE;
    m_board[destination.first][destination.second] = MARBLE;

    // Decrement marble fr‼️
    m_numMarbles--;

    return true;
}

void Solitaire::changeBoard(BOARDSHAPE shape){
    // If the provided board shape is the same, just re-initalize
    if(shape == m_shape) {
        newBoard();
    }
    // Otherwise reset the board
    else {
        clear();
        init(shape);
    }
}

bool Solitaire::newBoard(){
    if(m_board == nullptr) {
        return false;
    }

    initializeMemberVariables(m_shape);
    setupBoard(m_shape);
    return true;
}

void Solitaire::dumpBoard() {
    // this is to facilitate debugging
    cout << "  ";
    for (int k=0;k<m_numColumns;k++){
        cout << k << " ";
    }
    cout << endl;
    for (int i=1;i <= m_numRows;i++){
        cout << i-1 << " ";
        for (int j=1;j<=m_numColumns;j++){
            if (m_board[i-1][j-1] == OUT)
                cout << "  ";
            else if (m_board[i-1][j-1] == HOLE)
                cout << BLACKSTAR;
            else
                cout << REDSTAR;
        }
        cout << endl;
    }
    cout << endl;
}

int Solitaire::reportNumMarbles(){
    // this is to facilitate debugging 
    cout << "You have " << m_numMarbles << " marbles to remove!" << endl;
    return m_numMarbles;
}

void Solitaire::initializeMemoryBoard() {
    if(m_board == nullptr) {
        m_board = new int *[m_numRows];

        for (int i = 0; i < m_numRows; i++) {
            m_board[i] = new int[m_numColumns];
        }
    }
}

void Solitaire::populateBoard(const pair<int, int> void_positions[], size_t size) {
    // Fill the board with marbles since it's the majority of what makes up the board.
    for(int i=0; i<m_numRows; i++) {
        m_board[i] = new int[m_numColumns];
        for(int j=0; j<m_numColumns; j++) {
            m_board[i][j] = MARBLE;
        }
    }

    // Now we simply clear the corners to give the board it's final shape.

    // The valid positions represent the upper left corner of the board,
    // since all the boards provided are symmetrical we can just reflect them over
    // The x-axis, y-axis, and both the x and y axies
    for(size_t i = 0; i<size; i++) {
        pair<int, int> cc = void_positions[i];

        m_board[cc.first][cc.second] = OUT; // left top
        m_board[m_numRows - cc.first - 1][cc.second] = OUT; // right top
        m_board[cc.first][m_numColumns - cc.second - 1] = OUT; // left bottom
        m_board[m_numRows - cc.first - 1][m_numColumns - cc.second - 1] = OUT; // right bottom
    }

    // Calculate and set middle hole
    m_board[m_numRows/2][m_numColumns/2] = HOLE;
}

void Solitaire::initializeMemberVariables(BOARDSHAPE shape) {
    // Self explanatory
    switch (shape) {
        case ENGLISH:
            m_numRows = ENGLISHSIZE;
            m_numColumns = ENGLISHSIZE;
            m_numMarbles = NUMENGLISHMARBLES;
            break;
        case DIAMOND:
            m_numRows = DIAMONDSIZE;
            m_numColumns = DIAMONDSIZE;
            m_numMarbles = NUMDIAMONDMARBLES;
            break;
        default:
            // If non-supported shape is provided create empty object
            m_numRows = 0;
            m_numColumns = 0;
            m_numMarbles = 0;
    }
}

void Solitaire::setupBoard(BOARDSHAPE shape) {
    size_t size = 0;

    switch (m_shape) {
        case ENGLISH:
            size = sizeof(empty_spaces_english)/sizeof(empty_spaces_english[0]);
            populateBoard(empty_spaces_english, size);
            break;
        case DIAMOND:
            size = sizeof(empty_spaces_diamond)/sizeof(empty_spaces_diamond[0]);
            populateBoard(empty_spaces_diamond, size);
            break;
    }
}

void Solitaire::init(BOARDSHAPE shape) {
    m_shape = shape;

    // Functions create empty object if non-supported shape is provided
    initializeMemberVariables(shape);
    initializeMemoryBoard();
    setupBoard(shape);
    // Else we don't have to do anything since a false
    // result would mean that an invalid shape was passed
    // so no memory needs to be allocated as `initializeMemberVariables`
    // already sets board to nullptr if the shape is invalid.
}

string Solitaire::board_to_string() {
    string board_string;

    for(int i=0; i<m_numRows; i++) {
        for(int j=0; j<m_numColumns; j++) {
            board_string += to_string(m_board[i][j]);
        }
    }

    return board_string;
}