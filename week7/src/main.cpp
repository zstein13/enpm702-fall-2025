#include <chrono>  // For timing utilities
#include <iostream>
#include <memory>
#include <type_traits>
#include <vector>

#include "week7.hpp"

using namespace std::chrono;

//====</1>====//
// int main() {

//   std::vector<std::vector<long long>> matrix;

//   // Create a large vector representing a row of sensor data
//   std::vector<long long> row(10'000'000);

//   auto start{high_resolution_clock::now()};  // Start timer

//   for (long long i{0}; i < 10'000'000; i++) {
//     row[i] = i;
//   }

//   // Copy this row to our matrix
//   matrix.push_back(row);  // This COPIES all 1 million integers!

//   auto end{high_resolution_clock::now()};  // End timer

//   // Compute elapsed time
//   auto duration_ms = duration_cast<milliseconds>(end - start).count();
//   auto duration_s = duration_cast<duration<double>>(end - start).count();

//   std::cout << "Loop and copy completed in " << duration_ms << " ms ("
//             << duration_s << " s)\n";
// }

// //====</2>====//
// int main() {

//   std::vector<std::vector<long long>> matrix;

//   // Create a large vector representing a row of sensor data
//   std::vector<long long> row(10'000'000);

//   auto start{high_resolution_clock::now()};  // Start timer

//   for (long long i{0}; i < 10'000'000; i++) {
//     row[i] = i;
//   }

//   // Copy this row to our matrix
//   matrix.push_back(std::move(row));  // This MOVES row into matrix

//   auto end{high_resolution_clock::now()};  // End timer

//   // Compute elapsed time
//   auto duration_ms = duration_cast<milliseconds>(end - start).count();
//   auto duration_s = duration_cast<duration<double>>(end - start).count();

//   std::cout << "Loop and copy completed in " << duration_ms << " ms ("
//             << duration_s << " s)\n";
// }

// //====</3>====//
// int main() {
//   int x{10 + 20};  // "10 + 20" is a prvalue
//   int y{x + 5};    // "x + 5" is a prvalue

//   42;       // Literal - prvalue
//   3.14159;  // Literal - prvalue
//   true;     // Literal - prvalue

//   std::vector<int>{1, 2, 3};  // Temporary object - prvalue
//   x + y;                      // Result of operation - prvalue
// }

// //==== rvalue references ====//
// int main() {
//   int&& rref{10 + 20};  // The result of 10+20 is stored in memory
//                         // and lives as long as rref exists
//   std::cout << rref << '\n';  // Output: 30
//   rref = 100;                 // We can even modify it!
//   std::cout << rref << '\n';  // Output: 100
// }

// //====</4>====//
// int main() {
//   int&& rref{10 + 20};
//   // rref is an lvalue even though its type is int&&
//   static_assert(std::is_lvalue_reference_v<decltype((rref))>);
//   std::cout << "rref is an lvalue reference: "
//             << std::boolalpha
//             << std::is_lvalue_reference_v<decltype((rref))> << '\n';
// }

// //==== unique_ptr exclusive ownership ====//
// int main() {
//   std::unique_ptr<int> u = std::make_unique<int>(10);
//   std::unique_ptr<int> v{u};  // Error
// }

// //====</5>====//
int main() {
  {
    // Create managed resource on heap
    auto u = std::make_unique<int>(10);
    std::cout << *u << '\n';  // Output: 10 (dereference to access value)
    *u = 20;                  // modify the managed resource
    std::cout << *u << '\n';  // Output: 20
    // std::cout << u << '\n';   // Error: no operator<< for unique_ptr
  }  // u destructor automatically calls delete on managed resource
}

// //====</6>====//
// int main() {}

// //====</7>====//
// int main() {}

// //====</8>====//
// int main() {}

// //====</9>====//
// int main() {}

// //====</10>====//
// int main() {}

// //====</11>====//
// int main() {}

// //====</12>====//
// int main() {}

// //====</13>====//
// int main() {}

// //====</14>====//
// int main() {}

// //====</15>====//
// int main() {}

// //====</16>====//
// int main() {}

// //====</17>====//
// int main() {}

// //====</18>====//
// int main() {}

// //====</19>====//
// int main() {}

// //====</20>====//
// int main() {}

// //====</21>====//
// int main() {}

// //====</22>====//
// int main() {}

// //====</23>====//
// int main() {}

// //====</24>====//
// int main() {}

// //====</25>====//
// int main() {}

// //====</26>====//
// int main() {}

// //====</27>====//
// int main() {}

// //====</28>====//
// int main() {}

// //====</29>====//
// int main() {}
