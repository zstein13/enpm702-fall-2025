.. default-domain:: cpp
.. _final_project_micromouse_cpp:

=========================================================
Assignment 4
=========================================================

.. admonition:: Changelog
   :class: changelog

   - **v1.0 (11/07/2025)** — Initial release of Assignment 4 instructions.

.. admonition:: Resources
   :class: resources


   - ⚙️ `Starter Code (rwa4_starter) <https://example.com/rwa4_starter.zip>`_
   - 🔗 `MicroMouse Simulator (main) <https://github.com/mackorone/mms>`_
   - 🔗 `MicroMouse Simulator (API) <https://github.com/mackorone/mms#mouse-api>`_
   - 🔗 `MicroMouse Simulator (maze files) <https://github.com/mackorone/mms#maze-files>`_

**MicroMouse Robot Maze Navigation**

.. list-table::
   :widths: 20 30
   :stub-columns: 1
   :class: compact-table

   * - **Version**
     - v1.0
   * - **Due Date**
     - 11/25/2025
   * - **Points**
     - 50 pts
   * - **Work Mode**
     - Group assignment
   * - **Language**
     - C++17



---------------------------------------------------------
Guidelines
---------------------------------------------------------

This assignment is to be completed in **groups**, and all instructions must be followed carefully. Not adhering to these guidelines may result in a zero for the assignment.

.. important::
   
   - Each group member must contribute significantly to the project.
   - Keep your work private; do not share your files or code with other groups.
   - Any GitHub repository used for development must be private.
   - Submit your completed work as a zipped file via Canvas.
   - Feel free to discuss general concepts with other groups, but sharing specific implementation details is strictly forbidden.
   - The use of AI-generated code (e.g., ChatGPT, Copilot) for core logic is not permitted, though it may be used for documentation.


---------------------------------------------------------
Overview
---------------------------------------------------------

You will develop a C++ program that implements a **MicroMouse Robot Navigation System** for maze exploration. You are developing control software for a MicroMouse robot competing in `autonomous maze navigation <https://youtu.be/ZMQbHMgK2rw?si=FH-yd7i0Rrf44S3q>`_. The robot must efficiently navigate through an unknown warehouse-like 16x16 maze to reach one of the four center goal cells using sophisticated pathfinding algorithms and sensor systems. 

Your robot can be configured for different scanning approaches (minimal detection or comprehensive sensing), demonstrating how different configurations produce different behaviors. Your system must demonstrate well-designed object-oriented architecture with clear separation between navigation logic and shared resources.

**Key System Features:**

- **Aggregation** — Shared resources (maze, algorithm)
- **Encapsulation** — Proper data hiding and access control
- **Modular Design** — Separate systems working together cohesively
- **Configuration-Based Behavior** — Single robot class with multiple operational modes
- **Random Goal Selection** — Algorithm randomly selects one of four center goals for navigation

---------------------------------------------------------
Simulator
---------------------------------------------------------

Your program is required to interface with a graphical user interface simulator (`mms <https://github.com/mackorone/mms>`_). The simulator makes it easy to write and test maze-solving code without a physical robot.

Installation
~~~~~~~~~~~~~

.. admonition:: TODO
   :class: mytodo

    1. Download the `Linux precompiled version of the simulator <https://github.com/mackorone/mms/releases/download/v1.2.0/linux.zip>`_
    2. Unzip the file, which generates the `linux` folder
    3. ``cd <path to linux folder>``
    4. ``chmod +x mms-x86_64.AppImage``
    5. ``./mms-x86_64.AppImage --appimage-extract`` :math:`\rightarrow` creates the folder `squashfs-root`
    6. ``cd squashfs-root``
    7. ``chmod +x mms``
    8. ``./mms``
    9. The simulator should start (we will refer to this window as the `mms` window)

.. only:: html

   .. raw:: html

      <div style="display:flex; justify-content:center; align-items:center; gap:1rem;">
        <img src="../_static/rwa4/simulator_start.png"
             alt="Simulator"
             class="only-light"
             style="width:100%; border-radius:8px;">
        <img src="../_static/rwa4/simulator_start.png"
             alt="Simulator"
             class="only-dark"
             style="width:100%; border-radius:8px;">
      </div>

Maze Files
~~~~~~~~~~~~~~

The simulator only provides the graphical user interface and functionalities to interact with your code. You will also need maze files. In order to use a maze in the simulator, it must be:

- Nonempty
- Rectangular
- Fully enclosed
- Also note that official Micromouse mazes have additional requirements:

  - No inaccessible locations
  - Exactly three starting walls
  - Only one entrance to the center
  - Has a hollow center, i.e., the center peg has no walls attached to it
  - Has walls attached to every peg except the center peg
  - Is unsolvable by a wall-following robot

.. admonition:: TODO
   :class: mytodo
 
    - Download maze files:
    
        - Follow `instructions <https://github.com/mackorone/mms?tab=readme-ov-file#maze-files>`_ to retrieve the maze files.
        - or ``git clone https://github.com/micromouseonline/mazefiles.git``
    
    - Load maze files in the simulator.

        - Click the 🗂️ icon from the `mms` window
        - Navigate to the maze folder you cloned earlier
        - Select any file from `mazefiles` :math:`\rightarrow` `classic`

