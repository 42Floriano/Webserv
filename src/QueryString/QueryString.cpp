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

#include <iostream>
#include <string>
#include <map>
#include "../Url/Url.hpp"
#include "QueryString.hpp"

QueryString::QueryString(const std::string &str)
{
        this->parse(str);
}

void	QueryString::parse(const std::string &query)
{
        std::size_t	start = 0;

        while (start < query.length())
        {
                std::size_t end = query.find('&', start);
                if (end == std::string::npos)
                        end = query.length();

                std::size_t	eq = query.find('=', start);
                if (eq != std::string::npos && eq < end)
                {
                        std::string key = Url::decode(query.substr(start, eq - start));
                        std::string val = Url::decode(query.substr(eq + 1, end - eq - 1));
                        this->insert(std::make_pair(key, val));
                }
                start = end + 1;
        }

}

void	QueryString::print() const
{

        for (const_iterator it = begin(); it != end(); ++it)
        {
                std::cout << it->first << " = " << it->second << std::endl;
        }
}
