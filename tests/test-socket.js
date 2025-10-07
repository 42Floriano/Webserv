const {
  connect
} = require("net");

const {
  exit,
  argv
} = require("process");

const {
  createReadStream
} = require("fs");

const amount  = +argv[2] ? +argv[2] : 1;

function helloWorld() {

  const sock = connect({
    host: "127.0.0.1",
    port: 8080
  })

  sock
    .reduce((x,y)=>x+y, Buffer.alloc(0))
    .then(x => x.toString())
    .then(console.log);

}

for (i = 0; i < amount; i++) {
  helloWorld();
  console.log(i);
}
