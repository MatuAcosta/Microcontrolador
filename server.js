const express = require("express");
const app = express();
const PORT =  3000;
const bodyParser = require('body-parser')

app.use(express.json());
app.use(bodyParser.json())
app.use(express.urlencoded({extended:true}));

let arrValues = [];
app.get("/", async (req, res) => {
    console.log(arrValues)
    res.status(200).json(arrValues)
});
app.post("/post", [checkContador] , (req, res) => {
    const d = new Date();
    let obj = {
      sensor: req.body.sensor,
      contador:req.body.decena + req.body.unidad,
      time: d.getHours() + ":" + d.getMinutes() + ":" + d.getSeconds()
    }
    arrValues.push(obj);
    console.log(arrValues)
    res.status(201).send("Data Enviada");
})
app.listen(PORT, () => console.log("Listening on port", PORT));

function checkContador(req,res,next) {
    let contador = req.body.decena + req.body.unidad
    let cont = parseInt(contador);
    if(cont === 20) {
      arrValues = [] ; 
      console.log("RELLENANDO CAJA"); 
      setTimeout(() => {
        console.log("COMENZANDO SIGUIENTES PRODUCTOS")
      }, 5000);
    }else {
      next();
    }
}