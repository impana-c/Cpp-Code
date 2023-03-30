//
//  tree.cpp
//  Homework3
//
//  Created by Impana on 2/15/23.
//

#include <iostream>
#include <cassert>
using namespace std;

// Return the number of ways that all n1 elements of a1 appear in
// the n2 element array a2 in the same order (though not necessarily
// consecutively).  We decree that the empty sequence (i.e. one where
// n1 is 0) appears in a sequence of length n2 in 1 way, even if n2
// is 0.  For example, if a2 is the 7 element array
//    10 50 40 20 50 40 30
// then for this value of a1     the function must return
//    10 20 40                        1
//    10 40 30                        2
//    20 10 40                        0
//    50 40 30                        3
int countIsIn(const double a1[], int n1, const double a2[], int n2)
{
    if (n1 <= 0){
        return 1; //means the subsequence was found
    }
    if (n2 <= 0){
        return 0; //means the subsequence was not found
    }
        
    if (a1[n1-1] == a2[n2-1]){
        int result1 = countIsIn(a1,n1,a2,n2-1);
        int result2 = countIsIn(a1,n1-1,a2,n2-1);
        return result1 + result2;
    } else {
        return countIsIn(a1,n1,a2,n2-1);
    }
}

// Exchange two doubles
void exchange(double& x, double& y)
{
  double t = x;
  x = y;
  y = t;
}

// Rearrange the elements of the array so that all the elements
// whose value is > divider come before all the other elements,
// and all the elements whose value is < divider come after all
// the other elements.  Upon return, firstNotGreater is set to the
// index of the first element in the rearranged array that is
// <= divider, or n if there is no such element, and firstLess is
// set to the index of the first element that is < divider, or n
// if there is no such element.
// In other words, upon return from the function, the array is a
// permutation of its original value such that
//   * for 0 <= i < firstNotGreater, a[i] > divider
//   * for firstNotGreater <= i < firstLess, a[i] == divider
//   * for firstLess <= i < n, a[i] < divider
// All the elements > divider end up in no particular order.
// All the elements < divider end up in no particular order.
void divide(double a[], int n, double divider,
                                     int& firstNotGreater, int& firstLess)
{
    if (n < 0)
        n = 0;

    // It will always be the case that just before evaluating the loop
    // condition:
    //  firstNotGreater <= firstUnknown and firstUnknown <= firstLess
    //  Every element earlier than position firstNotGreater is > divider
    //  Every element from position firstNotGreater to firstUnknown-1 is
    //    == divider
    //  Every element from firstUnknown to firstLess-1 is not known yet
    //  Every element at position firstLess or later is < divider

  firstNotGreater = 0;
  firstLess = n;
  int firstUnknown = 0;
  while (firstUnknown < firstLess)
  {
      if (a[firstUnknown] < divider)
      {
          firstLess--;
          exchange(a[firstUnknown], a[firstLess]);
      }
      else
      {
          if (a[firstUnknown] > divider)
          {
              exchange(a[firstNotGreater], a[firstUnknown]);
              firstNotGreater++;
          }
          firstUnknown++;
      }
  }
    
}

// Rearrange the elements of the array so that
// a[0] >= a[1] >= a[2] >= ... >= a[n-2] >= a[n-1]
// If n <= 1, do nothing.
void order(double a[], int n){
    if (n <= 1)
        return;
    
    int firstNotGreater;
    int firstLess;
    
    divide(a, n, a[n-1], firstNotGreater, firstLess);
    if (firstLess == n){
        order(a, n-1);
    } else{
        order(a, n);
    }
}

void printOrder(const double a[], int n){
    if (n==0){
        cout << endl;
        return;
    }
    cout << a[0] << ", ";
    printOrder(a+1, n-1);
}

int main() {
    double arr1[7] = { 10,50,40,20,50,40,30 };
    double arr2[3] = { 10,20,40 };
    double arr4[3] = { 10,40,30 };
    double arr5[3] = { 20,10,40 };
    double arr3[3] = { 50,40,30 };

    assert(countIsIn(arr2, 3, arr1, 7) == 1);
    assert(countIsIn(arr4, 3, arr1, 7) == 2);
    assert(countIsIn(arr5, 3, arr1, 7) == 0);
    assert(countIsIn(arr3, 3, arr1, 7) == 3);

    double a1[10] = { 1,3,5,3,1,3,5,3,1,3 };
    double a2[5] = {1,3};
    double a3[5] = {3,5,3};
    double a4[5] = { 1,3,5,1,1 };
    double a5[5] = {3};
    /*cout << countIsIn(a5, 1, a1, 10) << endl;*/

    assert(countIsIn(a1, 0, a1, 5) == 1);
    assert(countIsIn(a1, -1, a1, -1) == 1); // treat - as 0
    assert(countIsIn(a2, 2, a1, 10) == 9);
    assert(countIsIn(a3, 3, a1, 10) == 10);
    assert(countIsIn(a4, 5, a1, 10) == 1);
    assert(countIsIn(a5, 1, a1, 10) == 5);
    assert(countIsIn(a2, 1, a1, 10) == 3);

    //testing ORDER
    double ar1[5] = { 5,1,4,3,2 };

    order(ar1, 1); // testing <= 1 behavior => do nothing
    assert(ar1[0] == 5);
    assert(ar1[1] == 1);
    assert(ar1[2] == 4);
    assert(ar1[3] == 3);
    assert(ar1[4] == 2);

    order(ar1, 5);
    assert(ar1[0] >= ar1[1]);
    assert(ar1[1] >= ar1[2]);
    assert(ar1[2] >= ar1[3]);
    assert(ar1[3] >= ar1[4]);

    double ar2[5] = { 3,0,-6,-2,8 };
    order(ar2, 5);
    assert(ar2[0] >= ar2[1]);
    assert(ar2[1] >= ar2[2]);
    assert(ar2[2] >= ar2[3]);
    assert(ar2[3] >= ar2[4]);

    double ar3[3] = { 0,0,0 }; // checking for undefined behavior
    assert(ar3[0] == 0);
    assert(ar3[1] == 0);
    assert(ar3[2] == 0);

    cout << "Passed all tests" << endl;

    double arr_1[3] = {10, 20, 40}; //1
//    double arr_1[3] = {10, 40, 30}; //2
//    double arr_1[3] = {20, 10, 40}; //0
//    double arr_1[3] = {50, 40, 30}; //3
    double arr_2[7] = {10, 50, 40, 20, 50, 40, 30};
    double arr_3[6] = {50, 40, 30, 50, 40, 30};
//    cout << countIsIn(arr_1, 3, arr_2, 7) << endl;
//    cout << countIsIn(arr_1, 3, arr_3, 6) << endl; //4

    order(arr_1, 3);
    order(arr_2, 7);
    order(arr_3, 6);

    printOrder(arr_1, 3);
    printOrder(arr_2, 7);
    printOrder(arr_3, 6);
}
