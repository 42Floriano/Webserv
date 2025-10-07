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

#include "ResponseHandler.hpp"

ResponseHandler::ResponseHandler(Request &req, Response &res, PollSet &pset,
                                 ConfigItem &server_config): _req(req),
        _res(res), _pset(pset), _server_config(server_config)
{
        this->handled = false;
        this->internal_handler = NULL;
}

ResponseHandler::~ResponseHandler(void)
{

}
