#include <iostream>   // Include iostream for input/output operations.
#include <cstdlib>    // Include cstdlib for system functions like clearing the screen.
#include <ctime>      // Include ctime for random number seeding.
using namespace std;  // Use the standard namespace to avoid prefixing std:: before standard functions.

enum enChoice {Stone = 1 , Paper = 2 , Scissors = 3};
enum enWinner {Player1 = 1 , Computer = 2 , Draw = 3};

struct stRoundInfo {
    int RoundNumber;
    enChoice Player1Choice;
    enChoice Computer1Choice;
    enChoice Draw;
    enWinner WinnerRound;
    string WinnerName;
};

struct stGameResult {
    int RoundsNumber;
    int CounterPlayer1Win;
    int CounterComputer1Win;
    int CounterDrawTimes;
    enWinner WinnerGame;
    string WinnerName;
};

int RandomNumber(int From , int To){
    return rand() % (To - From + 1) + From;
}

int ReadHowManyRounds(){
    int number;

    do {

        cout << "How Many Rounds 1 to 10 ?\n";
        cin >> number;

    } while(number > 10 || number < 1 );

    return number;
}

enChoice ReadChoicePlayer1(int GameRound){
    short Choice;

    do{

        cout << "Round [" << GameRound << "] begins: \n";
        cout << "Your Choice: [1]:Stone, [2]:Paper, [3]:Scissors ? ";
        cin >> Choice;
        
    } while(Choice > 3 || Choice < 1);

    return (enChoice)Choice;
}

enChoice GetChoiceComputer2(int GameRound){
    return (enChoice)RandomNumber(1, 3);
}

enWinner WhosWinInThisRound(stRoundInfo RoundResult){

    if(RoundResult.Player1Choice == RoundResult.Computer1Choice){
        return enWinner::Draw;
    }

    switch(RoundResult.Player1Choice){
        case enChoice::Stone:
            if(RoundResult.Computer1Choice == enChoice::Paper){
                return enWinner::Computer;
            }
            break;
        case enChoice::Paper:
            if(RoundResult.Computer1Choice == enChoice::Scissors){
                return enWinner::Computer;
            }
            break;
        case enChoice::Scissors:
            if(RoundResult.Computer1Choice == enChoice::Stone){
                return enWinner::Computer;
            }
            break;
    }

    return enWinner::Player1;
}

string GetWinnerName(enWinner TheWinner){

    string ArrayOfWinners[3] = {"Player1" , "Computer" , "Draw"};
    return ArrayOfWinners[TheWinner - 1];

}

string GetChoice(enChoice Choice){
    string ArrayOfChoice[3] = {"Stone" , "Paper" , "Scissors"};
    return ArrayOfChoice[Choice - 1];
}




void PrintResultOfRound(stRoundInfo RoundResult){

    cout << "-------------------- Round[" << RoundResult.RoundNumber << "] --------------------" << endl;
    cout << "Player1  Choice: " << GetChoice(RoundResult.Player1Choice) << endl;
    cout << "Computer Choice: " << GetChoice(RoundResult.Computer1Choice) << endl;
    cout << "Round Winner   : " << "[" << RoundResult.WinnerName << "]" << endl;
    cout << "---------------------------------------------------" << endl;

}

enWinner WhosWinInGame(stGameResult GameResult){

    if(GameResult.CounterPlayer1Win == GameResult.CounterComputer1Win){

        return enWinner::Draw;

    } else if (GameResult.CounterPlayer1Win < GameResult.CounterComputer1Win){

        return enWinner::Computer;

    } else {

        return enWinner::Player1;

    }


}

stGameResult FillGameResult(int HowManyRounds , int CounterPlayer1Win , int CounterComputer1Win , int DrawTimes){
    stGameResult GameResult;
    
    GameResult.RoundsNumber = HowManyRounds;
    GameResult.CounterPlayer1Win = CounterPlayer1Win;
    GameResult.CounterComputer1Win = CounterComputer1Win;
    GameResult.CounterDrawTimes = DrawTimes;
    GameResult.WinnerGame = WhosWinInGame(GameResult);
    GameResult.WinnerName = GetWinnerName(GameResult.WinnerGame);

    return GameResult;
}

void ColorizeScreen(enWinner Winner){
    if(Winner == enWinner::Player1){
        system("Color 2F");
    } else if(Winner == enWinner::Computer){
        cout << "\a\n";
        system("Color 4F");
    } else {
        system("Color 6F");
    }
}

stGameResult playGame(int HowManyRounds){
    stRoundInfo RoundResult;

    int CounterPlayer1Win = 0 , CounterComputer1Win = 0 , DrawTimes = 0;

    for(int GameRound = 1 ; GameRound <= HowManyRounds ; GameRound++){

        RoundResult.RoundNumber = GameRound;
        RoundResult.Player1Choice = ReadChoicePlayer1(GameRound);
        RoundResult.Computer1Choice = GetChoiceComputer2(GameRound);
        RoundResult.WinnerRound = WhosWinInThisRound(RoundResult);
        RoundResult.WinnerName = GetWinnerName(RoundResult.WinnerRound);

        // Increase The Win/Draw 
        if(RoundResult.WinnerRound == enWinner::Draw){
            DrawTimes++;
        } else if(RoundResult.WinnerRound == enWinner::Computer){
            CounterComputer1Win++;
        } else {
            CounterPlayer1Win++;
        }

        ColorizeScreen(RoundResult.WinnerRound);

        PrintResultOfRound(RoundResult);
    }

    return FillGameResult(HowManyRounds , CounterPlayer1Win , CounterComputer1Win , DrawTimes );
    

}

string Tabs(int NumberOfTabs){
    string t = "";

    for(int i = 0 ; i < NumberOfTabs ; i++){

        t += "\t";

    }

    return t;
}


void ShowGameOverScreen(){
    cout << Tabs(2) << "----------------------------------------------------------------------------------\n";
    cout << Tabs(2) << "                           +++ G a m e O v e r +++\n";
    cout << Tabs(2) << "----------------------------------------------------------------------------------\n";
}


void PrintGameResult(stGameResult GameResult){
    cout << Tabs(2) << "--------------------------------- [Game Results] ---------------------------------\n";
    cout << Tabs(2) << "Game Rounds             : " << GameResult.RoundsNumber << endl;
    cout << Tabs(2) << "Player1 Won Times       : " << GameResult.CounterPlayer1Win << endl;
    cout << Tabs(2) << "Computer Won Times      : " << GameResult.CounterComputer1Win << endl;
    cout << Tabs(2) << "Draw Times              : " << GameResult.CounterDrawTimes << endl;
    cout << Tabs(2) << "Final Winer             : " << GameResult.WinnerName << endl; 
    cout << Tabs(2) << "---------------------------------------------------------------------------------------\n"; 
}

void ResetScreen(){
    system("cls");
    system("Color 0F");
}

void startGame(){

    string PlayAgain = "Y";

    do{
        ResetScreen();
        int HowManyRounds = ReadHowManyRounds();
        stGameResult GameResult = playGame(HowManyRounds);
        ShowGameOverScreen();
        PrintGameResult(GameResult);
        ColorizeScreen(GameResult.WinnerGame);

    
        cout << "Do you want to play again? Y/N? ";
        cin >> PlayAgain;

    } while(PlayAgain == "Y" || PlayAgain == "y");

}

int main(){
    srand((unsigned)time(NULL));

    startGame();
}