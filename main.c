#include <windows.h>
#include <stdio.h>
HWND hNum1, hNum2, hResult;

// Calculator functions
double add(double a, double b) { return a + b; }
double sub(double a, double b) { return a - b; }
double mul(double a, double b) { return a * b; }
double divi(double a, double b) { return b == 0 ? 0 : a / b; }

// Window procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    if (msg == WM_COMMAND) {
        char a[20], b[20];
        GetWindowText(hNum1, a, 20);
        GetWindowText(hNum2, b, 20);

        double x = atof(a);
        double y = atof(b);
        double r = 0;

        if (wp == 1) r = add(x, y);
        else if (wp == 2) r = sub(x, y);
        else if (wp == 3) r = mul(x, y);
        else if (wp == 4) r = divi(x, y);

        char res[50];
        sprintf(res, "%g", r); // format result
        SetWindowText(hResult, res);
    }

    if (msg == WM_DESTROY) {
        PostQuitMessage(0);
    }

    return DefWindowProc(hwnd, msg, wp, lp);
}

// WinMain entry point for GUI
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int) {
    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInst;
    wc.lpszClassName = "CalcClass";

    RegisterClass(&wc);

    HWND hwnd = CreateWindow(
        "CalcClass",
        "GUI Calculator",
        WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME,  // fixed size window
        300, 200, 320, 250,
        NULL, NULL, hInst, NULL
    );

    // Number input boxes
    hNum1 = CreateWindow("EDIT", "",
        WS_CHILD | WS_VISIBLE | WS_BORDER,
        30, 20, 100, 25,
        hwnd, NULL, hInst, NULL);

    hNum2 = CreateWindow("EDIT", "",
        WS_CHILD | WS_VISIBLE | WS_BORDER,
        150, 20, 100, 25,
        hwnd, NULL, hInst, NULL);

    // Operation buttons
    CreateWindow("BUTTON", "+", WS_CHILD | WS_VISIBLE,
        30, 60, 40, 30, hwnd, (HMENU)1, hInst, NULL);

    CreateWindow("BUTTON", "-", WS_CHILD | WS_VISIBLE,
        80, 60, 40, 30, hwnd, (HMENU)2, hInst, NULL);

    CreateWindow("BUTTON", "*", WS_CHILD | WS_VISIBLE,
        130, 60, 40, 30, hwnd, (HMENU)3, hInst, NULL);

    CreateWindow("BUTTON", "/", WS_CHILD | WS_VISIBLE,
        180, 60, 40, 30, hwnd, (HMENU)4, hInst, NULL);

    // Result display
    hResult = CreateWindow("STATIC", "Result",
        WS_CHILD | WS_VISIBLE | WS_BORDER,
        30, 120, 220, 30,
        hwnd, NULL, hInst, NULL);

    ShowWindow(hwnd, SW_SHOW);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
