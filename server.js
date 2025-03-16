const express = require("express");
const cors = require("cors");
const bodyParser = require("body-parser");

const app = express();
app.use(cors());
app.use(bodyParser.json());

let lastStatus = {};

app.post("/update", (req, res) => {
  lastStatus = req.body;
  console.log("Received Data:", lastStatus);
  res.send({ message: "Data Received" });
});

app.get("/status", (req, res) => {
  res.json(lastStatus);
});

app.listen(5000, () => console.log("Server running on port 5000"));
