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

bool	ResponseHandler::handleResponse(void)
{
        console::debug << "=== Handle response START ===" << std::endl;
        this->_req.parse_path(this->getServerConfig());
        this->setHeader("Connection", "close");
        if (this->isMethodAllowed() == false)
        {
                console::debug << "Default INVALID METHOD handler called" << std::endl;
                this->handleInvalidMethod();
        }
        else if (this->isRedirection())
                this->handleRedirection();
        else if (this->isCGI())
                this->handleCGI();
        else if (this->_req.method() == "GET")
        {
                console::debug << "Default GET handler called" << std::endl;
                this->handleGET();
        }
        else if (this->_req.method() == "POST")
        {
                console::debug << "Default POST handler called" << std::endl;
                this->handlePOST();
        }
        else if (this->_req.method() == "DELETE")
        {
                console::debug << "Default DELETE handler called" << std::endl;
                this->handleDELETE();
        }
        this->handled = true;
        console::debug << "=== Handle response END ===" << std::endl;
        return (true);
}
