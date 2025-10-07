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

#ifndef HTTPHEADERS_HPP
# define HTTPHEADERS_HPP

#include <stdexcept>
#include <sys/types.h>
#include <string>
#include <map>
#include <sstream>

/* Wrapper around a  string->string map, used for handling http headers */

class HttpHeaders : protected std::map<std::string, std::string>
{

private: /* static utils */
        static void		normalize_key(std::string &key);
        static void		trim_string(std::string &str);
        static void		parse_key(std::istringstream &src, std::string &dst);
        static void		parse_value(std::istringstream &src, std::string &dst);


public: /* default constructor and deconstructor */
        HttpHeaders(void);
        ~HttpHeaders(void);

private: /* buffered key and value of the currently parsed item */
        std::string	key;
        std::string value;
        /* boolean saying if we can add / remove items to the map*/
        bool		sealed;

public:
        bool				empty(void) const;
        void				insert(const std::string &key, const std::string &value);
        const std::string	*get(const std::string &key) const;
        std::string			*mutable_get(const std::string &key);
        void				remove(const std::string &key);
        bool				is_sealed();
        void				seal(void);
        void				unseal(void);
        ssize_t				content_length(void) const;

        void				insert_buffered_key_value(void);

        void				parse(const std::string &line);

        std::string&			parse_new_header(const std::string &line);
        void				print(std::ostream &os) const;
        map::iterator		begin(void);
        map::iterator		end(void);
};

#endif
