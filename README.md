# CMake 简单入门

金维聪 2023.7.16

## 1 CMake 是什么

CMake 是一个**跨平台**的编译工具，可以用简单的语句编写`CMakeLists.txt`，来描述所有平台的编译流程，再由编译平台自动生成 Makefile 并编译工程。

## 2 CMake 安装

虽然CLion自带CMake，但是还是介绍一下CMake的安装。

Linux：进入[官网下载](https://cmake.org/download/)相应`.sh`安装脚本并运行即可；或者下载`.tar.gz`压缩包并解压，终端输入`sudo make install`安装，输入`vim ~/.bash_profile`在文件中添加`export PATH=<安装路径>:$PATH`；也可以下载源码自行编译。

Window：进入[官网下载](https://cmake.org/download/)相应`.msi`安装程序，一路确认到底即可；或者下载`.zip`压缩包并解压，复制其路径并添加到系统环境变量的PATH中。

## 3 CMake 使用

如上文所述，CMake 的语句简单，没有什么特殊的语法要求，甚至大小写都可以随缘。唯一可能要注意的是注释，使用 `#` 进行行注释，使用`#[[ ]]`进行块注释。

```cmake
# Hello CMakeLists.txt
cmake_minimum_required(VERSION 3.25)
#[[ Hello CMakeLists.txt
	Hello CMakeLists.txt]]
```

接下来将通过一些示例来介绍各语句的含义与用法。

### 3.1 单文件创建应用程序

首先准备一个测试文件，这里简单的写一个`main.cpp`：

```c++
#include <iostream>

int main()
{
    std::cout << "Hello, CMake!" << std::endl;
    return 0;
}
```

然后在同一目录下，添加`CMakeLists.txt`：

```cmake
cmake_minimum_required(VERSION 3.25)

project(hello_cmake)

set(CMAKE_CXX_STANDARD 17)

add_executable(hello_cmake main.cpp)
```

接下来依次介绍以上`CMakeLists.txt`中的四个指令：

- `cmake_minimum_required`：指定使用的 CMake 的最低版本，在 CLion 中一般会指定成捆绑的 CMake 版本。

- `project`：定义项目名称，还可以指定工程的版本、描述、主页地址、支持语言（可选）。

  ```cmake
  project(<PROJECT-NAME> [<language-name>...])
  project(<PROJECT-NAME>
          [VERSION <major>[.<minor>[.<patch>[.<tweak>]]]]
          [DESCRIPTION <project-description-string>]
          [HOMEPAGE_URL <url-string>]
          [LANGUAGES <language-name>...])
  ```

- `set`：给变量设置定值，具体功能很多，这里是指定 C++ 标准为 C++ 17。

  ```cmake
  set(<variable> <value>)
  ```

- `add_executable`：添加从源文件构建的可执行程序。

  ```cmake
  add_executable(<name> [WIN32] [MACOSX_BUNDLE]
                 [EXCLUDE_FROM_ALL]
                 [source1] [source2 ...])
  ```

编辑完`CMakeLists.txt`后，便可以执行`cmake`指令。但在这之前，应该建立一个`build`目录，在该目录下执行`cmake ..`指令，这样生成的过程文件都会放到该目录下，使项目目录更加整洁。

CLion 则提供了更加便捷的设置方法，只需要在`设置 | 构建、执行、部署 | CMake`中将`构建目录`设置成`build`，再点击`构建`即可。构建后运行得到以下结果：

```shell
Hello, CMake!

进程已结束,退出代码0
```

最后，再次回到以上`CMakeLists.txt`的最后一句，并更换一种写法：

```cmake
# Old CMake
add_executable(hello_cmake main.cpp)

# Modern CMake
add_executable(hello_cmake)

target_sources(hello_cmake
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    )
```

不难发现，旧 CMake 是**以目录为中心的（directory-oriented）**，即定义的属性只能在当前目录中使用，因此所有属性的依赖关系都要符合实际的文件目录；而 Modern CMake 是**以目标为中心的（target-oriented）**，所有属性都作为目标，源代码、目录等的指定都针对目标进行，这样就可以忽略实际的文件目录，更方便的设计依赖关系。事实上， **Modern CMake 可以看作一种面向对象思路**，目标就是对象，而其属性就相当于成员变量，而下文也会提到 Modern CMake 类似 public、private 等关键字的访问权限与继承类型控制。

### 3.2 构建静态库并链接

先创建一个`static_lib`目录，在目录下创建`.cpp`源文件、`.h`头文件：

- `static_lib/static_lib.cpp`

  ```c++
  #include <cstdio>
  
  namespace static_lib
  {
      void print()
      {
          printf("Hello, Static Library!\r\n");
      }
  }
  ```

- `static_lib/static_lib.h`

  ```c++
  namespace static_lib
  {
      extern void print();
  }
  ```

在该目录下再创建一个`CMakeLists.txt`：

```cmake
add_library(static_lib STATIC)

target_sources(static_lib
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/static_lib.cpp
        )

target_include_directories(static_lib
        INTERFACE
            ${CMAKE_CURRENT_SOURCE_DIR}
        )
```

接下来依次介绍以上`CMakeLists.txt`中的三个指令：

- `add_library`：顾名思义，就是新建一个库。

  ```cmake
  add_library(<name> [STATIC | SHARED | MODULE]
              [EXCLUDE_FROM_ALL]
              [<source>...])
  ```

  静态库使用 STATIC ，动态库则使用 SHARED 。如上文所述，根据 Modern CMake 的写法，这里不需要在该指令中指定源文件，而是在此之后对目标进行操作。

- `target_sources`：将源文件添加到指定目标中。

  ```cmake
  target_sources(<target>
    <INTERFACE|PUBLIC|PRIVATE> [items1...]
    [<INTERFACE|PUBLIC|PRIVATE> [items2...] ...])
  ```

  一下子就见到了我们的老熟人 PUBLIC 和 PRIVATE ，另外多出了一个新朋友 INTERFACE ，他们便是上文讲到的 Modern CMake 的访问权限与继承类型控制，规定了属性在不同目标之间的传递关系，接下来一一介绍：

  - PUBLIC：目标的属性不仅自己使用，还传递给依赖它的其他目标；
  - PRIVATE：目标的属性只能自己使用，不会传递给依赖它的其他目标；
  - INTERFACE：目标的属性不会自己使用，只能传递给依赖它的其他目标。

  可以发现 PUBLIC = PRIVATE + INTERFACE，但可能有人会问：INTERFACE 你人还怪好的嘞，舍己为人是为啥？这是因为有些目标没有实质内容，例如 header-only 库，只有头文件没有源文件，只能被引用不能过编译，便只能用 INTERFACE。

  另外还有指令中的`${CMAKE_CURRENT_SOURCE_DIR}`也很引人注目，这是 CMake 的宏定义之一，代表着当前 CMake 所在目录。

- `target_include_directories`：将包含目录添加到指定目标中，用法同上。

  ```cmake
  target_include_directories(<target> [SYSTEM] [AFTER|BEFORE]
    <INTERFACE|PUBLIC|PRIVATE> [items1...]
    [<INTERFACE|PUBLIC|PRIVATE> [items2...] ...])
  ```

至此，一个静态库便创建好了，接下来打开根目录下的`CMakeLists.txt`进行链接库的操作：

```cmake
add_subdirectory(static_lib)

target_link_libraries(hello_cmake
        PRIVATE
            static_lib
        )
```

添加以上两句便能完成，接下来依次介绍这两个指令：

- `add_subdirectory`：添加子目录，指定代码文件所在的目录。
- `target_link_libraries`：将库链接到指定目标。

修改`main.cpp`调用静态库：

```c++
#include <iostream>
#include <static_lib.h>

int main()
{
    std::cout << "Hello, CMake!" << std::endl;
    static_lib::print();
    return 0;
}
```

构建后运行得到以下结果：

```shell
Hello, CMake!
Hello, Static Library!

进程已结束,退出代码0
```

### 3.3 构建动态库并链接

首先解释一下静态库和动态库的区别：

- 静态库：函数和数据编译进一个二进制的`.a`引入库文件里面，链接时候会**直接复制**静态库内的函数和数据到可执行程序里面，所以在加载库的时候不需要加载相应的库函数。作为全局方式，减少调用时间，增加内存占用。在嵌入式项目中，一般用静态库。
- 动态库：往往是提供两个文件，一个`.a`引入库文件和一个`.dll`动态链接库文件，引入库文件只包含导出函数和函数的变量名，而动态链接库文件包含了所有的函数和数据，调用动态库是在编译到可执行程序的时候才会调用，**没有函数和数据的复制**。作为局部方式，减少内存占用，增加调用时间。

接下来开始构建，先创建一个`dynamic_lib`目录，在目录下创建`.cpp`源文件、`.h`头文件：

- `dynamic_lib/dynamic_lib.cpp`

  ```c++
  #include <cstdio>
  
  namespace dynamic_lib
  {
      __declspec(dllexport) void print()
      {
          printf("Hello, Dynamic Library!\r\n");
      }
  }
  ```

  这里的`__declspec(dllexport)`将函数导出为`.dll`文件。

- `dynamic_lib/dynamic_lib.h`

  ```c++
  namespace dynamic_lib
  {
      extern void print();
  }
  ```

在该目录下再创建一个`CMakeLists.txt`：

```cmake
add_library(dynamic_lib SHARED)

target_sources(dynamic_lib
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/dynamic_lib.cpp
        )

target_include_directories(dynamic_lib
        INTERFACE
            ${CMAKE_CURRENT_SOURCE_DIR}
        )
```

上文也提到了，动态库使用 SHARED，其余语句和静态库相同。

至此，一个动态库便创建好了，接下来打开根目录下的`CMakeLists.txt`进行链接库的操作：

```cmake
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)

add_subdirectory(dynamic_lib)

target_link_libraries(hello_cmake
        PRIVATE
        	static_lib
            dynamic_lib
        )
```

与静态库相比，只多出了一个指令：

- `set`：上文提到其作用是给变量设置定值，具体功能很多。这里设置了`.dll`动态链接库文件的生成路径为`build`。因为动态库的调用需要让`.exe`可执行程序和`.dll`动态链接库文件位于同一目录下，否则将会报错。

- 此外最后的`target_link_libraries`中可以看出，对同一目标的同一属性进行的同类操作可以缩写在同一个指令中，这也是很符合常理的。

修改`main.cpp`调用动态库：

```c++
#include <iostream>
#include <static_lib.h>
#include <dynamic_lib.h>

int main()
{
    std::cout << "Hello, CMake!" << std::endl;
    static_lib::print();
    dynamic_lib::print();
    return 0;
}
```

构建后运行得到以下结果：

```shell
Hello, CMake!
Hello, Static Library!
Hello, Dynamic Library!

进程已结束,退出代码0
```

### 3.4 文件目录的整理

既然 Modern CMake 让代码构建摆脱了文件目录的束缚，那何不将文件整理的更加干净捏？

这是之前的文件目录，`build`存放着所有的过程文件，剩下的全部都是代码文件。

```shell
hello_cmake
  ├─build
  ├─dynamic_lib
  └─static_lib
  
```

上文也提到了，若使用了动态库，`.dll`文件和`.exe`文件要在同一目录下，当前将`.dll`文件生成到`build`目录下，虽然程序确实可以运行了，但文件不免有些混乱。无独有偶，`.a`文件也被随意埋藏在`build`的多级目录下，不是很优雅。

因此，新建`bin`、`lib`、`src`目录，分别存放结果文件、静态库文件、代码文件，如下所示：

```shell
hello_cmake
  ├─bin
  ├─build
  ├─lib
  └─src
      ├─dynamic_lib
      └─static_lib
```

但更改目录之后需要对`CMakeLists.txt`做出相应的切割与修改：

- `hello_cmake/CMakeLists.txt`：

  ```cmake
  cmake_minimum_required(VERSION 3.25)
  
  project(hello_cmake)
  
  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
  
  add_subdirectory(src)
  ```

  根目录下的`CMakeLists.txt`设置项目的基本属性，并依次设置了`.a`静态库文件、`.exe`可执行程序、`.dll`动态链接库文件的生成位置，最后指定了子目录`src`。

- `hello_cmake/src/CMakeLists.txt`：

  ```cmake
  add_executable(hello_cmake)
  
  target_sources(hello_cmake
          PRIVATE
              main.cpp
          )
  
  add_subdirectory(static_lib)
  add_subdirectory(dynamic_lib)
  
  target_link_libraries(hello_cmake
          PRIVATE
              static_lib
              dynamic_lib
          )
  ```

至此，文件目录整理完毕，编译运行得到一样的输出结果。这里只是写明思路，具体嵌入式项目之中的文件目录还得根据实际情况做出调整。

### 3.5 嵌入式项目中的 CMake 使用

本节将以 CLion 环境下基于 HAL 库的 STM32 项目为例进行讲述。

首先，创建一个 STM32CubeMX 项目，选择 MCU 并完成基本配置后生成代码，CLion 会自动生成`CMakeLists.txt`与`CMakeLists_template.txt`，而每次生成代码都会根据后者的模板重新生成前者，因此对其修改应该在后者中进行。

接下来对`CMakeLists_template.txt`中的内容作进一步解释（对语句顺序做了一些手动调整，以便于进行后续讲解）：

```cmake
# 设置CMake的编译环境与版本
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
${cmakeRequiredVersion}

# 设置交叉编译器和工具链
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER  arm-none-eabi-gcc)
set(CMAKE_AR arm-none-eabi-ar)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)
set(SIZE arm-none-eabi-size)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# 项目设置，设置项目名称与所用语言
project(${projectName} C CXX ASM)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

# 添加硬件浮点数所需的宏定义、编译选项与链接，需要时取消注释
#add_compile_definitions(ARM_MATH_CM4;ARM_MATH_MATRIX_CHECK;ARM_MATH_ROUNDING)
#add_compile_options(-mfloat-abi=hard -mfpu=fpv4-sp-d16)
#add_link_options(-mfloat-abi=hard -mfpu=fpv4-sp-d16)

# 添加软件浮点数所需的编译选项，需要时取消注释
#add_compile_options(-mfloat-abi=soft)

# 设置编译选项
add_compile_options(-mcpu=${mcpu} -mthumb -mthumb-interwork)
add_compile_options(-ffunction-sections -fdata-sections -fno-common -fmessage-length=0)

# 设置排除C++17绝对地址警告，需要时取消注释
#set(CMAKE_CXX_FLAGS "$${CMAKE_CXX_FLAGS} -Wno-register")

# 添加汇编文件预处理的编译选项
add_compile_options($<$<COMPILE_LANGUAGE:ASM>:-x$<SEMICOLON>assembler-with-cpp>)

# 设置每种优化各自的编译选项，并打印相应信息
if ("$${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    message(STATUS "Maximum optimization for speed")
    add_compile_options(-Ofast)
elseif ("$${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
    message(STATUS "Maximum optimization for speed, debug info included")
    add_compile_options(-Ofast -g)
elseif ("$${CMAKE_BUILD_TYPE}" STREQUAL "MinSizeRel")
    message(STATUS "Maximum optimization for size")
    add_compile_options(-Os)
else ()
    message(STATUS "Minimal optimization, debug info included")
    add_compile_options(-Og -g)
endif ()

# 设置所用的链接器脚本
set(LINKER_SCRIPT $${CMAKE_SOURCE_DIR}/${linkerScript})

# 添加链接选项，告诉编译器单片机的Flash和RAM大小以及地址分布
add_link_options(-Wl,-gc-sections,--print-memory-usage,-Map=$${PROJECT_BINARY_DIR}/$${PROJECT_NAME}.map)
add_link_options(-mcpu=${mcpu} -mthumb -mthumb-interwork)
add_link_options(-T $${LINKER_SCRIPT})

# 旧CMake的包含头文件语句
include_directories(${includes})

# 旧CMake的设置值宏定义语句
add_definitions(${defines})

# 查找源文件，用于生成执行文件
file(GLOB_RECURSE SOURCES ${sources})

# 添加可执行文件，旧CMake写法
add_executable($${PROJECT_NAME}.elf $${SOURCES} $${LINKER_SCRIPT})

# 设置输出的HEX和BIN文件位置
set(HEX_FILE $${PROJECT_BINARY_DIR}/$${PROJECT_NAME}.hex)
set(BIN_FILE $${PROJECT_BINARY_DIR}/$${PROJECT_NAME}.bin)

# 生成HEX和BIN文件
add_custom_command(TARGET $${PROJECT_NAME}.elf POST_BUILD
        COMMAND $${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:$${PROJECT_NAME}.elf> $${HEX_FILE}
        COMMAND $${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:$${PROJECT_NAME}.elf> $${BIN_FILE}
        COMMENT "Building $${HEX_FILE}
Building $${BIN_FILE}")
```

对于嵌入式项目，CMake 需要额外设置交叉编译器和工具链，添加对汇编语言的支持，各种编译选项，设置单片机对应的链接器，并生成hex和bin文件用于烧录。

而生成的`CMakeLists.txt`大体上保留了旧 CMake 的风格，因此做出以下几个改动：

- 应用 Modern CMake 对源文件、宏定义与路径进行管理；
- 将 HAL 库打包构建成一个静态库，并在上层进行链接；
- 项目构建生成与项目基础设置相互独立。

在此之前，在根目录下创建`User`目录，并在该目录下创建`CMakeLists.txt`、`mainpp.cpp`。

#### 3.5.1 打包 HAL 库并链接

修改上述`CMakeLists_template.txt`的第62行之后的内容：

```cmake
file(GLOB_RECURSE SOURCES ${sources})

add_library(hal STATIC)

target_sources(hal
        PUBLIC
            ${SOURCES}
        )

target_include_directories(hal
        PUBLIC
            ${includes}
        )

target_compile_definitions(hal
        PUBLIC
            ${defines}
        )

add_subdirectory(User)
```

由于 HAL 库内部存在很多调用关系，而且受限于 STM32CubeMX 的代码生成，其内部也难以进行 CMake 库管理，目前只能将其属性规定为 PUBLIC，使 HAL 库内外都可以访问到。

接下来更改刚创建的`User/CMakeLists.txt`，让其链接上刚创建的`hal`库，并担任项目构建生成的工作：

```cmake
add_executable(${PROJECT_NAME}.elf ${LINKER_SCRIPT})

target_sources(${PROJECT_NAME}.elf
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/mainpp.cpp
        )

target_link_libraries(${PROJECT_NAME}.elf
        PRIVATE
            hal
        )

set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
        COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
        COMMENT "Building ${HEX_FILE}
Building ${BIN_FILE}")
```

在`mainpp.cpp`中创建`main()`主函数（记得勾选上`STM32CubeMX | Project Manager | Do not generate the main()`再重新生成代码）：

```c++
#include "main.h"
#include "gpio.h"

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    
    while (1)
    {

    }
}
```

可以发现，位于 HAL 库目录中的`main.h`和`gpio.h`头文件可以成功调用，链接成功。

#### 3.5.2 构建自定义库并链接

在本节中，将构建一个简易的 LED 库作为示例，接口预留与函数封装有所不足请见谅。

在`User`目录下创建以下文件结构（为了不和 HAL 库中的文件发生冲突，库文件添加`l`为前缀，代表`Library`），注意每一层目录都需要新建各自的`CMakeLists.txt`。

```shell
User
  │  CMakeLists.txt
  │  mainpp.cpp
  └─Library
      │  CMakeLists.txt
      └─RGB
              CMakeLists.txt
              lled.cpp
              lled.h
```

接下来先对`Library`目录下的文件进行讲解：

- `User/Library/CMakeLists.txt`：

  ```cmake
  add_subdirectory(RGB)
  ```

  只需要添加子目录即可。

- `User/Library/LED/CMakeLists.txt`：

  ```cmake
  add_library(led STATIC)
  
  target_sources(led
          PRIVATE
              ${CMAKE_CURRENT_SOURCE_DIR}/lled.cpp
          )
  
  target_include_directories(led
          INTERFACE
              ${CMAKE_CURRENT_SOURCE_DIR}
          )
  
  target_link_libraries(led
          PRIVATE
              hal
          )
  ```

  添加`led`静态库，添加源文件与包含目录，并链接`hal`库。

- `User/Library/LED/lled.cpp`与`User/Library/LED/lled.h`见项目文件，不再赘述。

为了在主函数中调用`led`库，还需要修改`User/CMakeLists.txt`，添加`Library`子目录并链接`led`库：

```cmake
add_subdirectory(Library)

target_link_libraries(${PROJECT_NAME}.elf
        PRIVATE
            hal
            led
        )
```

在`mainpp.cpp`的`main()`主函数中调用：

```c++
#include "main.h"
#include "gpio.h"
#include "lled.h"
#include "tim.h"

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_TIM5_Init();

    cRgb led(&htim5);
    while (1)
    {
        led.loop();
    }
}
```

编译成功，至此已完成自定义库的构建与链接。本教程抛砖引玉，希望能有所启发。

## 参考手册

- [CMake Reference Documentation — CMake 3.27.0-rc5 Documentation](https://cmake.org/cmake/help/latest/)

- [Quick CMake tutorial | CLion Documentation (jetbrains.com)](https://www.jetbrains.com/help/clion/quick-cmake-tutorial.html)