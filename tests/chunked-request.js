const {
  request
} = require("http");

const req = request({
  method: "GET",
  host: "127.0.0.1",
  port: "8080",
  headers: {
    "Transfer-Encoding": "chunked"
  }
})

function handleResponse(response) {
  response
    .reduce((x,y) => x + y)
    .then(bytes => bytes.toString())
    .then(console.log)
}

req.on("error", error => console.log(error.rawPacket.toString()))
req.on("response", handleResponse);
req.write("Hello, look at my body");
req.write("A");
req.write("B");
req.end();
