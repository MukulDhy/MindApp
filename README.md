# FastAPI Sensor Data API

![FastAPI Logo](https://fastapi.tiangolo.com/img/logo-margin/logo-teal.svg)




## End Point 

![https://mindapp-simulation.onrender.com/]
## Overview

Welcome to the FastAPI Sensor Data API! This project provides a robust and efficient API to fetch real-time sensor data such as heart rate, gyroscope coordinates, temperature, and more. Built using FastAPI, this application is designed to handle multiple requests quickly and efficiently.

## Features

- **Real-time Data**: Get instant access to various sensor readings.
- **RESTful API**: Follow REST principles to ensure a seamless integration experience.
- **Interactive Documentation**: Automatically generated API documentation using Swagger UI.
- **Scalable**: Designed to handle multiple requests simultaneously.

## API Endpoints

FastAPI Health Monitoring API
Introduction
This document provides details about the FastAPI application that serves as a health monitoring API. The API exposes various endpoints to retrieve health metrics from a simulated health monitoring device.
API Endpoints
1. Server Status
GET /
Returns the status of the server.
Response:

{
    "success": true,
    "message": "Python Server is working Fine....."
}

2. Heart Rate & SpO2
GET /health/heart
Returns simulated heart rate and SpO2 values.
Response:

{
    "heart_rate": <random_integer_between_60_and_100>,
    "sp_o2": <random_integer_between_95_and_100>
}

3. Gyroscope Data
GET /sensor/gyroscope
Returns gyroscope data for X, Y, and Z axes.
Response:

{
    "x": <random_float_between_-10_and_10>,
    "y": <random_float_between_-10_and_10>,
    "z": <random_float_between_-10_and_10>
}

4. Accelerometer Data
GET /sensor/accelerometer
Returns accelerometer data for X, Y, and Z axes.
Response:

{
    "x": <random_float_between_-5_and_5>,
    "y": <random_float_between_-5_and_5>,
    "z": <random_float_between_-5_and_5>
}

5. Temperature
GET /health/temperature
Returns the simulated body temperature.
Response:

{
    "temperature": <random_float_between_36.0_and_37.5>
}

6. Blood Pressure
GET /health/blood_pressure
Returns simulated blood pressure values.
Response:

{
    "systolic": <random_integer_between_110_and_140>,
    "diastolic": <random_integer_between_70_and_90>
}

7. Step Counter
GET /activity/steps
Returns the simulated number of steps taken.
Response:

{
    "steps": <random_integer_between_1000_and_15000>
}

8. Respiration Rate
GET /health/respiration
Returns the simulated respiration rate.
Response:

{
    "respiration_rate": <random_integer_between_12_and_20>
}

9. ECG Data
GET /health/ecg
Returns simulated ECG signal data.
Response:

{
    "ecg_signal": [<random_float_between_-1_and_1>, ... (10 values)]
}

10. Body Posture Detection
GET /sensor/posture
Returns the detected body posture.
Response:

{
    "posture": "<Standing | Sitting | Lying Down>"
}

11. Device Battery Status
GET /device/battery
Returns the simulated battery status of the device.
Response:

{
    "battery_level": <random_integer_between_10_and_100>,
    "charging": <true | false>
}


## Getting Started

### Prerequisites

- Python 3.7 or higher
- Virtual environment (optional but recommended)

### Installation

1. Clone the repository:

   ```bash
   git clone <YOUR_GITHUB_REPO_URL>
   cd <YOUR_PROJECT_FOLDER>
Create and activate a virtual environment:

bash
Copy
Edit
python -m venv venv
# On Windows
venv\Scripts\activate
# On macOS/Linux
source venv/bin/activate
Install the required packages:

bash
Copy
Edit
pip install -r requirements.txt
Running the Application
Run the FastAPI server:

bash
Copy
Edit
uvicorn main:app --host 0.0.0.0 --port 8000 --reload
Accessing the API
Once the server is running, you can access the interactive API documentation at:

arduino
Copy
Edit
http://127.0.0.1:8000/docs
Deployment
This application is deployed on Render. You can access the live API at:

arduino
Copy
Edit
https://<your-app-name>.onrender.com/docs
Contributing
We welcome contributions! If you would like to contribute to this project, please fork the repository and create a pull request.

License
This project is licensed under the MIT License. See the LICENSE file for details.

Acknowledgments
FastAPI
Uvicorn
Feel free to reach out with any questions or feedback!

markdown
Copy
Edit

### Tips for Customization:

- Replace `<YOUR_GITHUB_REPO_URL>` and `<YOUR_PROJECT_FOLDER>` with your actual GitHub repository URL and project folder name.
- Update the live API URL after deploying your application on Render.
- You can add more sections based on your project's needs, such as features, installation instructions, and acknowledgments.
- You can also enhance the formatting with badges, images, or other Markdown elements.

Let me know if you need further adjustments or additional information!
