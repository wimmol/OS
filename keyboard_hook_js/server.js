const express = require('express');
const bodyParser = require('body-parser')

const port = 3000

const app = express();
app.use( bodyParser.json());

app.post('/key', (req, res) => {
    console.log('Key pressed: ', req.body.key);
    res.sendStatus(200);
});

app.listen(port, () => console.log(`Started server at http://localhost:${port}!`));