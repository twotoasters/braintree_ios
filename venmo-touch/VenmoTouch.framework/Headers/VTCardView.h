/*
 * Venmo SDK
 *
 ******************************
 * VTCardView.h
 ******************************
 *
 * This view allows you to suggest existing payment methods to your users, so they don't have to
 * type in their card details. You can style it and set its origin & bounds by using the public
 * methods provided below.
 *
 * There is no VTCardViewDelegate. This is just a view that you should add to your payment
 * entry form. All delegate callbacks are handled through the delegate of your VTClient.
 *
 * Custom public methods on VTCardView are just for styling.
 *
 * You must use [touchClient touchCardView] to alloc and init a VTCardView.
 * Do NOT create a VTCardView with [[VTCardView alloc] init]
 *
 * The default size of a VTCardView is 300 width x 80 height. The height can not be changed,
 * but the width can be set to any value greater than or equal to 280.
 */

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface VTCardView : UIView

// UI customization on the "Use Card" button
@property (strong, nonatomic) UIColor *useCardButtonBackgroundColor;
@property (strong, nonatomic) UIColor *useCardButtonTitleColor;
@property (strong, nonatomic) UIColor *useCardButtonTitleShadowColor;
@property (strong, nonatomic) UIFont  *useCardButtonTitleFont;
@property (strong, nonatomic) UIColor *useCardButtonBorderColor;
@property (strong, nonatomic) UIColor *useCardButtonBorderShadowColor;

// Convenience method to set the width of the touch card view.
// Width must be >= 280
- (void)setWidth:(CGFloat)newWidth;

// Convenience method to set the origin of the touch card view.
- (void)setOrigin:(CGPoint)origin;

// Convenience method to set the corner radius of the "Use Card" button.
// Corner radius must be non-negative and no greater than 15 pixels. 0 <= newCornerRadius <= 15
// Default is 5 pixels.
- (void)setCornerRadius:(CGFloat)newCornerRadius;

@end
