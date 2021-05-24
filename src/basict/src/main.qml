import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    width: 1200
    height: 800
    title: qsTr("Flight Instrument")

    Rectangle {
        width:1200
        height:800
        
        Image {
            source:"file:src/basict/src/FlightInstrument_images/background.png"
            id:background
            x:0 ; y:0
            width:parent.parent.width
            height:800
        }
        Image {
            source:"file:src/basict/src/FlightInstrument_images/airspeed_markings.svg.png"
            id:airspeed_markings
            x:0 ; y:0
            width:400
            height:parent.parent.height/2
        }
        Image {
            source:"file:src/basict/src/FlightInstrument_images/airspeed_hand.svg.png"
            id:airspeed_hand
            x:0 ; y:0
            width:400
            height:400
            rotation: 0

            Connections{
                target: back
                onSpeedChanged: airspeed_hand.rotation = speed;
            }

            Behavior on rotation { NumberAnimation { duration: 50 } } 
        }
        Image {
            source:"file:src/basict/src/FlightInstrument_images/altimeter_pressure_inhg.svg.png"
            id:altimeter_pressure_inhg
            x:400 ; y:0
            width:400
            height:400
        }
        Image {
            source:"file:src/basict/src/FlightInstrument_images/altimeter_pressure_mbar.svg.png"
            id:altimeter_pressure_mbar
            x:400 ; y:0
            width:401
            height:401
        }
        Image {
            source:"file:src/basict/src/FlightInstrument_images/altimeter_background.svg.png"
            id:altimeter_background
            x:400 ; y:0
            width:400
            height:400
        }
        Image {
            source:"file:src/basict/src/FlightInstrument_images/heading_yaw.svg.png"
            id:heading_yaw
            x:0 ; y:400
            width:400
            height:400
            rotation: 0

            Connections{
                target: back
                onYawChanged: heading_yaw.rotation = yaw;
            }

            Behavior on rotation { NumberAnimation { duration: 50 } } 

        }
        Image {
            source:"file:src/basict/src/FlightInstrument_images/heading_markings.svg.png"
            id:heading_markings
            x:0 ; y:400
            width:400
            height:400
        }
        Image {
            source:"file:src/basict/src/FlightInstrument_images/turn_markings_1.svg.png"
            id:turn_markings_1
            x:400 ; y:400
            width:400
            height:400
        }
        Image {
            source:"file:src/basict/src/FlightInstrument_images/turn_ball_path.svg.png"
            id:turn_ball_path
            x:400 ; y:400
            width:400
            height:400
        }
        //Image {
        //    source:"file:src/basict/src/FlightInstrument_images/turn_ball.svg.png"
        //    id:turn_ball
        //    x:400 ; y:400
        //    width:400
        //    height:400
        //    rotation: 0

        //    Connections{
        //        target: back
        //        onRollChanged: turn_ball.rotation = roll;
        //    }
        //}
        Image {
            source:"file:src/basict/src/FlightInstrument_images/turn_markings_2.svg.png"
            id:turn_markings_2
            x:400 ; y:400
            width:400
            height:400
        }
        Image {
            source:"file:src/basict/src/FlightInstrument_images/turn_airplane.svg.png"
            id:turn_airplane
            x:400 ; y:400
            width:400
            height:400
            rotation: 0

            Connections{
                target: back
                onRollChanged: turn_airplane.rotation = roll;
            }

            Behavior on rotation { NumberAnimation { duration: 50 } } 
        }
        Image {
            source:"file:src/basict/src/FlightInstrument_images/altimeter_foreground.svg.png"
            id:altimeter_foreground
            x:400 ; y:0
            width:400
            height:400
        }
        Image {
            source:"file:src/basict/src/FlightInstrument_images/altimeter_hand_10000ft.svg.png"
            id:altimeter_hand_10000ft
            x:400 ; y:0
            width:400
            height:400
            rotation: 0

            Connections{
                target: back
                onAltitudeChanged10000: altimeter_hand_10000ft.rotation = altitude10000;
            }

            Behavior on rotation { NumberAnimation { duration: 50 } } 
        }
        Image {
            source:"file:src/basict/src/FlightInstrument_images/altimeter_hand_1000ft.svg.png"
            id:altimeter_hand_1000ft
            x:399 ; y:0
            width:401
            height:401
            rotation: 0

            Connections{
                target: back
                onAltitudeChanged1000: altimeter_hand_1000ft.rotation = altitude1000;
            }

            Behavior on rotation { NumberAnimation { duration: 50 } }
        }
        Image {
            source:"file:src/basict/src/FlightInstrument_images/altimeter_hand_100ft.svg.png"
            id:altimeter_hand_100ft
            x:400 ; y:0
            width:400
            height:400
            rotation: 0

            Connections{
                target: back
                onAltitudeChanged100: altimeter_hand_100ft.rotation = altitude100;
            }

            Behavior on rotation { NumberAnimation { duration: 50 } }
        }
        Image {
            source:"file:src/basict/src/FlightInstrument_images/attitude_roll_1.svg.png"
            id:attitude_roll_1
            x:800 ; y:0
            width:400
            height:400
            
        }
        Image {
            source:"file:src/basict/src/FlightInstrument_images/attitude_pitch.svg.png"
            id:attitude_pitch
            x:800 ; y:0
            width:400
            height:400
            rotation: 0

            Connections{
                target: back
                onRollChanged: attitude_pitch.rotation = roll;
            }

            Behavior on rotation { NumberAnimation { duration: 50 } } 

            Connections{
                target: back
                onPitchChanged: attitude_pitch.y = pitch;
            }

            Behavior on y { SmoothedAnimation { velocity: 200 } }

        }
        Image {
            source:"file:src/basict/src/FlightInstrument_images/pasted_layer.png"
            id:pasted_layer
            x:800 ; y:0
            width:400
            height:400
        }
        Image {
            source:"file:src/basict/src/FlightInstrument_images/attitude_roll_2.svg.png"
            id:attitude_roll_2
            x:800 ; y:0
            width:400
            height:400
        }
        Image {
            source:"file:src/basict/src/FlightInstrument_images/attitude_foreground_2.svg_copy.png"
            id:attitude_foreground_2
            x:800 ; y:0
            width:400
            height:400
            rotation: 0

            Connections{
                target: back
                onRollChanged: attitude_foreground_2.rotation = roll;
            }

            Behavior on rotation { NumberAnimation { duration: 50 } } 
        }
        Image {
            source:"file:src/basict/src/FlightInstrument_images/attitude_foreground_1.svg.png"
            id:attitude_foreground_1
            x:800 ; y:0
            width:400
            height:400
            rotation: 0

            Connections{
                target: back
                onRollChanged: attitude_foreground_1.rotation = roll;
            }
            
            Behavior on rotation { NumberAnimation { duration: 50 } } 
        }
        Image {
            source:"file:src/basict/src/FlightInstrument_images/attitude_ils_markings.svg.png"
            id:attitude_ils_markings
            x:800 ; y:0
            width:400
            height:400
        }
        Image {
            source:"file:src/basict/src/FlightInstrument_images/vario_markings.svg.png"
            id:vario_markings
            x:800 ; y:400
            width:400
            height:400
        }
        Image {
            source:"file:src/basict/src/FlightInstrument_images/vario_hand.svg.png"
            id:vario_hand
            x:800 ; y:400
            width:400
            height:400
            rotation: 0

            Connections{
                target: back
                onVerticalChanged: vario_hand.rotation = vertical;
            }

        }
        Image {
            source:"file:src/basict/src/FlightInstrument_images/foreground.png"
            id:foreground
            x:800 ; y:400
            width:400
            height:parent.parent.height/2
        }
    }

}