Build and Run
~~~~~~~~~~~~~~

.. admonition:: TODO
   :class: mytodo
 
    - Click on the + symbol to configure the simulator :math:`\rightarrow` `Edit Mouse Algorithm` window.
    
        .. only:: html

        .. raw:: html

            <div style="display:flex; justify-content:center; align-items:center; gap:1rem;">
                <img src="../_static/rwa4/config_mms.png"
                    alt="Configuration"
                    class="only-light"
                    style="width:100%; border-radius:8px;">
                <img src="../_static/rwa4/config_mms.png"
                    alt="Configuration"
                    class="only-dark"
                    style="width:100%; border-radius:8px;">
            </div>
        
        - **Name:** Give a name to this configuration
        - **Directory:** Provide absolute path to your executable (inside the `build` folder)
        - **Build Command:** I suugest you leave this empty. We will build the project in Visual Studio Code. If you prefer to build the whole project from the simulator, you will need to enter the whole ``g++`` command.
        - **Run Command:** Name of the executable. The simulator will try to run it using the path provided in the **Directory** field.
        - Click OK
        - Write and build the project in Visual Studio Code
        - Click `Run` (`mms` window)

Simulator API Reference
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The simulator provides an Application Programming Interface (API) that enables interaction between your code and the simulator.

The original API is available on GitHub:
`API.h <https://github.com/mackorone/mms-cpp/blob/master/API.h>`_.

For this assignment, the API has been modified to adhere to consistent class and attribute naming conventions, and it is encapsulated within the `micro_mouse` namespace.
The modified API interface is defined in `maze_api.hpp`, and its corresponding implementation resides in `maze_api.cpp`.

An overview of the provided API is summarized below:

.. code-block:: cpp
   :linenos:

    #pragma once
    #include <string>

    namespace micro_mouse {

    /**
    * @brief API for controlling and interacting with a maze environment
    *
    * This class provides methods to navigate through a maze, query maze
    * properties, manipulate walls, set colors and text, and handle reset events.
    */
    class MazeControlAPI {
    public:
    /**
    * @brief Get the width of the maze
    * @return The width of the maze in cells
    */
    static int get_maze_width();

    /**
    * @brief Get the height of the maze
    * @return The height of the maze in cells
    */
    static int get_maze_height();

    /**
    * @brief Check if there is a wall in front of the current position
    * @return true if there is a wall in front, false otherwise
    */
    static bool has_wall_front();

    /**
    * @brief Check if there is a wall to the right of the current position
    * @return true if there is a wall to the right, false otherwise
    */
    static bool has_wall_right();

    /**
    * @brief Check if there is a wall to the left of the current position
    * @return true if there is a wall to the left, false otherwise
    */
    static bool has_wall_left();

    /**
    * @brief Move forward in the maze
    * @param distance Number of cells to move forward (default: 1)
    */
    static void move_forward(int distance = 1);

    /**
    * @brief Turn right (clockwise) in the maze
    */
    static void turn_right();

    /**
    * @brief Turn left (counter-clockwise) in the maze
    */
    static void turn_left();

    /**
    * @brief Set a wall at the specified position and direction
    * @param x X coordinate of the cell
    * @param y Y coordinate of the cell
    * @param direction Direction of the wall ('n', 's', 'e', 'w' for north,
    * south, east, west)
    */
    static void set_wall(int x, int y, char direction);

    /**
    * @brief Clear a wall at the specified position and direction
    * @param x X coordinate of the cell
    * @param y Y coordinate of the cell
    * @param direction Direction of the wall ('n', 's', 'e', 'w' for north,
    * south, east, west)
    */
    static void clear_wall(int x, int y, char direction);

    /**
    * @brief Set the color of a cell in the maze
    * @param x X coordinate of the cell
    * @param y Y coordinate of the cell
    * @param color Color character identifier
    */
    static void set_color(int x, int y, char color);

    /**
    * @brief Clear the color of a cell in the maze
    * @param x X coordinate of the cell
    * @param y Y coordinate of the cell
    */
    static void clear_color(int x, int y);

    /**
    * @brief Clear all colors from the entire maze
    */
    static void clear_all_color();

    /**
    * @brief Set text at the specified cell in the maze
    * @param x X coordinate of the cell
    * @param y Y coordinate of the cell
    * @param text Text string to display at the cell
    */
    static void set_text(int x, int y, const std::string &text);

    /**
    * @brief Clear text from the specified cell in the maze
    * @param x X coordinate of the cell
    * @param y Y coordinate of the cell
    */
    static void clear_text(int x, int y);

    /**
    * @brief Clear all text from the entire maze
    */
    static void clear_all_text();

    /**
    * @brief Check if the maze was reset
    * @return true if the maze was reset, false otherwise
    */
    static bool was_reset();

    /**
    * @brief Acknowledge that the reset has been handled
    */
    static void ack_reset();

    /**
    * @brief Print a message in the simulator
    * To print anything in the simulator, use std::cerr
    * @param text
    */
    static void log(std::string_view text);

    }; // class MazeControlAPI

    } // namespace maze

