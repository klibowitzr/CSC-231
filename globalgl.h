//
//  globalgl.hpp
//  Navy Simulator
//
//  Created by Rachel klibowitz on 4/30/18.
//  Copyright © 2018 Rachel klibowitz. All rights reserved.
//

//#ifndef globalgl_hpp
//#define globalgl_hpp
//
//#include <stdio.h>
//
//#endif /* globalgl_hpp */
#if defined(WIN32)
#include <windows.h>
#endif

#if defined(__APPLE__)
#include <OpenGl/gl.h>
#include <OpenGl/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

