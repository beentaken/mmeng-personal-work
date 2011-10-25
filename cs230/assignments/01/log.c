/* Start Header -------------------------------------------------------
Copyright (C) 2011 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent
of DigiPen Institute of Technology is prohibited.

File Name: log.c
Purpose: Implementation for a basic log-to-file mechanism.
Language: ANSI C
Platform: N/A
Project: cs230_marcus.meng_1
Author: Marcus Meng (marcus.meng) 80002709
Creation date: 2011-05-30
- End Header --------------------------------------------------------*/
#include <stdio.h>

static FILE* log_file;

void log_init(void)
{
    log_file = fopen("Output.txt", "wt");
}

void log_close(void)
{
    fclose(log_file);
}

void log_message(const char* message)
{
    fprintf(log_file, "%s", message);
}

