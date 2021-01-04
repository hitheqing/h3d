#ifndef H3d_CONSOLE_H
#define H3d_CONSOLE_H

#if WIN32
#include <iostream>
#include <stdint.h>
#include <iostream>
#include <string>
#include <Windows.h>

//   0 = 黑色      8 = 灰色
//   1 = 蓝色      9 = 淡蓝色
//   2 = 绿色      A = 淡绿色
//   3 = 浅绿色    B = 淡浅绿色
//   4 = 红色      C = 淡红色
//   5 = 紫色      D = 淡紫色
//   6 = 黄色      E = 淡黄色
//   7 = 白色      F = 亮白色

//   控制台前景颜色
enum ConsoleForegroundColor
{
    enmCFC_Red          = FOREGROUND_INTENSITY | FOREGROUND_RED,
    enmCFC_Green        = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
    enmCFC_Blue         = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
    enmCFC_Yellow       = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
    enmCFC_Purple       = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
    enmCFC_Cyan         = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
    enmCFC_Gray         = FOREGROUND_INTENSITY,
    enmCFC_White        = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
    enmCFC_HighWhite    = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
    enmCFC_Black        = 0,
};

enum ConsoleBackGroundColor
{
    enmCBC_Red          = BACKGROUND_INTENSITY | BACKGROUND_RED,
    enmCBC_Green        = BACKGROUND_INTENSITY | BACKGROUND_GREEN,
    enmCBC_Blue         = BACKGROUND_INTENSITY | BACKGROUND_BLUE,
    enmCBC_Yellow       = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN,
    enmCBC_Purple       = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE,
    enmCBC_Cyan         = BACKGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE,
    enmCBC_White        = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,
    enmCBC_HighWhite    = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,
    enmCBC_Black        = 0,
};

inline void SetConsoleColor(ConsoleForegroundColor foreColor = enmCFC_White, ConsoleBackGroundColor backColor = enmCBC_Black)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, foreColor | backColor);
}

//int32_t main()
//{
//    int32_t allForeColors[] = { enmCFC_Red, enmCFC_Green, enmCFC_Blue, enmCFC_Yellow, enmCFC_Purple, enmCFC_Cyan, enmCFC_Gray, enmCFC_White, enmCFC_HighWhite, enmCFC_Black };
//    std::string allForeColorsName[] = { "enmCFC_Red", "enmCFC_Green", "enmCFC_Blue", "enmCFC_Yellow", "enmCFC_Purple", "enmCFC_Cyan", "enmCFC_Gray", "enmCFC_White", "enmCFC_HighWhite", "enmCFC_Black" };
//    int32_t allBackColors[] = { enmCBC_Red, enmCBC_Green, enmCBC_Blue, enmCBC_Yellow, enmCBC_Purple, enmCBC_Cyan, 0, enmCBC_White, enmCBC_HighWhite, enmCBC_Black };
//    std::string allBackColorsName[] = { "enmCBC_Red", "enmCBC_Green", "enmCBC_Blue", "enmCBC_Yellow", "enmCBC_Purple", "enmCBC_Cyan", "0", "enmCBC_White", "enmCBC_HighWhite", "enmCBC_Black " };
//    for(uint32_t i = 0; i < sizeof(allForeColors) / sizeof(allForeColors[0]); ++i)
//    {
//        for(uint32_t j = 0; j < sizeof(allForeColors) / sizeof(allForeColors[0]); ++j)
//        {
//            if(i != j && allBackColorsName[j] != "0")
//            {
//                SetConsoleColor((ConsoleForegroundColor)allForeColors[i], (ConsoleBackGroundColor)allBackColors[j]);
//                std::cout << "ForeColor:" << allForeColorsName[i] <<",backColor:"<< allBackColorsName[j] << std::endl;
//            }
//        }
//    }
//    getchar();
//    return 0;
//}

#define out_msg(s) SetConsoleColor(enmCFC_Blue,enmCBC_Black);  std::cout <<"[Hyhy] " << s   << std::endl << std::flush;SetConsoleColor();
#define out_wrn(s) SetConsoleColor(enmCFC_Yellow,enmCBC_Black);  std::cout <<"[Hyhy] " << s   << std::endl << std::flush;SetConsoleColor();
#define out_err(s) SetConsoleColor(enmCFC_Red,enmCBC_Black);  std::cout <<"[Hyhy] " << s   << std::endl << std::flush;SetConsoleColor();

#elif __APPLE__

#include <iostream>

#define ANSI_RESET "\x1b[0m"
#define ANSI_R "\x1b[31m"
#define ANSI_G "\x1b[32m"
#define ANSI_B "\x1b[34m"
#define ANSI_C "\x1b[36m"
#define ANSI_M "\x1b[35m"
#define ANSI_Y "\x1b[33m"

#define out_msg(s) std::cout << ANSI_B << "[Hyhy] " << s << ANSI_RESET  << std::endl << std::flush;
#define out_wrn(s) std::cout << ANSI_Y << "[Hyhy] " << s << ANSI_RESET  << std::endl << std::flush;
#define out_err(s) std::cout << ANSI_R << "[Hyhy] " << s << ANSI_RESET  << std::endl << std::flush;
#endif


#endif // H3d_CONSOLE_H
