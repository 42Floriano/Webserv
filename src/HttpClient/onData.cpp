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

void	HttpClient::onData(void)
{
        if (this->incoming._decoding_phase != HttpMessage::decoding_done)
        {
                HttpMessage::decode(this->incoming);
        }
        if (this->incoming._decoding_phase > HttpMessage::decoding_header
                        && this->handled == false)
        {
                console::info <<
                "http Request received (mind: request body may not be there yet)" << std::endl;
                console::info
                                << "Request data:" << std::endl;
                ++console::info
                                << this->incoming.method() << " " << this->incoming.path() << std::endl;
                this->incoming._headers.print(console::info);
                --console::info;
                this->handleRequest();
                this->_pset.registerCallback(POLLOUT, this);
                this->handled = true;
        }
        if (this->incoming._decoding_phase == HttpMessage::decoding_done)
        {
                this->_pset.removeCallback(POLLIN, this);
        }
        console::debug << "Current Body Size: " << this->incoming.current_body_size <<
                       std::endl;
}

void	HttpClient::handleRequest(void)
{
        ssize_t max_body_size = this->_handler.getMaxBodySize();
        if (max_body_size != -1
                        && this->incoming.current_body_size > (size_t) max_body_size)
        {
                this->_handler.setErrorResponse("", 413);
        }
        else
        {
                try
                {
                        this->_handler.handleResponse();
                }
                catch (const std::exception &err)
                {
                        console::error << "Handler error: " << err.what() << std::endl;
                        this->_handler.setErrorResponse("", 404);
                        // TODO: cleanup we may be still parsing the request
                        // ??? maybe is enough to:
                        // this->incoming.phase(HttpMessage::decoding_done);
                }
        }
}
