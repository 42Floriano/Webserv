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

#ifndef PROCESS_HPP
# define PROCESS_HPP

#include "Console.hpp"
#include <cerrno>

#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <cerrno>

#include <csignal>
#include <vector>
#include <map>

/**
 * @class Process
 * @brief A class to manage and execute system processes.
 *
 * This class provides functionality to spawn a new process, manage its input/output streams,
 * and handle its termination. It encapsulates the necessary details for process management
 * including command parsing and execution.
 */

class Process
{

public:

        /**
         * @brief Constructs a Process object with the given command.
         * @param cmd The command to be executed by the process.
         */

        Process(const std::string &cmd);
        ~Process(void);

        //TODO: the above, should use the below
        //Process(std::istream &input);

        //TODO: rename: stdio -> internal_stdio
        //TODO: rename: real_stdio -> external_stdio
public:
        int									pid;			/**< Process ID of the spawned process. */
        std::string							command;		/**< Command string to be executed. */
        std::vector<char *>					argv;			/**< Arguments for the command. */
        std::vector<char *>					envp;			/**< Environment variables for the command. */
        std::vector<int>
        stdio;          /**< Internal descriptors for standard input/output/error. */
        std::vector<int>
        real_stdio;     /**< External descriptors for standard input/output/error. */
        bool
        done;           /**< Indicates if the process has completed execution. */
        int									exit_status;    /**< Exit status of the process. */
        std::map<std::string, std::string>	env;


public:
        bool	is_done(void);
        /**
         * @brief Spawns the process.
         *
         * This method creates a new process using fork and exec system calls.
         */
        void	spawn(void);

        /**
         * @brief Gets the file descriptor for standard input.
         * @return The file descriptor for standard input.
         */
        int		stdin(void);

        /**
         * @brief Gets the file descriptor for standard output.
         * @return The file descriptor for standard output.
         */
        int		stdout(void);

        /**
         * @brief Gets the file descriptor for standard error.
         * @return The file descriptor for standard error.
         */
        int		stderr(void);

        /**
         * @brief Sends a signal to terminate the process.
         * @param sig The signal to send (default is SIGTERM).
         */
        void	kill(int sig = SIGTERM);

private:
        void	_configure_env(void);
        void	_check_if_done(void);

        /**
         * @brief Resolves the command string to an executable path.
         * @param str The command string to resolve.
         * @return The resolved command path.
         */
        std::string	_resolve_command(const std::string &str);

        /**
         * @brief Parses the command input from a stream.
         * @param cmd The input stream containing the command.
         */
        void		_parse_command(std::istream &cmd);

        /**
         * @brief Creates communication channels for the process.
         */
        void		_create_channels(void);

        /**
         * @brief Configures the standard input/output/error for the process.
         */
        void		_configure_stdio(void);

        /**
         * @brief Executes the command in the spawned process.
         */
        void		_execute(void);

        /**
         * @brief Forks the current process to create a new process.
         */
        void		_fork(void);
public:
        std::string&	operator[](const std::string &key);

};

#endif
