#include "ResponseHandler.hpp"

void ResponseHandler::_onPOLLERR(void)
{
        if (this->internal_handler)
        {
                this->unregister_internal_handler();
                this->close_internal_handler();
                this->delete_internal_handler();
        }
        this->unregister();
        this->PollCallback::close();
        delete this;
}
