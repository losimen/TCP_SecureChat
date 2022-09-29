#ifndef REQUESTEXECUTOR_H
#define REQUESTEXECUTOR_H

#include <QString>

#include "servertypes.h"
#include "clienttypes.h"


class RequestExecutor
{
public:
    RequestExecutor();

    static ClientTypes::Error error(const StatusCodes &statusCode, const QString &what);

    static ClientTypes::LogIn logIn(const ServerTypes::LogIn &logIn_server);
};

#endif // REQUESTEXECUTOR_H
