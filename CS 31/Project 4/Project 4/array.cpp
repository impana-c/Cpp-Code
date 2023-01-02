//
//  array.cpp
//  Project 4
//
//  Created by Impana on 11/1/22.
//

#include <iostream>
#include <string>
#include <cassert>
using namespace std;

const int RET_BAD_ARG = -1;

int appendToAll(string a[], int n, string value){
    if (n < 0){
        return RET_BAD_ARG;
    }
    //iterate through the array and append the value to each element
    for (int i = 0; i < n; i++){
        a[i] += value;
    }
    return n;
}

int lookup(const string a[], int n, string target){
    //return index of first instance of target
    for (int i = 0; i < n; i++){
        if (a[i] == target){
            return i;
        }
    }
    return -1;
}

int positionOfMax(const string a[], int n){
    if (n < 0){
        return RET_BAD_ARG;
    }
    //set max to first element of array
    string max = a[0];
    int x = -1;
    //iterate backwards to end with the last element and get back the smallest position of the max
    for (int i = n-1; i >= 0; i--){
        if (max <= a[i]){
            max = a[i];
            x = i;
        }
    }
    return x;
}

int rotateLeft(string a[], int n, int pos){
    //position cannot be greater than number of elements
    if ((n < 0) || (pos > n)){
        return RET_BAD_ARG;
    }
    string temp = a[pos];
    //rotate each element after pos to the left except the last one
    for (int i = pos; i < n-1; i++){
        a[i] = a[i+1];
    }
    //set last element to what element at position was orginally
    a[n-1] = temp;
    return pos;
}

int countRuns(const string a[], int n){
    if (n < 0){
        return RET_BAD_ARG;
    }
    int seqcount = 0;
    for (int i = 1; i < n; i++){
        //increment whenever two consecutive elements are not equal
        if (a[i-1] != a[i]){
            seqcount++;
        }
    }
    //add one because seqcount only calculated number of divisions between consecutive sequences
    return (seqcount + 1);
}

int flip(string a[], int n){
    if (n < 0){
        return RET_BAD_ARG;
    }
    string tempVal;
    // divide n by 2 to start swapping first half and second half
    for (int i = 0; i < (n / 2); i++) {
        tempVal = a[i];             // Temp for swap
        a[i] = a[n - 1 - i];        // First part of swap
        a[n - 1 - i] = tempVal;     // Second complete
    }
    return n;
}

int differ(const string a1[], int n1, const string a2[], int n2){
    if ((n1 < 0) || (n2 < 0)){
        return RET_BAD_ARG;
    }
    //set n to the lower value between n1 and n2 to use the array that is going to run out first
    int n;
    if (n1 < n2){
        n = n1;
    } else{
        n = n2;
    }
    //return index of first instance of elements in both arrays not being equal to each other
    for (int i=0; i<n; i++){
        if (a1[i] != a2[i]){
            return i;
        }
    }
    return n;
}

int subsequence(const string a1[], int n1, const string a2[], int n2){
    //length of main array cannot be less than the length of subsequence
    if ((n1 < 0) || (n2 < 0) | (n1<n2)){
        return RET_BAD_ARG;
    }
    //an empty array is always a subset of another array
    if (n2==0){
        return 0;
    }
    for (int i=0; i<n1; i++){
        //initialize counter to i
        int count = i;
        //check if the element in main array at current index is equal to starting element of subsequence
        if (a1[i] == a2[0]){
            //loop through subsequence
            for (int j = 0; j < n2; j++){
                if (a1[count] == a2[j]){
                    //increment counter
                    count++;
                    //if reach last element of subsequence
                    if (j == n2-1){
                        //return index of starting subsequence within main array
                        return i;
                    }
                }
            }
        }
    }
    return -1;
}

int lookupAny(const string a1[], int n1, const string a2[], int n2){
    if ((n1 < 0) || (n2 < 0)){
        return RET_BAD_ARG;
    }
    //iterate through main array
    for (int i = 0; i < n1; i++){
        //iterate through array to look up from
        for (int j = 0; j < n2; j++){
            if (a1[i] == a2[j]){
                return i;
            }
        }
    }
    return -1;
}

int split(string a[], int n, string splitter){
    if (n < 0){
        return RET_BAD_ARG;
    }
    
    //first move all elements equal to splitter to the end of array
    for (int i = 0; i < n; i++) {
        if ((a[i]) == splitter){
            rotateLeft(a, n, i);
        }
    }
    
    //first move all the elements <= splitter to the front of the array
    for (int i = 0; i < n; i++) {
        // if value of element at current index is less than splitter value
        if (a[i] <= splitter){
            //iterate through array again
            for (int j = 0; j < n; j++) {
                //check for any element before current index that has a value greater than splitter, and swap
                if ((a[j] > splitter) && (i>j)){;
                    string tempVal = a[i];
                    a[i] = a[j];
                    a[j] = tempVal;
                }
            }
        }
    }
    
    //return first element in array with a value >= to splitter
    for (int i = 0; i < n-1; i++) {
        if (!((a[i]) < splitter)){
            return i;
        }
    }
    return n;
}

