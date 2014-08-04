//
//  Car.h
//  HelloObjectiveC
//
//  Created by deyuan on 5/4/14.
//  Copyright (c) 2014 Deyuan. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "StreetLegal.h"

@interface Car : NSObject <StreetLegal> {
    // Protected instance variables (not recommended)
}

@property (copy, nonatomic)  NSString *model;

@property (getter=isRunning, readonly) BOOL running;

+ (void)setDefaultModel:(NSString *)aModel;

- (id)initWithModel:(NSString *)aModel;

- (void)drive;

- (void)driveFromOrigin:(id)theOrigin toDestination:(id)theDestination;

- (void)startEngine;

- (void)stopEngine;

- (void)driveForDistance:(NSNumber *)theDistance;

- (void)turnByAngle:(NSNumber *)theAngle
            quickly:(NSNumber *)useParkingBrake;

@end
