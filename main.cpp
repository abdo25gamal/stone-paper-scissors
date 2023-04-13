#include <iostream>
#include <cstdlib>
using namespace std;

enum enGameChoice 
{
        Stone = 1, 
        Paper = 2, 
        Scissors = 3
};

enum enWinner 
{
        Player1 = 1, 
        Computer = 2, 
        Draw = 3
};

struct stRoundInfo 
{
        short RoundNumber = 0;
        enGameChoice Player1Choice;
        enGameChoice ComputerChoice;
        enWinner Winner;
        string WinnerName;
};

struct stGameResults
{
       short GameRounds = 0;
       short Player1WinTimes = 0;
       short Computer2WinTimes = 0;
       short DrawTimes = 0;
       enWinner GameWinner;
       string WinnerName = "";
};

int ReadNumber(string Message)
{
        cout << Message << endl;
        int Number = 0;
        cin >> Number;
        while(cin.fail())
        {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                cout << "Invalid Number, " << Message << endl;
                cin >> Number;
        }
        return Number;
}

int ReadNumberInRange(int From, int To,string Message)
{
        int Number = ReadNumber(Message);
        while(Number < From || Number > To)
        {
                Number = ReadNumber(Message);
        }
        return Number;
}

int RandomNumber(int From, int To)
{
        return rand() % (To - From + 1)  + From;
}

string Tabs(short NumberOfTabs)
{
        string t = "";

        for(short i = 1; i < NumberOfTabs; ++i)
        {
                t += "\t"; 
                cout << t;
        }
        return t;
}

string WinnerName(enWinner Winner)
{
        string arrWinnerName[] = {"Player1" , "Computer", "No Winner"};
        return arrWinnerName[Winner - 1];
}

string ChoiceName(enGameChoice Choice)
{
        string arrGameChoice[3] = {"Stone", "Paper", "Scissors"};
        return arrGameChoice[Choice - 1];
}

enGameChoice ReadPlayer1Choice()
{
        return (enGameChoice) ReadNumberInRange(1,3,"Your Choice: [1]:Stone [2]:Paper [3]:Scissors");
}

enGameChoice GetComputerChoice()
{
        return (enGameChoice) RandomNumber(1,3);
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
        if(RoundInfo.Player1Choice == RoundInfo.ComputerChoice) {return enWinner::Draw;}

        switch (RoundInfo.Player1Choice)
        {
        case enGameChoice::Stone : 
        if(RoundInfo.ComputerChoice == enGameChoice::Paper){return enWinner::Computer;} 
        break;

        case enGameChoice::Paper : 
        if(RoundInfo.ComputerChoice == enGameChoice::Scissors){return enWinner::Computer;} 
        break;

        case enGameChoice::Scissors : 
        if(RoundInfo.ComputerChoice == enGameChoice::Stone){return enWinner::Computer;} 
        break;
        }

        return enWinner::Player1;
}

enWinner WhoWonTheGame(short Player1WinTimes, short ComputerWinTimes)
{
        if(Player1WinTimes > ComputerWinTimes){return enWinner::Player1;}
        else if(ComputerWinTimes > Player1WinTimes){return enWinner::Computer;}
        else {return enWinner::Draw;}
}

stGameResults FillGameResult(int GameRounds, short Player1WinTimes, short ComputerWinTimes, short DrawTimes)
{
        stGameResults GameResult;
        GameResult.GameRounds = GameRounds;
        GameResult.Player1WinTimes = Player1WinTimes;
        GameResult.Computer2WinTimes = ComputerWinTimes;
        GameResult.GameWinner = WhoWonTheGame(Player1WinTimes,ComputerWinTimes);
        GameResult.WinnerName = WinnerName(GameResult.GameWinner);
        return GameResult;
}

void SetWinnerScreenColor(enWinner Winner)
{
        switch (Winner)
        {
        case enWinner::Player1  : system("color 2F");               break;
        case enWinner::Computer : system("color 4F"); cout << "\a"; break;
        default                 : system("color 6F");               break;
        }
}

void PrintRoundInfo(stRoundInfo RoundInfo)
{
        cout << "________________Round [" << RoundInfo.RoundNumber << "]____________________\n\n";
        cout << "Player1  Choice  : " << ChoiceName(RoundInfo.Player1Choice) << endl;
        cout << "Computer Choice  : " << ChoiceName(RoundInfo.ComputerChoice) << endl;
        cout << "Round Winner     : [" << RoundInfo.WinnerName << "] \n";

        SetWinnerScreenColor(RoundInfo.Winner);
}

stGameResults PlayGame()
{
        short HowManyRounds = ReadNumberInRange(1,10,"How Many Rounds 1 to 10 ?");

        stRoundInfo RoundInfo;
        short Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

        for (short GameRound = 1; GameRound <= HowManyRounds; ++GameRound)
        {
                cout << "\n\n\nRound [" << GameRound << "] begines: \n";
                
                RoundInfo.RoundNumber    = GameRound;
                RoundInfo.Player1Choice  = ReadPlayer1Choice();
                RoundInfo.ComputerChoice = GetComputerChoice();
                RoundInfo.Winner         = WhoWonTheRound(RoundInfo);
                RoundInfo.WinnerName     = WinnerName(RoundInfo.Winner);

                if(RoundInfo.Winner == enWinner::Player1){++Player1WinTimes;}
                else if(RoundInfo.Winner == enWinner::Computer){++ComputerWinTimes;}
                else {++DrawTimes;}

                PrintRoundInfo(RoundInfo);
        }
        return FillGameResult(HowManyRounds,Player1WinTimes,ComputerWinTimes,DrawTimes);
}

void ShowGameOverScreen()
{
        cout << "\n\n";
        cout << Tabs(2) <<  "____________________________________________________\n";
        cout << Tabs(2) <<  "                ++Game Over++                       \n";
        cout << Tabs(2) <<  "____________________________________________________\n";
}

void ResetScreen()
{
        system("cls");
        system("color 0F");
}

void ShowFinalGameResult(stGameResults GameResults)
{
        cout << "\n\n";
        cout << Tabs(2) << "_______________[Game Results]_______________________\n\n";
        cout << Tabs(2) << "Game Rounds        : " << GameResults.GameRounds << endl;
        cout << Tabs(2) << "Player1  won times : " << GameResults.Player1WinTimes << endl;
        cout << Tabs(2) << "Computer won times : " << GameResults.Computer2WinTimes << endl;
        cout << Tabs(2) << "Draw times         : " << GameResults.DrawTimes << endl;
        cout << Tabs(2) << "Final Winner       : " << GameResults.WinnerName << endl;
        cout << Tabs(2) << "______________________________________________\n\n";

        SetWinnerScreenColor(GameResults.GameWinner);
}

void StartGame()
{
      char PlayAgain = 'Y';
      do
      {
        ResetScreen();
        stGameResults GameResult = PlayGame();
        ShowGameOverScreen();
        ShowFinalGameResult(GameResult);

        cout << endl << Tabs(3) << "Do you want to play again Y/N? ";
        cin >> PlayAgain; 

      } while (PlayAgain == 'Y' || PlayAgain == 'y');
}


int main()
{
        srand((unsigned)time(NULL));
        StartGame();
        return 0; 
}


