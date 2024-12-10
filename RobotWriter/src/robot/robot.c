/**
 * @file robot.c
 * @brief Implementation of robot control functions for positioning and movement.
 * @details
 * This file provides the implementation of functions that control a robot through
 * RS232 commands. It includes functionality to:
 * - Initialize and start up the robot.
 * - Move the robot to a home position.
 * - Send stroke commands that move the pen or tool along specified coordinates
 *   and toggle its state.
 *
 * All movements and actions are communicated to the robot via serial commands,
 * and the code ensures proper handling of command acknowledgments and waiting
 * periods.
 * @note View documentation at https://georgedowning20.github.io/MMME3085-RobotWriter/
 */
#include "robot.h"

///////////////////////////////////////////////////////////////////////
//                        PRIVATE   DECLARATIONS                     //
///////////////////////////////////////////////////////////////////////

/**
 * @brief Sends a command buffer to the robot and waits for a reply.
 * @param[in] buffer The command buffer to send.
 * @return SUCCESS on successful command transmission, or an appropriate error code.
 */
static errorCode_t SendCommands(char *const buffer);

///////////////////////////////////////////////////////////////////////
//                        PUBLIC   DEFINITIONS                       //
///////////////////////////////////////////////////////////////////////

/**
 * @details
 * Moves the robot to a defined home position by sending the appropriate G-code
 * command. After constructing the G-code command with the home coordinates, it
 * sends the command to the robot and prints the command for debugging purposes.
 */
errorCode_t HomeRobot(void)
{
    char buffer[256];                                                                                   // Buffer to hold command
    snprintf(buffer, sizeof(buffer), "S0 G0 X%.2lf Y%.2lf ; Home\n", HOME_X_VALUE_MM, HOME_Y_VALUE_MM); // Construct command
    SendCommands(buffer);                                                                               // Send command
    printf("%s", buffer);                                                                               // Print command

    return SUCCESS; // Return success
}

/**
 * @details
 * Sends a stroke command to the robot based on the provided cursor position and stroke data.
 * The stroke includes a vector (defining the movement direction and distance) and a pen state
 * (up or down). Depending on the pen state, the command uses either a rapid move (G0) with no
 * drawing or a linear move (G1) with drawing. After forming the command, the function sends it
 * to the robot and prints the command for debugging.
 */
errorCode_t SendStoke(const cursor_t *const cursor, const stroke_t stroke)
{
    Coord2D_t pos = AddCoord2D(cursor->posisiton, stroke.vec);                     // Calculate new position
    const char *command = stroke.pen_state ? "S1000 G1" : "S0 G0";                 // Set command based on pen state
    char buffer[256];                                                              // Buffer to hold command
    snprintf(buffer, sizeof(buffer), "%s X%.2lf Y%.2lf\n", command, pos.x, pos.y); // Construct command
    SendCommands(buffer);                                                          // Send command
    printf("%s", buffer);                                                          // Print command
    return SUCCESS;
}

/**
 * @details
 * Initializes the robot by attempting to open the RS232 port and then
 * sending a sequence of commands to prepare the robot. It sets the robot
 * to a known position, starts the spindle or pen movement, sets initial
 * speed parameters, and finally moves the robot to the home position.
 * If the COM port cannot be opened, it reports an error.
 */
errorCode_t StartUpRobot(void)
{
    if (CanRS232PortBeOpened() == -1)                       // Check if COM port can be opened
        return ErrorHandler(ERROR_UNABLE_TO_OPEN_COM_PORT); // Handle error

    char buffer[100];        // Buffer to hold command
    sprintf(buffer, "\n");   // Construct command
    PrintBuffer(&buffer[0]); // Print command

    Sleep(100);      // Wait for command to be sent
    WaitForDollar(); // Wait for reply
    Sleep(100);      // Wait for reply

    sprintf(buffer, "G1 X0 Y0 F1000\n"); // Construct command
    SendCommands(buffer);                // Send command

    sprintf(buffer, "M3\n"); // Construct command
    SendCommands(buffer);    // Send command

    sprintf(buffer, "S0\n"); // Construct command
    SendCommands(buffer);    // Send command

    HomeRobot();    // Move robot to home position
    return SUCCESS; // Return success
}

///////////////////////////////////////////////////////////////////////
//                        PRIVATE   DEFINITIONS                      //
///////////////////////////////////////////////////////////////////////

/**
 * @details Sends the provided command buffer to the robot and waits for a
 * reply using the rs232 library.
 */
static errorCode_t SendCommands(char *const buffer)
{
    PrintBuffer(&buffer[0]); // Print command
    WaitForReply();          // Wait for reply
    Sleep(1);                // Wait for reply
    return SUCCESS;          // Return success
}
