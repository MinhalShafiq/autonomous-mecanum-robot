#include <ArduinoHardware.h>
#include <geometry_msgs/Twist.h>
#include <ros.h>
#include <std_msgs/String.h>


//#include <ros/console.h>
#define EN_L 8
#define IN1_L 32
#define IN2_L 33

#define EN_R 9
#define IN1_R 34
#define IN2_R 35

#include <ros.h>
#define EN_R_b 10
#define IN1_R_b 36
#define IN2_R_b 37


#define EN_L_b 11
#define IN1_L_b 38
#define IN2_L_b 39

double w_r=0, w_l=0;

//wheel_rad is the wheel radius ,wheel_sep is
double wheel_rad = 0.0325, wheel_sep = 0.295;


ros::NodeHandle nh;
std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);
int lowSpeed = 200;
int highSpeed = 50;
double speed_ang=0, speed_lin ,speed_ylin,angle_c,x_c,y_c;
char forwardee[13] = "forward";
char bssee[13] = "rukja";
char nothing[13] = "nothing";
char leftt[13] = "left";
char rightt[13] = "right";
char fourtyfivee[16] = "fourtyfive";
char negfourtyfivee[16] = "negfourtyfive";
char cRotatee[25] = "rotate clockwise";
char anticRotatee[25] = "rotate anti clockwise";

void messageCb( const geometry_msgs::Twist& msg){
  /* 
   speed_ang = msg.angular.z;
   speed_lin = msg.linear.x;
   speed_ylin= msg.linear.y;
   */
  angle_c = msg.angular.z;
  x_c     = 100*(msg.linear.x);
  y_c     =  100*(msg.linear.y);

  //w_r = (speed_lin/wheel_rad) + ((speed_ang*wheel_sep)/(2.0*wheel_rad));
  //w_l = (speed_lin/wheel_rad) - ((speed_ang*wheel_sep)/(2.0*wheel_rad));
}


ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", &messageCb );
void Motors_init();
void MotorL(int Pulse_Width1);
void MotorR(int Pulse_Width2);
void forward(int spd);//
void reverse(int spd);//
void foutyfive(int spd);//
void negfourtyfive(int spd);//
void rukja(int spd); //
void left(int spd);//
void right(int spd);//
void cRotate(); //clockwise rotate
void anticRotate();//anticlockwise rotate

void setup(){

  Motors_init();

  nh.initNode();
  nh.advertise(chatter);
  nh.subscribe(sub);


}


void loop(){
  /* MotorL(w_l*10);
   
   MotorR(w_r*10);
   */
   // nh.logdebug("connnected");

   //analogWrite(EN_L,x_c);
   
  if(x_c > 0 && y_c==0)
  {
    forward(x_c);
    str_msg.data = forwardee;
    chatter.publish( &str_msg );
    nh.spinOnce();
    delay(10);
  }
  else if(y_c> 0 && x_c==0)
  {
    left(x_c);
    str_msg.data = leftt;
    chatter.publish( &str_msg );
    nh.spinOnce();
    delay(10);
    
  }
  
  
  else if(x_c< 0 && y_c==0)
  {
    reverse(x_c);
    str_msg.data = bssee;
    chatter.publish( &str_msg );
    nh.spinOnce();
    delay(10);
    
  }
  else if(y_c < 0 && x_c==0)
  {
    right(x_c);
    str_msg.data = rightt;
    chatter.publish( &str_msg );
    nh.spinOnce();
    delay(10);
  }
  else if(x_c > 0 && y_c > 0)
  {
    foutyfive(x_c);
    str_msg.data = fourtyfivee;
    chatter.publish( &str_msg );
    nh.spinOnce();
    delay(10);
  }
  else if(x_c < 0 && y_c < 0)
  {
     negfourtyfive(x_c);
     str_msg.data = negfourtyfivee;
     chatter.publish( &str_msg );
     nh.spinOnce();
     delay(10);
    
  }
  
  else if(x_c==0 && y_c==0)
  {
    rukja(x_c);
    str_msg.data = bssee;
    chatter.publish( &str_msg );
    nh.spinOnce();
    delay(10);
  }
  
  else if (angle_c>0)
  {
  cRotate(x_c);
  str_msg.data=cRotatee;
  chatter.publish(&str_msg );
  nh.spinOnce();
  delay(10);
  
  }
else if (angle_c<0)
  {
  anticRotate(x_c);
  str_msg.data=anticRotatee;
  chatter.publish(&str_msg );
  nh.spinOnce();
  delay(10);
  
  }
  //x_c=0;
 // y_c=0;
  nh.spinOnce();

}


