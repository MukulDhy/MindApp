from fastapi import FastAPI
import random
from pydantic import BaseModel

app = FastAPI()

last_status = {}

class StatusData(BaseModel):
    data: dict


@app.get("/")
def get_server_status():
    return {"success":True,"message":"Python Server is working Fine....."}


# Heart Rate & SpO2
@app.get("/health/heart")
def get_heart_data():
    return {"heart_rate": random.randint(60, 100), "sp_o2": random.randint(95, 100)}

# Gyroscope (X, Y, Z axis)
@app.get("/sensor/gyroscope")
def get_gyroscope():
    return {"x": round(random.uniform(-10, 10), 2), "y": round(random.uniform(-10, 10), 2), "z": round(random.uniform(-10, 10), 2)}

# Accelerometer (X, Y, Z axis)
@app.get("/sensor/accelerometer")
def get_accelerometer():
    return {"x": round(random.uniform(-5, 5), 2), "y": round(random.uniform(-5, 5), 2), "z": round(random.uniform(-5, 5), 2)}

# Temperature
@app.get("/health/temperature")
def get_temperature():
    return {"temperature": round(random.uniform(36.0, 37.5), 1)}

# Blood Pressure
@app.get("/health/blood_pressure")
def get_blood_pressure():
    return {"systolic": random.randint(110, 140), "diastolic": random.randint(70, 90)}

# Step Counter
@app.get("/activity/steps")
def get_steps():
    return {"steps": random.randint(1000, 15000)}

# Respiration Rate
@app.get("/health/respiration")
def get_respiration():
    return {"respiration_rate": random.randint(12, 20)}

# ECG Data
@app.get("/health/ecg")
def get_ecg():
    return {"ecg_signal": [round(random.uniform(-1, 1), 2) for _ in range(10)]}

# Body Posture Detection
@app.get("/sensor/posture")
def get_posture():
    return {"posture": random.choice(["Standing", "Sitting", "Lying Down"])}

# Device Battery Status
@app.get("/device/battery")
def get_battery():
    return {"battery_level": random.randint(10, 100), "charging": random.choice([True, False])}

@app.post("/update")
def update_status(status: StatusData):
    global last_status
    last_status = status.data
    print("Received Data:", last_status)
    return {"message": "Data Received"}

# Endpoint to fetch the latest received status (equivalent to Express "/status")
@app.get("/status")
def get_status():
    return last_status


# Run the server with Uvicorn if executed directly
if __name__ == "__main__":
    import uvicorn
    uvicorn.run(app, host="0.0.0.0", port=8000)
