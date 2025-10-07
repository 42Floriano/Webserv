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

class CGIHandler
{
private:
        std::string _scriptPath;
        std::string _cgiExec;
        std::string _CGIoutput;
        std::map<std::string, std::string> _envp;
        char 	**_envArray;
        int		_pipefd[2];

        void prepareENV(const Request& request, const Config& config);
        void prepareARGS(const Config& config);

public:
        CGIHandler(const Request& request, const Config& config);
        ~CGIHandler();

        bool		isCGI();
        std::string execute();
        void		setCGIoutput(void);
        void		freeArray(char **array);
        char		**setEnvinArray();
        std::string	getCgiOut();
};

std::ostream&	operator<<(std::ostream &os, CGIHandler &cgi);

#endif
