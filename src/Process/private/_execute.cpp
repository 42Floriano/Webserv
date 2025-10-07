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

#include "Process.hpp"

void	Process::_execute(void)
{
        if (this->pid == 0)
        {
                this->argv.push_back(NULL);
                this->envp.push_back(NULL);
                console::info << "Really Executing" << std::endl;
                errno = 0;
                ::execve(this->command.c_str(), &this->argv[0], &this->envp[0]);
                exit(errno);
        };
};
