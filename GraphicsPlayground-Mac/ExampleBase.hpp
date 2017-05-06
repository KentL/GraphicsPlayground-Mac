//
//  ExampleBase.hpp
//  GraphicsPlayground-Mac
//
//  Created by Kent Li on 2017-03-26.
//  Copyright © 2017 Kent Li. All rights reserved.
//

#ifndef ExampleBase_hpp
#define ExampleBase_hpp

#include <stdio.h>
#include "stdafx.h"

class ExampleBase{
public:
    virtual void Initialize()=0;
    virtual void Render()=0;
    virtual void HandleKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods)=0;
    virtual void HandleCursorPositionChange(GLFWwindow* window, double newXPos, double newYPos) = 0;
};
#endif /* ExampleBase_hpp */
