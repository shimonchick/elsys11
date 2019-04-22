const express = require('express');
const bodyParser = require('body-parser');
const app = express();
const port = 3000;
app.use(bodyParser.json());

app.get('/', (req, res) => {
let sum = 0;
  const query = req.query;

  for(let key in query){
    sum += parseInt(query[key], 10);
  }
  res.send({sum});
});

app.listen(port, () => console.log(`Example app listening on port ${port}!`));
