#include "ResponseHandler.hpp"

void ResponseHandler::unregister_internal_handler(void)
{
        if (this->internal_handler == NULL)
                return;
        if (this->isCGI())
        {
                ((CGIHandler *)this->internal_handler)->read_callback.unregister();
                ((CGIHandler *)this->internal_handler)->write_callback.unregister();
        }
        else
        {
                ((PollCallback *)this->internal_handler)->unregister();
        }
}
