#include <stdio.h>
#include <stdlib.h>

#include "serial.h"

#include <unistd.h>

#if defined(__WINDOWS__)
#include <conio.h>
#include <Windows.h>
#endif

#if defined(__linux__) || defined(__APPLE__)
#include <stdlib.h>
#include <unistd.h>

unsigned int Sleep(unsigned int ms) {
    return usleep(ms * 1000); // Convert milliseconds to microseconds
}

#endif

#include "rs232.h"

#define Serial_Mode
// #define DEBUG_MODE 

#ifdef Serial_Mode   // Code for running with robot

// Open port with checking
int CanRS232PortBeOpened ( void )
{
    char mode[]= {'8','N','1',0};
    if(RS232_OpenComport(cport_nr, bdrate, mode,0))
    {
#ifdef DEBUG_MODE
        printf("Can not open comport\n");
#endif
        return(-1);
    }
    return (0);      // Success
}

// Function to close the COM port
void CloseRS232Port (void)
{
    RS232_CloseComport(cport_nr);
}

// Write text out via the serial port
int PrintBuffer (char *buffer)
{
    RS232_cputs(cport_nr, buffer);
#ifdef DEBUG_MODE
    printf("sent: %s\n", buffer);
#endif
    return (0);
}

int WaitForDollar (void)
{
    int i, n;

    unsigned char buf[4096];

    while(1)
    {
#ifdef DEBUG_MODE
        printf (".");
#endif
        n = RS232_PollComport(cport_nr, buf, 4095);

        if(n > 0)
        {
#ifdef DEBUG_MODE
            printf ("RCVD: N = %d ", n);
#endif
            buf[n] = 0;   /* always put a "null" at the end of a string! */

            for(i=0; i < n; i++)
            {
                if(buf[i] == '$')  /* replace unreadable control-codes by dots */
                {
#ifdef DEBUG_MODE
                    printf("received %i bytes: %s \n", n, (char *)buf);
                    printf("\nSaw the Dollar\n");
#endif
                    return 0;
                }
            }

#ifdef DEBUG_MODE
            printf("received %i bytes: %s \n", n, (char *)buf);
#endif

            if ( (buf[0] == 'o') && (buf[1] == 'k') )
                return 0;
        }

        Sleep(100);
    }

    return(0);
}

int WaitForReply (void)
{
    int i, n;

    unsigned char buf[4096];

#ifdef DEBUG_MODE
    printf ("Waiting for reply\n");
#endif

    while(1)
    {
#ifdef DEBUG_MODE
        printf (".");
#endif
        n = RS232_PollComport(cport_nr, buf, 4095);

        if(n > 0)
        {
#ifdef DEBUG_MODE
            printf ("RCVD: N = %d ", n);
#endif
            buf[n] = 0;   /* always put a "null" at the end of a string! */

            for(i=0; i < n; i++)
            {
                if(buf[i] < 32)  /* replace unreadable control-codes by dots */
                {
                    buf[i] = '.';
                }
            }

#ifdef DEBUG_MODE
            printf("received %i bytes: %s\n", n, (char *)buf);
#endif

            if ( (buf[0] == 'o') && (buf[1] == 'k') )
                return 0;
        }

        Sleep(100);
    }

    return(0);
}

#else  // Code for testing with emulator

// Open port with checking
int CanRS232PortBeOpened ( void )
{
    return (0);      // Success
}

// Function to close the COM port
void CloseRS232Port (void)
{
    return;
}

// Print the buffer contents to the terminal
int PrintBuffer (char *buffer)
{
#ifdef DEBUG_MODE
    printf("%s \n",buffer);
#endif
    return (0);
}

// Dummy function, will wait for key press
int WaitForReply (void)
{
    getc(stdin);
    return (0);
}

// Dummy function, will wait for key press
int WaitForDollar (void)
{
    getc(stdin);
    return (0);
}

#endif
