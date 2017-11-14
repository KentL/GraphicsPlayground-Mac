//
//  Quad.hpp
//  GraphicsPlayground-Mac
//
//  Created by Kent Li on 2017-04-30.
//  Copyright © 2017 Kent Li. All rights reserved.
//

#ifndef Quad_hpp
#define Quad_hpp

#include <stdio.h>
#include "stdafx.h"
#include "Node.h"

namespace Geometry {
    class Quad: public Node{
    public:
        vec3* GetVertex();
    protected:
        vec3 VertexArray[4] ={
            vec3(-0.5,0,0.5),
            vec3(0.5,0,0.5),
            vec3(0.5,0,-0.5),
            vec3(-0.5,0,-0.5)
        };
    };
}

#endif /* Quad_hpp */
