#include "handlerrequest.h"

HandlerRequest::HandlerRequest()
{

}

void HandlerRequest::run()
{
    // Do request job here...

    emit on_finishRequest(34, this);
}
