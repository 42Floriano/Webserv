#include "ResponseHandler.hpp"
#include <stdlib.h>

void	ResponseHandler::on_eof_callback(void)
{
        this->unregister_internal_handler();
        this->close_internal_handler();
        this->delete_internal_handler();
        this->unregister();
        ::close(this->Socket::fd);
        delete this;
}
