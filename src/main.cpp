#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <atomic>
#include <conio.h>
#include <filesystem>
#include <iomanip>

using namespace std;
namespace fs = std::filesystem;

// ANSI escape codes for colors
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

atomic<bool> timerStarted(false);
atomic<bool> timesUp(false);

// Countdown timer
void startTimer(int duration) {
    int remaining = duration;
    while (remaining > 0 && !timesUp) {
        if (timerStarted) {
            // cerr << "\r" << YELLOW << "⏳ Time left: " << remaining << "s " << RESET;
            this_thread::sleep_for(chrono::seconds(1));
            remaining--;
        } else {
            this_thread::sleep_for(chrono::milliseconds(100));
        }
    }

    timesUp = true;
    cerr << "\n" << RED << "⏰ Time's up!" << RESET << endl;
}

// Load paragraphs from file
vector<string> loadParagraphs(const string& filename) {
    ifstream file(filename);
    vector<string> paragraphs;
    string line, paragraph;

    if (!file.is_open()) {
        cerr << RED << "❌ Error opening file: " << filename << RESET << endl;
        return paragraphs;
    }

    while (getline(file, line)) {
        if (line.empty()) {
            if (!paragraph.empty()) {
                paragraphs.push_back(paragraph);
                paragraph.clear();
            }
        } else {
            if (!paragraph.empty()) paragraph += "\n";
            paragraph += line;
        }
    }

    if (!paragraph.empty()) paragraphs.push_back(paragraph);
    file.close();
    return paragraphs;
}

//break para in chunks
vector<string> splitIntoChunks(const string& text, size_t maxChunkLength = 80) {
    vector<string> chunks;
    size_t start = 0;
    while (start < text.length()) {
        size_t len = min(maxChunkLength, text.length() - start);
        chunks.push_back(text.substr(start, len));
        start += len;
    }
    return chunks;
}

//Accuracy calculation
double calculateAccuracy(const string& original, const string& typed) {
    if (typed.empty()) return 0.0;
    int correct = 0;
    int minLength = min(original.length(), typed.length());
    for (int i = 0; i < minLength; i++) {
        if (original[i] == typed[i]) correct++;
    }
    return (double(correct) / typed.length()) * 100.0;
}

//Gross WPM
double calculateWPM(const string& typed, double timeInSeconds) {
    if (typed.empty()) return 0.0;
    int characters = typed.length();
    double words = characters / 5.0;
    double minutes = timeInSeconds / 60.0;
    return words / minutes;
}

//Net WPM
double calculateNetWPM(const string& original, const string& typed, double timeInSeconds) {
    if (typed.empty()) return 0.0;
    int correct = 0;
    int minLength = min(original.length(), typed.length());
    for (int i = 0; i < minLength; i++) {
        if (original[i] == typed[i]) correct++;
    }
    double correctWords = correct / 5.0;
    double minutes = timeInSeconds / 60.0;
    return correctWords / minutes;
}

// Display Results
void displayResults(const string& original, const string& typed, double timeElapsed) {
    cout << "\n" << CYAN << string(30, '=') << RESET << endl;
    cout << BOLD << "📝 TYPING TEST RESULTS 📝" << RESET << endl;
    cout << CYAN << string(30, '=') << RESET << endl;

    cout << "📄 Characters typed     : " << typed.length() << endl;
    cout << "🎯 Target characters     : " << original.length() << endl;

    double accuracy = calculateAccuracy(original, typed);
    cout << "✅ Accuracy              : " << GREEN << fixed << setprecision(1) << accuracy << "%" << RESET << endl;

    double grossWPM = calculateWPM(typed, timeElapsed);
    double netWPM = calculateNetWPM(original, typed, timeElapsed);

    cout << "🚀 Gross WPM (standard) : " << YELLOW << fixed << setprecision(1) << grossWPM << RESET << endl;
    cout << "🧠 Net WPM (accuracy)   : " << YELLOW << fixed << setprecision(1) << netWPM << RESET << endl;


    cout << CYAN << string(30, '=') << RESET << endl;
}

int main() {
    srand(time(0));
    fs::path filePath = fs::path(__FILE__).parent_path() / "../testParagraphs/paragraphs.txt";
    vector<string> paragraphs = loadParagraphs(filePath.string());

    if (paragraphs.empty()) {
        cerr << RED << "⚠️ No paragraphs found in the file." << RESET << endl;
        return 1;
    }

    int randomIndex = rand() % paragraphs.size();
    string randomParagraph = paragraphs[randomIndex];

    // Split into chunks
    vector<string> chunks = splitIntoChunks(randomParagraph, 80);

    cout << BOLD << "\n📖 Typing Test - Chunk Mode Activated\n" << RESET;
    cout << CYAN << "💡 Type each chunk. Timer starts on first key press. You have 100 seconds.\n" << RESET;

    string allUserInput;
    string currentInput;

    size_t currentChunkIndex = 0;
    const string& firstChunk = chunks[currentChunkIndex];

    cout << YELLOW << "\n🧩 Chunk " << (currentChunkIndex + 1) << "/" << chunks.size() << ":" << RESET << endl;
    cout << CYAN << firstChunk << RESET << endl;

    thread timerThread(startTimer, 100); // 100-second timer

    // Wait for first key press before enabling input
    while (!_kbhit()) {
        this_thread::sleep_for(chrono::milliseconds(10));
    }
    timerStarted = true;

    // Main typing loop
    while (!timesUp && currentChunkIndex < chunks.size()) {
        const string& chunk = chunks[currentChunkIndex];
        currentInput.clear();

        while (!timesUp && currentInput.length() < chunk.length()) {
            if (_kbhit()) {
                char ch = _getch();

                if (ch == 8) { // Backspace
                    if (!currentInput.empty()) {
                        currentInput.pop_back();
                        cout << "\b \b";
                    }
                } else {
                    cout << ch << flush;
                    currentInput += ch;
                }
            }
            this_thread::sleep_for(chrono::milliseconds(10));
        }

        allUserInput += currentInput;
        currentChunkIndex++;

        // Display next chunk if time remains
        if (!timesUp && currentChunkIndex < chunks.size()) {
            const string& nextChunk = chunks[currentChunkIndex];
            cout << YELLOW << "\n\n🧩 Chunk " << (currentChunkIndex + 1) << "/" << chunks.size() << ":" << RESET << endl;
            cout << CYAN << nextChunk << RESET << endl;
        }
    }

    timesUp = true;
    timerThread.join();

    double timeElapsed = 100.0;

    // Only compare as much as user typed
    string trimmedOriginal = randomParagraph.substr(0, allUserInput.length());

    displayResults(randomParagraph, allUserInput, timeElapsed);
    return 0;
}
