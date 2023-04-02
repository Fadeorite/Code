#include <bits/stdc++.h>
#include <conio.h>
using namespace std;
using namespace chrono;

const int SCSIZE = 27;
const int SCWIDTH = 43;
const double ZOOMLEVEL = 1.2;
const double YOLevel = 0.5;
const double XOLevel = 1;
const bool Fill = 1;
const bool DrawLines = 1;
const bool ScreenFlush = 1;

double f(double x) {
    return x;
}
const bool useFunc2 = 0;
double f2(double x) {
    return 10 - x;
}

const int XLINES = 2;
const int YLINES = 4;
const int NUMSIZE = 10;
const int NUMNEED = 1;

double GLINE = 1;
double Zoom = 1.0;
double XBase = 0;
double YBase = 0;
double YLevel = YOLevel;
double XLevel = XOLevel;

void print(double);
void printScreen();
void printNum(double);
bool isXOK(double);
bool isYOK(double);
void Ref();

int main() {
    while (true) {
        Ref();
        if (ScreenFlush)
            cout << "\033c";
        printScreen();
        char ch = getch();
        if (ch == 'w') XBase -= XLevel * XLINES;
        else if (ch == 's' || ch == 'x') XBase += XLevel * XLINES;
        else if (ch == 'a') YBase -= YLevel * YLINES;
        else if (ch == 'd') YBase += YLevel * YLINES;
        else if (ch == 'm') {
            XLevel = XOLevel;
            YLevel = YOLevel;
            XBase = 0;
            YBase = 0;
        } else if (ch == 'u') XLevel /= ZOOMLEVEL;
        else if (ch == 'o') XLevel *= ZOOMLEVEL;
        else if (ch == 'j') YLevel /= ZOOMLEVEL;
        else if (ch == 'l') YLevel *= ZOOMLEVEL;
        else if (ch == 'i') XLevel /= ZOOMLEVEL, YLevel /= ZOOMLEVEL;
        else if (ch == 'k') XLevel *= ZOOMLEVEL, YLevel *= ZOOMLEVEL;
        XLevel = min(XLevel, 100000.0);
        YLevel = min(YLevel, 50000.0);
        XLevel = max(XLevel, 0.000001);
        YLevel = max(YLevel, 0.0000005);
    }
}

