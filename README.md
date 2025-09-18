# Chess Game in C++

A terminal-based chess engine implemented in C++.  
This project simulates a complete game of chess with move validation, piece-specific rules, and a text-based visualization of the board.  

Developed collaboratively as a team project. 

---

## Features
- **Full rules of chess**: legal moves for all pieces, captures, alternating turns.
- **Object-Oriented Design**: each piece (`Pawn`, `Rook`, `Bishop`, `Knight`, `Queen`, `King`) is encapsulated in its own class with specialized movement logic.
- **Game & Board Management**: centralized `Game` and `Board` classes track state, validate moves, and manage turn order.
- **Command Interface**: play via terminal commands (`M e2e4` for moves, `Q` to quit, `S` to save, `L` to load).
- **Exception Handling** for invalid moves and user input.
- **UML Design Diagram** included (`docs/chessUML.pdf`).
- **Makefile Support** for simple compilation.

---

## Demo

Below is an example of gameplay. The move shown is **E2 to E4**, known as the *King’s Pawn Opening* — the most common opening in chess.

![Chess Demo 1](https://raw.githubusercontent.com/ldicker6/chess-game/main/docs/demo1.png)
![Chess Demo 2](https://raw.githubusercontent.com/ldicker6/chess-game/main/docs/demo2.png)

---

## Build & Run

### Prerequisites
- A C++ compiler (e.g., `g++`, `clang++`)
- `make`

### Compile
```bash
make
```

### Run
./chess

--- 
## Commands

- `?` → show list of commands  
- `M <move>` → make a move (e.g., `M E2E4`)  
- `S <filename>` → save game  
- `L <filename>` → load game  
- `Q` → quit game  

---

## UML Diagram

System design overview:

![UML Diagram](chessUML.pdf)

---

## Contributions

This project was developed collaboratively as part of a team. 

**My specific contributions included:**
- Implementing piece logic for select chess pieces (e.g., `Bishop.cpp`, `Knight.cpp`), focusing on correct movement rules.  
- Collaborating on shared gameplay functionality (like move validation and board updates).  
- Participating in algorithm discussions for game flow and rule enforcement.  
- Debugging and testing edge cases in piece movement.  

---

## Future Improvements

- Add AI opponent (minimax or heuristic-based search)
- Implement move history tracking with undo/redo functionality