.. warning::
   
   DO NOT MODIFY the provided API implementation. Your code should only call these static methods through the maze class wrapper methods. The API handles communication with the simulator through standard input/output streams.

.. note::

    Algorithms communicate with the simulator via stdin/stdout. To issue a command, simply print to stdout. To read a response, simply read from stdin. All valid commands are listed below. Invalid commands are simply ignored.

    - `std::cout` sends commands to the simulator
    - `std::cin` reads commands from the simulator
    - `std::cerr` prints in the simulator's main window

.. admonition:: Try demo code
   :class: mytodo
 
    The starter package provides a simple left-wall follower. This is just for demonstration purpose as the robot is not expected to reach the center of the maze (due to the nature of the mazes).

    .. code-block:: cpp
       :linenos:

        #include <iostream>
        #include <string>

        #include "maze_api.hpp"

        void log(const std::string& text) {
          std::cerr << text << std::endl;
        }

        using MMS = micro_mouse::MazeControlAPI;

        int main() {
          log("Running...");
          MMS::set_color(0, 0, 'G');
          MMS::set_text(0, 0, "S");
          
          MMS::set_text(7, 7, "(7,7)");
          MMS::set_text(7, 8, "(7,8)");
          MMS::set_text(8, 7, "(8,7)");
          MMS::set_text(8, 8, "(8,8)");
          MMS::set_color(7, 7, 'y');
          MMS::set_color(7, 8, 'y');
          MMS::set_color(8, 7, 'y');
          MMS::set_color(8, 8, 'y');
          while (true) {
            if (!MMS::has_wall_left()) {
              MMS::turn_left();
            }
            while (MMS::has_wall_front()) {
              MMS::turn_right();
            }
            MMS::move_forward();
          }
        }
---------------------------------------------------------
DFS Algorithm: Tree-Based Path Finding
---------------------------------------------------------

Maze pathfinding can be conceptualized as a tree traversal problem, where the starting position serves as the root node and the goal position represents a target leaf. Each cell in the maze corresponds to a node in the tree structure, with accessible adjacent cells forming the children of the current node.

This assignment focuses on implementing a depth-first search (DFS) algorithm for maze navigation. While DFS provides a systematic approach to exploring all possible paths, it does not guarantee optimal solutions and typically does not produce the shortest route to the destination.

Algorithm Behavior
~~~~~~~~~~~~~~~~~~~

The DFS algorithm operates by starting at the root node and exploring each branch to its maximum depth before backtracking to explore alternative paths. This exhaustive exploration strategy ensures that all reachable nodes are eventually visited, though not necessarily in the most efficient order.

The key characteristic of DFS is its commitment to exploring as deeply as possible along each path before considering alternatives. When the algorithm encounters a dead end or reaches a previously visited node, it backtracks to the most recent node with unexplored neighbors and continues the search from there.

Goal Selection
~~~~~~~~~~~~~~~

The maze contains four goal cells located at the center: (7,7), (7,8), (8,7), and (8,8). Before beginning navigation, the algorithm must randomly select one of these four cells as the target destination. This random selection ensures that different runs may have different objectives, adding variability to the navigation demonstration.

Search Order Protocol
~~~~~~~~~~~~~~~~~~~~~~~

To maintain consistency in maze traversal, the following directional priority sequence must be followed:

1. **North** (↑) — First priority direction
2. **East** (→) — Second priority direction
3. **South** (↓) — Third priority direction
4. **West** (←) — Fourth priority direction

This ordering ensures deterministic behavior across different implementations and makes debugging more predictable. The algorithm will always attempt to move North first when multiple directions are available.

Backtracking Mechanism
~~~~~~~~~~~~~~~~~~~~~~~~

When the algorithm reaches a position where no unvisited adjacent cells are available, the backtracking process begins. The algorithm retraces its steps along the current path, returning to previously visited nodes to identify unexplored branches. This systematic retreat continues until either:

1. An unvisited node is discovered along the backtracked path
2. All possible paths from the current branch have been exhausted

The process ensures complete coverage of all accessible areas within the maze structure while maintaining the integrity of the search path. Backtracking is what allows DFS to explore all possible solutions systematically.

Implementation Details
~~~~~~~~~~~~~~~~~~~~~~~

DFS can be implemented using stacks with the last-in-first-out (LIFO) approach. The stack maintains the current exploration path and facilitates backtracking when dead ends are encountered. During traversal, nodes are pushed onto the stack when exploring new paths and popped during backtracking when no further progress is possible.

A list of visited nodes is essential to prevent infinite cycles and ensure each node is processed only once. Without this mechanism, the algorithm could become trapped in loops, especially in maze configurations with multiple paths between the same locations.

In C++, `std::stack <https://en.cppreference.com/w/cpp/container/stack>`_ provides the LIFO data structure for maintaining the exploration path, while `std::set <https://en.cppreference.com/w/cpp/container/set>`_ serves as the visited nodes collection. The algorithm begins at the start node and systematically explores all possible paths until it either reaches the goal node or exhausts all reachable nodes.

