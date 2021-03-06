/*
 * File: CountFifteens.cpp
 * -----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter code for the CountFifteens problem from
 * Assignment #3.
 * [TODO: extend the documentation]
 */

#include <exception>
#include <iostream>
#include <string>
#include "card.h"
#include "console.h"
#include "error.h"
#include "simpio.h"
#include "tokenscanner.h"
#include "vector.h"
using namespace std;

/* Function prototypes */

int countFifteens(Vector<Card> & cards);

/*
 * Main program
 * ------------
 * This test program does no error-checking on the input.  One of the
 * extensions you might consider is adding code to this program (and
 * possibly to the Card class) to allow the program to report errors.
 */

int main() {
   while (true) {
      string line = getLine("Enter a hand of cards: ");
      if (line == "") break;
      TokenScanner scanner(line);
      scanner.ignoreWhitespace();
      Vector<Card> hand;
      while (scanner.hasMoreTokens()) {
         hand.add(Card(scanner.nextToken()));
      }

      int nWays = countFifteens(hand);
      string plural = (nWays == 1) ? "" : "s";
      cout << nWays << " way" << plural << endl;
}
    return 0;
}

/*
 * Counts the number of ways of making a total of 15 from the vector of
 * cards.
 */

bool sumIsFifteen(Vector<Card> cards){
    int sum = 0;
    for(Card c:cards){
        if(c.getRank()>10){
            sum+=10;
        }else{
            sum+=c.getRank();
        }
    }
    if(sum == 15){
        return true;
    }
    else{
        return false;
    }
}

void countFifteensRec(Vector<Card> soFar, Vector<Card> rest, int &count){
    if(rest.isEmpty()){
        if(sumIsFifteen(soFar))
            count++;
    }else{
        soFar.add(rest[0]);
        rest.remove(0);
        countFifteensRec(soFar, rest, count);
        soFar.remove(soFar.size()-1);
        countFifteensRec(soFar, rest, count);
    }
}

int countFifteens(Vector<Card> & cards) {
   int count = 0;
   Vector<Card> empty;
   countFifteensRec(empty, cards, count);
   return count;
}