void print(double t) {
    double x = f(t);
    double x2; if (useFunc2) x2 = f2(t);
    for (double i = YBase - YLevel * SCWIDTH / 2.0; i <= YBase + YLevel * SCWIDTH / 2.0; i += YLevel) {
        if (fabs(i - 0) < YLevel && fabs(t - 0) < XLevel && isYOK(i) && isXOK(t)) cout << "O";
        else if (useFunc2 && fabs(i - x2) < YLevel / 2 && fabs(i - x) < YLevel / 2) cout << "S";
        else if (Fill && ((x < i && i < 0) || (x > i && i > 0)) && ((x2 < i && i < 0) || (x2 > i && i > 0)))
            cout << "+";
        else if (Fill && ((x < i && i < 0) || (x > i && i > 0)))
            cout << "-";
        else if (useFunc2 && Fill && ((x2 < i && i < 0) || (x2 > i && i > 0)))
            cout << "=";
        else if (fabs(i - x) < YLevel / 2) cout << "-";
        else if (useFunc2 && fabs(i - x2) < YLevel / 2) cout << "=";
        else if (DrawLines && isYOK(i) && isXOK(t)) cout << "┼";
        else if ((DrawLines || fabs(i) < YLevel) && isYOK(i)) cout << "│";
        else if ((DrawLines || fabs(t) < XLevel) && isXOK(t)) cout << "─";
        else cout << " ";
    }
}
void printScreen() {
    double Tx = XOLevel / XLevel;
    double Ty = YOLevel / YLevel;
    for (int i = 0; i <= NUMSIZE; ++i) cout << " ";
    cout << setw(6) << right << fixed;
    if (Tx < 0.01) cout << setprecision(4);
    else if (Tx < 0.1) cout << setprecision(3);
    else if (Tx < 1) cout << setprecision(2);
    else if (Tx < 10) cout << setprecision(1);
    else cout << setprecision(0);
    cout << Tx << " X   " << setw(6) << right << fixed;
    if (Ty < 0.01) cout << setprecision(4);
    else if (Ty < 0.1) cout << setprecision(3);
    else if (Ty < 1) cout << setprecision(2);
    else if (Ty < 10) cout << setprecision(1);
    else cout << setprecision(0);
    cout << Ty << " Y         ";
    cout << "Pos: (" << fixed << setprecision(1) << XBase << ", "
         << fixed << setprecision(1) << YBase << ")"
         << endl;
    double X = XBase - XLevel * SCSIZE / 2;
    for (int i = 0; i <= NUMSIZE; ++i) cout << " ";
    cout << "┏";
    for (double i = YBase - YLevel * SCWIDTH / 2.0; i <= YBase + YLevel * SCWIDTH / 2.0; i += YLevel) cout << "━";
    cout << "┓" << endl;
    for (int k = 0; k < SCSIZE; ++k) {
        if ((DrawLines || fabs(X) < XLevel) && isXOK(X))
            printNum(X);
        else for (int i = 0; i < NUMSIZE; ++i) cout << " ";
        cout << " ┃";
        print(X);
        if (isXOK(X) && fabs(X - 0) < XLevel) cout << "Y";
        else cout << "┃";
        cout << endl;
        X += XLevel;
    }
    for (int i = 0; i <= NUMSIZE; ++i) cout << " ";
    cout << "┗";
    for (double i = YBase - YLevel * SCWIDTH / 2.0; i <= YBase + YLevel * SCWIDTH / 2.0; i += YLevel) {
        if (isYOK(i) && fabs(i - 0) < YLevel) cout << "X";
        else cout << "━";
    }
    cout << "┛" << endl;
    // cout << "Num: " << fixed << setprecision(2) << XLevel << " GLINE: " << GLINE << endl;
}
void printNum(double x) {
    if (isXOK(x) && fabs(x) < XLevel) cout << right << setw(NUMSIZE) << "O";
    else if (x > 0) {
        if (x < 0.1) {
            cout << setw(NUMSIZE) << right << fixed << setprecision(max(NUMNEED + 2, 0)) << x;
        } else if (x < 1) {
            cout << setw(NUMSIZE) << right << fixed << setprecision(max(NUMNEED + 1, 0)) << x;
        } else if (x < 10) {
            cout << setw(NUMSIZE) << right << fixed << setprecision(max(NUMNEED, 0)) << x;
        } else if (x < 100) {
            cout << setw(NUMSIZE) << right << fixed << setprecision(max(NUMNEED - 1, 0)) << x;
        } else if (x < 1000) {
            cout << setw(NUMSIZE) << right << fixed << setprecision(max(NUMNEED - 2, 0)) << x;
        } else cout << right << setw(NUMSIZE) << min(int(x), 99999999);
    } else if (x < 0) {
        if (x > -0.099) {
            cout << setw(NUMSIZE) << right << fixed << setprecision(max(NUMNEED + 2, 0)) << x;
        } else if (x > -0.99) {
            cout << setw(NUMSIZE) << right << fixed << setprecision(max(NUMNEED + 1, 0)) << x;
        } else if (x > -9.9) {
            cout << setw(NUMSIZE) << right << fixed << setprecision(max(NUMNEED, 0)) << x;
        } else if (x > -99.9) {
            cout << setw(NUMSIZE) << right << fixed << setprecision(max(NUMNEED - 1, 0)) << x;
        } else if (x > -999.9) {
            cout << setw(NUMSIZE) << right << fixed << setprecision(max(NUMNEED - 2, 0)) << x;
        } else cout << right << setw(NUMSIZE) << max(int(x), -9999999);
    }
}
bool isXOK(double x) {
    if (fabs(x - 0) > XLevel) x = fabs(x);
    double t = x - GLINE * floor(floor(x) / GLINE);
    return t >= 0 && t < XLevel;
}
bool isYOK(double y) {
    if (fabs(y - 0) > YLevel) y = fabs(y);
    double t = y - GLINE * floor(floor(y) / GLINE);
    return t >= 0 && t < YLevel;
}
void Ref() {
    double Level = max(XLevel, YLevel * 2);
    if (Level < 0.005) GLINE = 0.02;
    else if (Level < 0.0125) GLINE = 0.05;
    else if (Level < 0.025) GLINE = 0.1;
    else if (Level < 0.05) GLINE = 0.2;
    else if (Level < 0.125) GLINE = 0.5;
    else if (Level < 0.25) GLINE = 1;
    else if (Level < 0.5) GLINE = 2;
    else if (Level < 1.25) GLINE = 5;
    else if (Level < 2.5) GLINE = 10;
    else if (Level < 5) GLINE = 20;
    else if (Level < 12.5) GLINE = 50;
    else if (Level < 25) GLINE = 100;
    else if (Level < 50) GLINE = 200;
    else if (Level < 125) GLINE = 500;
    else if (Level < 250) GLINE = 1000;
    else if (Level < 500) GLINE = 2000;
    else if (Level < 1250) GLINE = 5000;
    else if (Level < 2500) GLINE = 10000;
    else if (Level < 5000) GLINE = 20000;
    else if (Level < 12500) GLINE = 50000;
    else if (Level < 25000) GLINE = 100000;
    else if (Level < 50000) GLINE = 200000;
    else GLINE = 500000;
}
