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

#include "AutoIndexGen.hpp"

AutoIndexGen::AutoIndexGen(const std::string &dirPath)
{

        this->generateIndex(0, dirPath);
        this->generateIndex(2, dirPath);
}

AutoIndexGen::~AutoIndexGen()
{

}

std::string		AutoIndexGen::findMethod(int method)
{

        this->_label.str("");
        this->_label.clear();
        switch (method)
        {
        case GET:
                this->_label	<< "	<form method=\"GET\" action=\"/files/\">\n"
                              << "		<label for=\"file\">Fichier à afficher :</label>\n";
                return "GET";
        case POST:
                return "POST";
        case DELETE:
                this->_label	<< "	<form method=\"POST\" action=\"/files/\">\n"
                              << "		<input type=\"hidden\" name=\"_method\" value=\"DELETE\">\n"
                              << "		<label for=\"file\">Fichier à supprimer :</label>\n";
                return "DELETE";
        default:
                return "EMPTY";
        }
}

#include "Console.hpp"

void	AutoIndexGen::generateIndex(int method, const std::string &dirPath)
{

        std::string			methodS = this->findMethod(method);
        DIR					*dir_stream = opendir(dirPath.c_str());
        if (dir_stream == NULL)
        {
                std::cout << "HOLY SHEET: " << dirPath << std::endl;
        }
        struct dirent		*dir_data = 0;

        std::ostringstream	methodIndex;

        methodIndex << "<!DOCTYPE html>\n"
                    << "<html lang=\"fr\">\n"
                    << "<head>\n"
                    << "	<meta charset=\"UTF-8\">\n"
                    << "	<title>\n" + methodS + " - Webserv</title>\n"
                    << "</head>\n"
                    << "<body>\n"
                    << "	<h1>Requête " + methodS + "</h1>\n"
                    << this->_label.str()
                    << "		<select name=\"name\" id=\"file\">\n";

        while ((dir_data = readdir(dir_stream)) != NULL)
        {
                std::string	filename(dir_data->d_name);
                if (filename != "." && filename != "..")
                        methodIndex << "			<option value=\"" + filename + "\">" + filename +
                                    "</option>\n";
        }

        methodIndex << "		</select>\n"
                    << "		<br><br>\n"
                    << "		<button type=\"submit\">Envoyer</button>\n"
                    << "	</form>\n"
                    << "</body>\n"
                    << "</html>\n";

        closedir(dir_stream);

        std::ofstream	file((std::string("../www/webserv/methods/") + methodS +
                             std::string(".html")).c_str());
        if (!file.is_open())
        {
                std::cout << "Error autoindex" << std::endl;
                return;
        }
        file << methodIndex.str();
        file.close();
}
