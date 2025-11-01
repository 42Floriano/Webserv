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

#include "HttpClient.hpp"
#include "ResponseHandler.hpp"

ResponseHandler::ResponseHandler(PollSet &pset, int fd, Address *addr,
                                 ConfigItem &server_config):
        HttpClient(pset, fd, addr),
        server_config(server_config)
{
        this->handled = false;
        this->internal_handler = NULL;
}
