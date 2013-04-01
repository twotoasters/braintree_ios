# Accept Credit Cards and Venmo Touch Using BTPaymentViewController, iOS Tutorial

Presenting `BTPaymentViewController` is the easiest way to add payments to your iOS app: if a user has cards saved with Venmo Touch, `BTPaymentViewController` shows a Use Card Button that allows the user to give you that card information with a single tap.  It also contains a `BTPaymentForm` that allows a user to type in credit card information, performs client side validation on that information, and then uses Client Side Encryption, allowing you to pass the information in a secure, PCI Compliant method through your own servers to the Braintree Gateway, so you can save the card and run transactions against it.

## Outline

* Add `braintree-ios` to your Xcode Project
* Configure your Braintree merchant settings
* Present `BTPaymentViewController`
* Handle `BTPaymentViewController` responses
    * New card added manually
    * New card added via Venmo Touch
    * `BTPaymentViewController` is dismissed without adding a card
* Server Side Integration


## Add `braintree-ios` to your Xcode Project

1. Add `braintree-ios` as a submodule in your project, and then drag the `braintree-ios` folder into your project Navigator in Xcode. Ensure "Copy items into destination group's folder" is checked. *Do not check* any of the Targets in the "Add to targets section" -- we'll configure this manually next. [Screenshot](https://github.com/venmo/braintree-ios/blob/master/braintree/docs/assets/xcode-add-braintree-ios-to-project.png)
1. In your App Target's "Build Phases":
    1. In "Compile Sources" add add all of the files from `BTPayment` [Screenshot]([https://github.com/venmo/braintree-ios/blob/master/braintree/docs/assets/xcode-compile-sources-add-BTPayment.png)
    1. In "Copy Bundle Resources" add `BraintreeResources.bundle` and `VenmoTouchResources.bundle` by dragging them into this section from the Project Navigator on the left [Screenshot](https://github.com/venmo/braintree-ios/blob/master/braintree/docs/assets/xcode-add-BraintreeResources-and-VenmoTouchResrouces-bundles.png)
    1. In "Link Binary With Libraries" add `VenmoTouch.framework` by dragging it from the Project Navigator on the left [Screenshot](https://github.com/venmo/braintree-ios/blob/master/braintree/docs/assets/xcode-add-VenmoTouch-framework.png)
    1. Also in "Link Binary With Libraries" *make sure to add*: [Screenshot](https://github.com/venmo/braintree-ios/blob/master/braintree/docs/assets/xcode-add-other-frameorks-in-link-binary-with-libraries.png)
        * `Security.framework`
        * `QuartzCore.framework`
        * `CoreGraphics.framework`
        * `UIKit.framework`
        * `Foundation.framework`
1. Add the same files in the same way to your App Tests Target.


## Configure your Braintree merchant settings

In `venmo-touch`&gt; `VenmoTouch.framework` &gt; `Headers` &gt; `VenmoTouchSettings.h`, define `BT_SANDBOX_MERCHANT_ID`, `BT_SANDBOX_CLIENT_SIDE_ENCRYPTION_KEY`, `BT_PRODUCTION_MERCHANT_ID`, and `BT_PRODUCTION_CLIENT_SIDE_ENCRYPTION_KEY`. These can be obtained from your merchant dasbhoard at https://www.braintreegateway.com

For testing,

    #define BT_ENVIRONMENT @"sandbox"

*NB!* Remember to change this to `@"production"` when you are finished testing and want to release your app.

## Present `BTPaymentViewController`

First, in your App Delegate, import the `VenmoTouch` headers and create a `initVTClient` method.  Make sure you call this method by adding `[self initVTClient];` to your `application didFinishLaunchingWithOptions` method.
    

    #import <VenmoTouch/VenmoTouch.h> // Don't forget to import VenmoTouch
    @implementation YourAppDelegate
    // ...
    - (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
    {
        // other code...
        [self initVTClient];
        // other code...
    }
    #pragma mark VenmoTouch
    // Initialize a VTClient with your correct merchant settings.
    // Don't forget to add some logic to toggle whether you are using Sandbox or Production merchant settings.
    - (void) initVTClient {
        if ([BT_ENVIRONMENT isEqualToString:@"sandbox"]) {
            NSLog(@"sanbox environment, merchant_id %@", BT_SANDBOX_MERCHANT_ID);
            [[VTClient alloc] initWithMerchantID:BT_SANDBOX_MERCHANT_ID
                    braintreePublicEncryptionKey:BT_SANDBOX_CLIENT_SIDE_ENCRYPTION_KEY
                                     environment:VTEnvironmentSandbox]; // init sharedClient
        } else {
            NSLog(@"production environment, merchant_id %@", BT_PRODUCTION_MERCHANT_ID);
            [[VTClient alloc] initWithMerchantID:BT_PRODUCTION_MERCHANT_ID
                    braintreePublicEncryptionKey:BT_PRODUCTION_CLIENT_SIDE_ENCRYPTION_KEY
                                     environment:VTEnvironmentProduction]; // init sharedClient
        }
    }

Next, import `BTPaymentViewController.h` in your ViewController header file, implement the `BTPaymentViewControllerDelegate` protocol, and add a property that references the `BTPaymentViewController`:

    #import "BTPaymentViewController.h" // Don't forget this!

    @interface SCViewController : UIViewController <BTPaymentViewControllerDelegate> // Implement the BTPaymentViewControllerDelegate protocol

    @property (strong, nonatomic) BTPaymentViewController *paymentViewController; // Create a property to reference the BTPaymentViewController we display
    //...

Then, create and present a `BTPaymentViewController` to collect a user's credit card information. This sample code shows how to create a Pay button that will display a `BTPaymentViewController`:

<pre><code>
#pragma mark PayButton
// add a PayButton that will present a BTPaymentViewController when tapped
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

// create and present a BTPaymentViewController (that has a cancel button)
- (void)payButtonTapped:(UIButton*)button {
    NSLog(@"payButtonTapped");
    self.paymentViewController = [BTPaymentViewController paymentViewControllerWithVenmoTouchEnabled:YES];
    // Tell the paymentViewController to notify this ViewController by calling it's BTPaymentViewControllerDelegate methods
    self.paymentViewController.delegate = self;
    
    // Add paymentViewController to a navigation controller.
    UINavigationController *paymentNavigationController =
    [[UINavigationController alloc] initWithRootViewController:self.paymentViewController];
    self.paymentViewController.navigationItem.leftBarButtonItem =
    [[UIBarButtonItem alloc]
     initWithBarButtonSystemItem:UIBarButtonSystemItemCancel target:paymentNavigationController
     action:@selector(dismissModalViewControllerAnimated:)]; // add the cancel button
    
    [self presentViewController:paymentNavigationController animated:YES completion:nil];
}
</code></pre>


## Handle `BTPaymentViewController` responses

The `BTPaymentViewController` sends your app card info via the `BTPaymentViewControllerDelegate` methods.  The following example code demonstrates how to receive this card info and pass it through your server to the Braintree Gateway. For detailed information and sample server code, refer to *braintree-ios Server Side Integration Tutorial* { link }

The following example code demonstrates how to handle both cards added via Venmo Touch and as well as cards typed manually into the `BTPaymentForm` and encrypted with Client Side Encryption for PCI Compliance.

<pre><code>
#pragma mark BTPaymentViewControllerDelegate

// When a user types in their credit card information correctly, the BTPaymentViewController sends you
// card details via the `didSubmitCardWithInfo` delegate method.
//
// NB: you receive raw, unencrypted info in the `cardInfo` dictionary, but
// for easy PCI Compliance, you should use the `cardInfoEncrypted` dictionary
// to securely pass data through your servers to the Braintree Gateway.
- (void)paymentViewController:(BTPaymentViewController *)paymentViewController
        didSubmitCardWithInfo:(NSDictionary *)cardInfo
         andCardInfoEncrypted:(NSDictionary *)cardInfoEncrypted {
    NSLog(@"didSubmitCardWithInfo %@ andCardInfoEncrypted %@", cardInfo, cardInfoEncrypted);
    [self savePaymentInfoToServer:cardInfoEncrypted]; // send card through your server to Braintree Gateway
}

// When a user adds a saved card from Venmo Touch to your app, the BTPaymentViewController sends you
// a paymentMethodCode that you can pass through your servers to the Braintree Gateway to
// add the full card details to your Vault.
- (void)paymentViewController:(BTPaymentViewController *)paymentViewController
didAuthorizeCardWithPaymentMethodCode:(NSString *)paymentMethodCode {
    NSLog(@"didAuthorizeCardWithPaymentMethodCode %@", paymentMethodCode);
    // Create a dictionary of POST data of the format
    // {"payment_method_code": "[encrypted payment_method_code data from Venmo Touch client]"}
    NSMutableDictionary *paymentInfo = [NSMutableDictionary dictionaryWithObject:paymentMethodCode
                                                            forKey:@"venmo_sdk_payment_method_code"];
    [self savePaymentInfoToServer:paymentInfo]; // send card through your server to Braintree Gateway
}

#pragma mark - networking

// The following example code demonstrates how to pass encrypted card data through your server
// to the Braintree Gateway. For a fully working example of how to proxy data through your server
// to the Braintree Gateway, see
// the braintree-ios Server Side Integration tutorial [link]
// and the sample-checkout-heroku Github project [link]

//#define SAMPLE_CHECKOUT_BASE_URL @"http://sample-checkout.herokuapp.com"
#define SAMPLE_CHECKOUT_BASE_URL @"http://localhost:5000"

// Pass card data through your server to Braintree Gateway.
// If card data is valid and added to your Vault, display a success message, and dismiss the BTPaymentViewController.
// If saving to your Vault fails, display an error message to the user via `BTPaymentViewController showErrorWithTitle`
// Saving to your Vault may fail, for example when
// * CVV verification does not pass
// * AVS verification does not pass
// * The card number was a valid Luhn number, but nonexistent or no longer valid
- (void) savePaymentInfoToServer:(NSDictionary *)paymentInfo {
    NSURL *url = [NSURL URLWithString: [NSString stringWithFormat:@"%@/card", SAMPLE_CHECKOUT_BASE_URL]];
    NSMutableURLRequest *request = [[NSMutableURLRequest alloc] initWithURL:url];
    
    // You need a customer id in order to save a card to the vault.
    // Here, for the sake of example, we set customer_id to device id.
    // In practice, this is probably whatever user_id your app has assigned to this user.
    NSString *customerId = [[UIDevice currentDevice] identifierForVendor].UUIDString;
    [paymentInfo setValue:customerId forKey:@"customer_id"];
    
    request.HTTPBody = [self postDataFromDictionary:paymentInfo];
    request.HTTPMethod = @"POST";
    
    [NSURLConnection sendAsynchronousRequest:request
                                       queue:[NSOperationQueue mainQueue]
                           completionHandler:^(NSURLResponse *response, NSData *body, NSError *requestError)
     {
         NSError *err = nil;
         NSDictionary *responseDictionary = [NSJSONSerialization JSONObjectWithData:body options:kNilOptions error:&err];
         NSLog(@"saveCardToServer: paymentInfo: %@ response: %@, error: %@", paymentInfo, responseDictionary, requestError);
         
         if ([[responseDictionary valueForKey:@"success"] isEqualToNumber:@1]) { // Success!
             // Don't forget to call the cleanup method,
             // `prepareForDismissal`, on your `BTPaymentViewController`
             [self.paymentViewController prepareForDismissal];
             // Now you can dismiss and tell the user everything worked.
             [self dismissViewControllerAnimated:YES completion:^(void) {
                 [[[UIAlertView alloc] initWithTitle:@"Success" message:@"Saved your card!" delegate:nil
                                   cancelButtonTitle:@"OK" otherButtonTitles:nil] show];
                 
             }];
             
         } else { // The card did not save correctly, so show the error from server with convenenience method `showErrorWithTitle`
             [self.paymentViewController showErrorWithTitle:@"Error saving your card" message:[self messageStringFromResponse:responseDictionary]];
         }
     }];
}

// Some boiler plate networking code below.

- (NSString *) messageStringFromResponse:(NSDictionary *)responseDictionary {
    return [responseDictionary valueForKey:@"message"];
}

// Construct URL encoded POST data from a dictionary
- (NSData *)postDataFromDictionary:(NSDictionary *)params {
    NSMutableString *data = [NSMutableString string];
    
    for (NSString *key in params) {
        NSString *value = [params objectForKey:key];
        if (value == nil) {
            continue;
        }
        if ([value isKindOfClass:[NSString class]]) {
            value = [self URLEncodedStringFromString:value];
        }
        
        [data appendFormat:@"%@=%@&", [self URLEncodedStringFromString:key], value];
    }
    
    return [data dataUsingEncoding:NSUTF8StringEncoding];
}

// This method is adapted from from Dave DeLong's example at
// http://stackoverflow.com/questions/3423545/objective-c-iphone-percent-encode-a-string ,
// and protected by http://creativecommons.org/licenses/by-sa/3.0/
- (NSString *) URLEncodedStringFromString: (NSString *)string {
    NSMutableString * output = [NSMutableString string];
    const unsigned char * source = (const unsigned char *)[string UTF8String];
    int sourceLen = strlen((const char *)source);
    for (int i = 0; i < sourceLen; ++i) {
        const unsigned char thisChar = source[i];
        if (thisChar == ' '){
            [output appendString:@"+"];
        } else if (thisChar == '.' || thisChar == '-' || thisChar == '_' || thisChar == '~' ||
                   (thisChar >= 'a' && thisChar <= 'z') ||
                   (thisChar >= 'A' && thisChar <= 'Z') ||
                   (thisChar >= '0' && thisChar <= '9')) {
            [output appendFormat:@"%c", thisChar];
        } else {
            [output appendFormat:@"%%%02X", thisChar];
        }
    }
    return output;
}
</code></pre>


## Server Side Integration

Run the following sample server locally to test this out: https://github.com/venmo/sample-checkout-heroku
