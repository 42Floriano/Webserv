#include "ResponseHandler.hpp"

void	ResponseHandler::delete_internal_handler(void)
{
        if (this->internal_handler == NULL)
                return ;
        if (this->isCGI())
        {
                delete (CGIHandler *)this->internal_handler;
        }
        else
        {
                delete (PollCallback *)this->internal_handler;
        }
}
