#include "ResponseHandler.hpp"

void ResponseHandler::close_internal_handler()
{
        if (this->internal_handler == NULL)
                return ;
        if (this->isCGI())
        {
                ((CGIHandler *)this->internal_handler)->read_callback.close();
                ((CGIHandler *)this->internal_handler)->write_callback.close();
        }
        else
        {
                ((PollCallback *)this->internal_handler)->close();
        }
}
