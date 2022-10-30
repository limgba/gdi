#pragma once

void MyPaint(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, HDC hdc, PAINTSTRUCT* ps);
void OnKeyDown(WPARAM wParam, LPARAM lParam);
void OnRightButtonDown(WPARAM wParam, LPARAM lParam);
void DeleteDCAndBitMapAndImage();