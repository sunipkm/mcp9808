#include <iostream>
#include <libmcp9808.h>

using namespace std;

int main(void)
{
    mcp9808 * dev = new mcp9808[2] ;
    dev[0].begin(MCP9808_I2CADDR_DEFAULT);
    cout << "Manufacturer ID: " << hex << dev[0].MfgID() << endl ;
    cout << "Device ID: " << dev[0].DevID() << endl ;
    dev[1].begin(MCP9808_I2CADDR_DEFAULT+1);
    cout << "Manufacturer ID: " << hex << dev[1].MfgID() << endl ;
    cout << "Device ID: " << dev[1].DevID() << endl ;
    int time = 0 ;
    while(true)
    {
        char out[1] = {MCP9808_REG_AMBIENT_TEMP} ; char in[2] = {0xff} ;
        cout << "Request data on 1: " << write(dev[0]._i2cbus,&out,1) << endl;
        cout << "Request data on 2: " << write(dev[1]._i2cbus,&out,1) << endl;
        usleep(10000) ; // 10 ms sleep
        read(dev[1]._i2cbus, &in, 2) ;
        uint16_t tmp = ((uint16_t)in[0]) << 8 | in[1] ;
        float temp = tmp != 0xFFFF ? (tmp & 0x0fff) / 16.0 : -273 ;
        temp -= tmp & 0x1000 ? 256 : 0 ;
        cout << "Read data on 2: " << hex << "0x" << in[0] << in[1] << dec << " Temp: " << temp << endl ;
        in[0] = 0xff , in[1] = 0xff ;
        read(dev[0]._i2cbus, &in, 2) ;
        tmp = ((uint16_t)in[0]) << 8 | in[1] ;
        temp = tmp != 0xFFFF ? (tmp & 0x0fff) / 16.0 : -273 ;
        temp -= tmp & 0x1000 ? 256 : 0 ;
        cout << "Read data on 1: " << hex << "0x" << in [0] << in [1] << dec << "Temp: " << temp << endl ;
        time += 1;
        usleep(990000);
        cout << "\x1b[A" << "\x1b[A" ;
    }
    delete[] dev ;
    return 0 ;
}