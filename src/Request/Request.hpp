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

#ifndef REQUEST_HPP
# define REQUEST_HPP

#include "Url.hpp"
#include "QueryString.hpp"
#include "PollSock.hpp"
#include "HttpMessage.hpp"
#include "Config.hpp"
#include <iostream>

struct Request : public HttpMessage
{
        Request(std::stringbuf &s);
        ~Request(void);

        Url			*url;
        QueryString	*query;
        std::string	resolved_path;
        const std::string&	method(void)			const;
        const std::string&	path(void)				const;
        const std::string&	request_version(void)	const;
        void				print(std::ostream &os) const;
        void	            target_path(void);
        void				parse_path(ConfigItem &server_config);
};

#endif
