#include "header.h"
using namespace std;

vector<string> tokenize(const string& line) {
    vector<string> tokens;
    istringstream ss(line);
    string token;
    while (getline(ss, token, ',')) {
        tokens.push_back(token);
    }
    return tokens;
}

vector<string> unroll_loop(const string& path) {
    ifstream inputFile(path);
    ofstream outputFile("Unrolled_Unscheduled.txt");

    if (!inputFile.is_open() || !outputFile.is_open()) {
        cerr << "ERROR OPENING FILE" << endl;
        return {"Error"};
    }

    int instructionBlk = 0;
    vector<string> instructions, otherLines;
    set<string> floatingRegisters; // To store the floating register
    string line;

    while (getline(inputFile, line)) {
        transform(line.begin(), line.end(), line.begin(), ::toupper);
        if (line.empty()) {
            continue;
        }
        if (line.find("ADD.I") != string::npos || line.find("BNE") != string::npos || instructionBlk) { //if it finds ADD.I and BNE
            otherLines.push_back(line);
            instructionBlk = 1;
        } else {
            instructions.push_back(line);
        }
        istringstream ss(line);
        string token;
        while (getline(ss, token, ',')) {
            if (token[0] == 'F') {
                floatingRegisters.insert(token);
            }
        }
    }
    vector<string> floatvector(floatingRegisters.begin(), floatingRegisters.end());
    sort(floatvector.begin(), floatvector.end());
    int regis = 8;
    int current = 0;

    for (int i = 0; i < 2; i++) { // For unrolling two times
        regis -= 8;
        unordered_map<string, string> mapRegister;
        current = 1; // Reset the current value to 1
        for (const string& regname : floatvector) {
            mapRegister[regname] = "F" + to_string(current);   //Give values to keys register names
            current++;
        }
        for (const string& instruction : instructions) {
            // if (instruction == "STALL") {
            //     outputFile << "stall" << endl;
            //     continue;
            // }
            vector<string> tokens = tokenize(instruction);
            for (string& token : tokens) {
                if (token[0] == 'F') {
                    token = mapRegister[token];
                }
                if (token.find("(") != string::npos) {
                    token = to_string(regis) + token.substr(token.find("("));
                }
            }
            string result = tokens[0] + " " + tokens[1];
            for (int j = 2; j < tokens.size(); j++) {
                result += "," + tokens[j];
            }
            outputFile << result << endl;
        }
    }

    regis -= 8;
    for (const string& line : otherLines) {
        vector<string> tokens = tokenize(line);
        for (string& token : tokens) {
            if (token.find("#") != string::npos) {
                token = "#" + to_string(regis);
            }
        }
        string result = tokens[0] + " " + tokens[1];
        for (int j = 2; j < tokens.size(); j++) {
            result += "," + tokens[j];
        }
        outputFile << result << endl;
    }

    inputFile.close();
    outputFile.close();
    return {"Unrolled_Unscheduled.txt"};
}

int main() {
    string path = "/home/dmacs-5/Documents/mtech_2023/Architecture/input.txt";
    vector<string> output = unroll_loop(path);
    if (output[0] == "Error") {
        cerr << "Error " << endl;
        return 1;
    }
    cout << "Output written to " << output[0] << endl;
    return 0;
}


