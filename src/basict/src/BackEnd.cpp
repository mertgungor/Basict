#include "BackEnd.h"

Back::Back(QObject *parent) : QObject(parent)
{

}

void Back::changeSpeed(float speed){

    (speed < 0)? speed = -speed : speed = speed;

    if(speed <= 40){
        speedChanged(speed*36/40);
        return;
    }else if( speed > 40 && speed <= 160){
        speedChanged(36 + (speed - 40)*1.94);
        return;
    }else{
        speedChanged(speed-160+270);
    }

}

void Back::changeAltitude(float altitude){
    //altitudeChanged(altitude*36/100);
    int ft10000 = static_cast<int>(altitude)/10000;    
    altitude -= ft10000*10000;
    int ft1000 = static_cast<int>(altitude)/1000;
    altitude -= ft1000*1000;
    float ft100 = altitude/100;
    changeAltitude100(ft100);
    changeAltitude1000(ft1000);
    changeAltitude10000(ft10000);
}

void Back::changeAltitude100(float altitude100){
    altitudeChanged100(altitude100*36);
}

void Back::changeAltitude1000(float altitude1000){
    altitudeChanged1000(altitude1000*36);
}

void Back::changeAltitude10000(float altitude10000){
    altitudeChanged10000(altitude10000*36);
}

void Back::changeRoll(float roll){
    rollChanged(roll);
}

void Back::changeYaw(float yaw){
    yaw -= 90;
    yawChanged(yaw);
}

void Back::changePitch(float pitch){
    pitchChanged(pitch);
}

void Back::changeVertical(float vertical){
    if(vertical > 0){
        vertical *= 8.13;
        verticalChanged(vertical);
        return;
    }else if(vertical < -20 || vertical > 20){

        (vertical < 0) ? vertical = -20 : vertical = 20;

        if(vertical < 0){

            vertical *= 8.13;
            vertical += 360;
            verticalChanged(vertical);

        }else {

            vertical *= 8.13;
            verticalChanged(vertical);

        }
    }else{
        vertical *= 8.13;
        vertical += 360;
        verticalChanged(vertical);
        return;
    }
}
