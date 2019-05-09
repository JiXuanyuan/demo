# Shell C

## KMP算法示例

    程序实现了KMP算法，并提供文本进行模式匹配演示。

## Makefile总述

    1）目标规则
        target ... : prerequisites ...
            command ...
        示例：
            main : main.o string.o
                gcc -o main main.o string.o
            main.o : main.c
                gcc -c main.c
            string.o : string.c string.h
                gcc -c string.c
        伪目标：
            .PHONY : clean
            clean :
                rm main *.o
    2.1）定义变量
        CC := gcc
        main : main.o
            $(CC) -c main.o
    2.2）自动化变量
        $@  所有目标
        $<  第一个依赖目标
        $?  依赖目标集合
    3）文件搜寻
        VPATH = src:include
        vpath %.h include
        vpath %.c src
    4）模式规则
        "%"表示长度任意的非空字符串
        %.o : %.c
            gcc -c $< -o $@
