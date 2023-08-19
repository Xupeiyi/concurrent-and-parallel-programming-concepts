let cluster = require('cluster');  // contains multiprocessing apis
let http = require('http');
let nprocessors = require('os').cpus().length;  // number of processors available
const port = 8888;

// parent process
if (cluster.isMaster) {  
    console.log(`Listening on port: ${port}`);
    console.log(`Number of processors: ${nprocessors}`);

    // fork a worker per processor
    for (let i = 0; i < nprocessors; i++) {
        cluster.fork();
    }

    // should a worker exits, create another
    cluster.on('exit', (worker, code, signal) => cluster.fork());
}
// worker process
else {
    http.createServer((req, res) => {
        res.writeHead(200);
        res.end(`Echoing request URI: ${req.url}\n`);
    }).listen(port);
}