//References 
  //https://gamedev.stackexchange.com/questions/27462/adding-cards-to-a-vector-for-computer-card-game
  //https://codereview.stackexchange.com/questions/119915/simple-blackjack-21-game-in-console
  //https://stackoverflow.com/questions/11479645/beginner-blackjack-game
  //http://www.dreamincode.net/forums/topic/59372-simple-c-code-for-a-game-of-blackjack/

  //Includes
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

  //This is a card. It's just a card, and only a card. It's nothing special, keep going!
struct card
{
    int face;
    int suit;
};

  //Global Variables
const int faceMax = 13, suitMax = 4, deckMax = 52;
string faces[] = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };
string suits[] = { "Diamonds", "Clubs", "Hearts", "Spades" };

//=============FUNCTIONS=============//a
  //Make a deck
vector<card> makeDeck(int numDecks){
  //Take the global variables, and make a deck of 52 cards (4 * 13)
  vector<card> myDeck; //face, suite
  for(int face = 0; face < faceMax; face++){
    for(int suit = 0; suit < suitMax; suit++){
      card cardSum = card {.face = face, .suit = suit};
      myDeck.push_back(cardSum);
  
    }//End of suitFor
  }//End of faceFor
  if(numDecks == 2)
  {
    vector<card> myDeck2;
    for(int face = 0; face < faceMax; face++){
      for(int suit = 0; suit < suitMax; suit++){
        card cardSum = card {.face = face, .suit = suit};
        myDeck2.push_back(cardSum);
    
      }//End of suitFor
    }//End of faceFor
    myDeck.insert (myDeck.end(),myDeck2.begin(),myDeck2.end());
  }
  return myDeck;
}//End of makeDeck Function

  //Make a card from the struct values using global strings.
string makeCard(const card deckCard){
  string cardFace = faces[deckCard.face];
  string cardSuit = suits[deckCard.suit];
  return cardFace + " of " + cardSuit;
}//End of makeCard Function

  //Print out the whole deck (for debugging purposes)
void printDeck(const vector<card> newDeck){
  for(int i = 0; i < newDeck.size(); i++){
    string cardString = makeCard(newDeck[i]);
    cout << cardString << endl;
  }//End of For Loop
}//End of printDeck Function

  //Shuffle the deck.
void shuffleDeck(vector<card> &newDeck){
  // initialize random seed: //
  std::random_shuffle(newDeck.begin(),newDeck.end());
}

//Deal a card to the player hand.
void dealCard(vector<card> &newDeck, vector<card> &hand){
  card dealtCard = newDeck.back();
  hand.push_back(dealtCard);
  newDeck.pop_back();
}//End of dealCard Function

//Sum the hand, based on cards received.
int score(const vector<card> &hand){
  int sum = 0;
  int ace = 0;
  for(int i = 0; i < hand.size();i++){
    
    int card = hand.at(i).face;
    
    if (card == 0)
    {
      ace++;
      sum = sum + 11;
    }
    else if(card == 10 || card == 11 || card == 12)
    {
      sum = sum + 10;
    }
    else
    {
      sum = sum + card + 1;
    }
  }//endOfFor1
  for (int i = 0; i < ace; i++){
    if(sum > 21){
      sum = sum - 10;
    }  
  }//endOfFor2
  return sum;
}//endOfScore

bool isWinner(const vector<card> &dealerHand, const vector<card> &playerHand){
  
  if (score(dealerHand) == 21 && dealerHand.size() == 2)
  {
    return false;
  }
  else if (score(playerHand) == 21 && playerHand.size() == 2)
  {
    return true;
  }
  else if (score(playerHand) > 21)
  {
    return false;
  }
  else if (score(dealerHand) > 21)
  {
    return true;
  }
  else if (score(dealerHand) >= score(playerHand))
  {
    return false;
  }
  else
  {
    return true;
  }
}


//==================MAIN=================//

