#include <iostream>
#include <libmcp9808.h>

using namespace std;

int main(void)
{
    mcp9808 * dev = new mcp9808 ;
    dev->begin(MCP9808_I2CADDR_DEFAULT);
    cout << "Manufacturer ID: " << hex << dev->MfgID() << endl ;
    cout << "Device ID: " << dev->DevID() << endl ;
    int time = 0 ;
    while(true)
    {
        cout << "Time: " << dec << time << " s" << endl ;
        cout << "Temperature: " << dev->readTemp()/100.0 << " C" << endl ;
        time += 1;
        usleep(1000000);
        cout << "\x1b[A" << "\x1b[A" ;
    }
    return 0 ;
}