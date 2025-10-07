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

#include "HttpHeaders.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "CGIHandler.hpp"
#include "HttpClient.hpp"
#include "ResponseHandler.hpp"
#include "Process.hpp"

void	ResponseHandler::handleCGI(void)
{
        // TODO: the cmd/binary full path should be set in the config:
        const ConfigItem	*cgi_path = this->getLocation()["cgi_path"];
        if (!cgi_path)
                throw std::runtime_error("No CGI path specified, we don't know what to run execute");
        std::string			cmd = cgi_path->args[0] + " ";
        const std::string	&script_path = this->getRequestPath();

        cmd += script_path;
        console::debug << "Script path: " << script_path << std::endl;
        console::debug << "Cmd: " << cmd << std::endl;

        this->setStatusLine(200);
        this->internal_handler = new CGIHandler(
                cmd,
                this->_req,
                this->_res,
                this->_pset
        );
        this->handled = true;
}
