//
//  linear.cpp
//  Homework3
//
//  Created by Impana on 2/13/23.
//

#include <iostream>
#include <cassert>
using namespace std;

bool somePredicate(double x)
{
    return x > 0;
}

// Return true if the somePredicate function returns true for at
// least one of the array elements; return false otherwise.
bool anyTrue(const double a[], int n)
{
    if(n<=0)
        return false;
    if (somePredicate(a[n-1]))
        return true;
    return (anyTrue(a,n-1));
}

// Return the number of elements in the array for which the
// somePredicate function returns true.
int countTrue(const double a[], int n)
{
    if(n<=0)
        return 0;
    if (somePredicate(a[n-1]))
        return (countTrue(a,n-1) + 1);
    return (countTrue(a,n-1));
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns true.  If there is no such
// element, return -1.
int firstTrue(const double a[], int n)
{
    if (n==0) return -1;
    
    if ((somePredicate(a[n-1])) && (firstTrue(a,n-1)==-1))
        return (n-1);
    else
        return (firstTrue(a, n-1));
}

// Return the subscript of the smallest element in the array (i.e.,
// return the smallest subscript m such that a[m] <= a[k] for all
// k from 0 to n-1).  If the function is told that no doubles are to
// be considered in the array, return -1.
int indexOfMinimum(const double a[], int n)
{
    if (n==1) return 0;
    if (n==0) return -1;
    
    if (a[n-1] > a[indexOfMinimum(a, n-1)])
        return (indexOfMinimum(a, n-1));
    else
        return (n-1);

}

// If all n1 elements of a1 appear in the n2 element array a2, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 is not a
// not-necessarily-contiguous subsequence of a2), return false.
// (Of course, if a1 is empty (i.e., n1 is 0), return true.)
// For example, if a2 is the 7 element array
//    10 50 40 20 50 40 30
// then the function should return true if a1 is
//    50 20 30
// or
//    50 40 40
// and it should return false if a1 is
//    50 30 20
// or
//    10 20 20
bool isIn(const double a1[], int n1, const double a2[], int n2)
{
    if (n1<=0)
        return true;
    if (n2<=0)
        return false;
    if (a1[n1-1] == a2[n2-1])
        return(isIn(a1, n1-1, a2, n2-1));
    return(isIn(a1, n1, a2, n2-1));
}

void printOrder(const double a[], int n){
    if (n==0){
        return;
    }
    cout << a[0] << endl;
    printOrder(a+1, n-1);
}

int main(){
    // testing anyTrue
   double a1[6] = { -5,-4,-3,-2,-1,5};
   double a2[6] = { 5,-4,-3,-2,-1,5 };
   double a3[6] = { -5,-4,3,-2,-1,-5 };
   double a4[5] = { -5,-4,-3,-2,-1 };
   assert(anyTrue(a1, 6));
   assert(anyTrue(a2, 6));
   assert(anyTrue(a3, 6));
   assert(!anyTrue(a4, 5));

   // testing countTrue
   double ar1[6] = { -5,-4,-3,-2,-1,5 };
   double ar2[5] = { -5,-4,-3,-2,-1 };
   double ar3[6] = { 5,-4,3,-2,-1,5 };
   double ar4[6] = { 5,4,3,2,-1,5 };
   double ar5[6] = { 5,4,3,2,1,5 };
   assert(countTrue(ar1, 6) == 1);
   assert(countTrue(ar2, 5) == 0);
   assert(countTrue(ar3, 6) == 3);
   assert(countTrue(ar4, 6) == 5);
   assert(countTrue(ar5, 6) == 6);

   // testing firstTrue
   assert(firstTrue(a1, 6) == 5);
   assert(firstTrue(a2, 6) == 0);
   assert(firstTrue(a3, 6) == 2);
   assert(firstTrue(a4, 5) == -1);

   // testing indexOfMin
   double arrray1[6] = { 5,1,3,2,1,-1 };
   assert(indexOfMinimum(ar1, 6) == 0);
   assert(indexOfMinimum(ar3, 6) == 1);
   assert(indexOfMinimum(ar4, 6) == 4);
   assert(indexOfMinimum(ar5, 6) == 4);
   assert(indexOfMinimum(arrray1, 6) == 5);
   assert(indexOfMinimum(arrray1, 0) == -1);

   // testing isIn
   double arr1[7] = { 10,50,40,20,50,40,30 };
   double arr2[3] = { 50,20,30 };
   double arr4[3] = { 50,40,40 };
   double arr5[3] = { 50,30,20 };
   double arr3[3] = { 10,20,20 };
   double arr6[3] = {};

   assert(isIn(arr2, 3, arr1, 7));
   assert(isIn(arr4, 3, arr1, 7));
   assert(!isIn(arr5, 3, arr1, 7));
   assert(!isIn(arr3, 3, arr1, 7));
   assert(isIn(arr6, 0, arr1, 7)); // testing first is 0, second is big
   assert(!isIn(arr1, 7, arr6, 0)); // first something, second empty
   assert(isIn(arr1, 0, arr6, 0)); // both empty

   cout << "Passed all test cases" << endl;

    double arr[4] = {-1, 0, -1, -1};
    cerr << anyTrue(arr,4) << endl;
    cerr << countTrue(arr,4) << endl;
    cerr << firstTrue(arr,4) << endl;
    cerr << indexOfMinimum(arr,4) << endl;
//    printOrder(arr,4);


    double arr_1[3] = {50, 20, 30}; //1
//    double arr_1[3] = {10, 20, 20}; //0
    double arr_2[7] = {10, 50, 40, 20, 50, 40, 30};
    cerr << isIn(arr_1, 3, arr_2, 7) << endl;
   }
