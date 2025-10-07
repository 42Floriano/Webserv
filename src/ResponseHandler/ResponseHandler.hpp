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

#ifndef RESPONSEHANDLER_HPP
# define RESPONSEHANDLER_HPP

#include <cstdlib>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <cstring>
#include <cstdio>
#include <unistd.h>

#include "CGIHandler.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "FdReader.hpp"
#include "FdWriter.hpp"

class ResponseHandler
{
        static const std::string	*get_mime(const std::string &path);
public:
        ResponseHandler(
                Request &req,
                Response &res,
                PollSet &pset,
                ConfigItem &server_config
        );
        ~ResponseHandler(void);

public:
        bool					isCGI();
        bool					isRedirection();
        ConfigItem&				getLocation(void) const;
        ssize_t					getMaxBodySize(void) const;
        ConfigItem&				getServerConfig(void) const;
        int					getErrorPageFd(int status_code, size_t *len);
        bool                                    handled;
        Request&				_req;
        Response&				_res;
        PollSet&                _pset;
        ConfigItem&				_server_config;
        int						internal_handler_type;
        void					*internal_handler;

public:
        Request&				req(void);
        Request&				res(void);

public:
        void                                    handleRedirection(void);
        void					handleCGI(void);
        void					handleGET(void);
        void					handlePOST(void);
        void					handleDELETE(void);
        void					handleInvalidMethod(void);

public:
        static size_t   getFileLength(const std::string &filename);
        const char		*getRequestPath(void);

public:
        bool		handleResponse(void);

public:
        bool	        isMethodAllowed() const;
public:
        void		setStatusLine(int statusCode);
        void		setHeader(const std::string &key, const std::string &value);
        void		setContentLength(size_t content_length);
        void	        setContentType(std::string &path);
        void		sealHeaders(void);
        std::string     getFilename(void);
        void            setErrorResponse(const std::string &msg, int statusCode);
public:
        int             openReg(std::string path, int bit);
};

#endif
