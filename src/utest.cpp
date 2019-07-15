#include <iostream>
#include <stdio.h>
#include "CSampleThread.h"


int main(int argc, char *argv[])
{
    printf("[%s (%d)] Unit Test\r\n", __func__, __LINE__);

    CTraditionalThread * pThread = new  CSampleThread();

    pThread->StartThread();
    pThread->StopThread();
    pThread->WaitStop();

    delete pThread;
    return 0;
}