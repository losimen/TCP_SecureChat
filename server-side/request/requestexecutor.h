#ifndef REQUESTEXECUTOR_H
#define REQUESTEXECUTOR_H

#include "servertypes.h"


class RequestExecutor
{
public:
    RequestExecutor();

    static void logIn(const ServerTypes::LogIn &data);
};

#endif // REQUESTEXECUTOR_H