Performance Considerations
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The choice of ``std::set`` over ``std::vector`` for tracking visited nodes is crucial for performance. The algorithm frequently performs two operations on the visited collection: checking if a node has been visited and marking a node as visited. The following table demonstrates the significant performance difference between these data structures.


.. list-table:: Performance comparison of container types for visited node tracking
   :widths: 30 35 35
   :stub-columns: 1
   :class: compact-table

   * - **Operation**
     - **std::vector**
     - **std::set**
   * - Lookup ("is visited?")
     - O(n) — linear search
     - O(log n) — tree search
   * - Insert ("mark visited")
     - O(1) — push_back
     - O(log n) — tree insertion
   * - **Overall Impact**
     - Gets slower as maze grows
     - Stays efficient

The critical operation "is this node already visited?" occurs frequently during maze traversal. With ``std::vector``, this requires searching through all previously visited nodes, creating a performance bottleneck that worsens as the maze size increases. In contrast, ``std::set`` provides logarithmic lookup time and automatically prevents duplicate entries, making it the optimal choice for this application. For large mazes containing thousands of nodes, this performance difference becomes substantial and can significantly impact the algorithm's execution time.

Pseudocode
~~~~~~~~~~~~~~

The iterative implementation of DFS uses explicit stack management to simulate the recursive call stack. The following pseudocode presents the complete approach:

.. prf:algorithm:: Depth-First Search for Maze Solving
   :label: dfs-maze-search

   **Inputs:** 

   - :math:`s` (stack of nodes, initially empty)
   - :math:`v` (list of visited nodes, initially empty)
   - :math:`m_{maze}` (2D array representing the maze)
   - :math:`m_{goal}` (goal node coordinates)
   - :math:`m_{start}` (start node coordinates)
   
   **Output:** true if a path to goal is found, otherwise false

   1. :math:`s.\text{push}(m_{start})`
   
   2. **while** not :math:`s.\text{empty}()` **do**
   
      a. :math:`n \gets s.\text{top}()` (examine current node without removing it)
      
      b. **if** :math:`n = m_{goal}` **then** return **true** (goal found)
      
      c. **if** :math:`n \in v` **then** (node already explored)
      
         i. :math:`s.\text{pop}()` (backtrack: remove dead end)
         
         ii. **continue**
      
      d. :math:`v.\text{insert}(n)` (mark current node as visited)
      
      e. :math:`moved \gets \text{false}`
      
      f. **if** :math:`m_{maze}[n.x][n.y+1]` is valid and :math:`(n.x, n.y+1) \notin v` **then** (check North)
      
         i. :math:`neighbor.x \gets n.x, neighbor.y \gets n.y + 1`
         
         ii. :math:`s.\text{push}(neighbor), moved \gets \text{true}`
      
      g. **else if** :math:`m_{maze}[n.x+1][n.y]` is valid and :math:`(n.x+1, n.y) \notin v` **then** (check East)
      
         i. :math:`neighbor.x \gets n.x + 1, neighbor.y \gets n.y`
         
         ii. :math:`s.\text{push}(neighbor), moved \gets \text{true}`
      
      h. **else if** :math:`m_{maze}[n.x][n.y-1]` is valid and :math:`(n.x, n.y-1) \notin v` **then** (check South)
      
         i. :math:`neighbor.x \gets n.x, neighbor.y \gets n.y - 1`
         
         ii. :math:`s.\text{push}(neighbor), moved \gets \text{true}`
      
      i. **else if** :math:`m_{maze}[n.x-1][n.y]` is valid and :math:`(n.x-1, n.y) \notin v` **then** (check West)
      
         i. :math:`neighbor.x \gets n.x - 1, neighbor.y \gets n.y`
         
         ii. :math:`s.\text{push}(neighbor), moved \gets \text{true}`
      
      j. **if** not :math:`moved` **then** :math:`s.\text{pop}()` (backtrack)
   
   3. **return** false (all reachable nodes explored, goal not found)

.. note::
   
   At the end of this algorithm, the stack :math:`s` contains the path from start to goal. You need to invert this stack to get that path.


.. only:: html

        .. raw:: html

            <div style="display:flex; justify-content:left; align-items:left; gap:1rem;">
                <img src="../_static/rwa4/i1.png"
                    alt="Demo"
                    class="only-light"
                    style="width:30%; border-radius:8px;">
            </div>

****

.. only:: html

        .. raw:: html

            <div style="display:flex; justify-content:left; align-items:left; gap:1rem;">
                <img src="../_static/rwa4/i2.png"
                    alt="Demo"
                    class="only-light"
                    style="width:30%; border-radius:8px;">
            </div>

****

.. only:: html

        .. raw:: html

            <div style="display:flex; justify-content:left; align-items:left; gap:1rem;">
                <img src="../_static/rwa4/i3.png"
                    alt="Demo"
                    class="only-light"
                    style="width:40%; border-radius:8px;">
            </div>

****

