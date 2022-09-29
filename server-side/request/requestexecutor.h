#ifndef REQUESTEXECUTOR_H
#define REQUESTEXECUTOR_H

#include <QString>

#include "servertypes.h"
#include "clienttypes.h"


class RequestExecutor
{
public:
    RequestExecutor();

    static ClientTypes::InvalidFormat invalidFormat(const QString what);
    static ClientTypes::MissingAgument missingArgument(const QString what);
    static ClientTypes::InternalError internalError(const QString what);

    static ClientTypes::LogIn logIn(const ServerTypes::LogIn &logIn_server);
};

#endif // REQUESTEXECUTOR_H
