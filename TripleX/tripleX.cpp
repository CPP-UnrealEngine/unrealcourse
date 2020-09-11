#include <iostream>
#include <ctime>
#include <string>
#include <vector>




const std::vector<std::vector<std::string>> riddle = {
    {"Hello Folks, here my first riddle is. Gollum knows you not smart. Better it is you don't event try\n This number is 10 at sum\n this number is 24 if you multiple all\nWhat is it you say?","2 2 6"},
    {"Well well, you not that dumb as i fought. We'll see...\n This number is 27 if you multiple all\n This number is 9 at sum\nWhat is it you say?","3 3 3"},
    {"Fancy smart Hobbitses do know there math well. Quick maths. This is going to be a hard one\nIt's the holy Triangle\nEach side Counts\nThere are three of them...and all the same\nWhat is it you say?","3 3 3"},
};


std::string getRiddleText(int level){
    return riddle[level][0];
}
std::string getRiddleResult(int level){
    return riddle[level][1];
}
bool isCorrect(std::string secret, std::string input){
    if(secret.length() != input.length()){
        return false;
    }
    std::string::iterator inputIterator = input.begin();
    for(std::string::iterator secretIterator = secret.begin(); secretIterator != secret.end(); ++secretIterator, ++inputIterator){
            if (*secretIterator != *inputIterator)
            {
                return false;
            }
    }
    return true;
}
int main(int argc, char* argv){
    bool isWin = true;
    for( int level = 0; level < riddle.size(); ++level){
        std::cout << getRiddleText(level) << std::endl;
        std::string input; 
        std::getline(std::cin, input);

        //std::cin.clear();
        //std::cin.ignore();
        //
        if(!isCorrect(getRiddleResult(level), input)){
            std::cout << "You Failed. Gollum bites you. Your death is painful and without glory"<< std::endl;
            isWin = false;
            break;
        }
        else{
            std::cout << "Well Thought. Let's dive further into the cave, I'll show you da way...yes...yes" << std::endl;
        }
    }
    if(isWin){
        std::cout << "here we are... the way to mordor nasty...uhm nice hobbitses...\nSmeagol jumps looks at you with hopeful eyes and jumps in a circle\nSmeagol might find peace\n" << std::endl;
    }
    
    return 0;
}

