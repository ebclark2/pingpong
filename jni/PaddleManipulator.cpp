#include "PaddleManipulator.hpp"

#include <android/log.h>

#include <algorithm>
#include <cmath>

//TEST
#include <sstream>
//END TEST

#define  LOG_TAG    "PaddleManipulator"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

test::PaddleManipulator::PaddleManipulator(osg::Camera * camera) :
	Camera(camera)
{
	setIgnoreHandledEventsMask(0u);
}

bool test::PaddleManipulator::handle(osgGA::GUIEventAdapter const& ea, osgGA::GUIActionAdapter & aa, osg::NodeVisitor * nv)
{
	return this->handle(ea, aa);
}

bool test::PaddleManipulator::handle(osgGA::GUIEventAdapter const& ea, osgGA::GUIActionAdapter & aa)
{
	//LOGI("Yay!");
//	if(Paddle)
//	{
//		Paddle->setPosition(osg::Vec3d(0, 0, -10));
//	}

	switch(ea.getEventType())
	{
	case osgGA::GUIEventAdapter::PUSH:
	case osgGA::GUIEventAdapter::DRAG:
	{
		osg::Vec3d eye, center, up;
		if(!Camera)
		{
			LOGI("No camera");
			return false;
		}
		Camera->getViewMatrixAsLookAt(eye, center, up);

		osg::Matrixd m;
		m.preMult(Camera->getViewport()->computeWindowMatrix());
		m.preMult(Camera->getProjectionMatrix());
		m.preMult(Camera->getViewMatrix());
		osg::Matrixd inv;
		inv.invert(m);

//		osg::Vec3d cursor = osg::Vec3d(ea.getX(), ea.getY(), 0) * inv;
		double b = 0.6 * (ea.getYmax() - ea.getYmin());
		double t = 0.9 * (ea.getYmax() - ea.getYmin());
		double hr = (ea.getY() - b) / (t - b);
		//double hr = (ea.getY() - ea.getYmin()) / (ea.getYmax() - ea.getYmin());
		if(ea.getMouseYOrientation() == osgGA::GUIEventAdapter::Y_INCREASING_DOWNWARDS)
		{
			hr = 1.0 - hr;
		}
		hr = std::max(0.0, std::min(1.0, hr));
//		double phr = .25 + (hr * .4);
//		if(ea.getMouseYOrientation() == osgGA::GUIEventAdapter::Y_INCREASING_DOWNWARDS)
//		{
//			phr - 1.0 - phr;
//		}
		osg::Vec3d base = osg::Vec3d(ea.getX(), 0, 0) * inv;
		base.z() = eye.z() + 6.5;
		base.y() = 0; //std::sin(osg::DegreesToRadians(20.0)) * -6.0;
//		double h = (cursor - base).length();
//		osg::Quat tr(osg::DegreesToRadians(-20.0), osg::Vec3d(1, 0, 0));
		osg::Vec3d dir(0, 0, 1); //= tr * (center - eye);
//		dir.normalize();
		//double l = std::sin(osg::DegreesToRadians(80.0)) * h;
		osg::Vec3d p = base + (dir * (hr * 2.5));
		Paddle->setPosition(p);
		std::ostringstream ss;
		ss << "Dir position: " << dir.x() << " " << dir.y() << " " << dir.z() << std::endl;
		ss << "Base position: " << base.x() << " " << base.y() << " " << base.z() << std::endl;
		ss << "Paddle position: " << p.x() << " " << p.y() << " " << p.z();
		LOGI(ss.str().c_str());

		//rotation
		double xr = ea.getXmax() - ea.getXmin();
		double hxr = xr/2.0;
		double xfc = ea.getX() - hxr;
		double xratio = xfc / hxr;
		Paddle->setRotation(xratio*osg::DegreesToRadians(60.0));
		break;
	}
	default:
		break;
	}

	return false;
}
