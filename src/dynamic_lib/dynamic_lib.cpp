//
// Created by JustinWCola on 2023/7/17.
//

#include <cstdio>

namespace dynamic_lib
{
    __declspec(dllexport) void print()
    {
        printf("Hello, Dynamic Library!\r\n");
    }
}