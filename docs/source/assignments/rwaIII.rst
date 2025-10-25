.. default-domain:: cpp
.. _rwaIII:

====================================================
RWA III — Robot Kinematics and Control
====================================================

**Course:** ENPM702 — C++ for Robotics  
**Duration:** 1.5 weeks  
**Total Points:** 30  
**Language:** C++17  

----------------------------------------------------
Assignment Overview
----------------------------------------------------

This assignment integrates **modern C++17 programming constructs**—templates, lambdas, and smart pointers—with **fundamental robotics concepts**.  
You will build a simplified **2-DOF planar robot arm controller** that demonstrates how software models, plans, and manages a robot's motion.

You will:

- Represent robot states and end-effector positions using **Plain Old Data (POD)** structs.
- Implement **forward kinematics** to compute the end-effector pose from joint angles.
- Generate a **smooth linear trajectory** between two configurations.
- Apply a **velocity-limit filter** using a **lambda callable**.
- Manage memory safely using **smart pointers** under the **RAII** principle.

The assignment emphasizes clear structure, modularity, and adherence to the **C++ Core Guidelines**.

----------------------------------------------------
Concept Reference
----------------------------------------------------

Forward Kinematics
==================

Forward kinematics computes the **end-effector position** from a known set of **joint angles**.
It answers the question: *“Where is the robot's tool tip given the current joint configuration?”*

For a **2-DOF planar arm**, the link lengths are :math:`L_1` and :math:`L_2`, and the joint angles are :math:`\theta_1` and :math:`\theta_2`.  
The end-effector position :math:`(x, y)` is calculated as:

.. math::

   x = L_1\cos(\theta_1) + L_2\cos(\theta_1 + \theta_2), \quad
   y = L_1\sin(\theta_1) + L_2\sin(\theta_1 + \theta_2)

This formula is fundamental for determining if a robot can reach a certain target and validating motion commands.

Smooth Linear Trajectory
========================

A **trajectory** is a sequence of robot states that defines how a robot moves from one configuration to another over time.  
A **smooth linear trajectory** ensures continuous, predictable motion without sudden jumps.

In this assignment, you will:

- Linearly interpolate joint angles between the start and goal positions using a scalar :math:`\alpha \in [0,1]`.
- Compute joint velocities corresponding to the rate of change in joint angles.

This process simulates a motion planner that generates intermediate waypoints for smooth robot motion.

Velocity-Limit Filter
=====================

Real robots must respect **joint velocity constraints** to prevent mechanical stress or instability.  
The **velocity-limit filter** ensures each joint's angular velocity remains within safe limits (:math:`|d\theta| \le 1.0` rad/s).

You will implement this filter as a **lambda function**, which:

- Takes a ``JointState`` as input.
- Checks its joint velocities.
- Clamps them to the allowed maximum if necessary.
- Returns the filtered ``JointState``.

This demonstrates how to use **lambda expressions** for inline, real-time control operations.

----------------------------------------------------
File Structure
----------------------------------------------------

You must create the following files:

.. code-block:: text

   robot_types.hpp / robot_types.cpp
   robot_kinematics.hpp
   robot_control.hpp / robot_control.cpp
   main.cpp
   CMakeLists.txt

**Guidelines:**

- **Templates** → defined entirely in ``.hpp``.
- **Non-template functions** → declared in ``.hpp`` and implemented in ``.cpp``.

----------------------------------------------------
Task 1 — Robot State POD Structs (6 pts)
----------------------------------------------------

**Objective:**  
Define the core data structures representing the robot's joint states and end-effector pose.

**Instructions:**

1. Define a ``JointState`` struct containing:
   - ``theta1`` and ``theta2``: joint angles (in radians).
   - ``dtheta1`` and ``dtheta2``: joint velocities (in radians per second).
2. Use **default member initializers** for velocities:

   .. code-block:: cpp

      struct JointState {
          double theta1;     // radians
          double theta2;     // radians
          double dtheta1 = 0.0;  // Default velocity
          double dtheta2 = 0.0;  // Default velocity
      };

   This allows:

   .. code-block:: cpp

      JointState q{M_PI/4, -M_PI/6};  // velocities default to 0.0

3. Define an ``EndEffectorPose`` struct containing ``x`` and ``y`` (in meters).
4. Implement ``void print_joint_state(const JointState&)`` in ``robot_types.cpp`` to print joint values and velocities clearly.
5. Demonstrate **aggregate initialization** (no constructors).

----------------------------------------------------
Task 2 — Forward Kinematics Template (8 pts)
----------------------------------------------------

**Objective:**  
Compute the robot's end-effector position from its joint angles.

**Instructions:**

1. Implement ``forward_kinematics()`` as a **templated function** in ``robot_kinematics.hpp``.
   - Input: any type with members ``theta1`` and ``theta2``.
   - Output: an ``EndEffectorPose`` with (x, y) coordinates.
2. Use ``<cmath>`` functions (``std::cos``, ``std::sin``).
3. Return the computed pose.

**Implementation Example:**

