#define _CRT_SECURE_NO_WARNINGS
#include "PreCompiledHeader/PreCompiledHeader.h"
#include <iostream>
#include "Engine/Engine.h"
#include "Level/GameLevel.h"
#include <math.h>
#include <fstream>
#include <windows.h>
#include <io.h>
using namespace cv;
using namespace std;

// ASCII 문자 집합 정의 
const char* ascii_chars = "   ...,:;-|=+*#%@@@@@";
int num_chars = strlen(ascii_chars);

void ResizeConsole(int width, int height)
{
    // 콘솔 핸들 가져오기
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // 콘솔 화면 버퍼 크기 설정
    COORD bufferSize;
    bufferSize.X = width;
    bufferSize.Y = height;
    SetConsoleScreenBufferSize(hConsole, bufferSize);
    // 콘솔 창 크기 설정 
    SMALL_RECT windowSize;
    windowSize.Left = 0;
    windowSize.Top = 0;
    windowSize.Right = width - 1;
    windowSize.Bottom = height - 1;
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
}

void SetConsoleFontSize(int size)
{
    // 콘솔 핸들 가져오기 
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // 폰트 정보를 명확히 초기화 
    CONSOLE_FONT_INFOEX cfi = { sizeof(CONSOLE_FONT_INFOEX) };
    cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;
    // 너비는 0으로 설정하여 자동 결정 
    cfi.dwFontSize.Y = size; // 높이 (글꼴 크기)
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy_s(cfi.FaceName, L"Consolas");
    // 폰트 이름 설정 // 글꼴 설정 적용
    SetCurrentConsoleFontEx(hConsole, FALSE, &cfi);
}

void PrintImage(std::string& _path, int _width = 0, int _height = 0, bool is_anim = false, int _col = 0, int _row = 0, int idx = 0)
{
    std::string buffer;
    cv::Mat image = cv::imread(_path, cv::IMREAD_COLOR);
    if (image.empty())
    {
        std::cerr << "Could not open or find the image." << std::endl;
        return;
    }

    cv::imshow("Display Window", image);
    cv::waitKey();
    cv::Mat resizedImage = image;
    int width = image.cols;
    int height = image.rows;

    int x_start = 0;
    int y_start = 0;

    if (is_anim)
    {
        x_start = (image.cols / _col) * (idx % _col);
        y_start = (image.rows / _row) * (idx / _col);
        width = image.cols / _col;
        height = image.rows / _row;
    }

    if (_width != 0 && _height != 0 && !is_anim)
    {
        if (width < height)
        {
            width = static_cast<int>(static_cast<float>(width) / height * _width);
            height = _height;
        }
        else
        {
            height = static_cast<int>(static_cast<float>(height) / width * _height);
            width = _width;
        }

    }

    cv::resize(image, resizedImage, cv::Size(width, height), 0, 0, cv::INTER_LANCZOS4);

    cv::imshow("Display Window", resizedImage);
    cv::waitKey();

    cv::Mat grayImage;
    cv::cvtColor(resizedImage, grayImage, cv::COLOR_RGB2GRAY);
    cv::imshow("Display Window", grayImage);
    cv::waitKey();

    double minVal, maxVal;
    cv::minMaxLoc(grayImage, &minVal, &maxVal);

    // 대비 강화 (히스토그램 스트레칭) 
    grayImage.convertTo(grayImage, CV_8U, 255.0 / (maxVal - minVal), -minVal * 255.0 / (maxVal - minVal));
    cv::imshow("Display Window", grayImage);
    cv::waitKey();

    // 텍스트 파일로 저장하기 위한 파일 이름 설정
    std::string txtFilename = _path.substr(0, _path.find_last_of(".")) + ".txt";
    if (is_anim)
    {
        int index = txtFilename.find(".");
        if (index != std::string::npos)
        {
            char num_buffer[5];
            snprintf(num_buffer, 5, "%d", idx);
            txtFilename.insert(index, num_buffer);
        }
    }
    std::ofstream outFile(txtFilename, std::ios::binary);

    // 픽셀별 그레이 값 출력 및 파일로 저장
    for (int y = y_start; y < y_start + height && y + 1 < grayImage.rows; y += 2)
    {
        for (int x = x_start; x < x_start + width && x < grayImage.cols; x++)
        {
            float GRAY = static_cast<float>(grayImage.at<uchar>(y, x) + grayImage.at<uchar>(y + 1, x)) / 2;
            int charIndex = static_cast<int>((GRAY * (num_chars - 1)) / 255);
            char asciiChar = ascii_chars[charIndex];
            std::cout << asciiChar;
            outFile << asciiChar;
        }
        outFile << '\n';
        std::cout << "\n";
    }

    outFile.close();
    std::cout << "ASCII art has been saved to " << txtFilename << std::endl;
}

void PrintAnimation(int _cols, int _rows, std::string& _path, int _sleep, int max_size)
{
    for (int i = 0; i < _rows * _cols; i++)
    {
        system("cls");
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 0,0 });
        PrintImage(_path, max_size, max_size, true, _cols, _rows, i);
        Sleep(_sleep);
    }
}

int ReadFolder(std::string& _path)
{
    string path = _path + "*.*";

    //  맨끝에 *대신 특정 확장자를 입력하면 그 확장자만 읽어올 수 있다.
    struct _finddata_t fd;

    intptr_t handle;

    if ((handle = _findfirst(path.c_str(), &fd)) == -1L)

    {
        cout << "No file in directory!" << endl;
        // 파일이 없을경우 발생시킬 이벤트.
    }
    do
    {
        string filename = _path + fd.name;
        PrintImage(filename);

    } while (_findnext(handle, &fd) == 0);

    _findclose(handle);
}


int main()
{
    ResizeConsole(300, 150);
    system("mode con:cols=300 lines=300 ");
    SetConsoleFontSize(5);
    SetConsoleTitleA("ImageConverter");

    std::string file_path = "C:\\GameProjects\\ConsolePortfolio\\Assets\\imgs\\nico.png";
    //ReadFolder(file_path);
    PrintImage(file_path, 100, 100);
    return 0;
}
