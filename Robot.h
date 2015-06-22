//
// Created by deva on 20/06/15.
//

#ifndef PIXAR_ROBOT_H
#define PIXAR_ROBOT_H

#include <vector>
#include <math.h>
#include <stdint.h>

namespace Roboto {
#define Rad2Deg     180/M_PI
#define Deg2Rad     M_PI/180
#define NumAngles   360

    typedef std::vector< double > Vector;
    typedef Vector Position;
    // Joint angles in degrees
    typedef std::vector< int > Angles;
    typedef Vector Links; // Links
    typedef std::vector< std::pair< int, int > > JntLims; // Pair's of Joint Lims

    class Robot
    {
      public:
	    Robot( int m_nlinks, int m_ndof );

	    Robot();

	    virtual ~Robot();

      protected:
	    int m_nlinks;
	    int m_ndof;
	    Angles m_theta;
	    Position m_pos;
	    Links m_links;
	    JntLims m_jnt_lims;
      protected:
	    virtual void init() = 0;

	    virtual void SetAngles( const Angles &t ) = 0;

	    virtual Angles GetAngles() = 0;

	    virtual void SetPosition( const Position &p ) = 0;

	    virtual Position GetPosition() = 0;
    };

    Vector Cos( NumAngles );
    Vector Sin( NumAngles );
}

#endif //PIXAR_ROBOT_H
