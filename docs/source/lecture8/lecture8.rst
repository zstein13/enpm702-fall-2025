Lecture 8 - OOP (Basics)
===============================================

This site accompanies *ENPM702 - Lecture 8: Object-Oriented Programming (Basics)*. It organizes the lecture into concise, browsable pages with examples, short exercises, and instructor notes.

Learning Outcomes
-----------------

By the end of this session, you will be able to:

- Understand the core principles of Object-Oriented Programming (encapsulation, abstraction, inheritance, polymorphism)
- Define and implement classes with proper encapsulation using access specifiers
- Distinguish between classes and objects, and understand instantiation
- Create constructors (default and parameterized) with member initializer lists
- Implement accessors (getters) and mutators (setters) with proper const-correctness
- Apply modern C++ features including ``std::string_view``, ``std::optional``, ``[[nodiscard]]``, and ``noexcept``
- Understand the software design process: requirements analysis and UML modeling
- Implement classes within proper namespace organization (``transportation``)
- Write well-documented code using Doxygen conventions

.. tip::
   Compile examples with ``-std=c++17 -Wall -Wextra -pedantic-errors -Werror`` for strong diagnostics.

Course Context
--------------

This lecture bridges the gap between procedural and object-oriented programming in C++. We introduce OOP concepts through a comprehensive vehicle control system example, following industry-standard practices from requirements analysis through implementation. The lecture emphasizes modern C++ idioms and prepares students for advanced OOP topics in Lecture 9.

**Prerequisites:**

- Strong understanding of C++ fundamentals (variables, functions, references, pointers)
- Familiarity with STL containers (``std::vector``, ``std::string``)
- Basic understanding of memory management concepts

**Connection to Future Topics:**

- Lecture 9 will cover inheritance, polymorphism, virtual functions, and advanced OOP patterns
- Project work will require implementing class hierarchies following the design patterns introduced here

Detailed Topics
---------------

The following sections explore each topic in Lecture 8:

.. toctree::
   :maxdepth: 2
   :caption: Lecture 8 Topics
   :titlesonly:

   design
   core_principles
   classes_and_objects
   encapsulation
   constructors
   modern_cpp_features
   exercises

Overview of Topics
------------------

**Design Phase**

- Requirements analysis: defining what the system must do
- Modeling phase: UML diagrams (class, sequence, state machine, system architecture)
- Introduction to PlantUML and modeling tools

**Core OOP Principles**

- Encapsulation: data hiding and controlled access
- Abstraction: simplifying complexity
- Inheritance: code reuse through hierarchies (covered in Lecture 9)
- Polymorphism: flexible and extensible interfaces (covered in Lecture 9)

**Classes and Objects**

- Class definition: blueprints for objects
- Object instantiation: creating instances from classes
- Member variables (attributes) and member functions (methods)
- Stack vs. heap allocation with smart pointers

**Encapsulation**

- Access specifiers: ``public``, ``private``, ``protected``
- Accessors (getters): ``const``-correct, ``[[nodiscard]]``, ``noexcept``
- Mutators (setters): validation and invariant enforcement

**Constructors**

- Default constructors: compiler-generated vs. user-defined
- Parameterized constructors: initialization with arguments
- Member initializer lists: efficient direct initialization
- Understanding construction order and avoiding two-step initialization

**Modern C++ Features**

- ``std::string_view``: lightweight string references for read-only access
- ``std::optional``: type-safe optional values
- ``[[nodiscard]]``: preventing accidental value discards
- ``noexcept``: exception specifications for optimization

**Implementation Example**

- Complete ``Vehicle`` class implementation within ``transportation`` namespace
- Project structure: separation of headers (``include/``) and source files (``src/``)
- CMake build configuration
- Doxygen documentation standards

Example: The Vehicle System
----------------------------

Throughout this lecture, we develop a ``Vehicle`` class as part of a larger transportation system. This example demonstrates:

**Design artifacts:**

- Functional requirements (FR-1 through FR-10)
- Non-functional requirements (performance, safety, reliability)
- UML class diagram showing ``Vehicle``, ``Driver``, ``Engine``, and ``Route``
- Sequence diagrams for driver-vehicle interactions
- State machine for vehicle lifecycle

**Implementation details:**

