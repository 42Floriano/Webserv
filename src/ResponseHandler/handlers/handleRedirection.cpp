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

void    ResponseHandler::handleRedirection(void)
{
        ConfigItem &loc = Config::match_location(&this->getServerConfig(),
                          this->_req.path());
        this->setStatusLine(atoi((*loc["return"])[0]->c_str()));
        this->setContentLength(0);
        console::debug << "Redirection, sending new location: "<<
                       loc["return"][0][1][0] << std::endl;
        this->setHeader("location", *(*loc["return"])[1]);
        this->sealHeaders();
}
