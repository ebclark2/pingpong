#include "Paddle.hpp"

class PaddleCallback : public::osg::NodeCallback
{
public:
	virtual void operator()(osg::Node * node, osg::NodeVisitor * nv)
	{
		test::Paddle * paddle = static_cast<test::Paddle*>(node);
		paddle->update();
	}
};

test::Paddle::Paddle() :
		HasUpdate(false)
{
	osg::Box *box = new osg::Box(osg::Vec3(0, 1, 0), (1.0/12.0)*6.0, (1.0/12.0)*8.0, (1.0/12.0)*1.0);
	osg::ShapeDrawable *boxd = new osg::ShapeDrawable(box);
	osg::Geode *geode = new osg::Geode();
	geode->addDrawable(boxd);
	osg::Vec3d pos(0,0,0);
	Trans = new osg::PositionAttitudeTransform;
	Trans->setPosition(pos);
	Trans->setAttitude(osg::Quat(osg::DegreesToRadians(-20.0), osg::Vec3d(1.0, 0.0, 0.0)));
	Trans->addChild(geode);
	this->addChild(Trans);

	this->setUpdateCallback(new PaddleCallback);
}

void test::Paddle::setPosition(osg::Vec3d const& pos)
{
	NewPosition = pos;
	HasUpdate = true;
}

void test::Paddle::setRotation(double rotation)
{
	Rotation = rotation;
	HasUpdate = true;
}

void test::Paddle::update()
{
	if(HasUpdate)
	{
		Trans->setPosition(NewPosition);
		Trans->setAttitude(osg::Quat(Rotation, osg::Vec3d(0, 0, 1)));
		HasUpdate = false;
	}
}
