#ifndef SUBMIT_h
#define SUBMIT_h

#include <pgmspace.h>

const char SUBMIT_HTML[] PROGMEM = R"=====(
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
                background: #76b852;
                background: linear-gradient(to right, #76b852, #8dc26f);
                font-family: Arial, Helvetica, sans-serif;
            }

            .main {
                display: flex;
                flex-direction: column;
                align-items: center;
                justify-content: center;
                height: 100vh;
                padding: 0 2rem;
                gap: 1rem;
                color: white;
                text-align: center;
                box-shadow: rgba(0, 0, 0, 0.09) 0px 2px 1px, rgba(0, 0, 0, 0.09) 0px 4px 2px, rgba(0, 0, 0, 0.09) 0px 8px 4px,
                    rgba(0, 0, 0, 0.09) 0px 16px 8px, rgba(0, 0, 0, 0.09) 0px 32px 16px;
            }

            .lds-facebook {
                display: inline-block;
                position: relative;
                width: 80px;
                height: 80px;
            }
            .lds-facebook div {
                display: inline-block;
                position: absolute;
                left: 8px;
                width: 16px;
                background: #fff;
                animation: lds-facebook 1.2s cubic-bezier(0, 0.5, 0.5, 1) infinite;
            }
            .lds-facebook div:nth-child(1) {
                left: 8px;
                animation-delay: -0.24s;
            }
            .lds-facebook div:nth-child(2) {
                left: 32px;
                animation-delay: -0.12s;
            }
            .lds-facebook div:nth-child(3) {
                left: 56px;
                animation-delay: 0;
            }
            @keyframes lds-facebook {
                0% {
                    top: 8px;
                    height: 64px;
                }
                50%,
                100% {
                    top: 24px;
                    height: 32px;
                }
            }
        </style>
    </head>
    <body>
        <div class="main">
            <h1>Submitted Successfully</h1>
            <div class="lds-facebook">
                <div></div>
                <div></div>
                <div></div>
            </div>
            <p>connecting to WiFi...</p>
        </div>
    </body>
</html>

)=====";

#endif