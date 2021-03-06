/**
 * @file colors.h
 * @author Edgar Boule (edgar.boule@utbm.fr)
 * @brief Header for simple usage of colors in c programs.
 * @version 0.1
 * @date 2021-04-08
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdio.h>
#include <stdlib.h>

/* Text colors */
#define BLK    "\x1B[30m"
#define RED    "\x1B[31m"
#define GRN    "\x1B[32m"
#define YEL    "\x1B[33m"
#define BLU    "\x1B[34m"
#define MAG    "\x1B[35m"
#define CYN    "\x1B[36m"
#define WHT    "\x1B[37m"


/* Background colors */
#define BBLK   "\x1B[40m"
#define BRED   "\x1B[41m"
#define BGRN   "\x1B[42m"
#define BYEL   "\x1B[43m"
#define BBLU   "\x1B[44m"
#define BMAG   "\x1B[45m"
#define BCYN   "\x1B[46m"
#define BWHT   "\x1B[47m"

/* Reset colors */
#define RST  "\x1B[0m"
