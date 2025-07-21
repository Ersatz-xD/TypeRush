#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include<cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <atomic>


using namespace std;

atomic<bool> timerStarted(false);
atomic<bool> timesUp(false);

//Countdown timer thread
void startTimer(int duration) {
    int remaining = duration;
    while (remaining> 0 && !timesUp)
    {
        if (timerStarted){
            cout << "\rTime left: " << remaining << " seconds";
            this_thread::sleep_for(chrono::seconds(1));
            remaining--;
        }
        else{
            this_thread::sleep_for(chrono::milliseconds(100)); // wait for user to start typing
        }
    }
    
    timesUp = true;
    cout << "\nTime's up!" << endl;
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




int main() {
    srand(time(0)); 
    vector<string> paragraphs = loadParagraphs("..\\testParagraphs\\paragraphs.txt");
    if (paragraphs.empty()) {
        cerr << "No paragraphs found in the file." << endl;
        return 1;
    }

    int randomIndex = rand() % paragraphs.size();
    string randomParagraph = paragraphs[randomIndex];      
    cout << "Randomly selected paragraph:\n" << randomParagraph << endl;    

    return 0;
}