.. code-block:: cpp

   #pragma once
   #include "robot_types.hpp"
   #include <cmath>

   template <typename State>
   EndEffectorPose forward_kinematics(const State& s,
                                      double L1 = 0.5,
                                      double L2 = 0.3) {
       EndEffectorPose pose;
       pose.x = L1 * std::cos(s.theta1) + L2 * std::cos(s.theta1 + s.theta2);
       pose.y = L1 * std::sin(s.theta1) + L2 * std::sin(s.theta1 + s.theta2);
       return pose;
   }

----------------------------------------------------------
Task 3 — Linear Trajectory and Velocity Filtering (8 pts)
----------------------------------------------------------

**Objective:**  
Generate intermediate robot states between a start and goal configuration, and apply a velocity-limit filter.

**Instructions:**

1. Implement ``interpolate_linear()`` (templated) in ``robot_control.hpp``:
   - Input: start and goal states, scalar ``alpha ∈ [0,1]``.
   - Output: interpolated ``State``.
   - Behavior:

     - Interpolates ``theta1`` and ``theta2`` linearly.
     - Computes ``dtheta1`` and ``dtheta2`` proportionally to the angle change.

2. Implement ``apply_filter()`` in ``robot_control.cpp``:

   - Input: ``std::vector<JointState>&`` and ``std::function<JointState(const JointState&)>``.
   - Apply the filter in-place to each element.

3. In ``main.cpp``, define a **lambda** that limits joint velocities (:math:`|d\theta| \le 1.0` rad/s) and pass it to ``apply_filter()``.


-----------------------------------------------------------
Task 4 — Trajectory Management with Smart Pointers (8 pts)
-----------------------------------------------------------

**Objective:**  
Integrate all components into a single simulation demonstrating motion planning, filtering, and memory safety.

**Instructions:**

1. Use ``std::make_unique`` to create a vector of ``JointState`` representing the trajectory.
2. Generate 21 states using ``interpolate_linear()`` (from α=0 to 1 in steps of 0.05).
3. Apply the velocity filter using ``apply_filter()``.
4. Use ``std::make_shared`` to create a vector of ``EndEffectorPose``.
5. For each filtered state, compute the end-effector pose using ``forward_kinematics()``.
6. Print:
   - Trajectory size.
   - Shared pointer reference count.
   - Start and end states (use ``print_joint_state()``).
7. Demonstrate that all resources are released automatically (RAII).

----------------------------------------------------
Code Quality and C++ Guidelines (6 pts)
----------------------------------------------------

Your code will be graded for adherence to **C++ Core Guidelines**:

- No raw pointers (``new`` or ``delete``).
- Correct ownership semantics using ``unique_ptr`` and ``shared_ptr``.
- Const-correctness and pass-by-reference for non-owning parameters.
- Uniform initialization (``{}``) used consistently.
- Clean compilation with ``-Wall -Wextra -Wpedantic``.
- Clear naming, concise comments, and documented units (radians, meters, rad/s).

----------------------------------------------------
Evaluation Rubric (30 pts)
----------------------------------------------------

.. list-table::
   :header-rows: 1
   :widths: 25 60 15

   * - **Section**
     - **Description**
     - **Points**
   * - Task 1
     - POD structs, default member initializers, and formatted printing
     - 6
   * - Task 2
     - Forward kinematics template implementation
     - 8
   * - Task 3
     - Linear interpolation and velocity filtering
     - 8
   * - Task 4
     - Smart pointers, memory safety, and RAII integration
     - 8
   * - Code Quality
     - Adherence to C++ Core Guidelines and best practices
     - 6
   * - **Total**
     - **Overall Assignment Score**
     - **30**

----------------------------------------------------
Learning Outcomes
----------------------------------------------------

Upon completing this assignment, you will:

- Implement **forward kinematics** using modern C++ templates.
- Generate **smooth robot trajectories** with interpolation and filtering.
- Apply **lambda functions** and ``std::function`` for modular control.
- Use **smart pointers** to ensure memory safety and proper ownership.
- Write maintainable, standard-compliant C++ code following the **C++ Core Guidelines**.

----------------------------------------------------
References and Further Reading
----------------------------------------------------

.. raw:: html

   <ul>
     <li><a href="https://www.nist.gov/el/intelligent-systems-division" target="_blank" rel="noopener noreferrer">
     NIST Robotics Kinematics Overview</a></li>
     <li><a href="https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines" target="_blank" rel="noopener noreferrer">
     C++ Core Guidelines</a></li>
     <li><a href="https://en.cppreference.com/w/cpp/language/raii" target="_blank" rel="noopener noreferrer">
     RAII Explained (cppreference)</a></li>
     <li><a href="https://en.cppreference.com/w/cpp/memory" target="_blank" rel="noopener noreferrer">
     Smart Pointers (cppreference)</a></li>
     <li><a href="https://en.cppreference.com/w/cpp/language/lambda" target="_blank" rel="noopener noreferrer">
     Lambda Expressions (cppreference)</a></li>
   </ul>

