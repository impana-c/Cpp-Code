//
//  game.cpp
//  Project 5
//
//  Created by Impana on 11/7/22.
//

#include "utilities.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include <random>
#include <limits>

using namespace std;

const char WORDFILENAME[] = "/Users/impana/Desktop/CS31/Project 5/Project 5/words.txt";
const int MAXWORDS = 9000;

int isValidProbeWord(char probeWord[101], const char words[][7], int nWords){
    int check = 0;
    
    // check if probe word length is not between 4-6
    if ( (strlen(probeWord) < 4) || (strlen(probeWord) > 6) ) {
        return 1;
    }
    // check if probe word has characters that are not letters or lowercase
    for (int i = 0; i < strlen(probeWord) ; i++){
        if (!isalpha(probeWord[i]) || !islower(probeWord[i]) ){
            return 1;
        }
    }
    
    // check whether probe word is in the list of valid words
    if ( (strlen(probeWord) >= 4) && (strlen(probeWord) <= 6) ){
        for (int i = 0; i < (nWords) ; i++){
            if (strcmp(probeWord, words[i]) == 0){
                check++;
            }
        }
        if (check == 0){
            return 2;
        }
    }
    
    return 0;
}

int playOneRound(const char words[][7], int nWords, int wordnum){
    // check if the list of words or the hidden word is out of range
    if ( (nWords < 0) || (wordnum < 0) || (wordnum >= nWords) ){
        return -1;
    }
    
    int numTries = 0;
    char hiddenWord[101];
    strcpy(hiddenWord, words[wordnum]);
    
    int gold = 0;
    int silver = 0;
    
    char probeWord[101] = "";
    
    char smallerWord[101] = "";
    
    char hiddenWord2[101]= "";
    char probeWord2[101] = "";

    while(strcmp(hiddenWord, probeWord) != 0){
        // get user input for probe word
        cout << "Probe word: ";
        cin.getline(probeWord, 100);
        
        // output the correct statement for the cases when the probe word is valid/invalid
        if (isValidProbeWord(probeWord, words, nWords) == 1){
            cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
        } else if (isValidProbeWord(probeWord, words, nWords) == 2){
            cout << "I don't know that word." << endl;
        } else{
            numTries++;
            
            // copy the hidden word and probe word to a new hidden word and probe word C-string
            strcpy(hiddenWord2, hiddenWord);
            strcpy(probeWord2, probeWord);
            
            // set the smaller word to the smaller one out of the hidden and probe word
            if (strlen(hiddenWord) < strlen(probeWord)){
                strcpy(smallerWord, hiddenWord);
            } else{
                strcpy(smallerWord, probeWord);
            }
            
            // if the character is the same at the same index for hidden word and probe word, increase gold count and remove those characters from consideration
            for (int i = 0; i<strlen(smallerWord); i++){
                if (hiddenWord2[i] == probeWord2[i]){
                    hiddenWord2[i] = '0';
                    probeWord2[i] = '0';
                    gold++;
                }
            }
            
            // traverse the smaller C string
            for (int i = 0; i<strlen(hiddenWord); i++){
                for (int j = 0; j<strlen(probeWord); j++){
                    // if the probe word has the same character at any index of the hidden word and it is not an inconsiderable character
                    if ((hiddenWord2[i] != '0') && (probeWord2[j] != '0') && (hiddenWord2[i] == probeWord2[j])){
                        // then increase silver count and remove those characters from considerations
                        hiddenWord2[i] = '0';
                        probeWord2[j] = '0';
                        silver++;
                        
                    }
                }
            }
            if (gold!=strlen(hiddenWord)){
                cout << "Golds: " << gold << ", Silvers: " << silver << endl;
                // reset gold and silver count
                gold = 0;
                silver = 0;
            }
        }
    }
    
    return numTries;
}

int main()
{
    char wordList[MAXWORDS][MAXWORDLEN+1];
    int nWords = getWords(wordList, 9000, WORDFILENAME);
    
    // check if there are no words in the list
    if (nWords < 1){
        cout << "No words were loaded, so I can't play the game." << endl;
        return 0;
    }
    
    int numRounds;
    cout << "How many rounds do you want to play? ";
    cin >> numRounds;
    cin.ignore();
    
    if (numRounds < 0){
        cout << "The number of rounds must be positive." << endl;
        return 0;
    }
    
    double avg = 0.0;
    int min = 0;
    int max = 0;
    for (int i = 1; i <= numRounds; i++){
        cout << endl;
        cout << "Round " << i << endl;
        
        // generate a random word to pick out of the words list
        int n = randInt(0, nWords-1);
        
        cout << "The hidden word is " << strlen(wordList[n])<< " letters long." << endl;
        
        if (i==0) cin.ignore(100000, '\n');
        
        int tries = playOneRound(wordList, nWords, n);
        
        if (tries == 1){
            cout << "You got it in 1 try." <<  endl;
        } else{
            cout << "You got it in " << tries << " tries." << endl;
        }
        
        if (i==1){
            // set the first min, max, and avg to number of tries from first round
            min = tries;
            max = tries;
            avg = tries;
        } else{
            avg = ((avg*(i-1)) + tries)/i;
            if (tries < min){
                min = tries;
            }
            if (tries > max){
                max = tries;
            }
        }
        cout << "Average: " << fixed << setprecision(2) << avg << ", minimum: " <<  min << ", maximum: " << max << endl;
    }
}


