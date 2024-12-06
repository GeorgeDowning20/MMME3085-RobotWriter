#include "robot.h"

static errorCode_t SendCommands(char *const buffer);

errorCode_t HomeRobot(void)
{
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "S0 G0 X%.2lf Y%.2lf ; Home\n", HOME_X_VALUE_MM, HOME_Y_VALUE_MM);
    SendCommands(buffer);
    printf("%s", buffer);

    return SUCCESS;
}

errorCode_t SendStoke(const cursor_t *const cursor, const stroke_t stroke)
{
    Coord2D_t pos = AddCoord2D(cursor->posisiton, stroke.vec);
    const char *command = stroke.pen_state ? "S1000 G1" : "S0 G0";
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "%s %s X%.2lf Y%.2lf\n",draw, command, pos.x, pos.y);
    SendCommands(buffer);
    printf("%s", buffer);
    return SUCCESS;
}

static errorCode_t SendCommands(char *const buffer)
{
    PrintBuffer(&buffer[0]);
    WaitForReply();
    Sleep(1);
    return SUCCESS;
}

errorCode_t StartUpRobot(void)
{
    if (CanRS232PortBeOpened() == -1)
        return ErrorHandler(ERROR_UNABLE_TO_OPEN_COM_PORT);

    char buffer[100];
    sprintf(buffer, "\n");
    PrintBuffer(&buffer[0]);

    Sleep(100);
    WaitForDollar();
    Sleep(100);

    sprintf(buffer, "G1 X0 Y0 F1000\n");
    SendCommands(buffer);

    sprintf(buffer, "M3\n");
    SendCommands(buffer);

    sprintf(buffer, "S0\n");
    SendCommands(buffer);

    HomeRobot();
    return SUCCESS;
}
