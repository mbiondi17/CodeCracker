#include <iostream>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <string>
#include <math.h>

bool PlayGameAtDifficulty(int Difficulty);
int LoadSaveGame();
void PrintIntro(int Level, int MaxLevel);
void HandleExit(int Level, int MaxLevel);

std::string LevelCodes [10] = {
    "Kodiak",
    "Cheetah",
    "Puma",
    "Jaguar",
    "Panther",
    "Tiger",
    "Leopard",
    "Snow Leopard",
    "Lion",
    "Mountain Lion"       
};

int main(void) {
    
    int MaxLevel = 10;
    int Level = LoadSaveGame();
    PrintIntro(Level, MaxLevel);    
    srand(time(NULL));

    while(Level <= MaxLevel) {
        
        bool WonLevel = PlayGameAtDifficulty(Level);
        if(WonLevel) {
            Level++;         
            if(Level <= MaxLevel) {
                std::cout << "Well done! You may cross this bridge. Best of luck, brave hero, on what remains of your quest!" << std::endl;
            }
            else break;
        }
        else {
            std::cout << "You have failed your quest, and the bridgekeeper has thrown you from the cliff to" << std::endl;
            std::cout << " your inevitable doom. You must restart from the beginning of your journey." << std::endl;
            Level = 1;
        }

        std::string Answer = "";

        std::cout << "Keep playing? Your progress will be saved if you quit. (y/n)" << std::endl;
        std::cin >> Answer;

        std::size_t indexOfYes = Answer.find('y');
        if(indexOfYes == std::string::npos) {
            break;
        }
        
        std::cin.clear();
        std::cin.ignore(); //discards the buffer        
    }
    
    HandleExit(Level, MaxLevel);
    return 0;
}

bool PlayGameAtDifficulty(int Difficulty) {
    bool GuessCorrect = false;
    int GuessNumber = 0;
    int MaxGuesses = 3;

    int CodeA, CodeB, CodeC;
    int CodeSum, CodeProduct;
    int GuessA, GuessB, GuessC;
    int GuessSum, GuessProduct;

    CodeA = rand() % (2 * Difficulty) + Difficulty;
    CodeB = rand() % (2 * Difficulty) + Difficulty;
    CodeC = rand() % (2 * Difficulty) + Difficulty;
    CodeSum = CodeA + CodeB + CodeC;
    CodeProduct = CodeA * CodeB * CodeC;

    while(GuessNumber < MaxGuesses && GuessCorrect == false) {
        std::cout << std::endl << std::endl << std::endl;
        std::cout << "Welcome, traveller, to bridge number " << Difficulty << "!\n";
        std::cout << "Shouldst thou wish to proceed, three numbers thou must guess." << std::endl;
        std::cout << "Added together, their sum is neither smaller nor greater than " << CodeSum << std::endl;
        std::cout << "Multiply the first, by the second, by the third, and thou art sure to get " << CodeProduct << std::endl;
        std::cout << "Enter your guess in the format: A B C, with each letter replaced by one number of your guess." << std::endl;

        std::cin >> GuessA >> GuessB >> GuessC;

        GuessSum = GuessA + GuessB + GuessC;
        GuessProduct = GuessA * GuessB * GuessC;

        if(GuessSum == CodeSum && GuessProduct == CodeProduct) {
            GuessCorrect = true;
        }
        else {
            GuessNumber++;
            std::cout << "Alas, that is not correct. Think carefully, adventurer. You have but " << MaxGuesses - GuessNumber << " attempts" << std::endl;
            std::cout << "remaining. You seem a decent fellow; I hate to kill you.";
        }
    }
    return GuessCorrect;
} 

int LoadSaveGame() {
    int LevelToLoad;
    std::ifstream SaveGameStream("save.txt");
    if(SaveGameStream.is_open()) {
        std::string LevelCode;
        getline(SaveGameStream,LevelCode);
        LevelToLoad = std::distance(LevelCodes, std::find(LevelCodes, LevelCodes + 10, LevelCode)) + 1;
    }
    else {
        LevelToLoad = 1;
    }
    return LevelToLoad;
}

void PrintIntro(int Level, int MaxLevel) {
    if(Level > MaxLevel) {
        std::string Answer = "";
        std::cout << "My, my! It seems you have already completed this challenge, hero! would you like to play again? y/n" << std::endl;
        std::cin >> Answer;

        std::size_t indexOfYes = Answer.find('y');
        if(indexOfYes != std::string::npos) {
            Level = 1;
            remove("save.txt");
        }
        else exit(0);
    } 
    if(Level == 1) {
        std::cout << "Welcome, adventurer! You seek the Grail, I know. How do I know? I'm a" << std::endl;
        std::cout << "Bridgekeeper! That's what I do; I know things. You can call me Tim." << std::endl << std::endl;
        std::cout << "In order to obtain the Grail, you must pass these ten bridges, each of which" << std::endl;
        std::cout << "present you with a puzzle you must solve in three attempts. Should you" << std::endl;
        std::cout << "fail one of these challenges, you'll be hurled to your death. Sorry." << std::endl << std::endl;
        std::cout << "Remember: After any bridge, you can take a break, and you'll be able to pick" << std::endl;
        std::cout << "up where you left off when you return to your quest." << std::endl;
    }
    else {
        std::cout << "Welcome back, brave one! You are ready to cross bridge number " << Level << "! Steel yourself for what may come." << std::endl;
    }

}

void HandleExit(int Level, int MaxLevel) {
    if(Level > MaxLevel) {
        std::cout << "Well met, hero! You have crossed all 10 bridges, and may take possession of the most Holy Grail!" << std::endl << std::endl << std::endl;
           
        std::cout << " |o^o^o^o^o|  " << std::endl;
        std::cout << " {   _!_   }  " << std::endl;
        std::cout << "  \\   !   /  " << std::endl;
        std::cout << "   `.   .'    " << std::endl;
        std::cout << "     )=(      " << std::endl;
        std::cout << "    ( + )     " << std::endl;
        std::cout << "     ) (      " << std::endl;
        std::cout << " .--'   `--.  " << std::endl;
        std::cout << " `---------'  " << std::endl << std::endl << std::endl;
    }
    else {
        std::cout << "Your progress is admirable! I eagerly await your triumphant return to claim the Grail!" << std::endl;
        
        std::ofstream SaveFile ("save.txt", std::ofstream::out | std::ofstream::trunc);
        if(SaveFile.is_open()) {
            SaveFile << LevelCodes[Level-1];
            SaveFile.close();
        }
        else std::cout << "Unable to open file :(" << std::endl;
    }
}
