int pot;
#include <SPI.h>
#include <Ethernet.h>
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(10, 0, 0, 20);
EthernetServer server(80);
String HTTP_req;
boolean LED_status = 0;
void setup()
{
    Ethernet.begin(mac, ip);
    server.begin();
    Serial.begin(9600);
    pinMode(2, OUTPUT);
}

void loop()
{
    EthernetClient client = server.available();
    if (client) {
        boolean currentLineIsBlank = true;
        while (client.connected()) {
            if (client.available()) {
                char c = client.read();
                HTTP_req += c;
                if (c == '\n' && currentLineIsBlank) {
                    client.println("HTTP/1.1 200 OK");
                    client.println("Content-Type: text/html");
                    client.println("Connection: close");
                    client.println();
                    client.println("<!DOCTYPE html>");
                    client.println("<html>");
                    client.println("<head>");
                    client.println("<title>Bozuculu Sıvı Seviye</title>");
                    client.println("</head>");
                    client.println("<body>");
                    client.println("<h1>LED</h1>");
                    client.println("<p>Click to switch LED on and off.</p>");
                    client.println("<form method=\"get\">");
                    ProcessCheckbox(client);
                    client.println("</form>");
                    client.println("</body>");
                    client.println("</html>");
                    Serial.print(HTTP_req);
                    HTTP_req = "";
                    break;
                }
                if (c == '\n') {
                    currentLineIsBlank = true;
                } 
                else if (c != '\r') {
                    currentLineIsBlank = false;
                }
            }
        }
        delay(1);
        client.stop();
    }
}

void ProcessCheckbox(EthernetClient cl)
{
  digitalWrite(7,HIGH);
  digitalWrite(9,HIGH);
  pot=analogRead(A0);
  pot=map(pot,285,306,0,18);
  Serial.println(pot);
  delay(1000);
  cl.println("<input type=\"button\" name=\"motor\" value=\"0\" onclick=\"submit();\"");
  cl.println("<input type=\"button\" name=\"motor\" value=\"1\" onclick=\"submit();\"");
  cl.println("<input type=\"button\" name=\"motor\" value=\"2\" onclick=\"submit();\"");
    if (HTTP_req.indexOf("motor=0") > -1) {
        if(pot<7)
          {
            analogWrite(10,0);
            analogWrite(5,250);
          }
        else if(pot>7)
          {
            analogWrite(5,0);
            analogWrite(10,250);
          }
        else if(pot==7)
          {
            analogWrite(5,0);
            analogWrite(10,0);
          }
    }
    if (HTTP_req.indexOf("motor=1") > -1) {
        analogWrite(5,0);
        analogWrite(10,255);
    }
    if (HTTP_req.indexOf("motor=2") > -1) {
      analogWrite(5,255);
        analogWrite(10,0); 
    }
}
