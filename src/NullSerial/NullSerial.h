class NullSerial : public Stream
{
public:
    virtual size_t write(uint8_t) { return (1); }
    virtual int available() { return (0); }
    virtual int read() { return (0); }
    virtual int peek() { return (0); }
    virtual void flush() {}
    void begin(int rate) {}
    void print(String string) {}
    void println(String string) {}
    void end() {}
};

NullSerial nullSerial;