.. only:: html

        .. raw:: html

            <div style="display:flex; justify-content:left; align-items:left; gap:1rem;">
                <img src="../_static/rwa4/i4.png"
                    alt="Demo"
                    class="only-light"
                    style="width:50%; border-radius:8px;">
            </div>

****

.. only:: html

        .. raw:: html

            <div style="display:flex; justify-content:left; align-items:left; gap:1rem;">
                <img src="../_static/rwa4/i5.png"
                    alt="Demo"
                    class="only-light"
                    style="width:50%; border-radius:8px;">
            </div>

****

.. only:: html

        .. raw:: html

            <div style="display:flex; justify-content:left; align-items:left; gap:1rem;">
                <img src="../_static/rwa4/i6.png"
                    alt="Demo"
                    class="only-light"
                    style="width:70%; border-radius:8px;">
            </div>


Path Following
~~~~~~~~~~~~~~~~~~

When any of these sensor functions return ``true``, indicating the presence of a wall, you must perform two critical actions:

1. **Update your internal maze representation**: Modify your maze data structure to reflect the newly discovered wall information.
2. **Synchronize the simulator**: Call ``set_wall(int x, int y, char direction)`` to ensure the simulator's visual representation matches your internal maze state.

This dual-update approach maintains consistency between your algorithm's understanding of the maze and the simulator's display, enabling accurate pathfinding and visualization throughout the robot's navigation process.

When the robot encounters unexpected walls during navigation, it must recompute the path from its current position using the DFS algorithm with the updated maze information.


MicroMouseRobot Class (25 points)
----------------------------------

Core Robot Implementation (20 points)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Create the main ``MicroMouseRobot`` class within the ``micro_mouse`` namespace:

**Required Public Interface:**

- ``MicroMouseRobot(const std::string& robot_id, std::shared_ptr<Maze> maze, std::shared_ptr<Algorithm> algorithm)`` — Constructor with robot identification and aggregated shared resources
- ``void navigate_maze()`` — Main navigation control loop using aggregated components
- ``bool scan_environment()`` — Environmental scanning based on current mode

**Configuration Methods:**

- ``void set_scanning_intensity(ScanningLevel level)`` — Adjust sensor usage

Robot Behavior Modes (5 points)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Implement enumerated types and corresponding behaviors for different operational modes:

**Scanning Levels (enum class ScanningLevel):**

1. **MINIMAL**: Forward-only wall detection using ``has_wall_front()``
2. **STANDARD**: Three-direction scanning (``has_wall_front()``, ``has_wall_left()``, ``has_wall_right()``)

The ``scan_environment()`` method implements configuration-driven sensor usage that demonstrates behavioral differences between robot modes. MINIMAL mode performs forward-only scanning for reactive navigation, while STANDARD mode scans all three directions (front, left, right) for proactive environmental mapping.

Both modes update the internal maze representation and simulator visualization through API wrapper methods. The algorithm uses visual markers to distinguish scanning patterns and returns whether new wall information was discovered, enabling the navigation system to trigger path recomputation when necessary.

The pseudocode for ``scan_environment()`` is provided below:

.. code-block:: text
   :linenos:

   Function scan_environment() -> bool:
       Data:
           current_scanning_level — enum ScanningLevel (MINIMAL or STANDARD)
           current_position — robot's current x,y coordinates
           current_direction — robot's facing direction (N,S,E,W)
           m_maze — shared maze object with API wrapper methods
       Output:
           true if any walls detected, otherwise false
       
       walls_detected = false  // track if any walls found during scan
       
       if current_scanning_level is MINIMAL:  // minimal scanning mode
           // Only scan forward direction
           if m_maze.has_wall_front():
               m_maze.update_wall(current_position.x, current_position.y, current_direction, true)
               m_maze.set_wall(current_position.x, current_position.y, direction_to_char(current_direction))
               walls_detected = true
           m_maze.set_color(current_position.x, current_position.y, 'R')  // mark as minimal scan
       else:  // standard scanning mode
           // Scan all three accessible directions: front, left, right
           if m_maze.has_wall_front():
               m_maze.update_wall(current_position.x, current_position.y, current_direction, true)
               m_maze.set_wall(current_position.x, current_position.y, direction_to_char(current_direction))
               walls_detected = true
           
           left_direction = get_left_direction(current_direction)
           if m_maze.has_wall_left():
               m_maze.update_wall(current_position.x, current_position.y, left_direction, true)
               m_maze.set_wall(current_position.x, current_position.y, direction_to_char(left_direction))
               walls_detected = true
           
           right_direction = get_right_direction(current_direction)
           if m_maze.has_wall_right():
               m_maze.update_wall(current_position.x, current_position.y, right_direction, true)
               m_maze.set_wall(current_position.x, current_position.y, direction_to_char(right_direction))
               walls_detected = true
           
           m_maze.set_color(current_position.x, current_position.y, 'B')  // mark as standard scan
       
       return walls_detected  // return whether any walls were discovered

Aggregation - Shared Components (25 points)
----------------------------------------------

Implement components that are shared and exist independently using ``std::shared_ptr``:

