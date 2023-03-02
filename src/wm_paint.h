#pragma once

void OnDestroy(HWND hWnd);
void MyPaint(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, HDC hdc, PAINTSTRUCT* ps);
void OnKeyDown(WPARAM wParam, LPARAM lParam);
void OnLeftButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam);
void OnRightButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam);
void DeleteDCAndBitMapAndImage();
void OnSetTimer(HWND hWnd);
void OnKillTimer(HWND hWnd);
void OnTimer(HWND hWnd, WPARAM wParam, LPARAM lParam);
void OnTimer_1(HWND hWnd, LPARAM lParam);