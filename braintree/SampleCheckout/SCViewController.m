//
//  SCViewController.m
//  SampleCheckout
//
//  Created by kortina on 3/28/13.
//  Copyright (c) 2013 Braintree. All rights reserved.
//

#import "SCViewController.h"

@interface SCViewController ()

@end

@implementation SCViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    [self addPayButton];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark PayButton
- (void) addPayButton {
    UIButton *payButton = [UIButton buttonWithType:UIButtonTypeRoundedRect];
    [payButton setTitle:@"Pay" forState:UIControlStateNormal];
    [payButton setEnabled:YES];
    [payButton setUserInteractionEnabled:YES];
    [payButton addTarget: self
                  action: @selector(payButtonTapped:)
        forControlEvents: UIControlEventTouchDown];
    payButton.frame = CGRectMake(100.0, 100.0, 120.0, 50.0);
    [self.view addSubview:payButton];
}
- (void)payButtonTapped:(UIButton*)button {
    NSLog(@"payButtonTapped");
    
    self.paymentViewController =
    [BTPaymentViewController paymentViewControllerWithVenmoTouchEnabled:YES];
    self.paymentViewController.delegate = self;
    
    // Add paymentViewController to a navigation controller.
    UINavigationController *paymentNavigationController =
    [[UINavigationController alloc] initWithRootViewController:self.paymentViewController];
    self.paymentViewController.navigationItem.leftBarButtonItem =
    [[UIBarButtonItem alloc]
     initWithBarButtonSystemItem:UIBarButtonSystemItemCancel target:paymentNavigationController
     action:@selector(dismissModalViewControllerAnimated:)]; // add the cancel button
    
    [self presentModalViewController:paymentNavigationController animated:YES];
    
}

#pragma mark BTPaymentViewControllerDelegate

- (void)paymentViewController:(BTPaymentViewController *)paymentViewController
        didSubmitCardWithInfo:(NSDictionary *)cardInfo
         andCardInfoEncrypted:(NSDictionary *)cardInfoEncrypted {
    NSLog(@"didSubmitCardWithInfo %@ andCardInfoEncrypted %@", cardInfo, cardInfoEncrypted);
}

- (void)paymentViewController:(BTPaymentViewController *)paymentViewController
didAuthorizeCardWithPaymentMethodCode:(NSString *)paymentMethodCode {
    NSLog(@"didAuthorizeCardWithPaymentMethodCode %@", paymentMethodCode);
}

@end
