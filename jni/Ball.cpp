#include "Ball.hpp"

#include <osg/Material>
#include <osg/Shape>
#include <osg/ShapeDrawable>
#include <osg/LineSegment>
#include <osgUtil/IntersectVisitor>
#include <osgUtil/LineSegmentIntersector>

#include <android/log.h>

//TEST
#include <sstream>
//END TEST

#define  LOG_TAG    "PaddleManipulator"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

namespace
{
double BALL_SPEED = 5.0;
double RESET_DISTANCE = 20.0;

bool intersectsPaddle(test::Paddle * paddle, osg::Vec3d const& istart, osg::Vec3d const& iend)
{
	osgUtil::IntersectVisitor iv;
	iv.addLineSegment(new osg::LineSegment(istart, iend));
	paddle->accept(iv);
	return iv.hits();
}
}

test::Ball::Ball() :
	State(SERVE_P1)
{
	osg::Sphere * sphere = new osg::Sphere(osg::Vec3d(0, 0, 0), (.5/12.0)*1.5748);
	osg::ShapeDrawable *sd = new osg::ShapeDrawable(sphere);
	sd->setColor(osg::Vec4d(1, 0, 0, 1));
	osg::StateSet* state = sd->getOrCreateStateSet();
	osg::Material* mat = new osg::Material;
	mat->setColorMode(osg::Material::AMBIENT_AND_DIFFUSE);
	mat->setAmbient(osg::Material::FRONT_AND_BACK, osg::Vec4d(1, 0, 0, 1));
	mat->setDiffuse(osg::Material::FRONT_AND_BACK, osg::Vec4d(0, 0, 0, 1));
	mat->setEmission(osg::Material::FRONT_AND_BACK, osg::Vec4d(1, 0, 0, 1));
	state->setAttributeAndModes(mat,
			osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
	sd->setStateSet(state);

	osg::Geode *geode = new osg::Geode();
	geode->addDrawable(sd);
	Trans = new osg::PositionAttitudeTransform;
	Trans->addChild(geode);
	this->addChild(Trans);
}

void test::Ball::accept(osg::NodeVisitor & visitor)
{
	if(visitor.getVisitorType() == osg::NodeVisitor::UPDATE_VISITOR)
	{
		this->update();
	}
	osg::Group::accept(visitor);
}

void test::Ball::update()
{
//	if(!PaddleMovements.empty())
//	{
//		ScopedLock lock(&Mtx);
//		while(!PaddleMovements.empty())
//		{
//			PaddleMovementData const& pmd = PaddleMovements.front();
//			handlePaddleMoved(pmd.paddle, pmd.prevPos, pmd.currPos);
//			PaddleMovements.pop_front();
//		}
//	}

	if((this->getPosition() - osg::Vec3d(0, 0, 12)).length() > RESET_DISTANCE)
	{
		State = SERVE_P1;
	}
	switch(State)
	{
	case SERVE_P1:
	{
		osg::Vec3d p = Paddle1->getPosition();
		p.z() = 7.5 + ((1.0/12.0)*3.0);
		this->setPosition(p);
		break;
	}
	case PLAY_P1:
	{
		this->setPosition(this->getPosition() + (Velocity / 60.0));
		if(intersectsPaddle(Paddle1, PreviousPosition, this->getPosition()))
		{
			setVelocity(Velocity * -1);
			State = PLAY_P2;
		}
		break;
	}
	case PLAY_P2:
	{
		this->setPosition(this->getPosition() + (Velocity / 60.0));
		if(intersectsPaddle(Paddle2, PreviousPosition, this->getPosition()))
		{
			setVelocity(Velocity * -1);
			State = PLAY_P1;
		}
		break;
	}
	default:
	{
		break;
	}
	}
}

void test::Ball::setVelocity(osg::Vec3d const& velocity)
{
	Velocity = velocity;
	Velocity.normalize();
	VelocityNormal = Velocity;
	Velocity *= BALL_SPEED;
}

void test::Ball::setPosition(osg::Vec3d const& position)
{
	PreviousPosition = this->getPosition();;
	Trans->setPosition(position);
}

void test::Ball::paddleMoved(Paddle * paddle, osg::Vec3d const& prevPos, osg::Vec3d const& currPos)
{
//	PaddleMovementData pmd(paddle, prevPos, currPos);
//	ScopedLock lock(&Mtx);
//	PaddleMovements.push_back(pmd);
	handlePaddleMoved(paddle, prevPos, currPos);
}

void test::Ball::handlePaddleMoved(Paddle * paddle, osg::Vec3d const& prevPos, osg::Vec3d const& currPos)
{
	if(getActivePaddle() == paddle)
	{
		osg::Vec3d istart = this->getPosition();
		osg::Vec3d iend = istart + (currPos - prevPos);
		if(intersectsPaddle(paddle, istart, iend))
		{
			setVelocity(currPos - prevPos);
			State = (State / 100) == 1 ? PLAY_P2 : PLAY_P1;
		}
	}
}

test::Paddle * test::Ball::getActivePaddle() const
{
	return (State/100 == 1 ? Paddle1 : Paddle2);
}

void test::Ball::setPaddle1(test::Paddle * paddle1)
{
	if(Paddle1)
	{
		Paddle1->removePaddleListener(this);
	}

	Paddle1 = paddle1;
	Paddle1->addPaddleListener(this);
}

void test::Ball::setPaddle2(test::Paddle * paddle2)
{
	if(Paddle2)
	{
		Paddle2->removePaddleListener(this);
	}

	Paddle2 = paddle2;
	Paddle2->addPaddleListener(this);
}

