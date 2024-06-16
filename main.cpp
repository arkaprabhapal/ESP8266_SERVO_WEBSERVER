#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Servo.h>  //Include the Servo Library

#include "PageIndex.h"; //--> Include the contents of the User Interface Web page from website, stored in the same folder as the .ino file  

#define ServoPort D1   //--> Defining Servo Port

#define LED1  D5   //-->Defining a Simple LED

//Make a wifi name and password as access point

const char* ssid = "ESPServo";  // your SSID

const char* password = "12345678"; //WIFI Password


Servo myservo;  //--> create servo object to control a servo

ESP8266WebServer server(80);  //--> Server on port 80

String SERstate1 = "OFF";

//This routine is executed when you open NodeMCU ESP8266 IP Address in browser

void handleRoot() {

  String s = MAIN_page; //Read HTML contents

  server.send(200, "text/html", s); //Send web page

}

//Procedure for handling servo control

void handleServo() {
  String POS = server.arg("servoPOS");
  int pos = POS.toInt();
  myservo.write(pos);   //--> Move the servo motor according to the POS value
  delay(15);
  Serial.print("Servo Angle:");
  Serial.println(pos);
  server.send(200, "text/plane", "");
}

void controlServo() {
  String t_state = server.arg("SERstate1");
  Serial.println(t_state);
  int pos;
  if (t_state == "1") {
    SERstate1 = pos;
    controlLED1();
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    controlLED1();
  }
  else if (t_state == "2") {
    SERstate1 = pos;
    myservo.write(45);
    controlLED1();
  }
  else if (t_state == "3") {
    SERstate1 = pos;
    myservo.write(90);
    controlLED1();
  }
  else if (t_state == "4") {
    SERstate1 = pos;
    myservo.write(180);
    controlLED1();
  }
  else {
    SERstate1 = "OFF";
  }
  server.send(200, "text/plane", SERstate1);
}

void statusSER() {
  server.send(200, "text/plane", SERstate1);
}
void controlLED1() {
  digitalWrite(LED1, HIGH);
  delay(200);
  digitalWrite(LED1, LOW);
  delay(200);
}


void setup() {

  Serial.begin(115200);
  delay(500);
  myservo.attach(ServoPort); //--> attaches the servo on D1 to the servo object
  pinMode(LED1, OUTPUT);
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);


  //Initialize Webserver
  server.on("/", handleRoot); //--> Routine to handle at root location. This is to display web page.
  server.on("/setPOS", handleServo); //--> Sets servo position from Web request
  server.on("/setSER1", controlServo);
  server.on("/readSER1", statusSER);
  server.begin();

  Serial.println("HTTP server started");

}


void loop() {

  server.handleClient();

}

After the main code Press Crtl+Shift+N for new tab and rename it PageIndex.h and press Enter then copy the this HTML code from here and again paste on it and Save it.

//Press Crtl+Shift+N for new tab and name it PageIndex.h and paste here
//Copy the HTML Code and paste in it

const char MAIN_page[] PROGMEM = R"=====(

<!DOCTYPE html>
<html>
  <head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
      html {
        font-family: Arial;
        display: inline-block;
        margin: 0px auto;
        text-align: center;
      }

      .slidecontainer {
        width: 100%;
      }

      .slider {
        -webkit-appearance: none;
        width: 50%;
        height: 15px;
        border-radius: 5px;
        background: rgb(102, 230, 17);
        outline: none;
        opacity: 0.5;
        -webkit-transition: .2s;
        transition: opacity .2s;
      }

      .slider:hover {
        opacity: 2;

      }
      
      .slider::-webkit-slider-thumb {
        -webkit-appearance: none;
        appearance: none;
        width: 25px;
        height: 25px;
        border-radius: 50%;
        background: rgb(26, 182, 202);
        cursor: pointer;
      }
      
      .slider::-moz-range-thumb {
        width: 25px;
        height: 25px;
        border-radius: 50%;
        background: #4CAF50;
        cursor: pointer;
      }
     
         /* Style the botton start stop */
   .btn{
   /* position: relative;
    border-radius: 15px 15px 15px 15px;
    width: 8%;
    height: 25px;
    border: none;
    outline: none;
    cursor: pointer;
    background: #fa1cb7;
    color: rgb(255, 255, 255);
    */
     background-color: #fa1cb7;
  color: white;
  padding: 14px 25px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
   }

   a:link, a:visited {
  background-color: #f44336;
  color: white;
  padding: 14px 25px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
}

a:hover, a:active {
  background-color: red;
}
       
        /* Style the footer */
   footer {
      background-color: rgb(43, 57, 255);
      padding: 8px;
      text-align: center;
      color: rgb(0, 255, 21);
      font-family: Comic Sans MS;
   }

    </style>
  </head>
  
  <body>
    <h1>ESP8266 NodeMCU Web Server Controlled Servo Motor</h1>
    <br><br>
    <div class="slidecontainer">
      <input type="range" min="0" max="180" value="50" class="slider" id="myRange">
      <p>Servo angle: <span id="demo"></span></p>
       <br><br>
      <label> Servo Sweep </label>
       <button type="button" onclick="sendData2(1)" class="btn">Start</button>
        <br><br>
        <label> 45 Degree Angle </label>
        <button type="button" onclick="sendData2(2)" class="btn">45 Degree</button>
         <br><br>
        <label> 90 Degree Angle </label>
        <button type="button" onclick="sendData2(3)" class="btn">90 Degree</button>
        <br><br>
        <label> 180 Degree Angle </label>
        <button type="button" onclick="sendData2(4)" class="btn">180 Degree</button>

      <label><span id="isiStatusSER1"></span></label>

    </div>
    
    <script>
      function sendData(pos) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            console.log(this.responseText);
          }
        };
        xhttp.open("GET", "setPOS?servoPOS="+pos, true);
        xhttp.send();
      } 
        /* fungsi send data on/off */
        function sendData2(StatusSer1) { 
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) { 
            document.getElementById("SERstate1").innerHTML = this.responseText;     
          }
        };
        
        xhttp.open("GET", "setSER1?;SERstate1=" + StatusSer1, true);   
        xhttp.send();
        }

    /* fungsi read data on/off */
        function getDataSER1() {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("isiStatusSER1").innerHTML = this.responseText;
          }
        };
        xhttp.open("put", "readSER1", true);    
        xhttp.send();
        }
      var slider = document.getElementById("myRange");
      var output = document.getElementById("demo");
      output.innerHTML = slider.value;
      slider.oninput = function() {
        output.innerHTML = this.value;
        sendData(output.innerHTML);
      }

    </script>
     <br><br><br><br>
     <footer>
     <p>
       By Tekronika</br>
      </p>
     <p>Pls Subscribe my Channel</p>
     <a href="https://www.youtube.com/@Tekronika" target="_blank">Subscribe</a>

    </footer>

  </body>

</html>
)=====";
