/* Start Header -------------------------------------------------------
Copyright (C) 2011 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent
of DigiPen Institute of Technology is prohibited.

File Name: log.h
Purpose: Prototypes for a basic log to file mechanism.
Language: ANSI C
Platform: N/A
Project: cs230_marcus.meng_1
Author: Marcus Meng (marcus.meng) 80002709
Creation date: 2011-05-30
- End Header --------------------------------------------------------*/
#ifndef LOG_H
#define LOG_H

void log_init(void);
void log_close(void);
void log_message(const char* message);

#endif /* LOG_H */

