// Endowments.cpp : Defines the entry point for the application.
//
#include "resource.h"
#include "framework.h"
#include <Commdlg.h>
#include "guts.cpp"
#include <string>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;
int screen = 0;                                 // the number of the screen we are on.
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HWND activeWindows[10];                         // an array of all active windows.
int numberOfActiveWindows = 0;                  // an integer to keep track of active windows in the array.

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.


    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_ENDOWMENTSSORTER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow))
    {
        MessageBox(NULL,
            _T("Call to RegisterClassEx failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ENDOWMENTSSORTER));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ENDOWMENTSSORTER));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_ENDOWMENTSSORTER);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Store instance handle in our global variable

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        MessageBox(NULL,
            _T("Call to RegisterClassEx failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

void redrawScreen(HWND hWnd)
{
    for (int i = numberOfActiveWindows - 1; i >= 0; i--)
    {
        DestroyWindow(activeWindows[i]);
    }
    numberOfActiveWindows = 0;
    InvalidateRect(hWnd, NULL, TRUE);
}

void initializeFile(OPENFILENAME& ofn)
{
    wchar_t szFile[260];
    // Initialize OPENFILENAME
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFile;
    //
    // Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
    // use the contents of szFile to initialize itself.
    //
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(szFile);
    //ofn.lpstrFilter = _T("All\0*.*\0Text\0*.TXT\0");
    ofn.lpstrFilter = _T(".csv");
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

}

void labelAttributes(HWND hWnd)
{
    //this function loops through all the attributes and displays them so that the user can choose whether they are information or attributres. 
    //create a window to carry the attributes
    HWND popUpWindow = CreateWindow(
        szWindowClass,
        szTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        500, 100,
        NULL,
        NULL,
        hInst,
        NULL);

    /*
        DLLNode<Attribute>* tempAttribute;
        tempAttribute = nullptr;
        all_attributes->getNextNode(tempAttribute);
        while (tempAttribute != nullptr)
        {

        } */
}
//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {

        int wmId = LOWORD(wParam);
        int identification = HIWORD(wParam);

        if (identification == BN_CLICKED && lParam != 0)
        {
            if (wmId == 105) // endowments button selected
            {
                OPENFILENAME ofn;       // common dialog box structure
                initializeFile(ofn);
                // Display the Open dialog box. 

                if (GetOpenFileName(&ofn))
                {
                    const wchar_t* filepath = ofn.lpstrFile;
                    wstring convertedFilepath(filepath);
                    std::string finalFilepath(convertedFilepath.begin(), convertedFilepath.end());
                    int success = openFile(finalFilepath, true, true);
                    //here is the list of processes that need to be completed.
                    if (success == 0) //successfully entered attributes
                    {
                        //label the attributes as either info or attribute
                        labelAttributes(hWnd);
                        //once done run through all the endowments to create them.

                    }
                    OutputDebugStringA("ok ");
                }
            }
            else if (wmId == 106) //students button selected. 
            {
                OPENFILENAME ofn;       // common dialog box structure
                initializeFile(ofn);
                // Display the Open dialog box. 

                if (GetOpenFileName(&ofn))
                {
                    const wchar_t* filepath = ofn.lpstrFile;
                    wstring convertedFilepath(filepath);
                    std::string finalFilepath(convertedFilepath.begin(), convertedFilepath.end());
                    OutputDebugStringA("nope ");
                }
            }
        }
        else {
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        RECT rect;
        if (GetWindowRect(hWnd, &rect))
        {
            switch (screen)
            {
            case 0:
            {
                TCHAR endowments_greeting[] = _T("Input the file containing the endowments data:");
                TextOut(hdc, 10, 10, endowments_greeting, _tcslen(endowments_greeting));
                activeWindows[numberOfActiveWindows++] = CreateWindow(L"BUTTON", L"Select File", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10, 40, 100, 30, hWnd, (HMENU)105, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);

                TCHAR students_greeting[] = _T("Input the file containg the students data:");
                TextOut(hdc, 10, 90, students_greeting, _tcslen(students_greeting));
                activeWindows[numberOfActiveWindows++] = CreateWindow(L"BUTTON", L"Select File", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10, 120, 100, 30, hWnd, (HMENU)106, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
                break;
            }
            case 1:
            {


                break;
            }
            }
            // TODO: Add any drawing code that uses hdc here...
        }
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
