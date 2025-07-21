#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include<cstdlib>
#include <ctime>

using namespace std;

//split test paragraphs by blank lines 
vector<string> splitParagraphs (const string& filename){
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
    
    return 0;
}
