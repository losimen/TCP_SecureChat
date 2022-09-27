#include "handlerrequest.h"

HandlerRequest::HandlerRequest()
{

}

void HandlerRequest::run()
{
    qDebug() << "handle request";

    emit result(34);
}
