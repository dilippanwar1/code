//
//  Bicycle.h
//  HelloObjectiveC
//
//  Created by deyuan on 5/5/14.
//  Copyright (c) 2014 Deyuan. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "StreetLegal.h"

@interface Bicycle : NSObject <StreetLegal>

- (void)startPedaling;
- (void)removeFrontWheel;
- (void)lockToStructure:(id)theStructure;

@end

