#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTime>
#include <QSize>
#include <QRect>
#include <QScreen>

#include "BackEnd.h"

#include <math.h>

#include <ros/ros.h>

#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/TwistStamped.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/State.h>
#include <sensor_msgs/NavSatFix.h>

#define _USE_MATH_DEFINES
#include <cmath>

struct Quaternion {
    double w, x, y, z;
};

struct EulerAngles {
    double roll, pitch, yaw;
};

EulerAngles ToEulerAngles(Quaternion q) {
    EulerAngles angles;

    // roll (x-axis rotation)
    double sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
    double cosr_cosp = 1 - 2 * (q.x * q.x + q.y * q.y);
    angles.roll = std::atan2(sinr_cosp, cosr_cosp);

    // pitch (y-axis rotation)
    double sinp = 2 * (q.w * q.y - q.z * q.x);
    if (std::abs(sinp) >= 1)
        angles.pitch = std::copysign(M_PI / 2, sinp); // use 90 degrees if out of range
    else
        angles.pitch = std::asin(sinp);

    // yaw (z-axis rotation)
    double siny_cosp = 2 * (q.w * q.z + q.x * q.y);
    double cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
    angles.yaw = std::atan2(siny_cosp, cosy_cosp);

    return angles;
}

void delay(int ms)
{
    QTime dieTime= QTime::currentTime().addMSecs(ms);  //addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

}

geometry_msgs::PoseStamped pose;

// Saves the pose of the drone
void pose_tracker(const geometry_msgs::PoseStamped::ConstPtr& _pose){
    pose = *_pose;
}

sensor_msgs::NavSatFix navFix;

void navFix_tracker(const sensor_msgs::NavSatFix::ConstPtr& _navFix){
    navFix = *_navFix;
}

geometry_msgs::TwistStamped gps_vel;

void gps_vel_tracker(const geometry_msgs::TwistStamped::ConstPtr& _gps_vel){
    gps_vel = *_gps_vel;
}

// This holds the current state of the drone
// Connected, the flight mode etc.
mavros_msgs::State current_state;

// Saves the state of the drone
void state_tracker(const mavros_msgs::State::ConstPtr& _current_state){
    current_state = *_current_state;
}

int main(int argc, char *argv[])
{

    ros::init(argc, argv, "basict");
    ros::NodeHandle nh;

    ros::Subscriber state_sub = nh.subscribe<mavros_msgs::State>
        ("mavros/state", 10, state_tracker);
    
    ros::Subscriber position = nh.subscribe<geometry_msgs::PoseStamped>
        ("mavros/local_position/pose",10, pose_tracker);
    
    ros::Subscriber nav = nh.subscribe<sensor_msgs::NavSatFix>
        ("mavros/global_position/global",10, navFix_tracker);

    ros::Subscriber vel = nh.subscribe<geometry_msgs::TwistStamped>
        ("mavros/global_position/gp_vel",10, gps_vel_tracker);

    double const knot = 5280/3600; //constant for converting 1feet/sec to mile/hour(knot)
    double const br = 3.2808; // 1br = 1 meter = 3.28 feet
    int ms = 200; // miliseconds to wait before updating UI

    float x = pose.pose.position.x; // current position of the drone
    float y = pose.pose.position.y;
    float z = pose.pose.position.z;

    float newX{0}; // new position of the drone
    float newY{0};
    float newZ{0};
    double v{0};
    float airSpeedKnot{0};
    float sec;

    //the setpoint publishing rate MUST be faster than 2Hz
    ros::Rate rate(20.0);

    // wait for FCU connection
    while(ros::ok() && !current_state.connected){
        ros::spinOnce();
        rate.sleep();
    }

    if(current_state.connected){
        ROS_INFO("CONNECTED");
    }

    Quaternion q;
    EulerAngles e;
    const float degree = 57.295779; // radian to degree constant

    

    Back *back = new Back;

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    //QSize size = qApp->screens()[0]->size();
    
    
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("back",back);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    float pitch;

    while(true){
        QScreen *screen = QGuiApplication::primaryScreen();
        int  height = screen->geometry().height();
        //int height = screenGeometry.height();

        //QSize size = qApp->screens()[0]->size();
        //int height = size.height();

        newX = pose.pose.position.x;
        newY = pose.pose.position.y;
        newZ = pose.pose.position.z;
        /*
        d = (newX*newX + newY*newY + newZ*newZ - x*x - y*y - z*z); 
        d = d < 0 ? -d : d;
        d = sqrt(d);
        */
        v = sqrt(gps_vel.twist.linear.x*gps_vel.twist.linear.x + gps_vel.twist.linear.y*gps_vel.twist.linear.y + gps_vel.twist.linear.z*gps_vel.twist.linear.z);
        
        delay(ms);
        airSpeedKnot = (v*br)*knot*5; // speed calculation
        
        pitch = -20*height/400;
        
        q.x = pose.pose.orientation.x;
        q.y = pose.pose.orientation.y;
        q.z = pose.pose.orientation.z;
        q.w = pose.pose.orientation.w; 
        e = ToEulerAngles(q);

        //ROS_INFO("pitch: %.2f\naltitude %.2f",e.pitch*57.3 ,(newZ - z)*5*5/3);

        back->changeSpeed(airSpeedKnot);
        back->changeVertical(gps_vel.twist.linear.z*5*5/3); // 5/3 to convert from feet/sec to 100feet/min 
        back->changeRoll(e.roll*degree);
        back->changeYaw(e.yaw*degree);
        back->changePitch(e.pitch*degree);
        back->changeAltitude(navFix.altitude);
        ros::spinOnce();
        //ROS_INFO("%d",height);

        x = newX;
        y = newY;
        z = newZ;
    }

    return app.exec();
}
