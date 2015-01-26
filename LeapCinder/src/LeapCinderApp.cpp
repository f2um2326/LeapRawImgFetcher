#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "cinder/Channel.h"
#include "cinder/Vector.h"
#include "cinder/gl/TextureFont.h"
#include "Leap.h"
#include "LeapMath.h"

#include <opencv2/opencv.hpp>

#ifdef _DEBUG
#pragma comment(lib, "opencv_core245d.lib")
#pragma comment(lib, "opencv_highgui245d.lib")
#pragma comment(lib, "opencv_calib3d245d.lib")
#pragma comment(lib, "opencv_imgproc245d.lib")
#else
#pragma comment(lib, "opencv_core245.lib")
#pragma comment(lib, "opencv_highgui245.lib")
#pragma comment(lib, "opencv_calib3d245.lib")
#pragma comment(lib, "opencv_imgproc245.lib")
#endif

using namespace ci;
using namespace ci::app;
using namespace std;

class TouchPointsApp : public AppNative {
  public:
	void setup();
	void draw();
	gl::Texture targetTexture;
  private:
    static const int windowWidth = 800;		// 800
    static const int windowHeight = 800;	// 800
    Leap::Controller leap;
};

void TouchPointsApp::setup()
{
    this->setWindowSize(windowWidth, windowHeight);
    this->setFrameRate(120);
    gl::enableAlphaBlending();

	Leap::Controller::PolicyFlag addImagePolicy = 
		(Leap::Controller::PolicyFlag)(Leap::Controller::PolicyFlag::POLICY_IMAGES | leap.policyFlags());
	leap.setPolicyFlags(addImagePolicy);
}

void TouchPointsApp::draw()
{
	/*
	Leap::Frame frame = leap.frame();
	Leap::ImageList images = frame.images();

	for(int i = 0; i < 2; i++){
		Leap::Image image = images[i];
		if(image.isValid()) {
			const unsigned char* image_buffer = image.data();

			//Draw the raw image data as a greyscale bitmap
			Surface surface(image.width(), image.height(), image.width() * 4, SurfaceChannelOrder::RGBA);
			//Surface surface(800, 800, 1, SurfaceChannelOrder::RGBA);
			int cursor = 0;
			Surface::Iter iter = surface.getIter();
			while( iter.line() ) {
				while( iter.pixel() ) {
					iter.r() = image_buffer[cursor];
					iter.g() = iter.b() = iter.r();
					iter.a() = 255;
					cursor++;
				}
			}
			targetTexture = gl::Texture(surface);
			gl::draw(targetTexture);
		} else {
			gl::Texture texture1(loadImage("F:/Users/dashu2326/Documents/Visual Studio 2012/Projects/LeapCinder/src/test.jpg"));
			gl::draw(texture1);
		}


	}
	*/

	///*
	gl::clear( Color( .97, .93, .79 ) );
	
    Leap::PointableList pointables = leap.frame().pointables();
    Leap::InteractionBox iBox = leap.frame().interactionBox();
    for( int p = 0; p < pointables.count(); p++ )
    {
        Leap::Pointable pointable = pointables[p];
        Leap::Vector normalizedPosition = iBox.normalizePoint(pointable.stabilizedTipPosition());
        float x = normalizedPosition.x * windowWidth;
        float y = windowHeight - normalizedPosition.y * windowHeight;
        
        if(pointable.touchDistance() > 0 && pointable.touchZone() != Leap::Pointable::Zone::ZONE_NONE)
        {
            gl::color(0, 1, 0, 1 - pointable.touchDistance());
        }
        else if(pointable.touchDistance() <= 0)
        {
            gl::color(1, 0, 0, -pointable.touchDistance());
        }
        else
        {
            gl::color(0, 0, 1, .05);
        }
        
        gl::drawSolidCircle(Vec2f(x,y), 40);
    }
	//*/
	//Surface surface1(loadImage("F:/Users/dashu2326/Documents/Visual Studio 2012/Projects/LeapCinder/src/test.jpg"));
	//gl::Texture texture1 = gl::Texture(surface1);
	////gl::Texture texture1(loadImage("F:/Users/dashu2326/Documents/Visual Studio 2012/Projects/LeapCinder/src/test.jpg"));
	//gl::draw(texture1);
	
}

CINDER_APP_NATIVE( TouchPointsApp, RendererGl )