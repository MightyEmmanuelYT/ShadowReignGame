# README

#Game Name: Shadow Reign

## **How to Run the Game**
1. **Install Required Tools**:
   - Ensure you have a C++ compiler installed on your system. Common options include:
     - GCC (GNU Compiler Collection)
     - Visual Studio (Windows)
     - Clang
   - For Windows, the game uses the `windows.h` library for setting console colors, so run it on a Windows environment.

2. **Compile the Game**:
   - Open a terminal or command prompt.
   - Navigate to the directory containing the game source code.
   - Use the following command to compile:
     ```bash
     g++ -o game main.cpp
     ```
     Replace `main.cpp` with the filename of the source code.

3. **Run the Game**:
   - Execute the compiled program using:
     ```bash
     ./game
     ```
     On Windows, run:
     ```cmd
     game.exe
     ```

4. **Enjoy the Game**:
   - Follow the on-screen instructions to play.

---

## **Game Mechanics**

### **Core Gameplay**
The game features a series of missions, each with:
- **Narrative Setup**: Each mission begins with a description of the current scenario to immerse the player.
- **Choice-Based Events**: Players are presented with scenarios and must select one of three options:
  - Correct choices progress the player toward a better outcome.
  - Incorrect choices have consequences, such as tougher decisions or losing a recruit.
- **Dynamic Scenarios**: Choices affect the flow of missions, including recruitment success and Eclipse’s decision to join the team.
- **Outcome Assessment**: At the end of each mission, the results are evaluated as:
  - **Perfect Win**: All correct choices made.
  - **Good Win**: More than half correct.
  - **Bad Loss**: Fewer than half correct.

### **Progression System**
- **Recruitment**: Mission 3 lets players choose from three recruits, each with unique abilities that affect the final mission.
- **Dynamic Storyline**: The final mission’s structure depends on recruited characters and Eclipse’s presence.
- **Color Feedback**:
  - Correct choices flash the screen green.
  - Incorrect choices flash red.

### **Final Mission and Endings**
- The final mission evaluates the player’s choices across the entire game.
- The ending narration reflects the player’s performance (Perfect, Good, or Bad) and reveals the outcome of Silas’s journey.

---

## **Implementation Details**

### **Use of Arrays**
- Arrays are used to structure events and choices for each mission. For example:
  ```cpp
  vector<Event> events = {
      {"Scenario 1 description", {
          {"Choice 1 description", true},
          {"Choice 2 description", false},
          {"Choice 3 description", false}
      }},
      {"Scenario 2 description", {
          {"Choice 1 description", false},
          {"Choice 2 description", true},
          {"Choice 3 description", false}
      }}
  };
  ```
  Each `Event` consists of a scenario and a list of `Choice` objects, encapsulating both the description and whether the choice is correct.

### **Game Logic**
- **Event Handling**:
  - The `handleEvent` function iterates through the `events` array, displays choices, and handles player input.
- **Dynamic Adjustments**:
  - In Mission 4, the options become more offensive or defensive based on player performance.
  - In the final mission, the presence of Eclipse or recruits dynamically alters the scenarios.

### **User Feedback**
- **Console Colors**:
  - The `windows.h` library is used to change the console text and background colors for visual feedback.
  - Correct choices flash green; incorrect choices flash red.
- **Narration**:
  - After every event, players receive a one-line narration detailing the consequence of their choice, enhancing immersion.

---

## **Acknowledgments**
- Thank you for playing! This game was designed as a blend of storytelling and choice-based gameplay, emphasizing player agency and dynamic outcomes.

