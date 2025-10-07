/*

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU Affero General Public License as
 published by the Free Software Foundation, either version 3 of the
 License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Affero General Public License for more details.

 You should have received a copy of the GNU Affero General Public License
 along with this program.  If not, see <https://www.gnu.org/licenses/>.

*/

#ifndef RESPONSE_HPP
# define RESPONSE_HPP

#include "Socket.hpp"
#include "HttpMessage.hpp"
#include "Request.hpp"
#include "Config.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>

class Response : public HttpMessage
{

public:
        enum /* methods */
        {
                GET,
                POST,
                DELETE,
                EMPTY,
        };

public:
        int							_status_code;
        bool						_is_set;

public:
        Response(std::stringbuf &s);
        ~Response(void);

public:
        void	response_version(const std::string &s);
        void	status_code(const std::string &s);
        void	status_msg(const std::string &s);

public:
        void				setMethod(const std::string &path);
        void 				setErrorResponse(const std::string &message);

};

std::ostream&	operator<<(std::ostream &os, const Response &res);
ConfigItem&	match_location(const std::string &path, ConfigItem &server_config);

#endif
