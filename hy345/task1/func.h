/*SINANIS ANDREAS CSD5150*/

#ifndef __func__
#define __func__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h> 
#include <pwd.h>

/**
 * @brief to size pou tha exoun oloi oi pinakes/buffers
 */
#define SIZE 1024

/**
 * @brief afairei ta white spaces aop to string
 * @param str to string pou tha tou afairethoun ta whitespaces
 * @return trimmed string
 */
char *trim_whitespace(char *str);

/**
 * @brief afairei ta quotes apo ena string, eite einai double or single quotes
 * @param str to string pou tha tou afairethoun ta quotes
 */
void quotes(char *str);

/**
 * @brief function pou elegxei an ena string einai whitespace h oxi
 * @param str to string pou tha ginei o elegxos
 * @return 0 to string einai whitespace
 * @return 1 to string den einai whitespace
 */
int is_whitespace(char *str);

/**
 * @brief ena array pou periexei commands kai simbola opws |,<,<<,>, to spaei se command kai sumbola
 * etsi wste na einai poio eykoli h diaxiristi sto exec
 * @param args o pinakas pou periexei tis edoles
 * @param n to size tou pinaka
 */
void rearrange_cmd(char *args[], int *n);

/**
 * @brief synartisi pou ginontai handle ola ta commands, apo pipes mexri redirection
 * @param args to command pou tha ektelestei 
 * */
void exec_cmd(char *args[]);

#endif