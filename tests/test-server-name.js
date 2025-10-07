const { request } = require("http");

let req = request({
	host: "127.0.0.1",
	port: 8080,
	path: "/index.html",
	headers: {
		"Host": "foo"
	},
})

req.on("response", response => {
	response.reduce((x,y) => x + y).then(console.log);
})

req.on("error", err => console.log(err.rawPacket.toString()));

req.end()
