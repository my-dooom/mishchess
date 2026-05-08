
//------------------------------------------------------------------------------------
// DATA STRUCTURES
//------------------------------------------------------------------------------------
typedef enum {
    EMPTY,
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING,
} piece_type;

typedef enum {
    White,
    Black,
} color;

typedef struct {
    piece_type type;
    color color;
} piece;

piece board[8][8];

void initialize_board();
