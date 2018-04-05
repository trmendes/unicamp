const WebSocketServer = require('websocket').server;
const http = require('http');

const server = http.createServer((request, response) => {
    console.log(`${new Date()} Received request from ${request.url}`);
    response.writeHead(404);
    response.end();
}).listen(8080, () => {
    console.log(`${new Date()} Server is listening on port 8080`);
});

wsServer = new WebSocketServer({
    httpServer: server,
    autoAcceptConnections: false
});

function originIsAllowed(origin) {
    /* Just in case you need to check something before accept a connection */
    return true;
}

wsServer.on('request', (request) => {
    if (!originIsAllowed(request.origin)) {
        request.reject(); console.log(`${new Date()} Connection Rejects from
            origin ${origin.request}`);
        return;
    }
    let connection = request.accept('echo-protocol', request.origin);
    console.log(`${new Date()} Connection Accepted`);

    connection.on('message', (message) => {
        if (message.type === 'utf8') {
            console.log(`Received Message: ${message.utf8Data}}`);
            connection.sendUTF(message.utf8Data);
        } else if (message.type === 'binary') {
            console.log(`${new Date()} Received Binary message of
            ${message.binaryData.length} bytes`);
            connection.sendBytes(message.binaryData);
        }
    });

    connection.on('close', (reasonCode, description) => {
        console.log(`$(new Date()) Peer $(connection.remoteAddress)
        disconnected`);
    });
});
