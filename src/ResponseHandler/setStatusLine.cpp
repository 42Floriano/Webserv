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

void ResponseHandler::setStatusLine(int statusCode)
{

        this->_res.response_version("HTTP/1.1");

        switch (statusCode)
        {
        case 100:
                this->_res.status_code("100");
                this->_res.status_msg("Continue");
                break;
        case 101:
                this->_res.status_code("101");
                this->_res.status_msg("Switching Protocols");
                break;
        case 102:
                this->_res.status_code("102");
                this->_res.status_msg("Processing");
                break;
        case 103:
                this->_res.status_code("103");
                this->_res.status_msg("Early Hints");
                break;
        case 200:
                this->_res.status_code("200");
                this->_res.status_msg("OK");
                break;
        case 201:
                this->_res.status_code("201");
                this->_res.status_msg("Created");
                break;
        case 202:
                this->_res.status_code("202");
                this->_res.status_msg("Accepted");
                break;
        case 203:
                this->_res.status_code("203");
                this->_res.status_msg("Non-Authorative Information");
                break;
        case 204:
                this->_res.status_code("204");
                this->_res.status_msg("No Content");
                break;
        case 205:
                this->_res.status_code("205");
                this->_res.status_code("Reset Content");
                break;
        case 206:
                this->_res.status_code("206");
                this->_res.status_msg("Partial Content");
                break;
        case 207:
                this->_res.status_code("207");
                this->_res.status_msg("Multi-Status");
                break;
        case 208:
                this->_res.status_code("208");
                this->_res.status_msg("Already Reported");
                break;
        case 226:
                this->_res.status_code("208");
                this->_res.status_msg("IM Used");
                break;
        case 301:
                this->_res.status_code("301");
                this->_res.status_msg("Moved Permanently");
                break;
        case 302:
                this->_res.status_code("302");
                this->_res.status_msg("Found");
                break;
        case 303:
                this->_res.status_code("303");
                this->_res.status_msg("");
                break;
        case 304:
                this->_res.status_code("304");
                this->_res.status_msg("Not Modified");
                break;
        case 307:
                this->_res.status_code("307");
                this->_res.status_msg("");
                break;
        case 308:
                this->_res.status_code("308");
                this->_res.status_msg("");
                break;
        case 400:
                this->_res.status_code("400");
                this->_res.status_msg("Bad Request");
                break;
        case 401:
                this->_res.status_code("401");
                this->_res.status_msg("Unauthorized");
                break;
        case 402:
                this->_res.status_code("402");
                this->_res.status_msg("Payment Required");
                break;

        case 403:
                this->_res.status_code("403");
                this->_res.status_msg("Forbidden");
                break;
        case 404:
                this->_res.status_code("404");
                this->_res.status_msg("Not Found");
                break;
        case 405:
                this->_res.status_code("405");
                this->_res.status_msg("Method Not Allowed");
                break;
        case 406:
                this->_res.status_code("406");
                this->_res.status_msg("Not Acceptable");
                break;
        case 407:
                this->_res.status_code("407");
                this->_res.status_msg("Proxy Authentication Required");
                break;
        case 408:
                this->_res.status_code("408");
                this->_res.status_msg("Request Timeout");
                break;
        case 409:
                this->_res.status_code("409");
                this->_res.status_msg("Conflict");
                break;
        case 410:
                this->_res.status_code("410");
                this->_res.status_msg("Gone");
                break;
        case 411:
                this->_res.status_code("411");
                this->_res.status_msg("Length Required");
                break;
        case 412:
                this->_res.status_code("412");
                this->_res.status_msg("Precondition Failed");
                break;
        case 413:
                this->_res.status_code("413");
                this->_res.status_msg("Content Too Large");
                break;
        case 414:
                this->_res.status_code("414");
                this->_res.status_msg("Uri Too Long");
                break;
        case 415:
                this->_res.status_code("415");
                this->_res.status_msg("Unsupported Media Type");
                break;
        case 416:
                this->_res.status_code("416");
                this->_res.status_msg("Range Not Satisfied");
                break;
        case 417:
                this->_res.status_code("417");
                this->_res.status_msg("Expectation Failed");
                break;
        case 418:
                this->_res.status_code("418");
                this->_res.status_msg("I'm a teapot");
                break;
        case 421:
                this->_res.status_code("421");
                this->_res.status_msg("Misdirect Request");
                break;
        case 422:
                this->_res.status_code("422");
                this->_res.status_msg("Unprocessable Content");
                break;
        case 423:
                this->_res.status_code("423");
                this->_res.status_msg("Locked");
                break;
        case 424:
                this->_res.status_code("424");
                this->_res.status_msg("Failed Dependency");
                break;
        case 425:
                this->_res.status_code("425");
                this->_res.status_msg("Too Early");
                break;
        case 426:
                this->_res.status_code("426");
                this->_res.status_msg("Update Required");
                break;
        case 428:
                this->_res.status_code("428");
                this->_res.status_msg("Precondition Required");
                break;
        case 429:
                this->_res.status_code("429");
                this->_res.status_msg("Too Many Requests");
                break;
        case 431:
                this->_res.status_code("431");
                this->_res.status_msg("Request Header Fields Too Large");
                break;
        case 451:
                this->_res.status_code("451");
                this->_res.status_msg("Unaviable For Legal Reason");
                break;
        case 500:
                this->_res.status_code("500");
                this->_res.status_msg("Internal Server Error");
                break;
        case 501:
                this->_res.status_code("501");
                this->_res.status_msg("Not Implemented");
                break;
        case 502:
                this->_res.status_code("502");
                this->_res.status_msg("Bad Gateway");
                break;
        case 503:
                this->_res.status_code("503");
                this->_res.status_msg("Service Unavailable");
                break;
        case 504:
                this->_res.status_code("504");
                this->_res.status_msg("Getaway Timeout");
                break;
        case 505:
                this->_res.status_code("505");
                this->_res.status_msg("HTTP Version Not Supported");
                break;
        case 506:
                this->_res.status_code("506");
                this->_res.status_msg("Variant Also Negotates");
                break;
        case 507:
                this->_res.status_code("507");
                this->_res.status_msg("Insufficient Storage");
                break;
        case 508:
                this->_res.status_code("508");
                this->_res.status_msg("Loop Detected");
                break;
        case 510:
                this->_res.status_code("510");
                this->_res.status_msg("Not Extended");
                break;
        case 511:
                this->_res.status_code("511");
                this->_res.status_msg("Network Authentication Required");
                break;
        default:
                throw std::runtime_error("Invalid HTTP response status code");
        }
}
