#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class SenselMorphBlockApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
};

void SenselMorphBlockApp::setup()
{
}

void SenselMorphBlockApp::mouseDown( MouseEvent event )
{
}

void SenselMorphBlockApp::update()
{
}

void SenselMorphBlockApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP( SenselMorphBlockApp, RendererGl )
