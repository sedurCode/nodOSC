#ifndef __ARMAFILTER_H__
#define __ARMAFILTER_H__

class ArmaFilter
{
    public:
        float tau;
        float fs;
        bool setup(float tau, float fs);
        bool reset();
        float process(float x);

    private:
        float stateMAz1;
        float stateMAz2;
        float alpha;
        float oneMinusAlpha;
};

#endif

/*

class Adafruit_LSM303_Accel_Unified : public Adafruit_Sensor
{
  public:
    Adafruit_LSM303_Accel_Unified(int32_t sensorID = -1);

    bool begin(void);
    bool getEvent(sensors_event_t*);
    void getSensor(sensor_t*);

    lsm303AccelData raw;   // Last read accelerometer data will be available here

  private:
    int32_t         _sensorID;

    void write8(byte address, byte reg, byte value);
    byte read8(byte address, byte reg);
    void read(void);
};


*/
