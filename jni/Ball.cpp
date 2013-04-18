#include "Ball.hpp"

#include <osg/Material>
#include <osg/Shape>
#include <osg/ShapeDrawable>

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
	this->addChild(geode);
}

void test::Ball::accept(osg::NodeVisitor & visitor)
{
	if(visitor.getVisitorType() == osg::NodeVisitor::UPDATE_VISITOR)
	{
		this->update();
	}
	osg::PositionAttitudeTransform::accept(visitor);
}

void test::Ball::update()
{
	switch(State)
	{
	case SERVE_P1:
	{
		osg::Vec3d p = Paddle1->getPosition();
		p.z() = 7.5 + ((1.0/12.0)*3.0);
		this->setPosition(p);
		break;
	}
	case PLAY_P2:
	{
		this->setPosition(this->getPosition() + (Velocity / 60.0));
		break;
	}
	default:
		break;
	}
}

void test::Ball::paddleMoved(Paddle * paddle, osg::Vec3d const& prevPos, osg::Vec3d const& currPos, osg::BoundingBox const& boundingBox)
{
	if(getActivePaddle() == paddle)
	{
		if(boundingBox.contains(this->getPosition()))
		{
			Velocity = currPos - prevPos;
			Velocity.normalize();

			if(State % 100 == 0)
			{
				State == (State / 100) == 1 ? PLAY_P2 : PLAY_P1;
			}
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

