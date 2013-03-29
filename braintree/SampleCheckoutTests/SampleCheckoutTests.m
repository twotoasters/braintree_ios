//
//  SampleCheckoutTests.m
//  SampleCheckoutTests
//
//  Created by kortina on 3/28/13.
//  Copyright (c) 2013 Braintree. All rights reserved.
//

#import "SampleCheckoutTests.h"
#import <VenmoTouch/VenmoTouchSettings.h>

@implementation SampleCheckoutTests

- (void)setUp
{
    [super setUp];
    
    // Set-up code here.
}

- (void)tearDown
{
    // Tear-down code here.
    
    [super tearDown];
}

- (void)testExample
{
    NSLog(@"BT_MERCHANT_ID: %@", BT_MERCHANT_ID);
    NSLog(@"BT_PUBLIC_ENCRYPTION_KEY: %@", BT_PUBLIC_ENCRYPTION_KEY);
    NSLog(@"BT_ENVIRONMENT: %@", BT_ENVIRONMENT);
    
    STAssertEqualObjects(BT_ENVIRONMENT, @"sandbox", @"Environment should be sandbox");
}

@end
