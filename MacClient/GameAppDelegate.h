//
//  GameAppDelegate.h
//  Game
//
//  Created by Viktor Zhuravel on 12/2/09.
//  Copyright 2009 Kring. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface GameAppDelegate : NSObject <NSApplicationDelegate> {
    NSWindow *window;
}

@property (assign) IBOutlet NSWindow *window;

@end
