#ifndef BACK_H
#define BACK_H

#include <QObject>
#include <QString>

class Back : public QObject
{
    Q_OBJECT
public:
    explicit Back(QObject *parent = nullptr);

signals:
    void speedChanged(float speed);
    void altitudeChanged(float altitude);
    void rollChanged(float roll);
    void yawChanged(float yaw);
    void pitchChanged(float pitch);
    void verticalChanged(float vertical);
    void altitudeChanged100(float altitude100);
    void altitudeChanged1000(float altitude1000);
    void altitudeChanged10000(float altitude10000);

public slots:
    void changeSpeed(float speed);
    void changeAltitude(float altitude);
    void changeRoll(float roll);
    void changeYaw(float yaw);
    void changePitch(float pitch);
    void changeVertical(float vertical);
    void changeAltitude100(float altitude100);
    void changeAltitude1000(float altitude1000);
    void changeAltitude10000(float altitude10000);

};

#endif // BACK_H