void Motors_init(){

  pinMode(EN_L, OUTPUT);
  pinMode(EN_R, OUTPUT);
  pinMode(IN1_L, OUTPUT);
  pinMode(IN2_L, OUTPUT);
  pinMode(IN1_R, OUTPUT);
  pinMode(IN2_R, OUTPUT);
  digitalWrite(EN_L, LOW);
  digitalWrite(EN_R, LOW);
  digitalWrite(IN1_L, LOW);
  digitalWrite(IN2_L, LOW);
  digitalWrite(IN1_R, LOW);
  digitalWrite(IN2_R, LOW);
  digitalWrite(EN_L_b, LOW);
  digitalWrite(EN_R_b, LOW);
  digitalWrite(IN1_L_b, LOW);
  digitalWrite(IN2_L_b, LOW);
  digitalWrite(IN1_R_b, LOW);
  digitalWrite(IN2_R_b, LOW);


}

void MotorL(int Pulse_Width1){

  if (Pulse_Width1 > 0){

    analogWrite(EN_L, Pulse_Width1);

    digitalWrite(IN1_L, HIGH);
    digitalWrite(IN2_L, LOW);

  }

  if (Pulse_Width1 < 0){

    Pulse_Width1=abs(Pulse_Width1);

    analogWrite(EN_L, Pulse_Width1);

    digitalWrite(IN1_L, LOW);
    digitalWrite(IN2_L, HIGH);

  }

  if (Pulse_Width1 == 0){

    analogWrite(EN_L, Pulse_Width1);

    digitalWrite(IN1_L, LOW);
    digitalWrite(IN2_L, LOW);

  }

}


