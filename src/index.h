#ifndef INDEX_h
#define INDEX_h

#include <pgmspace.h>

const char INDEX_HTML[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8" />
        <meta http-equiv="X-UA-Compatible" content="IE=edge" />
        <title>Soil Moisture Sensor</title>
        <meta name="viewport" content="width=device-width, initial-scale=1" />
        <style>
            body {
                margin: 0;
                background: #73c8a9;
                background: linear-gradient(to right, #73c8a9, #373b44);
                background-color: #487346;
                background-image: url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' width='200' height='200' viewBox='0 0 200 200'%3E%3Cg %3E%3Cpolygon fill='%234c8e43' points='100 57.1 64 93.1 71.5 100.6 100 72.1'/%3E%3Cpolygon fill='%236aac5f' points='100 57.1 100 72.1 128.6 100.6 136.1 93.1'/%3E%3Cpolygon fill='%234c8e43' points='100 163.2 100 178.2 170.7 107.5 170.8 92.4'/%3E%3Cpolygon fill='%236aac5f' points='100 163.2 29.2 92.5 29.2 107.5 100 178.2'/%3E%3Cpath fill='%2389CC7C' d='M100 21.8L29.2 92.5l70.7 70.7l70.7-70.7L100 21.8z M100 127.9L64.6 92.5L100 57.1l35.4 35.4L100 127.9z'/%3E%3Cpolygon fill='%23768c3a' points='0 157.1 0 172.1 28.6 200.6 36.1 193.1'/%3E%3Cpolygon fill='%2396ac58' points='70.7 200 70.8 192.4 63.2 200'/%3E%3Cpolygon fill='%23B6CC76' points='27.8 200 63.2 200 70.7 192.5 0 121.8 0 157.2 35.3 192.5'/%3E%3Cpolygon fill='%2396ac58' points='200 157.1 164 193.1 171.5 200.6 200 172.1'/%3E%3Cpolygon fill='%23768c3a' points='136.7 200 129.2 192.5 129.2 200'/%3E%3Cpolygon fill='%23B6CC76' points='172.1 200 164.6 192.5 200 157.1 200 157.2 200 121.8 200 121.8 129.2 192.5 136.7 200'/%3E%3Cpolygon fill='%23768c3a' points='129.2 0 129.2 7.5 200 78.2 200 63.2 136.7 0'/%3E%3Cpolygon fill='%23B6CC76' points='200 27.8 200 27.9 172.1 0 136.7 0 200 63.2 200 63.2'/%3E%3Cpolygon fill='%2396ac58' points='63.2 0 0 63.2 0 78.2 70.7 7.5 70.7 0'/%3E%3Cpolygon fill='%23B6CC76' points='0 63.2 63.2 0 27.8 0 0 27.8'/%3E%3C/g%3E%3C/svg%3E");
                font-family: Arial, Helvetica, sans-serif;
            }

            .main {
                display: flex;
                flex-direction: column;
                justify-content: center;
                height: 100vh;
                padding: 0 2rem;
                gap: 1rem;
                color: white;
                text-align: center;
                text-shadow: rgba(0, 0, 0, 0.25) 0px 54px 55px, rgba(0, 0, 0, 0.12) 0px -12px 30px, rgba(0, 0, 0, 0.12) 0px 4px 6px,
                    rgba(0, 0, 0, 0.17) 0px 12px 13px, rgba(0, 0, 0, 0.09) 0px -3px 5px;
            }

            input {
                max-width: unset;
                height: 3rem;
                font-size: 20px;
                padding: 0 1rem;
                border: none;
                border-radius: 5px;
                box-shadow: rgba(0, 0, 0, 0.35) 0px 5px 15px;
                border: 0px solid #487346;
                transition: border 0.1s ease-in-out;
            }

            input:focus {
                outline: none;
                border: 3px solid #487346;
            }

            input[type="submit"] {
                height: 3rem;
                font-size: 20px;
                color: white;
                background: #487346;
                border: none;
                border-radius: 5px;
                box-shadow: rgba(0, 0, 0, 0.35) 0px 5px 15px;
            }
        </style>
    </head>
    <body>
        <form action="/submit" method="POST" class="main">
            <h1>Soil Moisture Sensor</h1>
            <input type="text" name="ssid" id="ssid" placeholder="SSID" />
            <input type="password" name="password" id="password" placeholder="Password" />
            <input type="submit" value="Save" />
        </form>
    </body>
</html>

)=====";

#endif