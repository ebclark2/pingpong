#include "Table.hpp"

test::Table::Table()
{
	//9ft x 5ft table
	//1.0 = 9ft
	//1/9 = 1ft
	//1/9/6 = 2inches
	osg::Box *box = new osg::Box(osg::Vec3(0, 0, 0), 5.0f, 1.0f/6.0f, 9.0f);
	osg::ShapeDrawable *boxd = new osg::ShapeDrawable(box);
	osg::Geode *geode = new osg::Geode();
	geode->addDrawable(boxd);
	osg::Vec3d pos(0,0,0);
	this->addChild(geode);
}
