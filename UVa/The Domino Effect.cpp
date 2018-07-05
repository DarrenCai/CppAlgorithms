/**
 * UVa211
 * 多米诺效应
 */

#include <iostream>
using namespace std;

short k=0, bone[7][7], pip[7][8], ans[7][8], t; bool used[29] = {0}, visit[7][8] = {0};

void dfs(short row=0, short col=0) {
    if (col == 8) col=0, ++row;
    if (row==6 && col==7) {
        for (short i=0; i<7; ++i) {
            cout << endl;
            for (short j=0; j<8; ++j)
                cout << (ans[i][j]>9 ? "  ":"   ") << ans[i][j];
        }
        cout << endl; ++t;
    } else if (visit[row][col]) {
        dfs(row, col+1);
    } else {
        visit[row][col] = true;
        if (col<7 && !visit[row][col+1] && !used[bone[pip[row][col]][pip[row][col+1]]]) {
            used[bone[pip[row][col]][pip[row][col+1]]] = true;
            visit[row][col+1] = true;
            ans[row][col] = ans[row][col+1] = bone[pip[row][col]][pip[row][col+1]];
            dfs(row, col+1);
            used[bone[pip[row][col]][pip[row][col+1]]] = false;
            visit[row][col+1] = false;
        }
        if (row<6 && !used[bone[pip[row][col]][pip[row+1][col]]]) {
            used[bone[pip[row][col]][pip[row+1][col]]] = true;
            visit[row+1][col] = true;
            ans[row][col] = ans[row+1][col] = bone[pip[row][col]][pip[row+1][col]];
            dfs(row, col+1);
            used[bone[pip[row][col]][pip[row+1][col]]] = false;
            visit[row+1][col] = false;
        }
        visit[row][col] = false;
    }
}

int main()
{
    for (short i=0,t=0; i<7; ++i)
        for (short j=i; j<7; ++j) bone[i][j] = bone[j][i] = ++t;
    while (!cin.eof()) {
        for (short i=0; i<7; ++i)
            for (short j=0; j<8; ++j)
                if (!(cin >> pip[i][j])) return 0;
        if (k++) cout << endl << endl << endl;
        cout << "Layout #" << k << ":" << endl;
        for (short i=0; i<7; ++i) {
            cout << endl;
            for (short j=0; j<8; ++j) cout << "   " << pip[i][j];
        }
        cout << endl << endl << "Maps resulting from layout #" << k << " are:" << endl;
        t = 0; dfs();
        cout << endl << "There are " << t << " solution(s) for layout #" << k << '.' << endl;
    }
    return 0;
}