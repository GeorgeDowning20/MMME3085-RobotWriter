#include <stdio.h>
#include <string.h>

#ifndef SERIAL_H_INCLUDED
#define SERIAL_H_INCLUDED

#define cport_nr    0                /* COM number minus 1 */
#define bdrate      115200              /* 115200  */

#if defined(__linux__) || defined(__FreeBSD__) || defined(__APPLE__)
#include <unistd.h>
extern unsigned int Sleep(unsigned int ms);
#endif

int PrintBuffer (char *buffer);                 //JIB: Needed to match the function
int WaitForReply (void);                        // Wait for OK function
int WaitForDollar (void);                       // Wait for '$' function (for startup)
int CanRS232PortBeOpened ( void );              // Port open check
void CloseRS232Port (void);



#endif // SERIAL_H_INCLUDED