Maze Class (15 points)
~~~~~~~~~~~~~~~~~~~~~~~

The ``micro_mouse::Maze`` class serves as the central interface to the MazeControlAPI:

- 16×16 grid representation with individual cell objects
- Wall information storage and updates for both boundary and internal walls
- Goal identification with center 4 cells: (7,7), (7,8), (8,7), (8,8)
- Random goal selection from the four center cells
- Cell state management including visited status, colors, and text annotations
- Position tracking with x, y coordinates and current direction (N, S, E, W)
- Movement history recording for backtracking capabilities
- Wall detection integration using API sensor methods
- **All API interaction through maze class methods**

Algorithm Class (10 points)
----------------------------

The ``micro_mouse::Algorithm`` class requirements:

- DFS pathfinding implementation with random goal selection
- Path computation and validation with support for dynamic re-planning
- Wall detection integration based on robot scanning configuration
- Integration with maze class for seamless robot navigation coordination

Robot Configuration and Behavior Demonstration (10 points)
------------------------------------------------------------

Dynamic Behavior Configuration (5 points)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Implement the ability to reconfigure robot behavior during runtime with clear behavioral changes:

**Configuration Impact Examples:**

.. code-block:: cpp
   :linenos:

   // Minimal Scanning Configuration - Fast and basic
   robot->set_scanning_intensity(ScanningLevel::MINIMAL);
   // Results: Forward-only scanning, faster navigation, minimal wall detection

   // Standard Scanning Configuration - Comprehensive and thorough
   robot->set_scanning_intensity(ScanningLevel::STANDARD);
   // Results: Three-direction scanning, thorough wall detection, complete mapping

Behavioral Demonstrations (5 points)
-------------------------------------

Show measurable differences between configurations:

**Required Differences:**

- **Sensor Usage**: Varying wall detection patterns and API call frequencies
- **Visual Marking**: Different cell coloring and text annotation strategies
- **Exploration Approach**: Different scanning patterns and wall discovery rates
- **Navigation Efficiency**: Measurable differences in scanning frequency, exploration completeness, and path optimization

DFS Algorithm Implementation (20 points)
------------------------------------------

Core DFS Functionality (15 points)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Implement the complete DFS algorithm with the following requirements:

- Correct DFS implementation following specified search order protocol (North, East, South, West)
- Proper backtracking mechanism using stack data structure
- Effective path computation and following with dynamic re-planning capabilities
- Integration with wall discovery and maze representation updates

Goal Selection and Navigation (5 points)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Implement random goal selection and navigation features:

- Random goal selection from the four center cells at the start of each run
- Proper integration with maze and robot systems for seamless navigation
- Dynamic path recomputation when encountering unexpected walls during navigation

---------------------------------------------------------
Maze Reset Detection
---------------------------------------------------------

The simulator provides a reset button in the GUI that allows users to restart the maze. Your program must detect when this reset occurs and respond appropriately. The API provides two methods for reset detection:

- ``was_reset()`` — Returns ``true`` if the simulator was reset since the last check
- ``ack_reset()`` — Acknowledges the reset and clears the reset flag

Your main program must continuously monitor for resets and restart the navigation process when detected. This allows for multiple demonstration runs without restarting the entire program.

---------------------------------------------------------
Main Program Flow
---------------------------------------------------------

Your main program should demonstrate different robot configurations solving the same maze, with automatic reset detection:

.. code-block:: cpp
   :linenos:

   int main() {
       // Create shared resources (aggregation)
       auto maze = std::make_shared<micro_mouse::Maze>();
       auto algorithm = std::make_shared<micro_mouse::Algorithm>();
       
       // Create robot with shared resources (demonstrates aggregation)
       auto robot = std::make_unique<micro_mouse::MicroMouseRobot>("MM-001", maze, algorithm);
       
       bool first_run = true;
       
       while (true) {
           // Check for simulator reset
           if (maze->was_reset()) {
               maze->ack_reset();
               maze->log("=== Simulator Reset Detected ===");
               
               // Clear visualization and prepare for new run
               maze->clear_all_color();
               maze->clear_all_text();
               first_run = true;
           }
           
           if (first_run) {
               // === FIRST RUN: MINIMAL SCANNING MODE ===
               maze->log("=== Starting Minimal Scanning Mode ===");
               robot->set_scanning_intensity(ScanningLevel::MINIMAL);
               
               robot->navigate_maze();  // Robot uses its aggregated components
               
               // Clear visualization for next run (preserve discovered walls)
               maze->clear_all_color();
               maze->clear_all_text();
               first_run = false;
           } else {
               // === SECOND RUN: STANDARD SCANNING MODE ===
               maze->log("=== Starting Standard Scanning Mode ===");
               robot->set_scanning_intensity(ScanningLevel::STANDARD);
               
               robot->navigate_maze();  // Robot uses its aggregated components
               
               maze->log("=== Both runs completed. Click reset for new demonstration ===");
               
               // Wait for reset to start over
               while (!maze->was_reset()) {
                   // Small delay to prevent busy waiting
                   std::this_thread::sleep_for(std::chrono::milliseconds(100));
               }
           }
       }
       
       return 0;
   }