.. code-block:: cpp

   namespace transportation {

   class Vehicle {
   private:
       std::string color_;
       std::string model_;
       bool is_running_{false};
       int max_speed_;

   public:
       // Default constructor
       Vehicle();
       
       // Parameterized constructor with member initializer list
       Vehicle(const std::string& color, const std::string& model, 
               int max_speed)
           : color_{color}, model_{model}, max_speed_{max_speed} {}
       
       // Accessors (const-correct, nodiscard, noexcept)
       [[nodiscard]] bool is_running() const noexcept { 
           return is_running_; 
       }
       [[nodiscard]] const std::string& get_color() const noexcept { 
           return color_; 
       }
       [[nodiscard]] int get_max_speed() const noexcept { 
           return max_speed_; 
       }
       
       // Mutators with validation
       void set_color(const std::string& color);
       void set_max_speed(int speed);  // throws if speed < 0
       
       // Methods
       void start_engine();
       void stop_engine();
       void drive();
   };

   }  // namespace transportation

Best Practices Emphasized
--------------------------

**Encapsulation:**

- All attributes must be ``private`` or ``protected``
- Provide controlled access through accessors and mutators
- Validate data in mutators to maintain class invariants

**Modern C++ Idioms:**

- Use member initializer lists for all constructors
- Mark accessors as ``const noexcept`` when appropriate
- Use ``[[nodiscard]]`` on functions returning important values
- Prefer ``const std::string&`` for large types in parameters
- Use ``std::string_view`` for read-only string parameters (not for storage)

**Code Organization:**

- Separate interface (header files) from implementation (source files)
- Use namespaces to prevent naming conflicts
- Follow consistent naming conventions (``snake_case`` for members, trailing underscore)
- Document all public APIs with Doxygen comments

**Error Handling:**

- Use ``std::optional`` for operations that may fail
- Validate constructor parameters and throw descriptive exceptions
- Prefer compile-time guarantees (``const``, ``noexcept``) when possible

Common Pitfalls
---------------

.. warning::

   **Critical mistakes that result in assignment failure:**
   
   - Making class attributes ``public`` (violates encapsulation)
   - Forgetting ``const`` on accessor methods
   - Returning non-const references from accessors
   - Not using member initializer lists in constructors
   - Forgetting the semicolon after class definition

**Performance issues:**

- Passing ``std::string`` by value unnecessarily
- Using ``std::string_view`` for constructor parameters when storing as members
- Assignment in constructor body instead of member initializer lists

**Design issues:**

- Not validating input in mutators
- Mixing concerns across classes
- Tight coupling between unrelated classes

Resources and Further Reading
------------------------------

**C++ Standards and References:**

- `C++ Reference - Classes <https://en.cppreference.com/w/cpp/language/classes>`_
- `C++ Core Guidelines - Class Design <https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#S-class>`_

**UML and Design:**

- `PlantUML Documentation <https://plantuml.com/>`_
- `UML Class Diagrams <https://www.uml.org/>`_

**Modern C++ Features:**

- `std::string_view <https://en.cppreference.com/w/cpp/string/basic_string_view>`_
- `std::optional <https://en.cppreference.com/w/cpp/utility/optional>`_
- `Attributes (nodiscard, noexcept) <https://en.cppreference.com/w/cpp/language/attributes>`_

**Books:**

- *Effective C++* by Scott Meyers - Items on class design
- *C++ Primer* (5th Edition) - Chapter 7: Classes
- *Design Patterns* by Gang of Four - Foundational OOP patterns

Practice Exercises
------------------

1. **Basic Class Implementation:**
   Implement a complete ``Engine`` class with attributes (``horsepower``, ``fuel_type``) and methods (``start()``, ``stop()``). Include proper encapsulation, constructors, and accessors/mutators.

2. **Using std::optional:**
   Write a function ``std::optional<size_t> find_first_digit(std::string_view str)`` that returns the index of the first digit character, or ``std::nullopt`` if none exists.

3. **Member Initializer Lists:**
   Refactor a given class that uses assignment in constructor bodies to use member initializer lists. Measure the performance difference.

4. **Const-Correctness:**
   Review a provided class and identify all methods that should be marked ``const`` but aren't. Explain why each should be const.

5. **Design Exercise:**
   Create a UML class diagram for a ``Library`` system with classes for ``Book``, ``Member``, and ``Loan``. Identify relationships (association, aggregation, composition).

Next Steps
----------

- **Lecture 9** will cover inheritance hierarchies, virtual functions, polymorphism, abstract base classes, and the ``virtual`` keyword
- Begin working on your project's class design and UML diagrams
- Practice implementing classes with proper encapsulation and modern C++ features
- Review the ``transportation`` namespace implementation for design patterns

.. tip::

   Before the next lecture, ensure you can:
   
   - Implement a class with multiple constructors
   - Write const-correct accessors and validated mutators
   - Use member initializer lists effectively
   - Apply ``std::optional`` and ``std::string_view`` appropriately
   - Organize code within namespaces