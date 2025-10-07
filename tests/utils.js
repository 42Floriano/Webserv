const {
  connect
} = require("net");

const {
  request
} = require("request");

function rawConnection(port) {
  let connection = connect({
    host: "127.0.0.1",
    port
  });
}

function httpConnection(port, port, path, headers) {
  let connection = request({
    host: "127.0.0.1",
    port,
    path,
    headers
  })
}

module.exports = {
  httpConnection,
  rawConnection
};
