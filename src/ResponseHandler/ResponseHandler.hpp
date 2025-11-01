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

#include "HttpClient.hpp"
#include "CGIHandler.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "FdReader.hpp"
#include "FdWriter.hpp"

struct ResponseHandler: public HttpClient
{
        void	_onPOLLHUP(void);
        void	_onPOLLERR(void);
        // only two fields
        ConfigItem&			server_config;
        void				*internal_handler;

        // these are the event callbacks (poll events are handeled internally
        // and they expose these callbacks inste);
        void				on_nothing_to_write(void);
        void				on_eof_callback(void);
        void				on_read_error_callback(void);

        ResponseHandler(PollSet &pset, int fd, Address *addr,
                        ConfigItem &server_config);
        ~ResponseHandler();

        // Main function of this class: it overrides the underlying virtual
        // called by HttpClient
        bool				handleResponse(void);

        void				handleRedirection(void);
        void				handleCGI(void);
        void				handleGET(void);
        void				handlePOST(void);
        void				handleDELETE(void);
        void				handleError(int statusCode);

        // Internal handler cleaners
        void				delete_internal_handler(void);
        void				unregister_internal_handler(void);
        void				close_internal_handler(void);

        // Request types checkers
        bool				isCGI() const;
        bool				isRedirection() const;
        bool				isStandardMethod() const;
        bool				isCustomMethod() const;
        bool				isMethodAllowed() const;

        // Functions querying the config
        ConfigItem&			getLocation(void) const;
        ssize_t				getMaxBodySize(void) const;
        ConfigItem&			getServerConfig(void) const;
        std::string			resolvedRequestPath(void) const;

        // Helper functions used to set things in the response
        void				setStatusLine(int statusCode);
        void				setHeader(const std::string &key, const std::string &value);
        void				setContentLength(size_t content_length);
        void				setContentType(std::string &path);
        void				sealHeaders(void);

        // File system helpers
        std::string			getPostFilename(void);

        static size_t		getFileLength(const std::string &filename);
        int					openRegularFile(std::string path, int flags, ssize_t *len = NULL);
        int					openErrorPage(int status_code, ssize_t *len = NULL);

        static const std::string	*get_mime(const std::string &path);
};

#endif
