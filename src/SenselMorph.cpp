//
//  SenselMorph.cpp
//  SenselMorphBlock
//
//  Created by Blair Neal on 10/5/15.
//
//

#include "SenselMorph.h"

void SenselMorph::setup(){
    if (senselOpenConnection(0)) {
        cout<<"Sensel connection established"<<endl;
    }else{
        cout<<"Unable to establish Sensel connection"<<endl;
    }
    
    senselSetFrameContentControl(SENSEL_FRAME_CONTACTS_FLAG);
    senselStartScanning();
    
    numContacts = 0;
    
}

void SenselMorph::update(){
    numContacts = senselReadContacts(contacts);
    
    senselContacts.clear();
    
    for(int i=0; i< numContacts; i++){
        
        //LEAVING THIS ALL FOR DEBUG RIGHT NOW!!
        int force = contacts[i].total_force;
        float x_mm = contacts[i].x_pos_mm;
        float y_mm = contacts[i].y_pos_mm;
        //Read out shape information (ellipses)
        float major = contacts[i].major_axis_mm;
        float minor = contacts[i].minor_axis_mm;
        float orientation = contacts[i].orientation_degrees;
        
        int id = contacts[i].id;
        int event_type = contacts[i].type;
        
        string event;
        switch (event_type)
        {
            case SENSEL_EVENT_CONTACT_INVALID:
                event = "Invalid";
                break;
            case SENSEL_EVENT_CONTACT_START:
                event = "Start";
                break;
            case SENSEL_EVENT_CONTACT_MOVE:
                event = "Move";
                break;
            case SENSEL_EVENT_CONTACT_END:
                event = "End";
                break;
            default:
                event = "Error";
        }
        
        printf("Contact ID %d, event=%s, mm coord: (%f, %f), force=%d, " \
               "major=%f, minor=%f, orientation=%f\n",
               id, event.c_str(), x_mm, y_mm, force, major, minor, orientation); //can be commented out when done debugging
        
        
        SenselContact tempContact;
        
        tempContact.contactID = id;
        tempContact.force = lmap<float>(force,0, 65536,0,1);
        tempContact.position.x = lmap<float>(contacts[i].x_pos_mm, 0.0, getSensorWidth(), 0.0, 1.0);
        tempContact.position.y = lmap<float>(contacts[i].y_pos_mm, 0.0, getSensorHeight(), 0.0, 1.0);
        tempContact.majorAxis = contacts[i].major_axis_mm;
        tempContact.minorAxis = contacts[i].minor_axis_mm;
        tempContact.orientation = contacts[i].orientation_degrees;
        tempContact.contactType = event;
        
        
        
        senselContacts.push_back(tempContact);
        
    }
}

void SenselMorph::drawDebug(){
    
    for (int i=0; i<senselContacts.size(); i++) {
        
        vec2 curPos = vec2(lmap<float>(senselContacts[i].position.x,0,1,0, cinder::app::getWindowSize().x),lmap<float>(senselContacts[i].position.y,0,1,0, cinder::app::getWindowSize().y)  );
        
        //major/minor axis
        gl::pushModelMatrix();
        gl::color( Color( CM_HSV, i/(float)senselContacts.size(), 1, 1 ) );
        gl::translate(curPos);
        gl::rotate(toRadians((float)senselContacts[i].orientation));
        gl::drawSolidEllipse(vec2(), lmap<float>(senselContacts[i].minorAxis,0,30,0,100), lmap<float>(senselContacts[i].majorAxis,0,30,0,100));
        gl::color(ci::Color::white());
        gl::drawLine(vec2(), vec2(lmap<float>(senselContacts[i].minorAxis, 0, 30, 0, 100),0));
        gl::drawLine(vec2(), vec2(0,-lmap<float>(senselContacts[i].majorAxis, 0, 30, 0, 100)));
        gl::popModelMatrix();
        
        //vector ID and contact ID
        gl::pushModelMatrix();
        gl::translate(curPos);
        gl::color(ci::Color::black());
        gl::drawSolidRect(Rectf(-5,-5,7,10));
        gl::color(ci::Color::white());
        gl::drawStringCentered(ci::toString(i), vec2());
        
        gl::translate(vec2(0,20));
        gl::color(ci::Color::black());
        gl::drawSolidRect(Rectf(-40,-5,40,10));
        gl::color(ci::Color::white());
        gl::drawStringCentered("Contact ID: "+ ci::toString(senselContacts[i].contactID), vec2());
        gl::popModelMatrix();
        
        //force
        gl::drawStrokedCircle(curPos, lmap<float>(senselContacts[i].force, 0,1, 0,300));
        
        gl::drawString("Contact ID " + ci::toString(senselContacts[i].contactID)+ ", event=" + ci::toString(senselContacts[i].contactType)+ ", mm coord: (" + ci::toString(senselContacts[i].position) +" force=" + ci::toString(senselContacts[i].force)+" major=" + ci::toString(senselContacts[i].majorAxis) + ", minor=" + ci::toString(senselContacts[i].minorAxis)+ ", orientation=" + ci::toString(senselContacts[i].orientation), vec2(0,20+i*20));
        
    }
    
}

void SenselMorph::close(){
    cout<<"Closing Sensel Connection"<<endl;
    senselStopScanning();
    senselCloseConnection();
}
