
#define INCL_WIN
#include <os2.h>

#define ID_CANVAS  1

MRESULT EXPENTRY CanvasWndProc(HWND hwnd,
                               USHORT msg,
                               MPARAM mp1,
                               MPARAM mp2)
{
    switch (msg) {
    case WM_CLOSE:
        WinPostMsg(hwnd, WM_QUIT, 0L, 0L);
        return (MRESULT)0;

    default:
        return WinDefWindowProc(hwnd, msg, mp1, mp2);
    }
}

int main(void)
{
    HAB hab;
    HMQ hmq;
    QMSG qmsg;
    HWND hwndFrame;
    HWND hwndClient;
    ULONG flFrameFlags;

    hab = WinInitialize(0);
    hmq = WinCreateMsgQueue(hab, 0);

    WinRegisterClass(hab,
                     "CanvasClass",
                     CanvasWndProc,
                     CS_SIZEREDRAW,
                     0);

    flFrameFlags = FCF_TITLEBAR |
                   FCF_SYSMENU |
                   FCF_SIZEBORDER |
                   FCF_MINMAX;

    hwndFrame = WinCreateStdWindow(
        HWND_DESKTOP,
        WS_VISIBLE,
        &flFrameFlags,
        "CanvasClass",
        "Canvas",
        0L,
        (HMODULE)0,
        ID_CANVAS,
        &hwndClient
    );

    while (WinGetMsg(hab, &qmsg, 0, 0, 0))
        WinDispatchMsg(hab, &qmsg);

    WinDestroyWindow(hwndFrame);
    WinDestroyMsgQueue(hmq);
    WinTerminate(hab);

    return 0;
}