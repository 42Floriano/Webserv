#include "ResponseHandler.hpp"

void	ResponseHandler::setContentType(std::string &path)
{
        const std::string *content_type = ResponseHandler::get_mime(path);
		if (content_type)
			this->setHeader("Content-Type", *content_type);
}
