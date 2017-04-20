//
//  KeyboardInputHandler.h
//  GraphicsPlayground-Mac
//
//  Created by Kent Li on 2017-03-26.
//  Copyright © 2017 Kent Li. All rights reserved.
//

#ifndef KeyboardInputHandler_h
#define KeyboardInputHandler_h

class KeyboardInputHandler {
    
public:
    virtual void HandleKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods) = 0;

};

#endif /* KeyboardInputHandler_h */
