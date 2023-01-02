//
//  tax.cpp
//  Project 2
//
//  Created by Impana on 10/10/22.
//
#include <iostream>

//used to enable setprecision
#include <iomanip>
using namespace std;

int main()
{
    //Collecting the information for one taxpayer:
    string name;
    double taxableIncome;
    string occupation;
    int numChildren;
    double amount = 0;

    cout << "Name: ";
    getline (cin,name);
    cout << "Taxable income: ";
    cin >> taxableIncome;
    //To combat the problem of putting a getline after a cin (occupation after taxableIncome)
    string dummy;
    getline(cin, dummy);
    //
    cout << "Occupation: ";
    getline (cin,occupation);
    cout << "Number of children: ";
    cin >> numChildren;
    //
    
    cout << "---" << endl;
    
    //Checking for anny erroneous/unusual input
    if (name == "") {
        cout << "You must enter a name" << endl;
    }
    else if (taxableIncome < 0) {
        cout << "The taxable income must not be negative" << endl;
    }
    else if (occupation == "") {
        cout << "You must enter an occupation" << endl;
    }
    else if (numChildren < 0){
        cout << "The number of children must not be negative" << endl;
    }
    //
    
    //PARTS
    // 1. The first $55000 of taxable income is taxed at 4%.
    // 2. The next $70000 of taxable income is taxed at 7% in general. However, if the taxpayer's occupation is nurse or teacher (so spelled, entirely in lower case), the income in this bracket is taxed at only 5%.
    // 3. The amount of taxable income that exceeds $125000 is taxed at 9.3%.
    // 4. If the taxable income is under $125000, the tax is reduced by $200 per child; however, the tax is never allowed to go below zero.*/
    
    
    else {
        //Checking part 4 before we start subtracting from the taxableIncome variable
        if (taxableIncome < 125000){
            amount -= (200) * numChildren;
        }
        //Checking part 3 before we start subtracting from the taxableIncome variable
        else {
            amount += ((125000 - taxableIncome) * 0.093);
        }
        
        //Checking part 1: If the taxable income is already less than 55000, we can just add the taxable income taxed at 4% to the amount. If not, then we have to add 55000 taxed at 4% to the amount, and subtract 55000 from the taxableIncome variable so that we don't account for it in later calculations.
        if (taxableIncome <= 55000){
            amount += taxableIncome * 0.04;
        } else {
            amount += 55000 * 0.04;
            taxableIncome -= 55000;
            //Checking part 2: If the taxable income is already less than 70000, we can just add the taxable income taxed at 5% (if the occupation is nurse or teacher)/7& to the amount. If not, then we have to add 770000 taxed at 5% (if the occupation is nurse or teacher)/7& to the amount, and subtract 77000 from the taxableIncome variable so that we don't account for it in later calculations.
            if (taxableIncome <= 70000){
                if ((occupation == "nurse") || (occupation == "teacher")){
                    amount += (taxableIncome * 0.05);
                } else {
                    amount += (taxableIncome * 0.07);
                }
            } else {
                if ((occupation == "nurse") || (occupation == "teacher")){
                    amount += (70000 * 0.05);
                    taxableIncome -= 70000;
                } else {
                    amount += (70000 * 0.07);
                    taxableIncome -= 70000;
                }
            }
        }
        //we can never allow the amount to go below 0.
        if (amount < 0){
            amount = 0;
        }
        
        //setprecision(2) will give us an amount with decimals upto the hundredths place.
        cout << name << " would pay $" << fixed << setprecision(2) << amount << endl;
        //cout << name << " would pay $" << amount << endl;
    }
        
}
