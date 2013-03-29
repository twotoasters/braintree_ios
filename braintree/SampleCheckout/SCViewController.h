//
//  SCViewController.h
//  SampleCheckout
//
//  Created by kortina on 3/28/13.
//  Copyright (c) 2013 Braintree. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "BTPaymentViewController.h"

@interface SCViewController : UIViewController <BTPaymentViewControllerDelegate>

@property (strong, nonatomic) BTPaymentViewController *paymentViewController;

@end
