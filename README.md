# Webserv

A custom **HTTP/1.1 web server** built from scratch as part of the 42 Lausanne curriculum.  
This project re-implements the essential mechanisms of a modern web server, including request parsing, response generation, CGI handling, and efficient connection management through event-driven I/O.

---

## 🚀 Features

- Full **HTTP/1.1** request and response handling  
- Supports **GET**, **POST**, and **DELETE** methods  
- **Non-blocking I/O** with `epoll`/`kqueue` for concurrency  
- **CGI execution** (dynamic content)  
- **Configuration file** for server rules (ports, roots, error pages, etc.)  
- **Error handling** (400, 404, 500, etc.)  
- **Persistent connections** and **chunked transfer encoding**  
- Static file serving with directory listing (autoindex)

---

## 🧩 Tech Stack

- **Language:** C++  
- **System APIs:** Sockets, epoll/kqueue, fork, execve  
- **Concurrency:** Non-blocking I/O, multiplexing  
- **Build Tool:** Makefile  
- **Environment:** Linux / macOS  

---

## ⚙️ Installation & Build

```bash
# Clone the repository
git clone https://github.com/42Floriano/Webserv.git
cd Webserv

# Build the project
make
