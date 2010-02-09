//
//  iPhoneGameAppDelegate.m
//  iPhoneGame
//
//  Created by svp on 09.02.10.
//  Copyright __MyCompanyName__ 2010. All rights reserved.
//

#import "iPhoneGameAppDelegate.h"
#import "EAGLView.h"

@implementation iPhoneGameAppDelegate

@synthesize window;
@synthesize glView;

- (void) applicationDidFinishLaunching:(UIApplication *)application
{
//	test();
	[glView startAnimation];
}

- (void) applicationWillResignActive:(UIApplication *)application
{
	[glView stopAnimation];
}

- (void) applicationDidBecomeActive:(UIApplication *)application
{
	[glView startAnimation];
}

- (void)applicationWillTerminate:(UIApplication *)application
{
	[glView stopAnimation];
}

- (void) dealloc
{
	[window release];
	[glView release];
	
	[super dealloc];
}

@end
