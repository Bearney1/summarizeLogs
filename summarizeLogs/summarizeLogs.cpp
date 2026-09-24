

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

vector<string> split(string line, char symbol) {
    vector<string> result;
    string element;
    stringstream ss(line);
    while (getline(ss, element, symbol)) {
        result.push_back(element);
    }

    return result;
}

class Logs
{
public:
    struct typeOfData {
        int ERROR;
        int INFO;
        int WARNING;

    } summary;

    vector<string> accessLogs(string filename);
    int getNumberOfLogs();
    void analizeLogs();
    void showSummary();
private:

    

    vector<string> logs;
    string timeSpan;

    bool isAccessed = false;

};

vector<string> Logs::accessLogs(string filename) {
    if (isAccessed) { logs.clear(); isAccessed = false; };

    fstream file;
    file.open(filename);

    string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            logs.push_back(line);

         
        }

        file.close();
        
        isAccessed = true;
        return logs;
    }
    else {
        cerr << "Unable to open a file" << endl;
        return logs;
    }
}
int Logs::getNumberOfLogs() {
    return logs.size();
}
void Logs::analizeLogs() {
    summary = { 0, 0, 0 };

    timeSpan = logs[0].substr(0, 19) + " - " + logs[logs.size()-1].substr(0, 19);
    for (string line : logs) {
        vector<string> elements = split(line, ';');

        if (elements[1] == "ERROR") summary.ERROR++;
        if (elements[1] == "INFO") summary.INFO++;
        if (elements[1] == "WARNING") summary.WARNING++;

    }



};
void Logs::showSummary() {
    cout << "Wyniki przeprowadzonego podsumowania" << endl;
    cout << "\tIlosc zgloszen: " << logs.size() << endl << endl;
    cout << "\tPrzedzial czasowy: " << timeSpan << endl;
    cout << "\tIlosc zgloszen oznaczonych 'ERROR': " << summary.ERROR << endl;
    cout << "\tIlosc zgloszen oznaczonych 'INFO': " << summary.INFO << endl;
    cout << "\tIlosc zgloszen oznaczonych 'WARNING': " << summary.WARNING << endl;
    cout << "Koniec podsumowania" << endl;
}
int main()
{
    string filename = "C:\\Users\\lukas\\Documents\\projekty\\dummyData\\logs.txt";

    Logs log1;
    log1.accessLogs(filename);
    log1.analizeLogs();
    log1.showSummary();
}

