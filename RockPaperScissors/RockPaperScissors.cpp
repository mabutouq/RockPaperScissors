
#include <iostream>
#include<cstdlib>
#include <ctime> 
using namespace std;

enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };
enum enWinner { Player = 1, Computer = 2, Draw = 3 };

struct stRoundInfo
{
    short RoundNumber = 0;          
    enGameChoice PlayerChoice;     
    enGameChoice ComputerChoice;    
    enWinner Winner;                
    string WinnerName;              
};
struct stGameResults
{
    short GameRounds = 0;        
    short PlayerWinTimes = 0;   
    short ComputerWinTimes = 0;  
    short DrawTimes = 0;         
    enWinner GameWinner;         
    string WinnerName = "";
};


int RandomNumber(int From, int To)
{
    int RandNum = rand() % (To - From + 1) + From;
    return RandNum;
}
string WinnerName(enWinner Winner)
{
    string arrWinner[3] = { "Player","Computer","No Winner" };
    return arrWinner[Winner - 1];

}
enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
    if (RoundInfo.ComputerChoice == RoundInfo.PlayerChoice)
        return enWinner::Draw;
    
    switch (RoundInfo.PlayerChoice)
    {
    case enGameChoice::Stone:
        if (RoundInfo.ComputerChoice == enGameChoice::Paper)
            return enWinner::Computer;
        break;
    case enGameChoice::Paper:
        if (RoundInfo.ComputerChoice == enGameChoice::Scissors)
            return enWinner::Computer;
        break;
    case enGameChoice::Scissors:
        if (RoundInfo.ComputerChoice == enGameChoice::Stone)
            return enWinner::Computer;
        break;
    }

    return enWinner::Player;
}
string ChoiceName(enGameChoice Choice)
{
    string arrChoiceName[3] = { "Stone","Paper","Scissors" };
    return arrChoiceName[Choice - 1];
}
void SetWinnerScreenColor(enWinner Winner)
{
    switch (Winner)
    {
    case enWinner::Player:
        system("color 2F");
        break;
    case enWinner::Computer:
        system("color 4F");
        cout << "\a";
        break;
    case enWinner::Draw:
        system("color 6F");
        cout << "\a";

        break;
    }
}
void PrintRoundResults(stRoundInfo RoundInfo)
{
    cout << "\n____________ Round [" << RoundInfo.RoundNumber << "] ____________\n\n";
    cout << "Player1 Choice: " << ChoiceName(RoundInfo.PlayerChoice) << endl;
    cout << "Computer Choice: " << ChoiceName(RoundInfo.ComputerChoice) << endl;
    cout << "Round Winner   : [" << RoundInfo.WinnerName << "]\n";
    cout << "_________________________________________\n" << endl;

    SetWinnerScreenColor(RoundInfo.Winner);

}
enWinner WhoWonTheGame(short PlayerWinTimes, short ComputerWinTimes)
{
    if (PlayerWinTimes > ComputerWinTimes)
        return enWinner::Player;
    else if (ComputerWinTimes > PlayerWinTimes)
        return enWinner::Computer;
    else
        return enWinner::Draw;

}
stGameResults FillGameResults(int GameRounds, short PlayerWinTimes, short ComputerWinTimes, short DrawTimes)
{
    stGameResults GameResults;

    GameResults.GameRounds = GameRounds;
    GameResults.PlayerWinTimes = PlayerWinTimes;
    GameResults.ComputerWinTimes = ComputerWinTimes;
    GameResults.DrawTimes = DrawTimes;
    GameResults.GameWinner = WhoWonTheGame(PlayerWinTimes, ComputerWinTimes);
    GameResults.WinnerName = WinnerName(GameResults.GameWinner);

    return GameResults;
}
enGameChoice ReadPlayerChoice()
{
    short Choice = 1;
    do
    {
        cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissors ? ";
        cin >> Choice;

    } while (Choice < 1 || Choice>3);

    return (enGameChoice)Choice;
}
enGameChoice ReadComputerChoice()
{
    return enGameChoice(RandomNumber(1, 3));
}
stGameResults PlayGame(short Rounds)
{
    stRoundInfo RoundInfo;
    short PlayerWinsTimes = 0, ComputerWinsTimes = 0, DrawTimes = 0;

    for (short GameRound = 1; GameRound <= Rounds; GameRound++)
    {
        cout << "\nRound [" << GameRound << "] begins:\n";
        RoundInfo.RoundNumber = GameRound;
        RoundInfo.PlayerChoice = ReadPlayerChoice();
        RoundInfo.ComputerChoice = ReadComputerChoice();
        RoundInfo.Winner = WhoWonTheRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

        if (RoundInfo.Winner == enWinner::Player)
            PlayerWinsTimes++;
        else if (RoundInfo.Winner == enWinner::Computer)
            ComputerWinsTimes++;
        else
            DrawTimes++;
        
        PrintRoundResults(RoundInfo);
    }

    return FillGameResults(Rounds, PlayerWinsTimes, ComputerWinsTimes, DrawTimes);

}
string Tabs(short NumberOfTabs)
{
    string t = "";
    for (int i = 1; i < NumberOfTabs; i++)
    {
        t = t + "\t";
        cout << t;
    }
    return t;

}
void ShowGameOverScreen()
{
    cout << Tabs(2) << "------------------------------------------------\n\n";
    cout << Tabs(2) << "                 +++ Game Over +++\n";
    cout << Tabs(2) << "------------------------------------------------\n\n";
}
void ShowFinalGameResults(stGameResults GameResults)
{
    cout << Tabs(2) << "-------------[Game Results]------------\n\n";
    cout << Tabs(2) << "Game Rounds       : " << GameResults.GameRounds << endl;
    cout << Tabs(2) << "Player won times  : " << GameResults.PlayerWinTimes << endl;
    cout << Tabs(2) << "Computer won times: " << GameResults.ComputerWinTimes << endl;
    cout << Tabs(2) << "Draw times        : " << GameResults.DrawTimes << endl;
    cout << Tabs(2) << "Final Winner      : " << GameResults.WinnerName << endl;
    cout << Tabs(2) << "--------------------------------------------------------------------\n";

    SetWinnerScreenColor(GameResults.GameWinner);
}
short ReadHowManyRounds()
{
    short GameRounds = 1;

    do
    {
        cout << "How Many Rounds 1 to 10 ?";
        cin >> GameRounds;
    } while (GameRounds < 1 || GameRounds>10);

    return GameRounds;
}
void ResetScreen()
{
    system("cls");
    system("color 0F");
}
void StartGame()
{
    char PlayAgain = 'Y';
    do
    {
        ResetScreen();
        stGameResults GameResults = PlayGame(ReadHowManyRounds());
        ShowGameOverScreen();
        ShowFinalGameResults(GameResults);
        cout << "\n" << "Do you want to play again? Y/N? ";
        cin >> PlayAgain;

    } while (PlayAgain == 'Y' || PlayAgain == 'y');


}
int main()
{
    srand((unsigned)time(NULL));

    StartGame();





    return 0;
}
