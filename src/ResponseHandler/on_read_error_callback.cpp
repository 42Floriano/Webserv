#include "ResponseHandler.hpp"

void	ResponseHandler::on_read_error_callback(void)
{
        if (this->internal_handler != NULL)
        {
                this->unregister_internal_handler();
                this->close_internal_handler();
                this->delete_internal_handler();
        }
}
