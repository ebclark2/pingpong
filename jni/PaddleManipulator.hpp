#ifndef __PADDLEMANIPULATOR_HPP__
#define __PADDLEMANIPULATOR_HPP__

#include "Paddle.hpp"

#include <osg/Camera>
#include <osgGA/GUIEventHandler>

namespace test
{

class PaddleManipulator : public osgGA::GUIEventHandler
{
public:
	PaddleManipulator(osg::Camera * camera = NULL);

	virtual bool handle(osgGA::GUIEventAdapter const& ea, osgGA::GUIActionAdapter & aa, osg::NodeVisitor * nv);
	virtual bool handle(osgGA::GUIEventAdapter const& ea, osgGA::GUIActionAdapter & aa);

	inline void setPaddle(test::Paddle * paddle) { Paddle = paddle; }

	inline void setCamera(osg::Camera * camera) { Camera = camera; }

private:
	osg::ref_ptr<test::Paddle> Paddle;
	osg::ref_ptr<osg::Camera> Camera;
};

}

#endif /* __PADDLEMANIPULATOR_HPP__ */