---------------------------------------------------------
Documentation Requirements
---------------------------------------------------------

Design Document (3-5 pages)
============================

Your design document must include:

- Explanation of robot configurations and their behavioral differences
- Clear distinction between shared resources and robot-specific functionality
- How the same maze and algorithm instances are reused across different robot configurations
- Performance comparison between different scanning modes with quantitative analysis
- Justification for all design decisions and OOP principle applications
- Discussion of how configuration-based design achieves behavioral diversity
- Analysis of system integration and component interactions
- Explanation of random goal selection mechanism and its impact on navigation
- Description of reset detection implementation and program flow control

UML Class Diagram
=================

- Show all classes with complete method signatures and key attributes
- Indicate aggregation relationships (hollow diamond ◇) between Robot and shared resources
- Show all enumerated types and their relationships to the robot class
- Include multiplicity indicators and relationship labels
- Demonstrate clear namespace organization (``micro_mouse`` namespace only)
- Show dependency relationships between systems
- Illustrate API wrapper pattern in maze class

Code Documentation
==================

All code must be documented using Doxygen format with comprehensive coverage:

- Comprehensive class descriptions with purpose and responsibilities
- Parameter descriptions for all public methods with type information
- Return value explanations with possible value ranges
- Usage examples for complex methods and configuration options
- Pre-condition and post-condition documentation for critical methods
- Configuration option explanations with behavioral impact descriptions
- Document all public members including constructors, methods, and enumerations

---------------------------------------------------------
Deliverables
---------------------------------------------------------

- **Source Code**: Complete implementation following required structure with all specified classes
- **Documentation**: Design document (3-5 pages), UML diagram, comprehensive Doxygen comments
- **README**: Build instructions, dependencies, group member contributions, usage instructions
- **Demo Video**: 3-4 minutes showing robot in both configurations solving the maze sequentially with simulator running

---------------------------------------------------------
Grading Rubric (100 pts)
---------------------------------------------------------

.. warning::
   
   Ensure you follow the C++ `Core Guidelines <https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines>`_ and demonstrate all OOP principles effectively. Use ``snake_case`` throughout your implementation and keep everything in the ``micro_mouse`` namespace.

Code Implementation (80 points)
================================

MicroMouseRobot Class (25 pts)
------------------------------

.. list-table::
   :header-rows: 1
   :widths: 20 80

   * - **Points**
     - **Criteria**
   * - 22-25 pts
     - Well-designed robot class with clear public interface; proper scanning configuration methods; correct ``snake_case`` naming; proper encapsulation; excellent integration with shared components
   * - 15-21 pts
     - Basic robot functionality with some configuration options; minor design issues; some behavioral differences visible; adequate integration
   * - 5-14 pts
     - Poor robot design; minimal configuration capabilities; incorrect method implementations; poor integration
   * - 0-4 pts
     - Missing robot class or completely non-functional implementation

Aggregation - Shared Components (25 pts)
-----------------------------------------

.. list-table::
   :header-rows: 1
   :widths: 20 80

   * - **Points**
     - **Criteria**
   * - 22-25 pts
     - Proper maze and algorithm classes using ``shared_ptr``; correct sharing between robot runs; proper lifetime management; clear interfaces; comprehensive API wrapper implementation in maze class; all functionality working correctly
   * - 15-21 pts
     - Basic shared components with minor issues; some aggregation concepts demonstrated; most API wrapper functionality present; adequate shared resource management
   * - 5-14 pts
     - Poor aggregation implementation; memory management issues; unclear sharing; missing significant API wrapper functionality
   * - 0-4 pts
     - Incorrect sharing; memory leaks; missing aggregation design; no API wrapper implementation

Robot Configuration and Behavior (10 pts)
------------------------------------------

.. list-table::
   :header-rows: 1
   :widths: 20 80

   * - **Points**
     - **Criteria**
   * - 8-10 pts
     - Clear and measurable behavioral differences between scanning configurations; proper mode switching; effective demonstration of configuration impact; quantifiable performance differences
   * - 5-7 pts
     - Some behavioral differences visible; basic configuration options working; minor issues with mode switching
   * - 1-4 pts
     - Minimal behavioral differences; poor configuration implementation; limited mode functionality
   * - 0 pts
     - No meaningful behavioral differences; configuration system non-functional

DFS Algorithm Implementation (20 pts)
-------------------------------------

.. list-table::
   :header-rows: 1
   :widths: 20 80

   * - **Points**
     - **Criteria**
   * - 17-20 pts
     - Correct DFS implementation following specified search order protocol; proper backtracking mechanism; effective path computation and following; dynamic wall discovery and re-planning; random goal selection working correctly; proper integration with maze and robot systems
   * - 10-16 pts
     - Basic DFS implementation with minor issues; most pathfinding functionality working; some integration problems; goal selection implemented with minor issues
   * - 3-9 pts
     - Poor DFS implementation; significant algorithmic errors; limited pathfinding capability; random goal selection missing or incorrect
   * - 0-2 pts
     - Missing or completely incorrect DFS implementation; non-functional pathfinding; no goal selection

