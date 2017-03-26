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

class ExampleBase{
public:
    virtual void Initialize()=0;
    virtual void Render()=0;
    virtual void HandleKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods)=0;
};
#endif /* ExampleBase_hpp */