void MotorR(int Pulse_Width2){


  if (Pulse_Width2 > 0){

    analogWrite(EN_R, Pulse_Width2);

    digitalWrite(IN1_R, LOW);
    digitalWrite(IN2_R, HIGH);

  }

  if (Pulse_Width2 < 0){

    Pulse_Width2=abs(Pulse_Width2);

    analogWrite(EN_R, Pulse_Width2);

    digitalWrite(IN1_R, HIGH);
    digitalWrite(IN2_R, LOW);

  }

  if (Pulse_Width2 == 0){

    analogWrite(EN_R, Pulse_Width2);

    digitalWrite(IN1_R, LOW);
    digitalWrite(IN2_R, LOW);

  }
}
  void rukja(int spd)
  {
    analogWrite(EN_L,spd);
    analogWrite(EN_R,spd);
     analogWrite(EN_R_b,spd);
      analogWrite(EN_L_b,spd);
    

    
    digitalWrite(EN_L, LOW);
    digitalWrite(EN_R, LOW);
    digitalWrite(EN_L_b, LOW);
    digitalWrite(EN_R_b, LOW);

    digitalWrite(IN1_L, LOW);
    digitalWrite(IN2_L, LOW);
    digitalWrite(IN1_R, LOW);
    digitalWrite(IN2_R, LOW);
    digitalWrite(IN1_L_b, LOW);
    digitalWrite(IN2_L_b, LOW);
    digitalWrite(IN1_R_b, LOW);
    digitalWrite(IN2_R_b, LOW);
  }
  void forward(int spd)
  {
    analogWrite(EN_L,spd);
    analogWrite(EN_R,spd);
     analogWrite(EN_R_b,spd);
      analogWrite(EN_L_b,spd);
    
    digitalWrite(IN1_L,   HIGH);
    digitalWrite(IN2_L,   LOW);
    digitalWrite(IN1_R,   HIGH);
    digitalWrite(IN2_R,   LOW);
    digitalWrite(IN1_L_b, HIGH);
    digitalWrite(IN2_L_b, LOW);
    digitalWrite(IN1_R_b, HIGH);
    digitalWrite(IN2_R_b, LOW);

  }
  void reverse(int spd)
  {
	  analogWrite(EN_L,spd);
    analogWrite(EN_R,spd);
     analogWrite(EN_R_b,spd);
      analogWrite(EN_L_b,spd);
      
      
    analogWrite(EN_L,spd);
    analogWrite(EN_R,spd);
     analogWrite(EN_R_b,spd);
      analogWrite(EN_L_b,spd);
    

    
    digitalWrite(IN1_L,   LOW);
    digitalWrite(IN2_L,   HIGH);
    digitalWrite(IN1_R,   LOW);
    digitalWrite(IN2_R,   HIGH);
    digitalWrite(IN1_L_b, LOW);
    digitalWrite(IN2_L_b, HIGH);
    digitalWrite(IN1_R_b, LOW);
    digitalWrite(IN2_R_b, HIGH);

  }
  void foutyfive(int spd)
  {

    analogWrite(EN_L,spd);
    analogWrite(EN_R,spd);
     analogWrite(EN_R_b,spd);
      analogWrite(EN_L_b,spd);
    

    
    digitalWrite(IN1_L,   HIGH);
    digitalWrite(IN2_L,   LOW);

    digitalWrite(IN1_R,   LOW);
    digitalWrite(IN2_R,   LOW);

    digitalWrite(IN1_L_b, LOW);
    digitalWrite(IN2_L_b, LOW);

    digitalWrite(IN1_R_b, HIGH);
    digitalWrite(IN2_R_b, LOW);
  }

  void negfourtyfive(int spd)
  {

    analogWrite(EN_L,spd);
    analogWrite(EN_R,spd);
     analogWrite(EN_R_b,spd);
      analogWrite(EN_L_b,spd);
    
    
    digitalWrite(IN1_L,   LOW);
    digitalWrite(IN2_L,   LOW);

    digitalWrite(IN1_R,   HIGH);
    digitalWrite(IN2_R,   LOW);

    digitalWrite(IN1_L_b, HIGH);
    digitalWrite(IN2_L_b, LOW);

    digitalWrite(IN1_R_b, LOW);
    digitalWrite(IN2_R_b, LOW);
  }
  void left(int spd)
  {
    analogWrite(EN_L,spd);
    analogWrite(EN_R,spd);
     analogWrite(EN_R_b,spd);
      analogWrite(EN_L_b,spd);
    
    
    digitalWrite(IN1_L,   LOW);
    digitalWrite(IN2_L,   HIGH);

    digitalWrite(IN1_R,   HIGH);
    digitalWrite(IN2_R,   LOW);

    digitalWrite(IN1_L_b, HIGH);
    digitalWrite(IN2_L_b, LOW);

    digitalWrite(IN1_R_b, LOW);
    digitalWrite(IN2_R_b, HIGH);
  }

  void right(int spd)
  {

    analogWrite(EN_L,spd);
    analogWrite(EN_R,spd);
     analogWrite(EN_R_b,spd);
      analogWrite(EN_L_b,spd);
    

    
    digitalWrite(IN1_L,   HIGH);
    digitalWrite(IN2_L,    LOW);

    digitalWrite(IN1_R,   LOW);
    digitalWrite(IN2_R,   HIGH);

    digitalWrite(IN1_L_b, LOW);
    digitalWrite(IN2_L_b, HIGH);

    digitalWrite(IN1_R_b, HIGH);
    digitalWrite(IN2_R_b, LOW);

  }
void cRotate(int spd)
{
  
   analogWrite(EN_L,spd);
    analogWrite(EN_R,spd);
     analogWrite(EN_R_b,spd);
      analogWrite(EN_L_b,spd);
    digitalWrite(IN1_L,   HIGH);
    digitalWrite(IN2_L,   LOW);

    digitalWrite(IN1_R,   LOW);
    digitalWrite(IN2_R,   HIGH);

    digitalWrite(IN1_L_b, LOW);
    digitalWrite(IN2_L_b, HIGH);

    digitalWrite(IN1_R_b, HIGH);
    digitalWrite(IN2_R_b, LOW);

}

void anticRotate(int spd)
{

 analogWrite(EN_L,spd);
    analogWrite(EN_R,spd);
     analogWrite(EN_R_b,spd);
      analogWrite(EN_L_b,spd);
    digitalWrite(IN1_L,   LOW);
    digitalWrite(IN2_L,   HIGH);

    digitalWrite(IN1_R,   HIGH);
    digitalWrite(IN2_R,   LOW);

    digitalWrite(IN1_L_b, HIGH);
    digitalWrite(IN2_L_b, LOW);

    digitalWrite(IN1_R_b, LOW);
    digitalWrite(IN2_R_b, HIGH);

}
