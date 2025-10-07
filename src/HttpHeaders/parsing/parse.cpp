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

#include "Console.hpp"
#include "HttpHeaders.hpp"

static bool	is_obsolate_fold(const std::string &line)
{
        if (!line.empty())
        {
                if (line[0] == ' ' || line[0] == '\t')
                        return (true);
        }
        return (false);
}

void	HttpHeaders::parse(const std::string &line)
{

        if (this->sealed == false)
        {
                if (line.empty())
                {
                        if (!key.empty())
                                // we insert the buffered data in the underlyng map
                                this->insert_buffered_key_value();
                        // we seal headers (call to this->parse won't work anymore)
                        this->sealed = true;
                        console::debug << "Done parsing headers" << std::endl;
                }
                else if (!is_obsolate_fold(line))
                {

                        // we buffer a new header
                        if (!key.empty())
                                this->insert_buffered_key_value();
                        std::istringstream	iss(line);
                        HttpHeaders::parse_key(iss, this->key);
                        HttpHeaders::parse_value(iss, this->value);
                }
                else if (!key.empty() && is_obsolate_fold(line))
                {
                        // we join the obsolate fold to the current value
                        this->value += " " + line.substr(1);
                        HttpHeaders::trim_string(this->value);
                }
                else if (!key.empty() && !is_obsolate_fold(line))
                {
                        this->insert_buffered_key_value();
                }
                else /* if (!key.empty() && is_obsolate_fold(line)) */
                {
                        throw std::runtime_error("Headers with obsolate fold before a key/header_name is given ?");
                }
        }
        else
        {
                throw std::runtime_error("Headers were sealed, why are you still parsing ?");
        }
}
