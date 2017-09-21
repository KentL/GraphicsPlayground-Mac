//
//  Renderable.hpp
//  GraphicsPlayground-Mac
//
//  Created by Kent Li on 2017-05-03.
//  Copyright © 2017 Kent Li. All rights reserved.
//

#ifndef Renderable_hpp
#define Renderable_hpp

#include <stdio.h>
#include "stdafx.h"
#include "RenderTarget.h"
class Renderable{
public:
    virtual void Render(RenderTarget* target) = 0;
    virtual void SetCamera(Camera* camera) = 0;
    virtual void SetClipPanel(vec4 clipPanel){};
};
#endif /* Renderable_hpp */
