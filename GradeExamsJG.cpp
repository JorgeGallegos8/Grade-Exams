// Jorgeluis Gallegos
// COSC 1437
// Program Set 1
// Grades a 40 question test
// References: NONE

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>


using namespace std;

// Prototypes
void storeData(ifstream &inputFile, int &numOfTests, string &answerSheet, string &testsToGrade);
void testCalculations(int &numOfTests, string &answerSheet, string &testsToGrade, vector<vector<double>> &scores);

int main() {
    // Variables
    string answerSheet;
    string fileName;
    string testsToGrade;
    int numOfTests;
    int numOfQuestions = 40; // This cannot be changed, its coded to only grade 40 question tests
    bool running = true;
    char choice;
    
    
    while (running) {
        // Prompt user for name of the file
        cout << "Whats the name of the file: ";
        cin >> fileName;
        cout << '\n';

        // Create object of input file
        ifstream inputFile(fileName);
        if (!inputFile.is_open()) {
            cerr << "Error: Unable to open file.\n";
            return 1;
        }

        // Store data using function
        storeData(inputFile,numOfTests, answerSheet, testsToGrade);

        // First row is the score, second row is the percentage
        vector<vector<double>> scores(2, vector<double>(numOfTests)); 

        // Perform calculations
        testCalculations(numOfTests, answerSheet, testsToGrade, scores);

        // Display Results
        for (int i = 0; i < numOfTests; i++) {
            // i + 1 is the student number
            
            cout << "Student #" << i + 1 << ":" 
                << " | Score: " << static_cast<int>(scores[0][i])
                << fixed << setprecision(1)
                << " | Percentage " << scores[1][i] << "%" << "\n\n";
                    
        }

        // Prompt to run again
        cout << "Run Again (Y/N): ";
        cin >> choice;
        if (choice == 'n' || choice == 'N') {
            running = false;
        }
    }
    
    


    return 0;
}

/* 
    This function does the following
    -- Store file data
    -- File contains number of tests to grade in the first line
    -- Next line contains answer sheet in a single string
    -- Following lines contain single strings of answers to grade
*/
void storeData(ifstream &inputFile, int &numOfTests, string &answerSheet, string &testsToGrade) {
    // Local variables
    string line;

    // Read and store number of tests
    getline(inputFile, line);
    numOfTests = stoi(line);

    // Read and store answerSheet
    getline(inputFile,line);
    answerSheet = line;

    // Read all the tests into a single string
    for (int i = 0; i < numOfTests; i++) {
        getline(inputFile, line);
        testsToGrade += line;
    }
}

/*
    This function calculates the score
    -- (6) points for correct answers
    -- (-2) points for wrong answers
    -- (0) points for unanswered questions
    It also calculates the percentage of answered questions
*/
void testCalculations(int &numOfTests, string &answerSheet, string &testsToGrade, vector<vector<double>> &scores) {
    // Variables
    int numOfQuestions = 40;

    // Nested loop to go threw every test and its questions
    for(int i = 0; i < numOfTests; i++) {
        int score = 0;
        double percentage = 0;
        int correct = 0; // number of questions got right
        int numOfQuestionsAnswered = numOfQuestions; // This is used to determine the number of questions the user answered

        for(int j = 0; j < numOfQuestions; j++) {
            // Compares answer sheet and answer, then does calculations ************************ TODO ******************************
            if (testsToGrade[j] == '_') {
                numOfQuestionsAnswered -=1;
            }
            else if (answerSheet[j] == testsToGrade[j]) {
                score += 6;
                correct += 1;
            }
            
            else if (answerSheet[j] != testsToGrade[j]) {
                score -=2;
            }
            
        }
        // Calculate Percentage
        percentage = (static_cast<double>(correct) / numOfQuestionsAnswered) * 100.0;



        // Store score and percentage of student in scores,
        // First row score, second row percentage
        scores[0][i] = score;
        scores[1][i] = percentage;

        // Delete the students test from tests to grade string
        // This is done so that the same loop can be used on the same index of numOfQuestions
        testsToGrade.erase(testsToGrade.begin(), testsToGrade.begin() + numOfQuestions);
    }

}