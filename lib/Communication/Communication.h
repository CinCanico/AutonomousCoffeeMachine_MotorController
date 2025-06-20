class Communication
{
private:

public:
    Communication();
    ~Communication();

    void setup();
    void update();

    // Read serial functions
    void read();

    // Plot Functions
    void plotData(int);
    void plotData(float);
    void plotData(double);
};