int main() {
    string h[7] = { "rishi", "margaret", "gordon", "tony", "", "john", "liz" };
    assert(lookup(h, 7, "john") == 5);
    assert(lookup(h, 7, "gordon") == 2);
    assert(lookup(h, 2, "gordon") == -1);
    assert(lookup(h, 7, "") == 4);
    
    assert(positionOfMax(h, 7) == 3);
    assert(positionOfMax(h, 0) == -1);
    string pm2[4] = {"1", "@", "!", "100"};
    assert(positionOfMax(pm2, 4)==1);
    string pm3[4] = {"1", "12", "123", "1234"};
    assert(positionOfMax(pm3, 4)==3);
    
    string leader[6] = { "boris", "rishi", "", "tony", "theresa", "david" };
    string politician[5] = { "boris", "rishi", "david", "", "tony" };
    assert(differ(leader, 6, politician, 5) == 2);
    assert(differ(leader, 2, politician, 1) == 1);
    assert(differ(leader, 2, politician, 0) == 0);
    
    assert(flip(leader, 4) == 4 && leader[0]=="tony");
//  now leader is tony, "", rishi, boris, theresa, david
//    for (int i=0; i<6; i++){
//        cout << leader[i] << endl;
//    }

    string g[4] = { "rishi", "margaret", "liz", "theresa" };
    assert(differ(h, 4, g, 4) == 2);
    assert(appendToAll(g, 4, "?") == 4 && g[0] == "rishi?" && g[3] == "theresa?");
    assert(rotateLeft(g, 4, 1) == 1 && g[1] == "liz?" && g[3] == "margaret?");
    assert(split(g, 4, "rishi") == 2);
    
    string people[5] = { "boris", "gordon", "rishi", "liz", "john" };
    assert(appendToAll(people, 5, "!!!")==5);
    //    for (int i=0; i<5; i++){
    //        cout << people[i] << endl;
    //    }

    string d[5] = { "margaret", "margaret", "margaret", "tony", "tony" };
    assert(countRuns(d, 5) == 2);
    string d1[9] = {"tony", "boris", "rishi", "rishi", "gordon", "gordon", "gordon", "rishi", "rishi"};
    assert(countRuns(d1, 9) == 5);

    string f[3] = { "liz", "gordon", "tony" };
    assert(lookupAny(h, 7, f, 3) == 2);
    assert(flip(f, 3) == 3 && f[0] == "tony" && f[2] == "liz");
    
    string e[4] = { "gordon", "tony", "", "john" };
    assert(subsequence(h, 7, e, 4) == 2);
    string names[10] = { "john", "margaret", "theresa", "rishi", "boris", "liz" };
    string names1[10] = { "margaret", "theresa", "rishi" };
    assert(subsequence(names, 6, names1, 3) == 1);
    string names2[10] = { "john", "rishi" };
    assert(subsequence(names, 5, names2, 2) == -1);
    assert(subsequence(names, 5, names2, 0) == 0);
    assert(subsequence(names, 0, names2, 2) == -1);
    assert(subsequence(names, 0, names2, 0) == 0);
    
    string namess[10] = { "john", "margaret", "theresa", "rishi", "boris", "liz" };
    string set1[10] = { "david", "boris", "rishi", "margaret" };
    assert(lookupAny(namess, 6, set1, 4) == 1);
    string set2[10] = { "tony", "gordon" };
    assert(lookupAny(namess, 6, set2, 2) == -1);
    
    assert(split(h, 7, "liz") == 3);
    string pm1[6] = { "david", "liz", "margaret", "tony", "gordon", "boris" };
    assert (split(pm1, 6, "john") == 3);
//    for (int i=0; i<6; i++){
//        cout << pm1[i] << endl;
//    }
    
    string empty[4] = {"","","",""};
    assert(positionOfMax(empty, 4) == 0);
    assert(lookup(empty, 4, "") == 0);
    assert(differ(pm1,0,empty,0) == 0);
    assert(differ(pm1,6,empty,4) == 0);
    assert(appendToAll(empty, 4, "") == 4);
    assert(rotateLeft(empty, 4, 1) == 1);
    assert(subsequence(leader, 6, empty, 4) == -1);
    assert(flip(empty, 4) == 4 && empty[0] == "" && empty[2] == "");\
    assert(lookupAny(leader, 6, empty, 4) == 1);
    assert(split(empty, 4, "") == 0);
    
    string x[5] = {"a", "b", "c", "d", "e"};
    assert(positionOfMax(x, -4) == -1);
    assert(lookup(x, -4, "") == -1);
    assert(differ(pm1,0,x,-4) == -1);
    assert(differ(pm1,-6,x,4) == -1);
    assert(appendToAll(x, -4, "") == -1);
    assert(rotateLeft(x, -4, 1) == -1);
    assert(subsequence(x, -6, empty, 4) == -1);
    assert(flip(x, -4) == -1);
    assert(lookupAny(x, -6, empty, 4) == -1);
    assert(split(x, -4, "") == -1);
    
    cout << "All tests succeeded" << endl;
    return 0;
}