Documentation and Design (20 points)
====================================

Design Document (8 pts)
-----------------------

.. list-table::
   :header-rows: 1
   :widths: 20 80

   * - **Points**
     - **Criteria**
   * - 7-8 pts
     - Comprehensive design explanation; clear justification of OOP principles; thorough analysis of behavioral differences; discussion of random goal selection; well-written and professional
   * - 4-6 pts
     - Basic design documentation covering most requirements; minor gaps in analysis; adequate writing quality
   * - 1-3 pts
     - Incomplete documentation; superficial analysis; missing key elements; poor writing quality
   * - 0 pts
     - Missing or completely inadequate design documentation

UML Class Diagram (7 pts)
--------------------------

.. list-table::
   :header-rows: 1
   :widths: 20 80

   * - **Points**
     - **Criteria**
   * - 6-7 pts
     - Complete and accurate UML diagram; proper notation for aggregation; all classes and relationships shown; API wrapper pattern illustrated; professional presentation; correct use of UML symbols
   * - 3-5 pts
     - Basic UML with minor errors or missing elements; most relationships correct; adequate presentation
   * - 1-2 pts
     - Incomplete UML diagram; significant errors in notation; poor presentation
   * - 0 pts
     - Missing or completely incorrect UML diagram

Code Documentation (5 pts)
---------------------------

.. list-table:: 
   :widths: 20 80
   :stub-columns: 1
   :class: compact-table

   * - **Points**
     - **Criteria**
   * - 4-5 pts
     - Complete Doxygen documentation; clear and helpful comments; well-documented interfaces; usage examples provided
   * - 2-3 pts
     - Basic documentation with some missing elements; adequate comment coverage
   * - 1 pt
     - Minimal documentation; poor comment quality
   * - 0 pts
     - Missing or completely inadequate code documentation

Code Quality (Deductions up to -15 pts)
========================================

- Memory leaks or resource management issues (−5 pts)
- Compilation warnings (−3 pts)
- Poor code organization and structure (−5 pts)
- Not using ``snake_case`` naming convention (−3 pts)
- Missing error handling for critical operations (−3 pts)
- Not using ``micro_mouse`` namespace consistently (−3 pts)
- Poor separation of concerns between systems (−4 pts)
- Direct API calls instead of using maze wrapper methods (−5 pts)

---------------------------------------------------------
Submission Requirements
---------------------------------------------------------

- Create zip file named: ``final_project_group#.zip`` (replace # with your group number)
- Include all source code in proper directory structure as specified
- Include all documentation files (design doc, UML, README) in ``doc/`` folder
- Include demo video file (MP4 format preferred, max 100MB) showing simulator running
- Submit via Canvas before the specified deadline
- Late penalty: 10% per day up to 3 days, then 0 points

---------------------------------------------------------
Tips for Success
---------------------------------------------------------

- Start with the maze class API wrapper methods and test them individually with the simulator
- Implement random goal selection early and test with different seeds
- Test API calls through the maze wrapper methods frequently during development
- Implement one system at a time and test integration thoroughly before moving to the next
- Ensure all API interactions go through the maze class, not direct API calls
- Focus on making scanning configuration changes produce measurable and visible behavioral differences
- Use the logging function through maze wrapper extensively for debugging
- Document your design decisions as you implement to make the design document easier to write
- Test both robot configurations thoroughly and measure performance differences
- Record the video while actually testing to capture authentic behavior
- Start documentation early — don't leave it until the end
- Use version control (git) to track changes and coordinate group work
- Test the reset detection functionality thoroughly to ensure proper program flow control

---------------------------------------------------------
Common Pitfalls to Avoid
---------------------------------------------------------

- Making direct API calls instead of using maze class wrapper methods
- Creating new maze/algorithm instances for each robot run — these should be shared with ``shared_ptr`` and reused
- Forgetting to use the ``micro_mouse`` namespace for all classes and the API
- Not using ``snake_case`` naming convention consistently throughout the codebase
- Modifying the provided API implementation instead of just calling the static methods through wrappers
- Not implementing random goal selection or having it select the same goal every time
- Not demonstrating clear and measurable behavioral differences between robot configurations
- Making configuration changes that don't affect robot behavior in observable ways
- Poor integration between the robot class and the shared maze/algorithm components
- Not properly managing memory with smart pointers leading to leaks or double deletions
- Implementing the maze and algorithm as regular classes instead of demonstrating proper aggregation
- Not implementing the complete DFS algorithm with proper backtracking and path following
- Forgetting to update both internal maze representation and simulator when discovering walls
- Not following the specified search order protocol (North, East, South, West) in DFS implementation
- Not recording a video of the actual simulator running with both configurations
- Having a static or predetermined goal instead of random selection from the four center cells
- Not implementing proper reset detection, causing the program to become unresponsive to simulator resets
- Forgetting to call ``ack_reset()`` after detecting a reset, causing continuous reset detection

=================
Project Todo List
=================

.. todolist::