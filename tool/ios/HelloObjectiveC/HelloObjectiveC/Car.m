//
//  Car.m
//  HelloObjectiveC
//
//  Created by deyuan on 5/4/14.
//  Copyright (c) 2014 Deyuan. All rights reserved.
//

#import "Car.h"

static NSString *_defaultModel;

@implementation Car {
    // Private instance variables.
    double _odometer;
}

+ (void)initialize {
    if (self == [Car class]) {
        // Makes sure this isn't executed more than once
        _defaultModel = @"Nissan Versa";
    }
}

+ (void)setDefaultModel:(NSString *)aModel {
    _defaultModel = [aModel copy];
}

- (id)init {
    // Forward to the "designated" initialization method
    NSLog(@"Call init method.");
    return [self initWithModel:_defaultModel];
}

- (id)initWithModel:(NSString *)aModel {
    self = [super init];
    NSLog(@"Call initWithModel method.");
    if (self) {
        // Any custom setup work goes here
        _model = [aModel copy];
        _odometer = 0;
    }
    return self;
}

- (void)drive {
    NSLog(@"Driving a %@. Vrooooom!", self.model);
}

- (void)driveFromOrigin:(id)theOrigin toDestination:(id)theDestination {
    NSLog(@"Driving from %@ to %@.", theOrigin, theDestination);
}

- (void)startEngine {
    _running = YES;
}

- (void)stopEngine {
    _running = NO;
}

- (void)driveForDistance:(NSNumber *)theDistance {
    NSLog(@"The %@ just drove %0.1f miles",
          _model, [theDistance doubleValue]);
}

- (void)turnByAngle:(NSNumber *)theAngle
            quickly:(NSNumber *)useParkingBrake {
    if ([useParkingBrake boolValue]) {
        NSLog(@"The %@ is drifting around the corner!", _model);
    } else {
        NSLog(@"The %@ is making a gentle %0.1f degree turn",
              _model, [theAngle doubleValue]);
    }
}

- (void)signalStop {
    NSLog(@"Bending left arm downwards");
}

- (void)signalLeftTurn {
    NSLog(@"Extending left arm outwards");
}

- (void)signalRightTurn {
    NSLog(@"Bending left arm upwards");
}

@end
