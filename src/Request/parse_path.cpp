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

#include <map>
#include <iostream>
#include <string>
#include "Config.hpp"
#include "Url.hpp"
#include "QueryString.hpp"
#include "Request.hpp"

void	Request::target_path(void)
{

        std::map<std::string, std::string>::const_iterator it =
                this->query->find("name");
        if (it != this->query->end())
        {
                _first_line[1] = this->url->hier + '/' + it->second;
        }
}

void	Request::parse_path(ConfigItem &server_config)
{
        this->url = new Url(this->path());
        this->query = new QueryString(this->url->query);
        this->target_path();
        this->resolved_path = Config::resolve_path(&server_config, this->path());
}
