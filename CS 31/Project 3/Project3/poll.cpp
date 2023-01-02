//
//  poll.cpp
//  Project3
//
//  Created by Impana on 10/19/22.
//

#include <iostream>
#include <stdio.h>
#include <ctype.h>
using namespace std;

bool isValidUppercaseStateCode(string stateCode)
{
    const string codes =
        "AL.AK.AZ.AR.CA.CO.CT.DE.FL.GA.HI.ID.IL.IN.IA.KS.KY."
        "LA.ME.MA.MD.MI.MN.MS.MO.MT.NE.NV.NH.NJ.NM.NY.NC.ND."
        "OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
    return (stateCode.size() == 2  &&
            stateCode.find('.') == string::npos  &&  // no '.' in stateCode
            codes.find(stateCode) != string::npos);  // match found
}

bool isValidPollString(string pollData)
{
    for (int j = 0; j < pollData.size(); j++){
        //Check for whitespace. If there is any spaces within the pollData string, it is immediately an invalid poll string.
        if (isspace(pollData.at(j))){
            return false;
        }
        //Checking whether pollString has any extraneous characters such as %$^. A comma is not included in this description.
        if ((pollData[j] != ',') && (!((isdigit(pollData[j])) || (isalpha(pollData[j])))) ) {
            return false;
        }
    }
    
    if (pollData.size() == 0){
        return true;
    }
    
    //Check that the first and last characters of a state forecast are letters.
    if ( !(isalpha(pollData.at(0))) || !(isalpha(pollData.at(pollData.size()-1))) ){
        return false;
    }
    
    if ((pollData.size() > 1) && ((pollData.at(pollData.size()-2)) == ',')) {
        return false;
    }
    
    for (int j = 1; j < pollData.size()-1; j++){
        if (pollData.at(j) == ','){
            if ( !(isalpha(pollData.at(j-1))) || !(isalpha(pollData.at(j+1))) ){
                return false;
            }
        }
    }
    
    //Convert all letters in the poll string to upper case.
    for (int j = 0; j < pollData.size(); j++){
        if (isalpha(pollData.at(j))){
            char c = pollData.at(j);
            pollData.at(j) = toupper(c);
        }
    }
    
    for (int i = 0; i < pollData.size()-1; i++){
        //1.Check state code.
        if (isalpha(pollData.at(i)) && isalpha(pollData.at(i+1))){
            if (i>1){
                if (pollData.at(i-1)!=','){
                    return false;
                }
            }
            string statecode = "00";
            statecode.at(0) = pollData[i]; statecode.at(1) = pollData[i+1];
            if (!(isValidUppercaseStateCode(statecode))){
                return false;
            }
            //Check that the character after the statecode is an integer.
            else if ((i+2) < pollData.size()){
                if ( !(isdigit(pollData.at(i+2))) && pollData.at(i+2)!=','){
                    return false;
                }
            }
            //Incrementing i again here so that we can move on to the next character after the statecode.
            i++;
        }
        
        if (i>1) {
            if ( ((pollData.at(i-1))==',') && ((pollData.at(i+1))==',') ){
                return false;
            }
        }
        
        
        //2. Check party result.
        else if (isdigit(pollData[i])){
            int j = i;
            int count = 0;
            //Check how many digits come before the party code. If it is not exactly one or two, then it is not a valid party result.
            while ( (j<pollData.size()) && (!(isalpha(pollData[j]))) ){
                if (isdigit(pollData[j])){
                    count++;
                }
                j++;
            }
            if ((count==0)||(count>2)){
                return false;
            }
            //Increment i by the count (which is either going to be 1 or 2 if we haven't returned false already). This will allow us to move to the next character after the party result.
            i+=count;
            
            //Check if there are any sequences of two letters that are not state codes
            if ( (i+1) < pollData.size()){
                if (isalpha(pollData[i+1])){
                    return false;
                }
            }
        }
        
    }
    return true;
}

