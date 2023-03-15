#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <memory>

std::string& toLowerCase(std::string& str);

class Option {
public:
    std::string_view getName;
    std::string_view getStrongOpp;
    std::string_view getWeakOpp;

    Option(std::string_view name, std::string_view strong, std::string_view weak):
    getName(name), getStrongOpp(strong), getWeakOpp(weak) {}

    /** @param scores Array that keeps the scores. First pointer is the user's score, second is the computer's */
    void announceWinner(int* scores, int no) {
        switch(no) {
            case 0:
                scores[0]++;
                std::cout<< "The computer chose " << getWeakOpp << ". You won!" <<'\n';
                break;
            case 1:
                std::cout<< "The computer chose " << getName << ". Tie." <<'\n';
                break;
            case 2:
                scores[1]++;
                std::cout<< "The computer chose " << getStrongOpp << ". You lost!" <<'\n';
                break;
            default:
                std::cerr << "Random function returned an out of bound value" <<'\n';
        }
    }
    virtual ~Option() = default;
};

std::unique_ptr<Option> tasnif(std::string& str);

class Rock : public Option {
public:
    Rock(): Option("Rock", "Paper", "Scissors") {}
};

class Paper : public Option {
public:
    Paper(): Option("Paper", "Scissors", "Rock") {}
};

class Scissors : public Option {
public:
    Scissors(): Option("Scissors", "Rock", "Paper") {}
};

int main() {
    std::cout<< "Choose [Rock/r], [Paper/p] or [Scissors/s]: ";
    std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution rast(0,2);
    std::string str;
    int scores[2]{0,0};
    while(true) {
        std::cin >> str;
        std::unique_ptr<Option> secim = tasnif(toLowerCase(str));
        if (secim) {
            std::cout<<" ----------------------------------------------------------"<<'\n';
            std::cout << " Your choice was: " << secim->getName << ". ";
            secim->announceWinner(scores, rast(rnd));
            std::cout<<  " -----------------> YOU: " << scores[0] << " | " << scores[1] << " :COMPUTER <-----------------" <<'\n';
        } else {
            std::cerr << "Unknown parameter. Try again\n";
        }
    }

    return 0;
}

std::string& toLowerCase(std::string &str) {
    for(char& letter : str) {
        if(65<=letter && letter <=90) {
            letter+=32;
        }
    }
    return str;
}

std::unique_ptr<Option> tasnif(std::string &str) {
    if(str=="rock" || str=="r") {
        return std::make_unique<Rock>();
    } else if(str=="paper" || str=="p") {
        return std::make_unique<Paper>();
    } else if(str=="scissors" || str=="s") {
        return std::make_unique<Scissors>();
    } else {
        return nullptr;
    }
}
