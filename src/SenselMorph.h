//
//  SenselMorph.h
//  SenselMorphBlock
//
//  Created by Blair Neal on 10/5/15.
//
//
#include "cinder/app/App.h"
#include "cinder/Utilities.h"
#include "cinder/gl/gl.h"
#include "cinder/app/RendererGl.h"
#include "cinder/CinderMath.h"
#include "sensel.h"

using namespace ci;
using namespace std;

class SenselMorph{
public:
    SenselMorph() { };
    ~SenselMorph() { };
    
    struct SenselContact{
        vec2 position;
        float force;
        int area;// area multiplied by 65536
        int orientation;// angle from -90 to 90 multiplied by 256
        int majorAxis;// length of the major axis multiplied by 256
        int minorAxis;// length of the minor axis multiplied by 256
        //vel_t dx; // change in x from last frame
        //vel_t dy; // change in y from last frame
        int contactID;
        string contactType;
    };
    
    struct SenselLED{
        bool state; //off or on
        bool stateChange;
        int brightness;
        int lightIndex;
    };
    
    
    contact_t contacts[MAX_CONTACTS];
    int numContacts;
    
    void setup();
    void update();
    void updateLights();
    void drawDebug();
    
    vector<SenselContact> senselContacts;
    
    vector<SenselContact> getContacts(){ return senselContacts;}
    
    vec3 getAccelData() {return accelData; }
    
    vector<SenselLED> leds;
    
    void close();
    
    vec3 accelData;
    
    
};