int countSeats(string pollData, char party, int& seatCount)
{
    if (! (isValidPollString(pollData))){
        return 1;
    }
    if (! (isalpha(party))){
        return 2;
    }
    
    int seats = 0;
    for (int i = 1; i < pollData.size(); i++){\
        if (toupper(pollData.at(i)) == toupper(party)){
            //Checking that the previous character is not a letter and therefore is not a state code.
            if (!(isalpha(pollData.at(i-1)))){
                if (isdigit(pollData.at(i-1)) && isdigit(pollData.at(i-2))){
                    //cout << "2" << endl;
                    int x = pollData.at(i-1) - 48;
                    x += 10 * (pollData.at(i-2) - 48);
                    seats += x;
                } else if (isdigit(pollData.at(i-1))){
                    //cout << "3" << endl;
                    seats += pollData.at(i-1) - 48;
                }
            }
        }
    }
    seatCount = seats;
    return 0;
}

int main()
{
    int seats;
    seats = -999;    // so we can detect whether countSeats sets seats
    
    if (countSeats("CT5D", 'd', seats) == 0  &&  seats == 5){
        cout << "1. Passed test: countSeats(\"CT5D\", 'd', seats)" << endl;
    }
    
    if (countSeats("CT55D", 'd', seats) == 0  &&  seats == 55){
        cout << "2. Passed test: countSeats(\"CT55D\", 'd', seats)" << endl;
    }
    
    if (countSeats("CT5D,NY9R16D1I,VT,ne3r00D", 'd', seats) == 0  &&  seats == 21){
        cout << "3. Passed test: countSeats(\"CT5D,NY9R16D1I,VT,ne3r00D\", 'd', seats)" << endl;
    }
    
    if (isValidPollString("CT5D3t,VT")){
        cout << "4. Passed test: isValidPollString(\"CT5D3t,VT\")" << endl;
    }
    
    if (!(isValidPollString("CT%7D"))){
        cout << "5. Passed test: isValidPollString(\"CT%7D\")" << endl;
    }
    
    if (!(isValidPollString("CT567D"))){
        cout << "6. Passed test: isValidPollString(\"CT567D\")" << endl;
    }
    
    if (!(isValidPollString("CT 5D"))){
        cout << "7. Passed test: isValidPollString(\"CT 5D\")" << endl;
    }
    
    if (isValidPollString("CT5D,NY9R16D1I,VT,ne3r00D")){
        cout << "8. Passed test: isValidPollString(\"CT5D,NY9R16D1I,VT,ne3r00D\")" << endl;
    }
    if (!(isValidPollString("ZT5D,NY9R16D1I,VT,ne3r00D"))){
        cout << "9. Passed test: isValidPollString(\"ZT5D,NY9R16D1I,VT,ne3r00D\")" << endl;
    }
     
    seats = -999;    // so we can detect whether countSeats sets seats
    if (countSeats("CT5D,NY9R16D1I,VT,ne3r00D", '%', seats) == 2  &&  seats == -999){
        cout << "10. Passed test: countSeats(\"CT5D,NY9R16D1I,VT,ne3r00D\", '%', seats)" << endl;
    }
    
    if (!(isValidPollString("CAOKNE"))){
        cout << "11. Passed test: isValidPollString(\"CAOKNE\")" << endl;
    }
    
    if (!(isValidPollString("CT5D,NY9R16D1I,VT3,ne3r00D51"))){
        cout << "12. Passed test: isValidPollString(\"CT5D,NY9R16D1I,VT3,ne3r00D51\")" << endl;
    }
    
    if (!(isValidPollString("CT5DE6TX,VT"))){
        cout << "13. Passed test: isValidPollString(\"CT5DE6TX,VT\")" << endl;
    }
    
    seats = -999;    // so we can detect whether countSeats sets seats
    if (countSeats("CT5D,NY9R16D1I,VT3,ne3r00D51", 'd', seats) == 1  &&  seats == -999){
        cout << "14. Passed test: countSeats(\"CT5D,NY9R16D1I,VT3,ne3r00D51\", '%', seats)" << endl;
    }
    
    if (!(isValidPollString("CT5D6T,V,VT"))){
        cout << "15. Passed test: isValidPollString(\"CT5D6T,V,VT\")" << endl;
    }
    
    if (!(isValidPollString("CT5D6T,VT,6"))){
        cout << "16. Passed test: isValidPollString(\"CT5D6T,VT,V\")" << endl;
    }
    
    if (!(isValidPollString("CT5D6T,OKCA,CA"))){
        cout << "17. Passed test: isValidPollString(\"CT5D6T,OKCA,CA\")" << endl;
    }
    
    if (!(isValidPollString("ct5d,ny9r17+1i"))){
        cout << "18. Passed test: isValidPollString(\"ct5d,ny9r17+1i\")" << endl;
    }
}
