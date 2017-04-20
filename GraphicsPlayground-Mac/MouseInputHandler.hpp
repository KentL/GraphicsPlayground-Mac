//
//  MouseInputHandler.hpp
//  GraphicsPlayground-Mac
//
//  Created by Kent Li on 2017-03-26.
//  Copyright © 2017 Kent Li. All rights reserved.
//

#ifndef MouseInputHandler_h
#define MouseInputHandler_h

class MouseInputHandler {
    
public:
    virtual void HandleCursorPositionChange(GLFWwindow* window, double newXPos, double newYPos) = 0;
    
};
#endif /* MouseInputHandler_h */
