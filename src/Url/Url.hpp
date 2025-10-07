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

#ifndef URL_HPP
# define URL_HPP

#include "Console.hpp"

struct	Url: protected std::string
{

        static std::string	encode(const std::string &str);
        static std::string	decode(const std::string &str);

        static std::string	get_protocol(const std::string &url);
        static std::string	get_host(const std::string &url);
        static std::string	get_port(const std::string &url);
        static std::string	get_hier(const std::string &url);
        static std::string	get_path(const std::string &url);
        static std::string	get_query(const std::string &url);
        static std::string	get_fragment(const std::string &url);

        std::string	protocol;
        std::string	hier;
        std::string	host;
        std::string	port;
        std::string	path;
        std::string	query;
        std::string	fragment;

        Url(void);
        Url(const std::string &url);
        Url&	operator=(const std::string &url);

        const std::string&	to_string(void);

        void	print(std::ostream &os) const;
};

std::ostream& operator<<(std::ostream &os, const Url &url);

#endif
