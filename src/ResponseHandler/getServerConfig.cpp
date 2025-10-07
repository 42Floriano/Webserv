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

#include "ConfigIter.hpp"
#include "ResponseHandler.hpp"

ConfigItem&	ResponseHandler::getServerConfig(void) const
{
        const std::string	*host_header = this->_req._headers.get("Host");
        if (host_header == NULL)
                throw std::runtime_error("Panic: handle me, there is no host in headers");

        ConfigIter	it = ConfigIter::begin(this->_server_config, "server");
        ConfigIter	end = ConfigIter::end(this->_server_config);

        while (it != end)
        {
                std::string actual_server_name;

                const ConfigItem *server_name = (*it)["server_name"];
                if (server_name != NULL)
                {
                        actual_server_name = server_name->args[0];
                }
                else
                {
                        //careful this shit segfaults if host and listen are not in the config of a server
                        actual_server_name = (*it)["host"]->args[0] + ":" + (*it)["listen"]->args[0];
                }
                if (actual_server_name == *host_header)
                {
                        return (*it);
                }
                ++it;

        }
        throw std::runtime_error("Panic: Host header did not match any server_name");
}
