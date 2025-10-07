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

#ifndef CGIHANDLER_HPP
# define CGIHANDLER_HPP

#include "Process.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "FdWriter.hpp"
#include "CGIReader.hpp"

struct CGIHandler
{
        Process		proc;
        CGIReader	read_callback;
        FdWriter	write_callback;

        CGIHandler(const std::string &cmd, Request &req, Response &res, PollSet &pset);
        ~CGIHandler();
};

#endif
