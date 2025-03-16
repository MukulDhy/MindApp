import React, { useState, useEffect } from "react";
import axios from "axios";

function App() {
  const [status, setStatus] = useState({});

  useEffect(() => {
    const interval = setInterval(() => {
      axios
        .get("https://mindapp-simulation.onrender.com/status")
        .then((response) => setStatus(response.data))
        .catch((error) => console.error(error));
    }, 1200);

    return () => clearInterval(interval);
  }, []);

  return (
    <div style={{ textAlign: "center", marginTop: "50px" }}>
      <h1>ESP32 WiFi Monitor</h1>
      <h2>
        Status: <span style={{ color: status.color }}>{status.status}</span>
      </h2>
      {status.status === "Connected" && (
        <h3>Signal Strength: {status.rssi} dBm</h3>
      )}
    </div>
  );
}

export default App;
