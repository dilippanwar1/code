//
//  main.m
//  HelloObjectiveC
//
//  Created by deyuan on 5/4/14.
//  Copyright (c) 2014 Deyuan. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Car.h"
#import "Bicycle.h"

int main(int argc, const char * argv[])
{
    @autoreleasepool {
        Car *toyota = [[Car alloc] init];

        [toyota setModel:@"Toyota Cool"];
        NSLog(@"Created a %@", [toyota model]);
        
        toyota.model = @"Toyota Wooo";
        NSLog(@"Changed to %@", toyota.model);
        
        Car *delorean = [[Car alloc] initWithModel:@"Delorean"];
        
        NSLog(@"%@ is an instance of the %@ class",
              [delorean model], [delorean class]);
        
        // Check an object against a class and all subclasses
        if ([delorean isKindOfClass:[NSObject class]]) {
            NSLog(@"%@ is an instance of NSObject or one "
                  "of its subclasses",
                  [delorean model]);
        } else {
            NSLog(@"%@ is not an instance of NSObject or "
                  "one of its subclasses",
                  [delorean model]);
        }

        // Check an object against a class, but not its subclasses
        if ([delorean isMemberOfClass:[NSObject class]]) {
            NSLog(@"%@ is a instance of NSObject",
                  [delorean model]);
        } else {
            NSLog(@"%@ is not an instance of NSObject",
                  [delorean model]);
        }
        
        // Convert between strings and classes
        if (NSClassFromString(@"Car") == [Car class]) {
            NSLog(@"I can convert between strings and classes!");
        }
        
        Car *honda = [[Car alloc] init];
        NSLog(@"%d", honda.running);        // [honda running]
        [honda startEngine];
        NSLog(@"%d", honda.isRunning);        // [honda running]
        
        [honda driveFromOrigin:@"CTU" toDestination:@"LAX"];
        
        Car *honda2 = [[Car alloc] init];
        NSMutableString *model = [NSMutableString stringWithString:@"Honda Civic"];
        honda2.model = model;
        
        NSLog(@"%@", honda2.model);
        [model setString:@"Nissa Versa"];
        NSLog(@"%@", honda2.model);            // Still "Honda Civic"
        
        Car *porsche = [[Car alloc] init];
        porsche.model = @"Porsche 911 Carrera";

        /*
        SEL stepOne = NSSelectorFromString(@"startEngine");
        SEL stepTwo = @selector(driveForDistance:);
        SEL stepThree = @selector(turnByAngle:quickly:);

        // This is the same as:
        // [porsche startEngine];
        [porsche performSelector:stepOne];
        
        // This is the same as:
        // [porsche driveForDistance:[NSNumber numberWithDouble:5.7]];
        [porsche performSelector:stepTwo
                      withObject:[NSNumber numberWithDouble:5.7]];
        
        if ([porsche respondsToSelector:stepThree]) {
            // This is the same as:
            // [porsche turnByAngle:[NSNumber numberWithDouble:90.0]
            //              quickly:[NSNumber numberWithBool:YES]];
            [porsche performSelector:stepThree
                          withObject:[NSNumber numberWithDouble:90.0]
                          withObject:[NSNumber numberWithBool:YES]];
        }
        NSLog(@"Step one: %@", NSStringFromSelector(stepOne));
        */
        
        Bicycle *bike = [[Bicycle alloc] init];
        [bike startPedaling];
        [bike signalLeftTurn];
        [bike signalStop];
        [bike lockToStructure:nil];
        
        id <StreetLegal> mysteryVehicle = [[Car alloc] init];
        [mysteryVehicle signalLeftTurn];
        
        mysteryVehicle = [[Bicycle alloc] init];
        [mysteryVehicle signalLeftTurn];

        if ([mysteryVehicle conformsToProtocol:@protocol(StreetLegal)]) {
            [mysteryVehicle signalStop];
            [mysteryVehicle signalLeftTurn];
            [mysteryVehicle signalRightTurn];
        }
    }
    return 0;
}

