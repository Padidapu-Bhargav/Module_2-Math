#include <Arduino.h>
#ifdef ESP32
  #include <WiFi.h>
  #include <AsyncTCP.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>:
#endif
#include <ESPAsyncWebServer.h>
#include"matfun.h"

AsyncWebServer server(80);

const char* ssid = "Bhargav";
const char* password = "123456789";

const char* input_parameter00 = "input00";
const char* input_parameter01 = "input01";
const char* input_parameter10 = "input10";
const char* input_parameter11 = "input11";
const char* input_parameter20 = "input20";
const char* input_parameter21 = "input21";
const char* input_parameter30 = "input30";
const char* input_parameter31 = "input31";
const char* matrix1[2]={input_parameter00,input_parameter01};     // matrix for vertex B
const char* matrix2[2]={input_parameter10,input_parameter11};     // matrix for vertex C
const char* matrix3[2]={input_parameter20,input_parameter21};     // matrix for vertex D
const char* matrix4[1]={input_parameter30};     // theta

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
    <title>TRIANGLE</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
      html {font-family: Times New Roman; display: inline-block; text-align: center;}
      h2 {font-size: 2.0rem; color: blue;}
    </style> 
    </head><body>
    <h2>TRIANGLE CONSTRUCTION</h2> 
    <p>Enter the values of points B, C and D
    <form action="/get">
      Enter the values of Point B: <input type="number" name="input00"> <input type="number" name="input01"><br><br>
      Enter the values of Point D: <input type="number" name="input10"> <input type="number" name="input11"><br><br>
      Enter the values of Point C: <input type="number" name="input20"> <input type="number" name="input21"><br><br> 
       Enter the value of theta: <input type="number" name="input30"><br><br>
      <input type="submit" value="Submit">
    </form><br>
  </body></html>)rawliteral";

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connecting...");
    return;
  }
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {

	double **A,**B,**C,**D,**M,**E,**theta1; //declaring matrices names
  	double AB,AC,AD,AE,BC,BD,BE,CD,CE,DE; //side lengths
	int m =2, n=1; // (mxn) matrix
	double theta,Alpha,Beta,Beta1;


//creating Matrix B and loading the first column of the vertivces data file
B = load_ser(request,matrix1,2);
D = load_ser(request,matrix2,2);
C = load_ser(request,matrix3,2);

BD = Matnorm(Matsub(B,D,m,n),m);
CD = Matnorm(Matsub(C,D,m,n),m);

theta1 =load_ser(request,matrix4,1);
theta =theta1[0][0];
Alpha = (180 - theta)/2;

AB = BD * (sin(Alpha*(M_PI/180)) / sin(theta*(M_PI/180)));

A = Mat_1(B, AB, Alpha*(M_PI/180),1);

AD= Matnorm(Matsub(A,D,m,n),m);
AC= Matnorm(Matsub(A,C,m,n),m);

Beta1=(180/M_PI)*acos((AC*AC+CD*CD-AD*AD)/(2*AC*CD));

CE = AC * (sin(theta*(M_PI/180)) / sin(Alpha*(M_PI/180)));

Beta = Alpha + Beta1;

E = Mat_1(C,CE,Beta*(M_PI/180),-1);

AE= Matnorm(Matsub(A,E,m,n),m);
BC= Matnorm(Matsub(B,C,m,n),m);
DE= Matnorm(Matsub(D,E,m,n),m);

String response;


if( round(AB) == round(AD) )
	response += "<p> AD equals to AB</p>";
else
	response += "<p>AD not equals to AB</p>";

if( round(AC) == round(AE) )
	response += "<p>AC equals to AE</p>";
else
	response += "<p>AC not equals to AE</p>";

if( round(BC) == round(DE) )
	response += "<p>BC equals to DE</p>";
else
	response += "<p>BC not equals to DE</p>";


	response += "<br><a href=\"/\">Return to Home Page</a>";
    // Send the HTML response with dynamic content
    request->send(200, "text/html", response);
});
  server.onNotFound(notFound);
  server.begin();
}
void loop() { 
}
