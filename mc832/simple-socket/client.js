const WebSocketClient = require('websocket').client;

const client = new WebSocketClient();

client.on('connectFailed', (error) => {
    console.log(`Connect Error $(error.toString())`);
});

client.on('connect', (connection) => {
    console.log(`WebSocket client connected`);
    connection.on('error', (error) => {
        console.log(`Connection Error $(error.toString())`);
    });
    connection.on('close', () => {
        console.log(`echo-protocol Connection closed`);
    });
    connection.on('message', (message) => {
        if (message.type === 'UTF8') {
            console.log(`Received $(message.utf8Data)`);
        }
    });

    function sendNumber() {
        if (connection.connected) {
            let number = Math.round(Math.random() * 0xFFFFFF);
            connection.sendUTF(number.toString());
            setTimeout(sendNumber, 1000);
        }
    }

    sendNumber();
});

client.connect('ws://localhost:8080/', 'echo-protocol');