int main() {
  srand(time(0)); //Initialize Random Seed
  

   //Initialize Game Variables
    
      //Number of decks
  int numDecks;
  cout << "Number of decks: (1 or 2) ";
  cin >> numDecks;
  
      //Number of players
  int numPlayers;
  cout << "Number of players: (1 or 2) ";
  cin >> numPlayers;
  if(numPlayers != 1 && numPlayers != 2)
  {
    numPlayers = 2;
  }
  
      //Betting Array
  int betArr[numPlayers];
  
      //Initialize The Game
  int runGame = true;
  
      //Game Loop
  while(runGame)
  {
      //Initialize The Deck
    vector<card> newDeck = makeDeck(numDecks);
    //printDeck(newDeck); //Uncomment to print the deck contents for testing
    shuffleDeck (newDeck); //Shuffle The Deck
    
    for(int i = 0; i < numPlayers; i++)
    {
      cout << endl << "Place your bet, player " << (i + 1) << ": $";
      cin >> betArr[i];
    }
    cout << endl;
    
      //Initialize the player'(s) hands
    vector<vector<card>> playerHands;
    playerHands.resize(numPlayers);
    
      //Initialize the dealer's hand
    vector<card> dealerHand;
    dealCard(newDeck, dealerHand);
    cout << endl << "The dealer has an ";
    printDeck(dealerHand);
    cout << "and one face-down card." << endl;
    dealCard(newDeck, dealerHand);
    
      //Deal Player Cards
    for(int i = 0; i < numPlayers; i++)
    {
      dealCard(newDeck, playerHands[i]);
      dealCard(newDeck, playerHands[i]);
      
        //Check Blackjack
      if(score(playerHands[i]) == 21)
      {
        printDeck(playerHands[i]);
        cout << "Player " << (i + 1) << ", you have Blackjack!";
      }

        //Hit Player
      int hitMe = true;
      while(score(playerHands[i]) < 21 && hitMe)
      {
        cout << endl << "Player " << (i + 1) << ", you have:" << endl;
        printDeck(playerHands[i]);
        cout << "Score: " << score(playerHands[i]) << endl;
        cout << endl << "Do you want to hit? (y/n)" << endl;
        string pChoice;
        cin >> pChoice;
        if(pChoice[0] == 'y' || pChoice[0] == 'Y') //Ya, yeah, yes, yop, yee, or y/Y.
        {
          dealCard(newDeck,playerHands[i]);
          
          //Check Player Hand
          if(score(playerHands[i]) == 21)
          {
            cout << endl << "Player " << (i + 1) << ", you have:" << endl;
            printDeck(playerHands[i]);
            cout << "Score: " << score(playerHands[i]) << endl;
            cout << "Player " << (i + 1) << ", you have Blackjack!" << endl;
          }
          else if(score(playerHands[i]) > 21)
          {
            cout << endl << "Player " << (i + 1) << ", you have:" << endl;
            printDeck(playerHands[i]);
            cout << "Score: " << score(playerHands[i]) << endl;
            cout << "Player " << (i + 1) << " has gone bust!" << endl;
          }
        }
        else //Move to the next iteration of the loop
        {
          hitMe = false;
        }
       }//End of Score While
    }//End of For Players
      
      //Hit Dealer
    int dealerSum = score(dealerHand);
    while (dealerSum < 16){
      dealCard(newDeck, dealerHand);
      dealerSum = score(dealerHand);
    }//End of While dealerSum
      
      //Show Dealer Hand
    cout << endl << "The dealer has:" << endl;
    printDeck(dealerHand);
    cout << "Dealer's score is " << score(dealerHand) << endl << endl;
    
      //Check Dealer Hand
    if(score(dealerHand) > 21)
    {
      cout << "The dealer has gone bust!" << endl << endl;
    }
    else if (score(dealerHand) == 21)
    {
      cout << "The dealer has Blackjack!" << endl << endl;
    }
    
      //Determine Winner
    for(int i = 0; i < numPlayers; i++)
    {
      cout << "Player " << (i + 1) << "'s score is " << score(playerHands[i]) << endl;
      if (isWinner(dealerHand, playerHands[i]) == true)
      {
        cout << "Player " << (i + 1) << " wins against the house!" << endl;
        cout << "Their total winnings are $" << (betArr[i] * 1.5) << "!" << endl << endl;
      }
      else
      { 
        cout << "The house wins against player " << (i + 1) << "!" << endl;
        cout << "Their total losses are $" << (betArr[i]) << endl << endl;
      }
    }
    //================REPLAY?=================//
    cout << "Do you want to play again? (y/n)";
    string pChoice;
    cin >> pChoice;
    if(pChoice[0] == 'y' || pChoice[0] == 'Y')
    {
      //Continues
    }
    else
    {
     runGame = false; 
    }
  }
  cout << "Thank you, come again!";
  return 0;
} //End of Main



