/**
 * @file week3_exercise.cpp
 * @author Zeid Kootbally (zeidk@umd.edu)
 * @brief Code snippets for exercises on normal pointers
 * @version 1.0
 * @date 2025-09-15
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <iomanip>
#include <iostream>
#include <typeinfo> // needed for typeid

int main() {

  //======== 1
  // int a{10};
  // int *p{&a};

  // // Modify the value of a through p
  // *p = 20;

  // std::cout << a << '\n';  // 20
  // std::cout << *p << '\n'; // 20
  // std::cout << p << '\n';

  // //======== 2-1
  // int a{10};
  // int *p{&a};

  // *p *= 2;

  // std::cout << a << '\n'; // 20
  // std::cout << *p << '\n'; // 20

  // //======== 2-2
  // int a{2}; // int 2
  // int *p{&a}; // address of 2
  // int **q{&p}; // address of pointer p
  // int ***r{&q}; // address of pointer q

  // std::cout << *p << '\n'; // 2
  // std::cout << **q << '\n'; // 2
  // std::cout << ***r << '\n'; // 2

  // //======== 3
  // int a{5};
  // int b{5};

  // int *p1{&a}; // p1 points to a
  // int *p2{&b}; // p2 points to b
  // int *p3{&a}; // p3 points to a

  // std::cout << std::boolalpha; // print bools as true/false
  // std::cout << (p1 == p2) << '\n'; //false p1 and p2 represent mem addresses
  // std::cout << (*p1 == *p2) << '\n'; // true
  // std::cout << (p1 == p3) << '\n'; //true

  // //======== 4
//   int a{10};
//   int b{20};

//   int *p1{&a}; // mem address of a
//   int *p2{&b}; // mem address of b
//   int *p3{&a}; // mem address of a
// // p1 == p3
//   std::cout << std::boolalpha; // print bools as true/false
//   std::cout << (*p1 == *p2) << '\n'; //false
//   std::cout << (*p1 == *p3) << '\n'; //true
//   std::cout << (*p1 > *p2) << '\n'; //false
//   std::cout << (*p1 >= *p2) << '\n'; //false
//   std::cout << (*p1 < *p2) << '\n'; //true
//   std::cout << (*p1 <= *p2) << '\n'; //true
//   std::cout << (*p1 != *p2) << '\n'; //true

  // //======== 5
  // int a{10};
  // int b{20};

  // int *p1{&a};
  // int *p2{&b};
  // int *p3{&a};

  // // // write your code here
  // std::cout << p1 << '\n';
  // std::cout << *p1 << '\n';

  // std::cout << p2 << '\n';
  // std::cout << *p2 << '\n';

  // std::cout << p3 << '\n';
  // std::cout << *p3 << '\n';

  // //======== 6
  // int *p1{new int{2}};
  // int *p2{p1};
  // std::cout << p1 << '\n';
  // std::cout << p2 << '\n';
  
  // delete p2;
  // std::cout << p2 << '\n';
  // p2 = nullptr;
  // std::cout << p2 << '\n';

  // int *p{new int{15}};
  // std::cout << p << '\n'; // 0x55555556b2b0
  // delete p;
  // std::cout << p << '\n';  // 0x55555556b2b0
  // std::cout << *p << '\n'; // UB
  // std::cout << p1 << '\n';
  // delete p1;

  // //======== 7
  int *p1{new int(10)}; //raw pointer
  int *p2{new int(20)}; //raw pointer
  int &ref{*p1};
  std::cout << typeid(ref).name() << '\n';
  std::cout << ref << '\n';
  std::cout << &ref << '\n';
  // ref = *p2;
  // *p2 = 30;
  // p1 = new int(40);
  // delete p2;
  // *p1 = *p2;
  // int *p3{p2};
  // ref = 50;
  // delete p3;
}