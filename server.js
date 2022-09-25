const express = require("express");
const app = express();
const PORT =  3000;
const bodyParser = require('body-parser')
let contCajas = 1;
app.use(express.json());
app.use(bodyParser.json())
app.use(express.urlencoded({extended:true}));

let arrValues = [];
app.get("/", async (req, res) => {
    console.log(arrValues)
    res.status(200).json(arrValues)
});
app.post("/post", (req, res) => {
    let {message} = req.body; 

    const d = new Date();
    if(message === "start"){
      let obj = {
        caja: contCajas
      };
      obj["start"] = d.toLocaleTimeString();
      arrValues.push(obj);     
    }
    else if (message="finish"){
      arrValues.forEach(el => {
          if(el.caja === contCajas){
            el["finish"] = d.toLocaleTimeString()
            el["duracion"] = calcTiempo(el.start,el.finish);
          } 
      });
      contCajas++;
    }   
    console.log(arrValues)
    res.status(201).send({message:"Data Enviada"});
})
app.listen(PORT, () => console.log("Listening on port", PORT));

function calcTiempo(start,finish) {
  let inicio = start.split(':').map(el => parseInt(el));
  let fin = finish.split(':').map(el => parseInt(el));
  let difHour = fin[0] - inicio[0];
  let difMin = fin[1] - inicio[1];
  let difSec = fin[2] - inicio[2];
  return difHour + ':'+ difMin +':' + difSec 
}