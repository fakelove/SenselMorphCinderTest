#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "SenselMorph.h"


using namespace ci;
using namespace ci::app;
using namespace std;

class SenselMorphTestApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
    
        SenselMorph sensel;
};

void SenselMorphTestApp::setup()
{
    setWindowSize(1100, 600);
    setFrameRate(60);
    sensel.setup();
}

void SenselMorphTestApp::mouseDown( MouseEvent event )
{
}

void SenselMorphTestApp::update()
{
    sensel.update();
}

void SenselMorphTestApp::draw()
{

	gl::clear( Color( 0, 0, 0 ) );
    sensel.drawDebug();
}

CINDER_APP( SenselMorphTestApp, RendererGl )
