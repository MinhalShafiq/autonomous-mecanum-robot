#include <Encoder.h>
#include <ros.h>
#include <ros/time.h>
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/Twist.h>


ros::NodeHandle  nh;

geometry_msgs::TransformStamped t;
tf::TransformBroadcaster broadcaster;

char base_footprint[] = "/base_footprint";
char odom[] = "/odom";
Encoder myEnc(2, 3);
Encoder myEnc_1(18,19);
int deltaEncoderCounts[4];
int xytCounts[2];
unsigned long odom_timer = 0;


void setup() {
  //Serial.begin(9600);
  //Serial.println("Basic Encoder Test:");
  nh.initNode();
  broadcaster.init(nh);

}

long oldPosition    = -999;
long oldPosition_1  = -999;

void loop() {
  long newPosition   = myEnc.read();
  long newPosition_1 = myEnc_1.read();
  long *newPositionptr;
  long *newPositionptr_1;
  
  newPositionptr   =  &newPosition;
  newPositionptr_1 =  &newPosition_1;
  
  
  signed long deltaCounts;
  signed long deltaCounts_1;
  
  deltaCounts=newPosition-oldPosition;
  deltaCounts_1=newPosition_1-oldPosition_1;
  
  
  if (newPosition != oldPosition) {
     oldPosition = newPosition;
     deltaEncoderCounts[1]=newPosition;
     deltaEncoderCounts[2]=newPosition;
    //Serial.println(newPosition);
    //Serial.println(*newPositionptr);
  }
  if (newPosition_1 != oldPosition_1) {
    oldPosition_1 = newPosition_1;
    //Serial.println(newPosition_1);
    //Serial.println(*newPositionptr_1
    deltaEncoderCounts[0]=newPosition_1;
    deltaEncoderCounts[3]=newPosition_1;
  }
  // Serial.println(*newPositionptr);
  //Serial.println(*newPositionptr_1);
   /*
    deltaEncoderCounts[0]=newPosition_1;
    deltaEncoderCounts[1]=newPosition;
    deltaEncoderCounts[2]=newPosition;
    deltaEncoderCounts[3]=newPosition_1;
    */
    
   

  //for troubleshooting encoders 
   
  /*
  Serial.print(newPosition);
  Serial.print("       ");
  Serial.print(deltaCounts);
  Serial.print("       ");
  Serial.print(newPosition_1);
  Serial.print("       ");
  Serial.print(deltaCounts_1);
  Serial.println();
  */
  
  //for trouble delta Ecnoders
 
/*
  Serial.print("       ");
  Serial.print(deltaEncoderCounts[0]);
  Serial.print("       ");
  Serial.print(deltaEncoderCounts[1]);
  Serial.print("       ");
  Serial.print(deltaEncoderCounts[2]);
  Serial.print("       ");
  Serial.print(deltaEncoderCounts[3]);
  Serial.println();
  */
  
  

  xytCounts[0] = (deltaEncoderCounts[0] + deltaEncoderCounts[1] + deltaEncoderCounts[2] + deltaEncoderCounts[3]) / 4;
  xytCounts[1] = (0 - deltaEncoderCounts[0] + deltaEncoderCounts[1] + deltaEncoderCounts[2] - deltaEncoderCounts[3]) / 4;
  xytCounts[2] = (0 - deltaEncoderCounts[0] + deltaEncoderCounts[1] - deltaEncoderCounts[2] + deltaEncoderCounts[3]) / 4;



/*
  Serial.print("       ");
  Serial.print(xytCounts[0]);
  Serial.print("       ");
  Serial.print(xytCounts[1]);
  Serial.print("       ");
  Serial.print(xytCounts[2]);
  Serial.println();
  
  */
   
  
  t.header.frame_id = odom;
  t.child_frame_id = base_footprint;
  
  t.transform.translation.x = (xytCounts[0]*0.000672);
  t.transform.translation.y = (xytCounts[1]*0.000672);
  
  t.transform.rotation = tf::createQuaternionFromYaw(xytCounts[2]*0.000672);
  t.header.stamp = nh.now();
  
  broadcaster.sendTransform(t);
  nh.spinOnce();
  
  delay(10);
  
 
}
