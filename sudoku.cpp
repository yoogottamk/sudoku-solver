#include <iostream>

using namespace std;

//  Function for taking the sudoku input
void inputSudoku(int sud[9][9]);

//  Function to display the sudoku array in a readable format
void displaySudoku(int sud[9][9]);

//  Function that checks if the sudoku at it's current state is valid
bool isValid(int sud[9][9]);

//  Function that returns the next empty position
int getNextZero(int sud[9][9]);

//  Function that does the actual solving
void solveSudoku(int sud[9][9]);

//  Function that fills all the single poosible blocks
void fillSingles(int sud[9][9]);

int main() {

    int sud[9][9];

    cout << "\n\t\t\tWelcome to Sudoku Solver\n";
    inputSudoku(sud);
    displaySudoku(sud);
    if(isValid(sud)) {
        cout << "\nInput looks OK..solving....\n";

        //  ?? seems to delay the result rather than making it fast..
        //
        //  fillSingles(sud);

        solveSudoku(sud);
        if(getNextZero(sud) < 0) {
            system("clear");
            cout << "\nSOLVED!!\n";
            displaySudoku(sud);
        }
    }

    return 0;
}

void inputSudoku(int sud[9][9]) {
    cout << "\nFill it as you see it."
        << "\nEnter a 0 in unfilled."
        << "\nEnter the sudoku:\n";

    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++)
            cin >> sud[i][j];
    }
}

void displaySudoku(int sud[9][9]) {
    cout << "\nSudoku looks like:\n";

    int rc = 0, cc = 0;

    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            if(sud[i][j])
                cout << sud[i][j] << ' ';
            else
                cout << ' ' << ' ';
            cc++;

            if(cc == 3 && j != 8) {
                cout << "| ";
                cc = 0;
            }
        }
        cout << "\n";
        rc++;
        cc = 0;

        if(rc == 3 && i != 8) {
            cout << "------+-------+------\n";
            rc = 0;
        }
    }
}

bool isValid(int sud[9][9]) {
    int store[10] = {0};

    //  Checking for rows
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            if(sud[i][j])
                store[sud[i][j]]++;
        }
        for(int k = 1; k < 10; k++) {
            if(store[k] > 1)
                return false;
            store[k] = 0;
        }
    }

    //  Checking for cols
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            if(sud[j][i])
                store[sud[j][i]]++;
        }
        for(int k = 1; k < 10; k++) {
            if(store[k] > 1)
                return false;
            store[k] = 0;
        }
    }

    //  Checking all blocks
    for(int l = 0; l < 3; l++) {
        for(int m = 0; m < 3; m++) {
            for(int i = 0; i < 3; i++) {
                for(int j = 0; j < 3; j++) {
                    if(sud[3 * l + i][3 * m + j])
                        store[sud[3*l + i][3*m + j]]++;
                }
            }
            for(int k = 1; k < 10; k++) {
                if(store[k] > 1)
                    return false;
                store[k] = 0;
            }
        }
    }

    return true;
}

int getNextZero(int sud[9][9]) {
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            if(sud[i][j] == 0)
                return (10*i + j);
        }
    }

    return -1;
}

void solveSudoku(int sud[9][9]) {
    int st[81], top = -1;

    st[++top] = getNextZero(sud);
    int pos = st[top];

    while(pos >= 0) {
        system("clear");
        displaySudoku(sud);

        int i = pos / 10;
        int j = pos % 10;

        if(sud[i][j] == 9) {
            sud[i][j] = 0;
            top--;
            pos = st[top];
            continue;
        }

        while (sud[i][j] < 9) {
            sud[i][j]++;
            if(isValid(sud))
                break;
        }

        if(isValid(sud)) {
            st[++top] = getNextZero(sud);
            pos = st[top];
            continue;
        }

        if(!isValid(sud) && sud[i][j] == 9) {
            sud[i][j] = 0;
            top--;
            pos = st[top];
            continue;
        }
    }
}

void fillSingles(int sud[9][9]) {
    int pos = getNextZero(sud);
    int count = 0, found;

    while(pos > 0) {
        count = 0;
        found = 0;
        for(int i = 1; i <= 9; i++){
            sud[pos / 10][pos % 10] = i;
            system("clear");
            displaySudoku(sud);
            if(isValid(sud)) {
                count++;
                found = sud[pos / 10][pos % 10];
            }
        }

        if(count > 1)
            found = -1;

        sud[pos / 10][pos % 10] = found;

        pos = getNextZero(sud);
    }

    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            if(sud[i][j] < 0)
                sud[i][j] = 0;
        }
    }
}
