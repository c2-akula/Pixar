//
// Created by deva on 20/06/15.
//

#include "Robot.h"

using namespace std;
using namespace Roboto;

void Robot::init()
{
	m_jnt_lims = JntLims( m_ndof );
	m_links = Links( m_ndof );
	m_pos = Position( 3 );
	m_theta = Angles( m_ndof );

//	we initialize the sine and cosine lookup
//	table, in order to optimize performance
	for ( int i = 0; i < NumAngles; ++i )
	{
		Cos[i] = cos( i * Deg2Rad );
		Sin[i] = sin( i * Deg2Rad );
	}
}


Robot::~Robot()
{ }

Robot::Robot( int m_nlinks, int m_ndof ) : m_nlinks( m_nlinks ), m_ndof( m_ndof )
{
	init();
}

Robot::Robot()
{ }
