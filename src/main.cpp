#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include<cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <atomic>
#include <conio.h>
#include <filesystem>




using namespace std;
namespace fs = std::filesystem;

atomic<bool> timerStarted(false);
atomic<bool> timesUp(false);

//Countdown timer thread
void startTimer(int duration) {
    int remaining = duration;
    while (remaining> 0 && !timesUp)
    {
        if (timerStarted){
           // cerr << "\rTime left: " << remaining << " seconds";
            this_thread::sleep_for(chrono::seconds(1));
            remaining--;
        }
        else{
            this_thread::sleep_for(chrono::milliseconds(100)); // wait for user to start typing
        }
    }
    
    timesUp = true;
    cerr << "\nTime's up!" << endl;
}


//split test paragraphs by blank lines 
vector<string> loadParagraphs (const string& filename){
    ifstream file(filename);
    vector<string> paragraphs;
    string line, paragraph;

    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return paragraphs;
    }

    while (getline(file, line)) {
        if (line.empty()) {
            if (!paragraph.empty()) {
                paragraphs.push_back(paragraph);
                paragraph.clear();
            }
        } else {
            if (!paragraph.empty()) {
                paragraph += "\n";
            }
            paragraph += line;
        }
    }

    if (!paragraph.empty()) {
        paragraphs.push_back(paragraph);
    }
    file.close();
    return paragraphs;
    
}

//accuracy calculation
double calculateAccuracy(const string& original, const string& typed) {
    if (typed.empty()) return 0.0;
    
    int correct = 0;
    int minLength = min(original.length(), typed.length());
    
    for (int i = 0; i < minLength; i++) {
        if (original[i] == typed[i]) {
            correct++;
        }
    }
    
    return (double(correct) / typed.length()) * 100.0;
}


int main() {
    srand(time(0)); 
    fs::path filePath = fs::path(__FILE__).parent_path() / "../testParagraphs/paragraphs.txt";
    vector<string> paragraphs = loadParagraphs(filePath.string());

    if (paragraphs.empty()) {
        cerr << "No paragraphs found in the file." << endl;
        return 1;
    }

    int randomIndex = rand() % paragraphs.size();
    string randomParagraph = paragraphs[randomIndex];
    string userInput;      
    
    cout << "Type the following paragraph as fast as you can:\n" << randomParagraph << endl;
    cout << "Start typing below. Timer will start when you begin typing...\n\n";


    thread timerThread(startTimer, 10); // Start a 10 second timer
    

    // Wait until user presses any key
    while (!_kbhit()) {
        this_thread::sleep_for(chrono::milliseconds(10));
    }
    timerStarted = true; 

    while(!timesUp && userInput.length() < randomParagraph.length()) {
       if (_kbhit()) {
        char ch = _getch();

        if (ch == 8) { // Backspace key
            if (!userInput.empty()) {
                userInput.pop_back(); // Remove last character

                // Move cursor back, overwrite with space, then move back again
                cout << "\b \b";
            }
        } else {
            cout << ch;
            userInput += ch;
        }
    }
    this_thread::sleep_for(chrono::milliseconds(10));
    }

    timesUp = true; 
    timerThread.join(); 

    cout << "You typed: " << userInput << endl;
    return 0;
}
