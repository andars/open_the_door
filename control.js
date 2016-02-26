function send_command(cmd) {
    console.log('sending command ' + cmd);
    req = new XMLHttpRequest();

    req.open('GET', '/' + cmd);
    req.send();
}

function handler(cmd) {
    return function() {
        send_command(cmd);
    }
}

document.addEventListener('touchstart', function (e) {
            e.preventDefault();
});
