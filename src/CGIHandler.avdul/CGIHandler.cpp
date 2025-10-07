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

#include "CGIHandler.hpp"


CGIHandler::CGIHandler(const Request& request, const Config& config)
{
        prepareARGS(config);
        prepareENV(request, config);
}

CGIHandler::~CGIHandler() {}


void CGIHandler::prepareENV(const Request& request, const Config& config)
{
        (void)config;
        this->_envp["REQUEST_METHOD"] = request.method();
        // this->_envp["QUERY_STRING"] = request.queryString();
        this->_envp["PATH_INFO"] = request.path();
        // this->_envp["SERVER_NAME"] = config.getServerName();
        // this->_envp["SERVER_PORT"] = config.getPort();
        // this->_envp["SERVER_PROTOCOL"] = config._protocole;
        this->_envp["GATEWAY_INTERFACE"] = "CGI/1.1";
        this->_envp["REDIRECT_STATUS"] = "200";
        for (std::map<std::string, std::string>::const_iterator it =
                                request.headers().begin();
                        it != request.headers().end(); ++it)
        {
                if (it->first == "Content-Type")
                        this->_envp["CONTENT_TYPE"] = it->second;
                if (it->first == "Content-Length")
                        this->_envp["CONTENT_LENGHT"] = it->second;
                if (it->first == "Auth-scheme")
                        this->_envp["AUTH_TYPE"] = it->second;
        }
        return ;
}

void CGIHandler::prepareARGS(const Config& config)
{
        (void)config;
        _scriptPath = "/cgi-bin/test.py";
        // _cgiExec = config._cgiExec; // need to have the exec.py
        return ;
}

bool CGIHandler::isCGI()
{
        if (this->_scriptPath.size() >= 4
                        && this->_scriptPath.substr(_scriptPath.size() - 3) == ".py")
                return true;
        else
                return false;
}


char	**CGIHandler::setEnvinArray()
{

        char	**env = new char*[_envp.size() + 1];
        int		i = 0;
        for (std::map<std::string, std::string>::iterator	it = _envp.begin();
                        it != _envp.end(); ++it)
        {
                std::string	elem = it->first + "=" + it->second;
                env[i] = new char[elem.size() + 1];
                strcpy(env[i], elem.c_str());
                i++;
        }
        env[i] = NULL;
        return env;
}


void	CGIHandler::freeArray(char **array)
{
        if (array)
        {
                for (int i = 0; array[i] != NULL; i++)
                {
                        delete[] array[i];
                }
                delete array;
        }
}

void	CGIHandler::setCGIoutput(void)
{
        _CGIoutput =	this->_envp["SERVER_PROTOCOL"] + " " +
                        this->_envp["REDIRECT_STATUS"] + " OK\r\n\r\n";
}

std::string CGIHandler::getCgiOut()
{
        return _CGIoutput;
}

std::string	CGIHandler::execute()
{
        if (!isCGI())
                return "HTTP/1.1 400 Bad request\r\n\r\nThis is not a CGI request";
        if (socketpair(AF_UNIX, SOCK_STREAM, 0, _pipefd) == -1)
                return "HTTP/1.1 501 Internal server error\r\n\r\n";
        _envArray = setEnvinArray();
        pid_t pid = fork();
        if (pid < 0)
                return "HTTP/1.1 502 Internal Server error\r\n\r\n";
        if (pid == 0)
        {
                dup2(_pipefd[1], STDIN_FILENO);
                dup2(_pipefd[1], STDOUT_FILENO);
                close(_pipefd[0]);
                char	*args[] = { (char*)this->_cgiExec.c_str(), (char*)this->_scriptPath.c_str(), NULL};
                if (execve(this->_cgiExec.c_str(), args, _envArray) == -1)
                {
                        perror("execve failed");
                        exit(1);
                }
                console::debug << "CGI executed successfully\n";
        }
        else
        {
                close(_pipefd[1]);
                char buffer[4096];
                ssize_t bytes_read;
                while ((bytes_read = read(_pipefd[0], buffer, sizeof(buffer))) > 0)
                        _CGIoutput.append(buffer, bytes_read);
                int status;
                waitpid(pid, &status, 0);
                close(_pipefd[0]);
                freeArray(_envArray);
                return _CGIoutput;
        }
        return "";
}

std::ostream&	operator<<(std::ostream &os, CGIHandler &cgi)
{
        os << cgi.execute();
        return os;
}
