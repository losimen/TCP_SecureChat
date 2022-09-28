#include "servertypes.h"
#include "servererrors.h"

using namespace ServerTypes;


LogIn LogIn::parseData(QJsonObject jsonObject)
{
    QJsonObject::const_iterator endIt = jsonObject.constEnd();

    if (jsonObject.find("request") == endIt)
        throw ServerErrors::MissingArgument("request");

    return LogIn();
}
